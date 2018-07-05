#pragma once

#include <algorithm>
#include "grid_world.h"

class CliffWalk : public GridWorld {
protected:
	pair<int, int> start_state;
	pair<int, int> goal_state;
	vector<vector<vector<double>>> action_rewards;

public:
	CliffWalk(int height, int width, double g, double e, double a);
	pair<int, int> move(pair<int, int> state, int action);
	int epsilonGreedyPolicy(pair<int, int> state);
	double play(void (CliffWalk::*learning_method)(pair<int, int>, int, pair<int, int>, int, double), double step_size = 0);
	void sarsa(pair<int, int> current_state, int current_action, pair<int, int> new_state, int new_action, double step_size);
	void expectedSarsa(pair<int, int> current_state, int current_action, pair<int, int> new_state, int new_action, double step_size);
	void qLearning(pair<int, int> current_state, int current_action, pair<int, int> new_state, int new_action, double step_size);
};