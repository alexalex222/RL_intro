//
// Created by Kuilin Chen on 2018-07-12.
//

#ifndef CHAPTER08_DYNA_PARAMS_H
#define CHAPTER08_DYNA_PARAMS_H

#include <vector>
#include <string>

using std::vector;
using std::string;

struct DynaParams {
public:
    double gmma; // discount
    double epsilon; // probability for exploration
    double alpha;   // step size
    double time_weight; // weight for elapsed time
    int planning_step;  // planning step
    int runs;   // average of # of independent runs
    string methods[2];
    double theta;   // threshold for probability queue

    DynaParams() {
        gmma = 0.95;
        epsilon = 0.1;
        alpha = 0.1;
        time_weight = 0.0;
        planning_step = 5;
        runs = 10;
        methods[0] = "Dyna-Q";
        methods[1] = "Dyna-Q+";
        theta = 0.0;
    }
};

#endif //CHAPTER08_DYNA_PARAMS_H
