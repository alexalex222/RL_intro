//
// Created by Kuilin Chen on 2018-07-13.
//

#ifndef CHAPTER09_VALUE_FUNCTION_H
#define CHAPTER09_VALUE_FUNCTION_H


#include "random_walk.h"

// base class for value function
class ValueFunction {
public:
    RandomWalk p;

    ValueFunction();

    // get the state value
    virtual double value(int state) = 0;

    /*
     update parameters
     @delta: step size * (target - old estimation)
     @state: state of current sample
     */
    virtual void update(int state, double delta) = 0;
};


#endif //CHAPTER09_VALUE_FUNCTION_H
