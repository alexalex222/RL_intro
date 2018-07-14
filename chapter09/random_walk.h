//
// Created by Kuilin Chen on 2018-06-28.
//

#ifndef CHAPTER06_RANDOM_WALK_H
#define CHAPTER06_RANDOM_WALK_H


#include <vector>
#include <climits>
#include <chrono>
#include <random>
#include <algorithm>
#include <iostream>

using std::vector;
using std::pair;

class RandomWalk {

private:
    int n_states;		//number of states
    int start_state;	// start state
    int action_left;    // move left
    int action_right;   // move right
    vector<int> states; // states in random walk
    vector<int> actions;    // lists of actions
    vector<double> old_state_values;		// old (or initial) state values
    vector<double> real_state_values;		// real state values
    vector<int> end_states;
    double gamma;		// discount
    int step_range;     // maximum stride for an action

public:
    RandomWalk(int n = 1000, int left_reward=-1, int right_reward=1, double discount=1.0);
    pair<int, int> takeAction(int state, int action);
    int getAction();
    int getSize();
    vector<int> getEndStates();
    int getStartState();

};


#endif //CHAPTER06_RANDOM_WALK_H
