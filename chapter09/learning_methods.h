//
// Created by Kuilin Chen on 2018-07-13.
//

#ifndef CHAPTER09_LEARNING_METHODS_H
#define CHAPTER09_LEARNING_METHODS_H

#include "random_walk.h"
#include "value_function.h"
#include "aggreg_value_function.h"
#include "tilings_value_function.h"
#include "bases_value_function.h"

/*
 * gradient Monte Carlo algorithm
 * @vf: an instance of class ValueFunction
 * @alpha: step size
 * @distribution: array to store the distribution statistics
 */
void gradientMonteCarlo(ValueFunction* vf, double alpha, vector<double>* distribution = nullptr) {
    int current_state =vf->p.getStartState();
    vector<int> trajectory;
    trajectory.push_back(current_state);

    vector<int> end_states = vf->p.getEndStates();
    int reward = 0;
    while (std::find(end_states.begin(), end_states.end(), current_state) == end_states.end()) {
        int action = vf->p.getAction();
        pair<int, int> result = vf->p.takeAction(current_state, action);
        int new_state = result.first;
        reward = result.second;
        trajectory.push_back(new_state);
        current_state = new_state;
    }

    for (size_t i = 0; i < trajectory.size() - 1; i++) {
        int state = trajectory[i];
        double delta = alpha * (reward - vf->value(state));
        vf->update(state, delta);
        if (distribution != nullptr) {
            distribution->at(static_cast<unsigned long>(state)) += 1.0;
        }
    }

}

/*
 * semi-gradient n-step TD algorithm
 * @valueFunction: an instance of class ValueFunction
 * @n: # of steps
 * @alpha: step size
 */
void semiGradientTemporalDifference(ValueFunction* vf, int alpha, int n) {
    int current_state =vf->p.getStartState();
    vector<int> trajectory;
    trajectory.push_back(current_state);
    int reward = 0;
    vector<int> rewards;
    rewards.push_back(0);

    // track time
    int step = 0;
    int final_step = INT_MAX;

    vector<int> end_states = vf->p.getEndStates();
    int new_state = 0;
    while (true) {
        step++;
        if (step < final_step) {
            int action = vf->p.getAction();
            pair<int, int> result = vf->p.takeAction(current_state, action);
            new_state = result.first;
            reward = result.second;
            trajectory.push_back(new_state);
            rewards.push_back(reward);


            if (std::find(end_states.begin(), end_states.end(), current_state) != end_states.end()) {
                final_step = step;
            }
        }

        int update_time = step - n;
        if (update_time > 0) {
            double returns = 0.0;
            for (int t = update_time + 1; t < std::min(final_step, update_time + n) + 1; t++) {
                returns += rewards[t];
            }

            // add state value to the return
            if (update_time + n <= final_step) {
                returns += vf->value(trajectory[update_time + n]);
            }
            int state_to_update = trajectory[update_time];
            // update the value function
            if (std::find(end_states.begin(), end_states.end(), current_state) == end_states.end()) {
                double delta = alpha * (returns - vf->value(state_to_update));
                vf->update(state_to_update, delta);
            }
        }

        if (update_time == final_step - 1) break;

        current_state = new_state;

    }

}

#endif //CHAPTER09_LEARNING_METHODS_H
