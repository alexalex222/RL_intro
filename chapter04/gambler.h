//
// Created by Kuilin Chen on 2018-06-17.
//

#ifndef CHAPTER04_GAMBLER_H
#define CHAPTER04_GAMBLER_H

#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>

using std::vector;

class Gambler {
private:
    int goal;
    double win_prob;
    vector<int> states;
    vector<int> policy;
    vector<int> all_actions;
    vector<double> state_values;

public:
    Gambler(int g = 100);
    void value_iteration(double tolerance=1e-9);
    void get_optimal_policy();
    void show();

};


#endif //CHAPTER04_GAMBLER_H
