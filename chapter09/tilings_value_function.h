//
// Created by Kuilin Chen on 2018-07-13.
//

#ifndef CHAPTER09_TILINGS_VALUE_FUNCTION_H
#define CHAPTER09_TILINGS_VALUE_FUNCTION_H

#include "random_walk.h"
#include "value_function.h"


// a wrapper class for tile coding value function
class TilingsValueFunction: public ValueFunction {
private:
    const int num_tilings;
    const int tile_width;
    const int tile_offset;
    int tile_size;
    vector<vector<double>> params;  // weight for each tile
    vector<int> tilings;

public:
    /*
     * @obj: RandWalk object
     * @n: # of tilings
     * @width: each tiling has several tiles, this parameter specifies the width of each tile
     * @offset: specifies how tilings are put together
     */
    TilingsValueFunction(int n, int width, int offset);

    // get the value of the state
    double value(int state) override;

    /*
     * update parameters
     * @state: state of current sample
     * @delta: step size * (target - old estimation)
     */
    void update(int state, double delta) override;
};


#endif //CHAPTER09_TILINGS_VALUE_FUNCTION_H
