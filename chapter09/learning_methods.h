//
// Created by Kuilin Chen on 2018-07-13.
//

#ifndef CHAPTER09_LEARNING_METHODS_H
#define CHAPTER09_LEARNING_METHODS_H

#include "random_walk.h"
#include "value_function.h"
#include "aggreg_value_function.h"
#include "tilings_value_function.h"
#include "basis_value_function.h"
#include "square_wave_value_function.h"
#include <memory>

using std::unique_ptr;
using std::shared_ptr;

 /// Gradient Monte Carlo method
 /// \param vf : pointer of class ValueFunction
 /// \param alpha : step size
 /// \param distribution : array to store the distribution statistics
void gradientMonteCarlo(unique_ptr<ValueFunction>& vf, double alpha, unique_ptr<vector<double>>& distribution) {
    int current_state =vf->p.getStartState();
    vector<int> trajectory;
    trajectory.push_back(current_state);


    int reward = 0;
    while (!(vf->p.isTerminal(current_state))) {
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


/// Semi-Gradient Temporal Difference method
/// \param vf : a pointer to class ValueFunciton
/// \param alpha : step size
/// \param n : # of step
void semiGradientTemporalDifference(unique_ptr<ValueFunction>& vf, double alpha, int n) {
    int current_state =vf->p.getStartState();
    vector<int> trajectory;
    trajectory.push_back(current_state);
    int reward = 0;
    vector<int> rewards;
    rewards.push_back(0);

    int step = 0;   ///< track time
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

            /// add state value to the return
            if (update_time + n <= final_step) {
                returns += vf->value(trajectory[update_time + n]);
            }
            int state_to_update = trajectory[update_time];
            /// update the value function
            if (std::find(end_states.begin(), end_states.end(), current_state) == end_states.end()) {
                double delta = alpha * (returns - vf->value(state_to_update));
                vf->update(state_to_update, delta);
            }
        }

        if (update_time == final_step - 1) break;

        current_state = new_state;

    }

}

void approximate (vector<pair<double, double>> samples, SquareWaveValueFunction& vf) {
    for (auto sample : samples) {
        double x = sample.first;
        double y = sample.second;
        double delta = y - vf.value(x);
        vf.update(delta, x);
    }
}

int squareWave(double x) {
    if (x > 0.5 && x < 1.5) return 1;
    else return 0;
}

vector<std::pair<double, double>> gen_sample(int n) {
    vector<std::pair<double, double>> samples;
    for (int i = 0; i < n; i++) {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<double > dis(0.0, 2.0);
        double x = dis(gen);
        double y = squareWave(x);
        samples.emplace_back(std::make_pair(x, y));
    }
    return samples;
}

#endif //CHAPTER09_LEARNING_METHODS_H
