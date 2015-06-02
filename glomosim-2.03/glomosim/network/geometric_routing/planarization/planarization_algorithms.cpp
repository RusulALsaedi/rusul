#include "planarization_algorithms.hpp"

/*
void GenerateGabrielOverlayFromBeacon(
  const list<PlanarNeighborTableEntry>& neighbor_table,
  const Coordinates& location,
  const MobileHost& beac_src) {
    
    
    bool is_gabriel_edge = true, not_in_table = true;
    double src_to_beac = location.distSq(beac_src.location);
    for(auto neighbor = neighbor_table.begin(); neighbor != neighbor_table.end(); ++neighbor) {
        double src_to_nbr = location.distSq(neighbor->host.location);
        double beac_to_nbr = beac_src.location.distSq(neighbor->host.location);
        if((src_to_nbr + beac_to_nbr) < src_to_beac) {
            is_gabriel_edge = false;
        }
        if((src_to_beac + beac_to_nbr) < src_to_nbr) {
            neighbor->edge_in_planar_overlay = false;
        }
        if(neighbor->host.address == beac_src.address) {
            neighbor->host.setLocation(beac_src.location);
            not_in_table = false;
        }
    }
    if(not_in_table){
        PlanarNeighborTableEntry entry;
        entry.host = beac_src;
        entry.edge_in_planar_overlay = is_gabriel_edge;
        neighbor_table.push(entry);
    }
}
*/