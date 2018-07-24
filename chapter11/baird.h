#pragma once

#include <vector>
#include <iostream>
#include <random>
#include <Eigen/Dense>

using std::vector;
using namespace Eigen;

#define DASHED 0
#define	SOLID 1
#define INTEREST 1

class Baird {
public:
	vector<int> states;	///<all states state 0-5 are upper states>
	int lower_state;	///< lower state (6)
	double gamma;		///< discount

	double behavior_solid_prob;

	int feature_size;	///< each state is represented by a vector of feature_size
	MatrixXd features;	///< feature parameters
	double reward;
	vector<int> actions;

	VectorXd state_distribution;
	MatrixXd state_distribution_matrix;
	MatrixXd projection_matrix;


	Baird(int num_states = 7, int lower_state_val = 6, double discount = 0.99, int feature_size_val = 8, double reward_val = 0.0);

	int takeAction(int state, int action);

	int targetPolicy(int state);

	int behaviorPolicy(int state);

	int semiGradientOffPolicyTD(int state, VectorXd& theta, double alpha);

	void semiiGradientDP(VectorXd& theta, double alpha);

	int tdc(int state, VectorXd& theta, VectorXd& weight, double alpha, double beta);

	void expectedTDC(VectorXd& theta, VectorXd& weight, double alpha, double beta);

	double expectedEmphaticTD(VectorXd& theta, double emphasis, double alpha);

	double compute_RMSE(VectorXd& theta);

	double compute_RMSE_BE(VectorXd& theta);

};