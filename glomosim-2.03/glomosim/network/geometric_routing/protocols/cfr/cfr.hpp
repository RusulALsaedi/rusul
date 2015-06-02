#ifndef CFR_HPP_
#define CFR_HPP_

#include <list>
#include <mutex>
#include <string>
#include <queue>

#include "coordinates.hpp"
#include "location_provider.hpp"
#include "planarization_algorithms.hpp"
#include "routing_protocol.hpp"
#include "routing_protocol_interface.h"

using std::queue;
using std::list;
using std::string;

enum Direction { CLOCKWISE, COUNTERCLOCKWISE };

struct CFRPacket {
  int sequence_num;
  MobileHost* source;
  MobileHost* destination;
  NODE_ADDR prev_hop;
  NODE_ADDR next_hop;
  Direction direction;

  string payload;
};

class GlomoRoutingCFR : public GeometricRoutingProtocol {
 public:
  GlomoRoutingCFR(NODE_ADDR);

 private:
  queue<CFRPacket> _receive_buffer;
  list<CFRPacket> _send_buffer;
  PlanarNeighborTable* _neighbor_table;
  int _sequence_num;
};

#endif