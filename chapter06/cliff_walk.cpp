#include "cliff_walk.h"

CliffWalk::CliffWalk(int height, int width, double g, double e, double a): GridWorld(height, width, g, e, a){
	start_state = std::make_pair(3, 0);
	goal_state = std::make_pair(3, 11);

	action_rewards = vector<vector<vector<double>>>(height, vector<vector<double>>(width, vector<double>(actions.size(), -1.0)));
	for (int i = 1; i < 11; i++) action_rewards[2][i][action_down] = -100.0;
	action_rewards[3][0][action_right] = -100.0;
}

pair<int, int> CliffWalk::move(pair<int, int> state, int action) {
	int i = state.first;
	int j = state.second;
	int ii = 0;
	int jj = 0;

	if (action == action_up) {
		ii = std::max(i - 1, 0);
		jj = j;
	}
	if (action == action_down) {
		if (j >= 1 && j <= 10) {
			ii = start_state.first;
			jj = start_state.second;
		}
		else {
			ii = std::min(i + 1, world_height - 1);
			jj = j;
		}
	}
	if (action == action_left) {
		ii = std::max(i, 0);
		jj = std::max(j - 1, 0);
	}
	if (action == action_right) {
		if (i == 3 && j == 0) {
			ii = start_state.first;
			jj = start_state.second;
		}
		else {
			ii = std::max(i, 0);
			jj = std::min(j + 1, world_width - 1);
		}
		
	}
	return std::make_pair(ii, jj);
}

int CliffWalk::epsilonGreedyPolicy(pair<int, int> state) {
	int action = 0;
	if (rand() % (static_cast<int>(1.0 / epsilon)) == 0) {
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

double CliffWalk::play(void (CliffWalk::*learning_method)(pair<int, int>, int, pair<int, int>, int, double), double step_size) {
	if (step_size == 0.0) step_size = alpha;
	pair<int, int> current_state = start_state;
	int current_action = epsilonGreedyPolicy(current_state);
	double rewards = 0.0;
	while (current_state != goal_state) {
		pair<int, int> new_state = move(current_state, current_action);
		int new_action = epsilonGreedyPolicy(new_state);
		current_reward = action_rewards[current_state.first][current_state.second][current_action];
		rewards += current_reward;


		(this->*(learning_method))(current_state, current_action, new_state, new_action, step_size);

		current_state = new_state;
		current_action = new_action;
	}
	return rewards;
}

void CliffWalk::sarsa(pair<int, int> current_state, int current_action, pair<int, int> new_state, int new_action, double step_size) {
	double value_target = 0.0;
	value_target = state_action_values[new_state.first][new_state.second][new_action];
	value_target = value_target * gamma;
	state_action_values[current_state.first][current_state.second][current_action] += step_size*(current_reward + value_target - \
		state_action_values[current_state.first][current_state.second][current_action]);
}

void CliffWalk::expectedSarsa(pair<int, int> current_state, int current_action, pair<int, int> new_state, int new_action, double step_size) {
	double value_target = 0.0;
	vector<double> action_values = state_action_values[new_state.first][new_state.second];
	double best_value = static_cast<double>(INT_MIN);
	vector<int> best_actions;
	for (size_t i = 0; i < action_values.size(); i++) {
		if (action_values[i] > best_value) {
			best_value = action_values[i];
		}
	}
	for (size_t i = 0; i < action_values.size(); i++) {
		if (action_values[i] == best_value) {
			best_actions.push_back(i);
		}
	}

	for (auto a : actions) {
		if (std::find(best_actions.begin(), best_actions.end(), a) != best_actions.end()) {
			value_target += ((1.0 - epsilon) / static_cast<double>(best_actions.size()) + epsilon / static_cast<double>(actions.size())) * state_action_values[new_state.first][new_state.second][a];
		}
		else {
			value_target += epsilon / static_cast<double>(actions.size()) * state_action_values[new_state.first][new_state.second][a];
		}
	}
	value_target = value_target * gamma;
	state_action_values[current_state.first][current_state.second][current_action] += step_size*(current_reward + value_target - \
		state_action_values[current_state.first][current_state.second][current_action]);
}

void CliffWalk::qLearning(pair<int, int> current_state, int current_action, pair<int, int> new_state, int new_action, double step_size) {
	double best_value = static_cast<double>(INT_MIN);
	vector<double> action_values = state_action_values[new_state.first][new_state.second];
	for (size_t i = 0; i < action_values.size(); i++) {
		if (action_values[i] > best_value) best_value = action_values[i];
	}
	state_action_values[current_state.first][current_state.second][current_action] += step_size*(current_reward + gamma*best_value - \
		state_action_values[current_state.first][current_state.second][current_action]);
}