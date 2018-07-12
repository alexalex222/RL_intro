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
	double current_reward;	// current reward
	vector<int> actions;	// all possible actions
	vector<vector<double>> state_values;	// state values
	vector<vector<vector<double>>> state_action_values;	// state actin values
public:
	GridWorld(int height, int width);
	virtual pair<int, int> takeAction(pair<int, int> state, int action);
};