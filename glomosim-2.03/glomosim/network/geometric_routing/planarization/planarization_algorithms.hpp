#ifndef PLANARIZATION_ALGORITHMS_H_
#define PLANARIZATION_ALGORITHMS_H_

#include <list>
#include "main.h"
#include "coordinates.hpp"
#include "mobile_host.hpp"

using std::list;

class PlanarNeighborTable {
public:
    struct Neighbor {
        MobileHost* host;
        bool is_planar_nbr;
    };
    
    list<Neighbor> entries;
};


class GabrielGraph : public PlanarNeighborTable {
    
};


#endif