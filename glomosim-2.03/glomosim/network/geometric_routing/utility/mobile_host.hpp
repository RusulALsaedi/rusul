#ifndef MOBILE_HOST_HPP_
#define MOBILE_HOST_HPP_

#include "main.h"
#include "coordinates.hpp"


class MobileHost {
public:
    MobileHost(NODE_ADDR address, Coordinates location = Coordinates(-1,-1,-1))
     : _address(address), _location(location) { };
    
    NODE_ADDR getHostAddress() {
        return _address;
    }
    void setLocationTo(Coordinates location){
        _location = location;
    }
    double distSq(const MobileHost& remote) const {
        return _location.distSq(remote._location);
    }
    double dist(const MobileHost& remote) const {
        return sqrt(distSq(remote));
    }
    
protected:
    NODE_ADDR _address;
    Coordinates _location;
};

#endif