#include "random_walk.h"

RandomWalk::RandomWalk(int n, int start, double discount) {
	this->n_states = n;
	this->start_state = start;
	this->gamma = discount;
	this->init_state_values = vector<double>(this->n_states + 2, 0.0);
	
	for (int i = -(n+1); i <= (n-1); i = i + 2) {
		this->real_state_values.push_back(static_cast<double>(i) / 20.0);
	}
	this->real_state_values.push_back(0.0);
	this->real_state_values[0] = 0.0;	

	this->end_states.push_back(0);
	this->end_states.push_back(n + 1);
}


void RandomWalk::temporalDifference(vector<double>& state_values, int n, double alpha) {
	int current_state = this->start_state;
	vector<int> states(1, current_state);
	vector<double> rewards(1, 0.0);

	int t = 0;		// time step;
	int end_time = INT_MAX;

	int new_state = current_state;

	while (true) {
		t++;	// go to next time step	
		int reward = 0;
		if (t < end_time) {
			if (rand()%2 == 1)  {
				new_state = current_state + 1;
			}
			else {
				new_state = current_state - 1;
			}

			if (new_state == 0) {
				reward = -1;
			}
			else if (new_state == this->end_states.back()) {
				reward = 1;
			}
			else {
				reward = 0;
			}
			// store the new state and reward
			states.push_back(new_state);
			rewards.push_back(reward);

			if (std::find(end_states.begin(), end_states.end(), new_state) != end_states.end()) end_time = t;
		}

		int update_time = t - n;
		

		if (update_time >= 0) {
			double total_rewards = 0.0;
			for (int i = update_time + 1; i <= std::min(end_time, update_time + n); i++) {
				total_rewards += pow(this->gamma, i - update_time - 1)*rewards[i];
			}

			if (update_time + n <= end_time) {
				total_rewards += pow(this->gamma, n) * state_values[states[update_time + n]];
			}
			int state_to_update = states[update_time];

			if (std::find(end_states.begin(), end_states.end(), state_to_update) == end_states.end()) {
				state_values[state_to_update] += alpha*(total_rewards - state_values[state_to_update]);
			}
		}

		if (update_time == end_time - 1) {
			break;
		}
		current_state = new_state;
	}

}

void RandomWalk::testLearning() {
	std::cout.precision(5);
	std::cout << std::fixed;

	double truncate_value = 0.55;
	vector<int> steps;		// all possible steps
	for (int i = 0; i < 10; i++) {
		steps.push_back(static_cast<int>(pow(2, i)));
	}
	vector<double> alphas;		// all possible alphas
	for (double a = 0.1; a <= 1.0; a = a + 0.1) alphas.push_back(a);

	int runs = 100;		// number of independent runs
	int episodes = 10;	// each run has 10 episodes

	vector<vector<double>> errors(steps.size(), vector<double>(alphas.size(), 0));	// track errors for each (step, alpha) conbination
	std::cout << "Learning... " << std::endl;
	for (int run = 0; run < runs; run++) {
		for (size_t step_idx = 0; step_idx < steps.size(); step_idx++) {
			for (size_t alpha_idx = 0; alpha_idx < alphas.size(); alpha_idx++) {
				int step = steps[step_idx];
				double alpha = alphas[alpha_idx];
				std::cout << "Run: " << run + 1 << " Step: " << step << " alpha: " << alpha << std::endl;
				vector<double> current_state_values(this->n_states + 2, 0.0);
				for (int ep = 0; ep < episodes; ep++) {
					temporalDifference(current_state_values, step, alpha);
					double total_error = 0.0;
					for (size_t s = 0; s < this->real_state_values.size(); s++) {
						total_error += pow((current_state_values[s] - this->real_state_values[s]), 2);
					}
					errors[step_idx][alpha_idx] += sqrt(total_error / this->n_states);
				}
				
			}
		}
	}

	


	for (size_t step_idx = 0; step_idx < steps.size(); step_idx++) {
		for (size_t alpha_idx = 0; alpha_idx < alphas.size(); alpha_idx++) {
			errors[step_idx][alpha_idx] = errors[step_idx][alpha_idx] / (runs*episodes);
			std::cout << errors[step_idx][alpha_idx] << "\t";
		}
		std::cout << std::endl;
	}

}