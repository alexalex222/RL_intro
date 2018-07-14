#include <iostream>
#include "learning_methods.h"

void testMonteCarlo() {
    int episodes = 1e5;
    double alpha = 2e-5;

    // we have 10 aggregations in this example, each has 100 states
    ValueFunction* vf = new AggregValueFunction(10);
    vector<double>* distribution = new vector<double >(1000+2, 0.0);
    for (int e = 0; e < episodes; e++) {
        std::cout << "Episode: " << e << std::endl;
        gradientMonteCarlo(vf, alpha, distribution);
    }

    double sum = 0.0;
    for (auto it = distribution->begin(); it != distribution->end(); it++) {
        sum += *it;
    }
    for (auto it = distribution->begin(); it != distribution->end(); it++) {
        *it = *it/sum;
    }

    vector<double> state_values;

}

int main() {

    return 0;
}