//
// Created by Kuilin Chen on 2018-07-12.
//

#ifndef CHAPTER08_MAZE_H
#define CHAPTER08_MAZE_H

#include "grid_world.h"
#include <algorithm>

using std::pair;

class Maze : public GridWorld {
    vector<pair<int, int>> start_state;
    vector<pair<int, int>> goal_state;
    vector<pair<int, int>> obstacles;
    int max_step;
    int resolution;

public:
    Maze(int height, int width, int factor=1);
    vector<pair<int, int>> extend_state(pair<int, int> state, int factor);
    pair<int, int> takeAction(pair<int, int> state, int action) override;
};


#endif //CHAPTER08_MAZE_H
