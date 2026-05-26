//
//  Rate_map.cpp
//  SINGER
//
//  Created by Yun Deng on 6/4/24.
//

#include "Rate_map.hpp"

Rate_map::Rate_map() {}

Rate_map::Rate_map(double rate, double length) {
    coordinates = {0.0, length};
    rate_distances = {0.0, rate * length};
    sequence_length = length;
}

void Rate_map::load_map(string filename, double start_position, double end_position) {
    ifstream fin(filename);
    if (!fin.good()) {
        cerr << "input rate map file not found" << endl;
        exit(1);
    }
    rate_distances.push_back(0);
    double left, right, rate, clip_left, clip_right;
    double last_right = NAN;
    while (fin >> left >> right >> rate) {
        if (!std::isnan(last_right) && left != last_right) {
            cerr << "Error: rate map has an internal gap or an overlap between "
                 << "start (" << left << ") and previous endpoint (" 
                 << last_right << ")." << endl;
            exit(1);
        }
        last_right = right;

        if (right <= start_position) continue;
        if (left >= end_position) break;
        clip_left = max(left, start_position) - start_position;
        clip_right = min(right, end_position) - start_position;
        coordinates.push_back(clip_left);
        rate_distances.push_back(
            rate_distances.back() + rate * (clip_right - clip_left)
        );
    }
    if (coordinates.empty() || coordinates.front() > 0 || right < end_position) {
        cerr << "Error: rate map does not fully contain interval ["
             << start_position << ", " << end_position << ")." << endl;
        exit(1);
    }
    sequence_length = end_position - start_position;
    coordinates.push_back(sequence_length);
}

int Rate_map::find_index(double x) {
    auto it = upper_bound(coordinates.begin(), coordinates.end(), x);
    it--;
    int index = (int) distance(coordinates.begin(), it);
    assert(index >= 0 and index <= coordinates.size() - 1);
    return index;
}

double Rate_map::cumulative_distance(double x) {
    int index = find_index(x);
    double prev_dist = rate_distances[index];
    double next_dist = rate_distances[index+1];
    double p = (x - coordinates[index])/(coordinates[index+1] - coordinates[index]);
    double dist = (1-p)*prev_dist + p*next_dist;
    return dist;
}

double Rate_map::segment_distance(double x, double y) {
    return cumulative_distance(y) - cumulative_distance(x);
}

double Rate_map::mean_rate() {
    double mr = rate_distances.back()/sequence_length;
    return mr;
}
