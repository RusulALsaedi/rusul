#ifndef CONFIGURATION_PARAM_HPP_
#define CONFIGURATION_PARAM_HPP_

#include <string>

using std::string;

class ConfigurationParameters {
public:
    ConfigurationParameters(const ConfigurationParameters&) = delete;
    ConfigurationParameters& operator=(const ConfigurationParameters&) = delete;
    static ConfigurationParameters* instance();
    
    string nodePlacementFile() {
        return _node_placement_file;
    };
    string mobilityTraceFile() {
        return _mobility_trace_file;
    };
    bool isStatic() {
        return _is_static;
    };
    string routingProtocol() {
        return _routing_protocol;
    }
    
private:
    static ConfigurationParameters* _instance;
    ConfigurationParameters();
    static void cleanUp();
    
    string _node_placement_file;
    string _mobility_trace_file;
    bool _is_static;
    string _routing_protocol;
};

#endif
