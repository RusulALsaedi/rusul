#ifndef ROUTING_PROTOCOL_HPP_
#define ROUTING_PROTOCOL_HPP_

#include "configuration_param.hpp"
#include "mobile_host.hpp"

class GeometricRoutingProtocol {
 public:
  GeometricRoutingProtocol(NODE_ADDR address) : _local_host(address){};

 protected:
  MobileHost _local_host;
};

class GeometricRoutingProtocolFactory {
 public:
  GeometricRoutingProtocolFactory()
      : _config(ConfigurationParameters::instance()){};
  GeometricRoutingProtocol* createProtocol(NODE_ADDR);

 private:
  ConfigurationParameters* _config;
};

#endif