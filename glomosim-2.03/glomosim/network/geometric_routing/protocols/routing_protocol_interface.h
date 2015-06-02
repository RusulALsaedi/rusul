#ifndef PROTOCOL_INTERFACE_H_
#define PROTOCOL_INTERFACE_H_

#ifdef __cplusplus

extern "C" {

#endif

#include "glomo_network_headers.h"

typedef void GeometricRoutingProtocolProxy;

void GeometricRoutingProtocolInit(GlomoNode*, GeometricRoutingProtocolProxy**,
                                  const GlomoNodeInput*);

void GeometricRoutingProtocolFinalize(GlomoNode*);

void GeometricRoutingProtocolHandleProtocolEvent(GlomoNode*, Message*);

void GeometricRoutingProtocolPacketDropNotificationHandler(GlomoNode*,
                                                           const Message*,
                                                           const NODE_ADDR);

void GeometricRoutingProtocolRouterFunction(GlomoNode*, Message*, NODE_ADDR,
                                            BOOL*);

void GeometricRoutingProtocolHandleProtocolPacket(GlomoNode*, Message*,
                                                  NODE_ADDR, NODE_ADDR, int);

#ifdef __cplusplus
}

#endif

#endif
