//
//  Polar_map.cpp
//  SINGER
//

#include "Polar_map.hpp"

Polar_map::Polar_map() {}

void Polar_map::load_map(string site_polar_file, double start_position, double end_position) {
    ifstream fin(site_polar_file);
    if (!fin.good()) {
        cerr << "input site polarization file not found" << endl;
        exit(1);
    }
    /* duplicated positions will be ignored by map.insert */
    double position, polar;
    while (fin >> position >> polar) {
        if (position < start_position) { continue; }
        if (position > end_position) { break; }
        assert(polar > 0.0 and polar < 1.0);
        ancestral_prob.insert({position - start_position, polar});
    }
}

void Polar_map::set_default(double prob) {
    default_ancestral_prob = prob;
}

double Polar_map::at_position(double position) {
    if (ancestral_prob.empty()) { return default_ancestral_prob; }
    std::map<double, double>::const_iterator itt = ancestral_prob.find(position);
    return itt == ancestral_prob.end() ? default_ancestral_prob : itt->second;
}
