//
// Created by Kuilin Chen on 2018-06-16.
//

#ifndef CHAPTER04_GRIDWORLD_H
#define CHAPTER04_GRIDWORLD_H

#include <vector>
#include <iostream>
#include <math.h>

using std::vector;
using std::pair;

class GridWorld {
private:
    int world_size;
    double action_prob;
    double reward;
    vector<char> actions;
    vector<pair<int, int>> states;
    int iteration;
    vector<vector<double>> state_values;


public:
    GridWorld(int size);
    pair<int, int> next_state(pair<int, int> state, char action);
    void compute_state_values(double tolerance, bool in_place);
    void print_state_values();
    int get_iteration();

};


#endif //CHAPTER04_GRIDWORLD_H
