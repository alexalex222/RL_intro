#include "windy_grid.h"


WindyGrid::WindyGrid(int height, int width, double g, double e, double a):GridWorld(height, width, g, e, a) {
	current_reward = -1;
	static const int arr[] = { 0, 0, 0, 1, 1, 1, 2, 2, 1, 0 };
	wind = vector<int>(arr, arr + sizeof(arr) / sizeof(arr[0]));
	state_action_values = vector<vector<vector<double>>>(world_height, vector<vector<double>>(world_width, vector<double>(actions.size(), 0.0)));
	start_state = std::make_pair(3, 0);
	goal_state = std::make_pair(3, 7);
}

pair<int, int> WindyGrid::move(pair<int, int> current_state, int action) {
	int i = current_state.first;
	int j = current_state.second;
	int ii = 0;
	int jj = 0;

	if (action == action_up) {
		ii = std::max(i - 1 - wind[j], 0);
		jj = j;
	}
	if (action == action_down) {
		ii = std::max(std::min(i + 1 - wind[j], world_height - 1), 0);
		jj = j;
	}
	if (action == action_left) {
		ii = std::max(i - wind[j], 0);
		jj = std::max(j - 1, 0);
	}
	if (action == action_right) {
		ii = std::max(i - wind[j], 0);
		jj = std::min(j + 1, world_width - 1);
	}
	return std::make_pair(ii, jj);
}

int WindyGrid::epsilonGreedyPolicy(pair<int, int> state) {
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

int WindyGrid::play() {
	int time = 0;	// track the total time step in the current episode
	pair<int, int> current_state = start_state;		// initialize the state

	int current_action = epsilonGreedyPolicy(current_state);		// choose action based on epsilon greedy policy
	
	while (current_state != goal_state) {
		pair<int, int> new_state = move(current_state, current_action);
		int new_action = epsilonGreedyPolicy(new_state);
		state_action_values[current_state.first][current_state.second][current_action] += \
			alpha*(current_reward + state_action_values[new_state.first][new_state.second][new_action] - \
			state_action_values[current_state.first][current_state.second][current_action]);
		current_state = new_state;
		current_action = new_action;
		time++;
	}
	return time;
}

void WindyGrid::testLearning() {
	std::cout.precision(5);
	std::cout << std::fixed;


	int episodes = 5000;
	for (int ep = 0; ep < episodes; ep++) {
		int time = play();
	}

	vector<vector<char>> optimal_policy(world_height, vector<char>(world_width, 'G'));
	for (int i = 0; i < world_height; i++) {
		for (int j = 0; j < world_width; j++) {
			std::cout << i << " " << j << " : ";
			if (std::make_pair(i, j) == goal_state) continue;
			int best_action = 0;
			double max_value = INT_MIN;
			for (size_t a = 0; a < actions.size(); a++) {
				std::cout << state_action_values[i][j][a] << "\t";
				if (state_action_values[i][j][a] > max_value) {
					max_value = state_action_values[i][j][a];
					best_action = a;
				}
			}

			if (best_action == action_up) optimal_policy[i][j] = 'U';
			else if (best_action == action_down) optimal_policy[i][j] = 'D';
			else if (best_action == action_left) optimal_policy[i][j] = 'L';
			else if (best_action == action_right) optimal_policy[i][j] = 'R';
			std::cout << optimal_policy[i][j] << "\t";

			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	// print results

	for (size_t i = 0; i < wind.size(); i++) {
		std::cout << wind[i] << "\t";
	}
	std::cout << std::endl;
	
	for (int i = 0; i < world_height; i++) {
		for (int j = 0; j < world_width; j++) {
			std::cout << optimal_policy[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}