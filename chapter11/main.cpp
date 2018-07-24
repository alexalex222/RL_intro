#include <iostream>
#include <fstream>
#include "baird.h"
#include <Eigen/Dense>

using namespace Eigen;

// define the format you want, you only need one instance of this...
const static IOFormat CSVFormat(StreamPrecision, DontAlignCols, ", ", "\n");

void testSemiGradientOffPolicyTD() {
	Baird b;
	int feature_size_val = b.feature_size;	
	double alpha = 0.01;
	int steps = 1000;
	VectorXd theta = VectorXd::Constant(feature_size_val, 1);
	theta(6) = 10;	
	MatrixXd thetas = MatrixXd::Zero(feature_size_val, steps);
	
	int state = b.states[rand() % b.states.size()];
	for (int step = 0; step < steps; step++) {
		state = b.semiGradientOffPolicyTD(state, theta, alpha);
		thetas.col(step) = theta;
	}
	
	std::ofstream ofs("Semi_Gradient_Off_Policy_TD.csv");
	ofs << thetas.transpose().format(CSVFormat);
	ofs.close();
}

void testSemiGradientDP() {
	Baird b;
	int feature_size_val = b.feature_size;

	double alpha = 0.01;
	int steps = 1000;
	VectorXd theta = VectorXd::Constant(feature_size_val, 1);
	theta(6) = 10;
	MatrixXd thetas = MatrixXd::Zero(feature_size_val, steps);
	for (int step = 0; step < steps; step++) {
		b.semiiGradientDP(theta, alpha);
		thetas.col(step) = theta;
	}

	std::ofstream ofs("Semi_Gradient_DP.csv");
	ofs << thetas.transpose().format(CSVFormat);
	ofs.close();
}

void testTDC() {
	Baird b;
	int feature_size_val = b.feature_size;

	double alpha = 0.005;
	double beta = 0.05;
	int steps = 1000;
	VectorXd theta = VectorXd::Constant(feature_size_val, 1);
	theta(6) = 10;
	VectorXd weight = VectorXd::Zero(feature_size_val);
	MatrixXd thetas = MatrixXd::Zero(feature_size_val, steps);
	VectorXd rmsve = VectorXd::Zero(steps);
	VectorXd rmspbe = VectorXd::Zero(steps);

	int state = b.states[rand() % b.states.size()];
	for (int step = 0; step < steps; step++) {
		state = b.tdc(state, theta, weight, alpha, beta);
		thetas.col(step) = theta;
		rmsve(step) = b.compute_RMSE(theta);
		rmspbe(step) = b.compute_RMSE_BE(theta);
	}
	thetas.transposeInPlace();
	MatrixXd results(thetas.rows(), thetas.cols() + rmsve.cols() + rmspbe.cols());
	results << thetas, rmsve, rmspbe;

	std::ofstream ofs("tdc.csv");
	ofs << results.format(CSVFormat);
	ofs.close();
}

void testExpectedTDC() {
	Baird b;
	int feature_size_val = b.feature_size;

	double alpha = 0.005;
	double beta = 0.05;
	int steps = 1000;
	VectorXd theta = VectorXd::Constant(feature_size_val, 1);
	theta(6) = 10;
	VectorXd weight = VectorXd::Zero(feature_size_val);
	MatrixXd thetas = MatrixXd::Zero(feature_size_val, steps);
	VectorXd rmsve = VectorXd::Zero(steps);
	VectorXd rmspbe = VectorXd::Zero(steps);

	for (int step = 0; step < steps; step++) {
		b.expectedTDC(theta, weight, alpha, beta);
		thetas.col(step) = theta;
		rmsve(step) = b.compute_RMSE(theta);
		rmspbe(step) = b.compute_RMSE_BE(theta);
	}

	thetas.transposeInPlace();
	MatrixXd results(thetas.rows(), thetas.cols() + rmsve.cols() + rmspbe.cols());
	results << thetas, rmsve, rmspbe;

	std::ofstream ofs("expected_tdc.csv");
	ofs << results.format(CSVFormat);
	ofs.close();

}


void testExpectedEmphaticTD() {
	Baird b;
	int feature_size_val = b.feature_size;

	double alpha = 0.03;
	int steps = 1000;
	VectorXd theta = VectorXd::Constant(feature_size_val, 1);
	theta(6) = 10;
	MatrixXd thetas = MatrixXd::Zero(feature_size_val, steps);
	VectorXd rmsve = VectorXd::Zero(steps);
	

	double emphasis = 0.0;
	for (int step = 0; step < steps; step++) {
		emphasis = b.expectedEmphaticTD(theta, emphasis, alpha);
		thetas.col(step) = theta;
		rmsve(step) = b.compute_RMSE(theta);
		
	}

	thetas.transposeInPlace();
	MatrixXd results(thetas.rows(), thetas.cols() + rmsve.cols());
	results << thetas, rmsve;

	std::ofstream ofs("emphatic_td.csv");
	ofs << results.format(CSVFormat);
	ofs.close();

}

int main() {
	testSemiGradientOffPolicyTD();
	testSemiGradientDP();
	testTDC();
	testExpectedTDC();
	testExpectedEmphaticTD();

	std::string filename = "../plot_results.py";
	std::string command = "python ";
	command += filename;
	system(command.c_str());

	return 0;
}