#ifndef COORDINATES_HPP_
#define COORDINATES_HPP_

#include <cmath>

class Coordinates {
public:
    Coordinates() : _x(0), _y(0), _z(0) { };
    Coordinates(double x, double y, double z = 0) : _x(x), _y(y), _z(z) { };
    double distSq(const Coordinates& rhs) const {
        return (  ((_x - rhs._x)*(_x - rhs._x))
                + ((_y - rhs._y)*(_y - rhs._y))
                + ((_z - rhs._z)*(_z - rhs._z)));
    }
    double dist(const Coordinates& rhs) const {
        return sqrt(distSq(rhs));
    }
    
private:
    double _x;
    double _y;
    double _z;
};

#endif
