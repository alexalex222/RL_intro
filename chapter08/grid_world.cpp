#include "grid_world.h"

GridWorld::GridWorld(int height, int width): action_up(0), action_down(1), action_left(2), action_right(3) {
	this->world_height = height;
	this->world_width = width;
	this->current_reward = 0.0;
	this->actions.push_back(action_up);
	this->actions.push_back(action_down);
	this->actions.push_back(action_left);
	this->actions.push_back(action_right);
	state_values = vector<vector<double>>(height, vector<double>(width, 0.0));
	state_action_values = vector<vector<vector<double>>>(height, vector<vector<double>>(width, vector<double>(actions.size(), 0.0)));
}


pair<int, int> GridWorld::takeAction(pair<int, int> current_state, int action) {
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