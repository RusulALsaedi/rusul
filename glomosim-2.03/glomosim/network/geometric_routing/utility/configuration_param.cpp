#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include "configuration_param.hpp"

using std::string;
using std::ifstream;
using std::istringstream;

ConfigurationParameters* ConfigurationParameters::_instance = NULL;

ConfigurationParameters* ConfigurationParameters::instance() {
    if(_instance == NULL) {
        _instance = new ConfigurationParameters();
    }
    return _instance;
}


ConfigurationParameters::ConfigurationParameters()
 : _node_placement_file(""),
   _mobility_trace_file(""),
   _is_static(true),
   _routing_protocol("") {
    
    string node_placement_param(""), mobility_param("");
    ifstream file;
    file.open("config.in");
    assert("Configuration file failed to open." && !file.fail());
    string line, token;
    istringstream str_stream;
    std::getline(file, line);
    while(!file.eof()) {
        // Parse uncommented lines and extract parameters
        if(line != "" && line[0] != '#') {
            str_stream.str(line);
            str_stream >> token;
            if(token == "NODE-PLACEMENT") {
                str_stream >> node_placement_param;
            }
            if(token == "NODE-PLACEMENT-FILE" && node_placement_param == "FILE") {
                str_stream >> _node_placement_file;
            }
            if(token == "MOBILITY") {
                str_stream >> mobility_param;
                if(mobility_param != "NONE") {
                    _is_static = false;
                }
            }
            if(token == "MOBILITY-TRACE-FILE" && mobility_param == "TRACE") {
                str_stream >> _mobility_trace_file;
            }
            if(token == "GEOMETRIC-PROTOCOL") {
                str_stream >> _routing_protocol;
            }
            str_stream.str(string());
            str_stream.clear();
        }
        std::getline(file, line);
    }
    file.close();
    assert("Geometric routing protocol must be specified."
           && _routing_protocol != "");
    if(node_placement_param == "FILE") {
        assert("Node placement file must be provided."
               && _node_placement_file != "");
    }
    if(mobility_param == "TRACE") {
        assert("Mobility trace file must be provided."
               &&  _mobility_trace_file != "");
    }
    atexit(&cleanUp);
}

void ConfigurationParameters::cleanUp() {
    delete _instance;
    _instance = NULL;
}