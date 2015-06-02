#include "routing_protocol_interface.h"

#include <iostream>  // TODO: Remove after testing

#include "routing_protocol.hpp"

extern "C" {

void GeometricRoutingProtocolInit(GlomoNode* node,
                                  GeometricRoutingProtocolProxy** proxy,
                                  const GlomoNodeInput* node_input) {
  std::cout << "Node: " << node->nodeAddr << ": INIT\n";

  GeometricRoutingProtocolFactory protocol_factory;
  GeometricRoutingProtocol* protocol =
      protocol_factory.createProtocol(node->nodeAddr);
  *proxy = static_cast<GeometricRoutingProtocolProxy*>(protocol);
  NetworkIpSetPacketDropNotificationFunction(
      node, &GeometricRoutingProtocolPacketDropNotificationHandler);
  NetworkIpSetRouterFunction(node, &GeometricRoutingProtocolRouterFunction);
}

void GeometricRoutingProtocolFinalize(GlomoNode* node) {
  std::cout << "Node: " << node->nodeAddr << ": FINALIZE\n";
}

void GeometricRoutingProtocolHandleProtocolEvent(GlomoNode* node,
                                                 Message* msg) {
  std::cout << "Node: " << node->nodeAddr
            << ": HANDLE PROTOCOL EVENT\n";
}

void GeometricRoutingProtocolPacketDropNotificationHandler(
    GlomoNode* node, const Message* msg, const NODE_ADDR next_hop_address) {
  std::cout << "Node: " << node->nodeAddr
            << ": PACKET DROP NOTIFICATION HANDLER\n";
  GlomoNetworkIp* ip_layer = (GlomoNetworkIp*)node->networkData.networkVar;
  GeometricRoutingProtocolProxy* proxy =
      (GeometricRoutingProtocolProxy*)ip_layer->routingProtocol;
  GeometricRoutingProtocol* protocol =
      static_cast<GeometricRoutingProtocol*>(proxy);

  //
  // TODO: Add packet drop statistics
  //
}

void GeometricRoutingProtocolRouterFunction(GlomoNode* node, Message* msg,
                                            NODE_ADDR dest_addr,
                                            BOOL* packet_was_routed) {
  std::cout << "Node: " << node->nodeAddr
            << ": ROUTER FUNCTION\n";
  //
  // TODO: Add routing interface
  //
}

void GeometricRoutingProtocolHandleProtocolPacket(GlomoNode* node, Message* msg,
                                                  NODE_ADDR src_addr,
                                                  NODE_ADDR dest_addr,
                                                  int ttl) {
  std::cout << "Node: " << node->nodeAddr
            << ": ROUTING_PROTOCOL_HANDLE_PROTOCOL_PACKET\n";
}
}
