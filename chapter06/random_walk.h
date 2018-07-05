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

class RandomWalk {

private:
    int n_states;		//number of states
    int start_state;	// start state

    vector<double> init_state_values;		// initial state values
    vector<double> real_state_values;		// real state values
    vector<int> end_states;
    double gamma;		// discount

public:
    RandomWalk(int left_reward=-1, int right_reward=1, int n=19, double discount=1.0);
    void temporalDifference(vector<double>& state_values, int n, double alpha);
    void testLearning();

};


#endif //CHAPTER06_RANDOM_WALK_H
