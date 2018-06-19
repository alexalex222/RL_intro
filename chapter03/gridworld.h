//
// Created by Kuilin Chen on 2018-06-18.
//

#ifndef CHAPTER03_GRIDWORLD_H
#define CHAPTER03_GRIDWORLD_H

#include <vector>
#include <unordered_map>
#include <iostream>

using std::vector;
using std::pair;
using std::unordered_map;

class GridWorld {
private:
    int world_size;
    double action_prob;
    double state_action_reward;
    vector<double> special_reward;
    double discount;
    vector<char> actions;
    vector<pair<int, int>> states;
    int iteration;
    vector<vector<double>> state_values;
    vector<pair<int, int>> special_states;
    vector<pair<int, int>> special_states_prime;

public:
    GridWorld(int size);
    pair<int, int> next_state(pair<int, int> state, char action);
    void compute_state_values(double tolerance=1e-4, bool in_place=true, bool optimal=false);
    void print_state_values();
};


#endif //CHAPTER03_GRIDWORLD_H
