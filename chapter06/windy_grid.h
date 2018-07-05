#pragma once

#include "grid_world.h"


class WindyGrid: public GridWorld{
private:
	vector<int> wind;
	pair<int, int> start_state;
	pair<int, int> goal_state;

public:
	WindyGrid(int height, int width, double g, double e, double a);
	pair<int, int> move(pair<int, int> current_state, int action);
	int epsilonGreedyPolicy(pair<int, int> state);
	int play();
	void testLearning();
};