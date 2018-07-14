//
// Created by Kuilin Chen on 2018-07-13.
//

#include "bases_value_function.h"

BasesValueFunction::BasesValueFunction(unsigned long ord, int type) {
    order = ord;
    params = vector<double>(order + 1, 0.0);
    if (type == POLYNOMIAL_BASES) {
        for (int i = 0; i <= order; i++) {
            bases.emplace_back([i](double s) {return std::pow(s, i);});
        }
    }
    else if (type == FOURIER_BASES) {
        for (int i = 0; i <= order; i++) {
            bases.emplace_back([i](double s) {return std::cos(3.1415926*i*s);});
        }
    }
}

double BasesValueFunction::value(int state) {
    // map the state into [0, 1]
    double s = static_cast<double>(state)/ static_cast<double>(p.getSize());
    double value = 0.0;
    for (int i = 0; i <= order; i++) {
        value += bases[i](s)*params[i];
    }
    return value;
}

void BasesValueFunction::update(int state, double delta) {
    // map the state into [0, 1]
    double s = static_cast<double>(state)/ static_cast<double>(p.getSize());
    for (int i = 0; i <= order; i++) {
        params[i] += bases[i](s)*delta;
    }
}