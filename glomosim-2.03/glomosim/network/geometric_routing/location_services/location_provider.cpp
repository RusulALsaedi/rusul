#include "location_provider.hpp"

#include <cassert>
#include <sstream>
#include <stdlib.h>
#include <string>


using std::unordered_map;
using std::ifstream;
using std::istringstream;
using std::string;

LocationProvider* LocationProvider::_instance = NULL;
ConfigurationParameters* LocationProvider::_config = NULL;
const Coordinates LocationProvider::npos(-1, -1, -1);

LocationProvider* LocationProvider::instance() {
    if(_instance == NULL) {
        _instance = new LocationProvider(generateHostTable());
    }
    return _instance;
}

void LocationProvider::addHostsFromTrace(HostTable* host_table, ifstream& trace) {
    string line, str_time, str_x, str_y, str_z;
    NODE_ADDR address;
    clocktype time;
    double x, y, z;
    istringstream str_stream;
    std::getline(trace, line);
    while(!trace.eof()) {
        if(line != "" && line[0] != '#') {
            // Parse uncommented lines and extract numeric characters
            // Trace file format: 10 100[S] (200.0, 150.0, 0.2)
            str_stream.str(line);
            str_stream >> address >> str_time >> str_x >> str_y >> str_z;
            if(str_time[str_time.size() - 1] == 'S') {
                str_time = str_time.substr(0, str_time.size() - 2);
            }
            str_x = str_x.substr(1, str_x.size() - 2);
            str_y = str_y.substr(0, str_y.size() - 2);
            str_z = str_z.substr(0, str_z.size() - 2);
            time = std::stoul(str_time);
            x = std::stod(str_x);
            y = std::stod(str_y);
            z = std::stod(str_z);
            // Populate hashmap with extracted data
            HostTableKey key = std::make_pair(address, time);
            Coordinates coordinates(x, y, z);
            host_table->insert(std::make_pair(key, coordinates));
            str_stream.str(string());
            str_stream.clear();
        }
        std::getline(trace, line);
    }
}

LocationProvider::HostTable* LocationProvider::generateHostTable() {
    _config = ConfigurationParameters::instance();
    assert("Location Service requires node placement via file."
           && _config->nodePlacementFile() != "");
    HostTable* host_table = new HostTable;
    ifstream trace;
    trace.open(_config->nodePlacementFile().c_str());
    assert("Node placement file failed to open." && !trace.fail());
    addHostsFromTrace(host_table, trace);
    trace.close();
    if(!_config->isStatic()) {
        trace.open(_config->mobilityTraceFile().c_str());
        assert("Mobility trace file failed to open." && !trace.fail());
        addHostsFromTrace(host_table, trace);
        trace.close();
    }
    return host_table;
} // TODO: Replace with exceptions

LocationProvider::LocationProvider(HostTable* host_table)
: _host_table(host_table) {
    atexit(&cleanUp);
}

LocationProvider::~LocationProvider() {
    delete _host_table;
}

void LocationProvider::cleanUp() {
    delete _instance;
    _instance = NULL;
}

Coordinates LocationProvider::getLastKnownLocation(const HostTableKey& key) {
    unordered_map<HostTableKey, Coordinates>::iterator it;
    if(_config->isStatic()) {
        it = _host_table->find(std::make_pair(key.first, 0));
        if(it != _host_table->end()) {
            return it->second;
        }
        else  {
            return npos;
        }
    }
    else  {
        it = _host_table->find(key);
        if(it != _host_table->end()) {
            return it->second;
        }
        else  {
            for(int t = key.second; t >= 0; --t) {
                it = _host_table->find(std::make_pair(key.first, t));
                if(it != _host_table->end()) {
                    return it->second;
                }
            }
            return npos;
        }
    }
}