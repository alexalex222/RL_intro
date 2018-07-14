//
// Created by Kuilin Chen on 2018-07-13.
//

#ifndef CHAPTER09_AGGREG_VALUE_FUNCTION_H
#define CHAPTER09_AGGREG_VALUE_FUNCTION_H

#include "random_walk.h"
#include "value_function.h"

class AggregValueFunction: public ValueFunction {
private:
    int groups;
    int groups_size;
    vector<double> params;  // theta

public:
    AggregValueFunction(int group_num);

    // get state value
    double value(int state) override;

    /*
     update parameters
     @delta: step size * (target - old estimation)
     @state: state of current sample
     */
    void update(int state, double delta) override;
};


#endif //CHAPTER09_AGGREG_VALUE_FUNCTION_H
