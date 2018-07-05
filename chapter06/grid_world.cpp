#include "grid_world.h"

GridWorld::GridWorld(int height, int width, double g, double e, double a): action_up(0), action_down(1), action_left(2), action_right(3) {
	this->world_height = height;
	this->world_width = width;
	this->gamma = g;
	this->epsilon = e;
	this->alpha = a;
	this->current_reward = 0.0;
	this->actions.push_back(action_up);
	this->actions.push_back(action_down);
	this->actions.push_back(action_left);
	this->actions.push_back(action_right);
	state_values = vector<vector<double>>(height, vector<double>(width, 0.0));
	state_action_values = vector<vector<vector<double>>>(height, vector<vector<double>>(width, vector<double>(actions.size(), 0.0)));
}

int GridWorld::epsilonGreedyPolicy(pair<int, int> state) {
	int action = 0;
	if (rand() % (static_cast<int>(1.0 / epsilon)) == 1) {
		action = actions[rand() % 4];
	}
	else {
		vector<double> values = state_action_values[state.first][state.second];
		vector<int> max_actions;
		double max_value = -1000000.0;
		for (size_t i = 0; i < values.size(); i++) {
			if (values[i] > max_value) max_value = values[i];
		}
		for (size_t i = 0; i < values.size(); i++) {
			if (values[i] == max_value) max_actions.push_back(i);
		}
		action = max_actions[rand() % (max_actions.size())];
	}
	return action;
}

pair<int, int> GridWorld::move(pair<int, int> current_state, int action) {
	int i = current_state.first;
	int j = current_state.second;
	int ii = 0;
	int jj = 0;

	if (action == action_up) {
		ii = std::max(i - 1, 0);
		jj = j;
	}
	if (action == action_down) {
		ii = std::max(std::min(i + 1, world_height - 1), 0);
		jj = j;
	}
	if (action == action_left) {
		ii = std::max(i, 0);
		jj = std::max(j - 1, 0);
	}
	if (action == action_right) {
		ii = std::max(i, 0);
		jj = std::min(j + 1, world_width - 1);
	}
	return std::make_pair(ii, jj);
}