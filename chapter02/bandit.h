//
// Created by Kuilin Chen on 2018-07-10.
//

#ifndef CHAPTER02_BANDIT_H
#define CHAPTER02_BANDIT_H

#include <vector>
#include <random>
#include <cmath>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

using std::vector;
using std::string;


class Bandit {
protected:
    int k;      // number of arms
    double epsilon;     // probability for exploration
    double step_size;   // step size
    double initial;
    bool sample_averages;   // use sample averages to update estimations instead of constant step size
    vector<int> indices;
    int ucb_param;
    bool gradient;  // if true, use gradient based bandit algorithm
    bool gradient_baseline; // if true, use average reward for gradient base bandit algorithm
    double average_reward;
    double true_reward;
    int best_action;
    int time;
    vector<double> q_true;   // true reward for each action
    vector<double> q_est;   // estimation for each action
    vector<int> action_count;   // # of chosen times for each action
    vector<double> action_prob; // probability of taking each action

public:
    Bandit(int k_arm, double explore_rate, double init, double step, bool use_sample_avg,
           int ucb, bool g, bool g_bl, double true_r);
    int getAction();
    double takeAction(int action);
    int getBestAction();
    static int weight_random_choice(vector<int>& pool, vector<double>& prob);

};


#endif //CHAPTER02_BANDIT_H
