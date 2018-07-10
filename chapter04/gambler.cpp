//
// Created by Kuilin Chen on 2018-06-17.
//

#include "gambler.h"

Gambler::Gambler(int g) {
    this->goal = g;
    this->win_prob = 0.4;
    this->states = vector<int>(this->goal + 1, 0);
    this->all_actions = vector<int>(this->goal + 1, 0);
    for (int i = 0; i <= this->goal; i++) {
        this->states[i] = i;
        this->all_actions[i] = i;
    }
    this->policy = vector<int>(this->goal + 1, 0);

    this->state_values = vector<double>(this->goal + 1, 0.0);
    this->state_values[this->goal] = 1.0;
}

void Gambler::value_iteration(double tolerance) {
    while (true) {
        double delta = 0.0;
        for (int s = 1; s <= this->goal; s++) {
            int state = this->states[s];
            auto first = this->all_actions.begin();
            auto last = this->all_actions.begin() + std::min(state, this->goal - state) + 1;
            vector<int> actions = vector<int>(first, last);
            vector<double> action_rewards;
            for(auto action : actions) {
                double r = win_prob * state_values[state + action] + (1 - win_prob) * state_values[state - action];
                action_rewards.push_back(r);
            }
            double new_state_value = *std::max_element(std::begin(action_rewards), std::end(action_rewards));
            delta += fabs(state_values[state] - new_state_value);
            state_values[state] = new_state_value;
        }

        if (delta < tolerance) break;
    }
}

void Gambler::get_optimal_policy() {
    this->value_iteration();
    for (int s = 1; s <= this->goal; s++) {
        int state = this->states[s];
        auto first = this->all_actions.begin();
        auto last = this->all_actions.begin() + std::min(state, this->goal - state) + 1;
        vector<int> actions = vector<int>(first, last);
        double max_reward = 0;
        int optimal_action = 0;
        for(auto action : actions) {
            double r = win_prob * state_values[state + action] + (1 - win_prob) * state_values[state - action];
            if (r > max_reward) {
                max_reward = r;
                optimal_action = action;
            }
        }
        policy[state] = optimal_action;
    }
}

void Gambler::show() {
    std::ofstream my_file;
    my_file.open ("state_values.csv");
    std::cout.precision(2);
    std::cout << std::fixed;
    std::cout << "state values: " << std::endl;
    for (int i = 1; i <= this->goal; i++) {
        my_file << state_values[i];
        if (i != this->goal) my_file << "\n";
        std::cout << this->state_values[i] << "\t";
        if (i % 10 == 0) std::cout << std::endl;
    }
    my_file.close();


    my_file.open ("optimal_policy.csv");
    std::cout << "optimal policy" << std::endl;
    for (int i = 1; i <= this->goal; i++) {
        my_file << policy[i];
        if (i != this->goal) my_file << "\n";
        std::cout << this->policy[i] << "\t";
        if (i % 10 == 0) std::cout << std::endl;
    }
    my_file.close();

    std::string filename = "../plot_results.py";
    std::string command = "python ";
    command += filename;
    system(command.c_str());
}