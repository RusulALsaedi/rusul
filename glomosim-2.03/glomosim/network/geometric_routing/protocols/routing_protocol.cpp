#include "routing_protocol.hpp"

#include <cassert>

#include "cfr.hpp"
#include "configuration_param.hpp"

GeometricRoutingProtocol* GeometricRoutingProtocolFactory::createProtocol(
    NODE_ADDR address) {
  GeometricRoutingProtocol* protocol;
  if (_config->routingProtocol() == "CFR") {
    protocol = new GlomoRoutingCFR(address);
  }
  // Add new routing protocol options here...
  else {
    assert("Geometric routing protocol name not found." &&
           false);  // TODO: Replace with exception
  }
  return protocol;
}
