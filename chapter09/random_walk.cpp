//
// Created by Kuilin Chen on 2018-06-28.
//

#include "random_walk.h"


RandomWalk::RandomWalk(int n, int left_reward, int right_reward, double discount): action_left(-1), action_right(1) {
    this->n_states = n;
    this->start_state = (n + 1)/2;
    this->gamma = discount;
    this->step_range = 100;

    for (int i = 0; i <= n; i++) {
        this->states.push_back(i);
    }

    for (int i = (n+1)*left_reward; i <= (n+1)*right_reward; i = i + (right_reward - left_reward)) {
        this->real_state_values.push_back(static_cast<double>(i) / (n+1));
    }

    // use dynamic programming to calculate the true state values based on the initial guess above
    while (true) {
        old_state_values = real_state_values;
        for (int state = 1; state <= n; state++) {
            real_state_values[state] = 0.0;
            for (int action : actions) {
                for (int step = 1; step <= step_range; step++) {
                    step = step*action;
                    int new_state = state + step;
                    new_state = std::max(std::min(new_state, this->n_states+1), 0);
                    real_state_values[state] += 1.0/(2*step_range) * real_state_values[new_state];
                }
            }
        }
        double e = 0.0;
        for (size_t i = 0; i < real_state_values.size(); i++) {
            e += abs(real_state_values[i] - old_state_values[i]);
        }

        if (e < 1e-2) break;
    }

    // correct the state values for terminal states
    this->real_state_values.back() = 0.0;
    this->real_state_values[0] = 0.0;

    for (size_t t = 0; t < real_state_values.size(); t++) {
        std::cout << real_state_values[t] << std::endl;
    }

    this->end_states.push_back(0);
    this->end_states.push_back(n + 1);
}

pair<int, int> RandomWalk::takeAction(int state, int action) {
    int step = rand()%100 + 1;
    step = step*action;
    int new_state = state + step;
    new_state = std::max(std::min(new_state, this->n_states+1), 0);
    int reward = 0;
    if (new_state == 0) reward = -1;
    else if (new_state == this->n_states + 1) reward = 1;
    else reward = 0;

    return pair<int, int>(new_state, reward);
}

int RandomWalk::getAction() {
    if (rand()%2 == 1) return 1;
    return -1;
}

int RandomWalk::getSize() {
    return n_states;
}

vector<int> RandomWalk::getEndStates() {
    return end_states;
}

int RandomWalk::getStartState() {
    return start_state;
}