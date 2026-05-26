//
//  Polar_map.hpp
//  SINGER
//

#ifndef Polar_map_hpp
#define Polar_map_hpp

#include <stdio.h>
#include <limits>
#include <map>
#include "Node.hpp"

class Polar_map {  /* wrapper over std::map with a default value and I/O */
    
public:

    double default_ancestral_prob = 0.99;
    map<double, double> ancestral_prob;
    
    Polar_map();
    
    void load_map(string site_polar_file, double start_position, double end_position);
    void set_default(double prob);
    double at_position(double position);
};

#endif /* Polar_map_hpp */
