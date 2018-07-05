#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;
using std::pair;

class GridWorld {
protected:
	const int action_up;
	const int action_down;
	const int action_left;
	const int action_right;
	int world_height;
	int world_width;
	double gamma;		// discount
	double epsilon;		// probability for exploration
	double alpha;		// step size
	double current_reward;	// current reward
	vector<int> actions;	// all possible actions
	vector<vector<double>> state_values;	// state values
	vector<vector<vector<double>>> state_action_values;	// state actin values
public:
	GridWorld(int height, int width, double g, double e, double a);
	virtual pair<int, int> move(pair<int, int> state, int action);
	virtual int epsilonGreedyPolicy(pair<int, int> state);
};