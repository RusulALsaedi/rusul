#ifndef LOCATION_PROVIDER_HPP_
#define LOCATION_PROVIDER_HPP_

extern "C" {
    
#include "glomo_network_headers.h"
    
}

#include <fstream>
#include <utility>
#include <unordered_map>

#include "configuration_param.hpp"
#include "coordinates.hpp"


using std::ifstream;

typedef std::pair<NODE_ADDR, clocktype> HostTableKey;

namespace std {
    template <>
    class hash<HostTableKey> {
    public:
        size_t operator()(const HostTableKey &key) const {
            return hash<NODE_ADDR>()(key.first) ^ hash<clocktype>()(key.second);
        };
    };
};

class LocationProvider {
public:
    typedef std::unordered_map<HostTableKey, Coordinates> HostTable;
    static const Coordinates npos;
    LocationProvider() = delete;
    LocationProvider(const LocationProvider&) = delete;
    LocationProvider& operator=(const LocationProvider&) = delete;
    static LocationProvider* instance();
    Coordinates getLastKnownLocation(const HostTableKey&);
    
private:
    static LocationProvider* _instance;
    
    LocationProvider(HostTable*);
    ~LocationProvider();
    static void cleanUp();
    static HostTable* generateHostTable();
    static void addHostsFromTrace(HostTable*, ifstream&);
    
    static ConfigurationParameters* _config;
    HostTable* _host_table;
};

#endif