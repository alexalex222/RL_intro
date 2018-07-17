//
// Created by Kuilin Chen on 2018-07-13.
//

#ifndef CHAPTER09_BASES_VALUE_FUNCTION_H
#define CHAPTER09_BASES_VALUE_FUNCTION_H

#include <cmath>
#include "random_walk.h"
#include "value_function.h"

#define POLYNOMIAL_BASES 0
#define FOURIER_BASES 1

// a wrapper class for polynomial / Fourier -based value function
class BasisValueFunction: public ValueFunction {
private:
    unsigned long order;
    vector<double> params;
    std::vector<std::function<double(double)>> bases;

public:
    ///
    /// \param ord: # of bases, each function also has one more constant parameter (called bias in machine learning)
    /// \param type: polynomial basis or Fourier basis
    explicit BasisValueFunction(unsigned long ord, int type);

    ///
    /// \param state: the state of random walk
    /// \return state value
    double value(int state) override;

    ///
    /// \param state: the state of random walk
    /// \param delta: step size * (target - old estimation)
    void update(int state, double delta) override;

};


#endif //CHAPTER09_BASES_VALUE_FUNCTION_H
