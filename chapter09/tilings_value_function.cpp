//
// Created by Kuilin Chen on 2018-07-13.
//

#include "tilings_value_function.h"

TilingsValueFunction::TilingsValueFunction(int n, int width, int offset) : num_tilings(n), tile_width(width), tile_offset(offset)
{
    // To make sure that each sate is covered by same number of tiles, we need one more tile for each tiling
    tile_size = p.getSize() / (tile_width + 1);
    params = vector<vector<double>>(num_tilings, vector<double>(tile_size, 0.0));

    /*
     * For performance, only track the starting position for each tiling
     * As we have one more tile for each tiling, the starting position will be negative
     */
    for (int i = -tile_width + 1; i < 0; i = i + tile_offset) {
        tilings.push_back(i);
    }

}

double TilingsValueFunction::value(int state) {
    double state_value = 0.0;
    for (size_t i = 0; i < tilings.size(); i++) {
        int tile_index = (state - tilings[i])/tile_width;
        state_value += params[i][tile_index];
    }
    return state_value;
}

void TilingsValueFunction::update(int state, double delta) {
    /*
     * each state is covered by same number of tilings
     * so the delta should be divided equally into each tiling (tile)
     */
    delta = delta / static_cast<double>(num_tilings);

    for (size_t i = 0; i < tilings.size(); i++) {
        int tile_index = (state - tilings[i])/tile_width;
        params[i][tile_index] += delta;
    }

}