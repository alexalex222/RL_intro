//
// Created by Kuilin Chen on 2018-07-13.
//

#include "aggreg_value_function.h"

AggregValueFunction::AggregValueFunction(int group_num) {
    this->groups = group_num;
    this->groups_size = p.getSize()/group_num;
    this->params = vector<double>(group_num, 0.0);
}

AggregValueFunction::~AggregValueFunction() {
    std::cout << "Destroy AggregValueFunction" << std::endl;
}

double AggregValueFunction::value(int state) {
    vector<int> end_states = p.getEndStates();
    if(std::find(end_states.begin(), end_states.end(), state) != end_states.end()) {
        return 0.0;
    }
    unsigned int group_index = (state - 1) / groups_size;
    return params[group_index];
}

void AggregValueFunction::update(int state, double delta) {
    unsigned int group_index = (state - 1)/groups_size;
    params[group_index] = params[group_index] + delta;
}