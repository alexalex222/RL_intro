#pragma once

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
	RandomWalk(int n=19, int start=10, double discount=1.0);
	void temporalDifference(vector<double>& state_values, int n, double alpha);
	void testLearning();

};