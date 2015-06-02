#include "cfr.hpp"

#include <iostream>  // TODO: Remove after testing

#include "coordinates.hpp"
#include "location_provider.hpp"
#include "routing_protocol_interface.h"


using std::list;
using std::string;

GlomoRoutingCFR::GlomoRoutingCFR(NODE_ADDR address)
    : GeometricRoutingProtocol(address) {
  
}