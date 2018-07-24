#include "baird.h"

Baird::Baird(int num_states, int lower_state_val, double discount, int feature_size_val, double reward_val) : lower_state(lower_state_val), gamma(discount), feature_size(feature_size_val), reward(reward_val) {
	behavior_solid_prob = 1.0 / num_states;
	states = vector<int>(num_states, 0);
	state_distribution_matrix = MatrixXd::Zero(num_states, num_states);
	state_distribution = VectorXd::Zero(num_states);
	for (int i = 0; i < num_states; i++) {
		states[i] = i;
		state_distribution_matrix(i, i) = 1.0 / num_states;
		state_distribution(i) = 1.0 / num_states;
	}

	std::cout << "State distribution matrix: " << "\n" << state_distribution_matrix << std::endl;

	features = MatrixXd::Zero(num_states, feature_size);
	for (int i = 0; i < lower_state; i++) {
		features(i, i) = 2;
		features(i, feature_size - 1) = 1;
	}
	features(lower_state, feature_size - 2) = 1;
	features(lower_state, feature_size - 1) = 2;

	std::cout << "Feature matrix: " << "\n" << features << std::endl;

	actions = vector<int>(2, 0);
	actions[0] = DASHED;
	actions[1] = SOLID;

	MatrixXd temp = features.transpose()*state_distribution_matrix*features;
	MatrixXd pinv = temp.completeOrthogonalDecomposition().pseudoInverse();
	projection_matrix = features*pinv*features.transpose()*state_distribution_matrix;

	std::cout << "Pojection matrix: " << "\n" << projection_matrix << std::endl;
}

int Baird::takeAction(int state, int action) {
	if (action == SOLID) return lower_state;
	return  states[rand() % lower_state];
}

int Baird::targetPolicy(int state) {
	return SOLID;
}

int Baird::behaviorPolicy(int state) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::binomial_distribution<int> d(1, behavior_solid_prob);

	if (d(gen) == 1) return SOLID;
	else return DASHED;
}

int Baird::semiGradientOffPolicyTD(int state, VectorXd& theta, double alpha) {
	int action = behaviorPolicy(state);
	int next_state = takeAction(state, action);

	double rho = 0.0;
	if (action == DASHED) rho = 0.0;
	else rho = 1.0 / behavior_solid_prob;

	double delta = reward + gamma*(features.row(next_state)*theta)(0, 0) - (features.row(state)*theta)(0, 0);
	delta *= rho*alpha;
	theta += features.row(state)*delta;
	return next_state;
}


void Baird::semiiGradientDP(VectorXd& theta, double alpha) {
	VectorXd delta = VectorXd::Zero(feature_size);
	for (auto current_state : states) {
		double expected_return = 0.0;
		// compute bellman error for each state
		for (auto next_state : states) {
			if (next_state == lower_state) {
				expected_return += reward + gamma*theta.dot(features.row(next_state));
			}
		}
		double bellman_error = expected_return - theta.dot(features.row(current_state));
		delta += bellman_error*features.row(current_state);
	}
	
	theta += alpha / states.size()*delta;

}

int Baird::tdc(int state, VectorXd& theta, VectorXd& weight, double alpha, double beta) {
	int action = behaviorPolicy(state);
	int next_state = takeAction(state, action);
	double rho = 0.0;
	if (action == DASHED) rho = 0.0;
	else rho = 1.0 / behavior_solid_prob;
	double delta = reward + gamma*(features.row(next_state)*theta)(0, 0) - (features.row(state)*theta)(0, 0);
	theta += alpha * rho * (delta * features.row(state) - gamma * features.row(next_state)*(weight.dot(features.row(state))));
	weight += beta * rho * (delta - (features.row(state)*weight)(0, 0))*features.row(state);
	return next_state;
}

void Baird::expectedTDC(VectorXd& theta, VectorXd& weight, double alpha, double beta) {
	for (auto current_state : states) {
	/*
	 *When computing expected update target, if next state is not lower state, importance ratio will be 0,
	 * so we can safely ignore this case and assume next state is always lower state
	 */
		double delta = reward + gamma * (features.row(lower_state)*theta)(0, 0) - (features.row(current_state)*theta)(0, 0);
		double rho = 1.0 / behavior_solid_prob;

		VectorXd expected_update_theta = 1.0 / states.size() * behavior_solid_prob * rho * (delta * features.row(current_state) - gamma * (weight.dot(features.row(current_state))) * features.row(lower_state));
		theta += alpha*expected_update_theta;
		VectorXd expected_update_weight = 1.0 / states.size() * behavior_solid_prob * rho * (delta - (weight.dot(features.row(current_state)))) *features.row(current_state);
		weight += beta * expected_update_weight;
	}
}

double Baird::expectedEmphaticTD(VectorXd& theta, double emphasis, double alpha) {
	VectorXd expected_update = VectorXd::Zero(feature_size);
	double expected_next_emphasis = 0.0;
	double next_emphasis = 0.0;
	double rho = 0.0;
	for (auto state : states) {
		if (state == lower_state) {
			rho = 1.0 / behavior_solid_prob;
		}
		else {
			rho = 0.0;
		}

		next_emphasis = gamma*rho*emphasis + INTEREST;
		expected_next_emphasis += next_emphasis;

		/*
		*When computing expected update target, if next state is not lower state, importance ratio will be 0,
		* so we can safely ignore this case and assume next state is always lower state
		*/

		int next_state = lower_state;
		double delta = reward + gamma * theta.dot(features.row(next_state))- theta.dot(features.row(state));
		expected_update += 1.0 / states.size()*behavior_solid_prob*next_emphasis*1.0 / behavior_solid_prob*delta*features.row(state).transpose();
	}

	theta += alpha*expected_update;
	return expected_next_emphasis / states.size();

}


double Baird::compute_RMSE(VectorXd& theta) {
	VectorXd values = static_cast<VectorXd>(features*theta);
	double rmse = sqrt((values.cwiseAbs2()).dot(state_distribution));
	return rmse;
}

double Baird::compute_RMSE_BE(VectorXd& theta) {
	VectorXd bellman_error = VectorXd::Zero(states.size());
	for (auto state : states) {
		for (auto next_state : states) {
			if (next_state == lower_state) {
				bellman_error(state) += reward + gamma*theta.dot(features.row(next_state)) - theta.dot(features.row(state));
			}
		}
	}
	bellman_error = projection_matrix*bellman_error;
	double rmse = sqrt((bellman_error.cwiseAbs2()).dot(state_distribution));
	return rmse;
}