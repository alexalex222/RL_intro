//
// Created by Kuilin Chen on 2018-06-18.
//

#include "gridworld.h"

GridWorld::GridWorld(int size) {
    this->world_size = size;
    this->action_prob = 0.25;
    this->state_action_reward = 0.0;
    this->special_reward.push_back(10.0);
    this->special_reward.push_back(5.0);
    this->discount = 0.9;
    this->actions.push_back('U');
    this->actions.push_back('D');
    this->actions.push_back('R');
    this->actions.push_back('L');
    this->state_values = vector<vector<double>>(this->world_size, vector<double>(this->world_size, 0));
    this->iteration = 0;

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            states.push_back(pair<int, int>(i, j));
        }
    }

    this->special_states.push_back(pair<int, int>(0, 1));
    this->special_states.push_back(pair<int, int>(0, 3));
    this->special_states_prime.push_back(pair<int, int>(4, 1));
    this->special_states_prime.push_back(pair<int, int>(2, 3));

}

pair<int, int> GridWorld::next_state(pair<int, int> state, char action) {
    int i = state.first;
    int j = state.second;

    for (int p = 0; p < this->special_states.size(); p++) {
        if (i == special_states[p].first && j == special_states[p].second) {
            this->state_action_reward = special_reward[p];
            return special_states_prime[p];
        }
    }

    if (i == 0 && action == 'U') {
        this->state_action_reward = -1.0;
        return state;
    }

    if (i == this->world_size - 1 && action == 'D') {
        this->state_action_reward = -1.0;
        return state;
    }
    if (j == 0 && action == 'L') {
        this->state_action_reward = -1.0;
        return state;
    }
    if (j == this->world_size - 1 && action == 'R') {
        this->state_action_reward = -1.0;
        return state;
    }

    this->state_action_reward = 0.0;
    if (action == 'U') return pair<int, int>(i - 1, j);
    else if (action == 'D') return pair<int, int>(i + 1, j);
    else if (action == 'R') return pair<int, int>(i, j+1);
    else if (action == 'L') return pair<int, int>(i, j - 1);

    return state;
}

void GridWorld::compute_state_values(double tolerance, bool in_place, bool optimal) {
    vector<vector<double>> new_state_values(this->world_size, vector<double>(this->world_size, 0.0));
    while (true) {

        // in_place update
        vector<vector<double>>* values = &(this->state_values);
        if (in_place) values = &new_state_values;

        for(vector<pair<int, int>>::iterator s = this->states.begin(); s != this->states.end(); s++) {
            int i = s->first;
            int j = s->second;
            double value = 0.0;
            double max_reward = -999.0;
            char optimal_action = 'U';
            for (vector<char>::iterator a = this->actions.begin(); a != this->actions.end(); a++) {
                pair<int, int> next_state = this->next_state(*s, *a);
                int ii = next_state.first;
                int jj = next_state.second;
                value += action_prob*(state_action_reward + discount*(*values)[ii][jj]);
                double r = state_action_reward + discount*(*values)[ii][jj];
                if (r > max_reward) {
                    max_reward = r;
                    optimal_action = *a;
                }
            }
            if (optimal) new_state_values[i][j] = max_reward;
            else new_state_values[i][j] = value;
        }

        // check convergence
        double e = 0;
        for (int i = 0; i < this->world_size; i++) {
            for (int j = 0; j < this->world_size; j++) {

                e += fabs(new_state_values[i][j] - this->state_values[i][j]);
            }
        }

        if (e < tolerance) {
            state_values = new_state_values;
            if(optimal) std::cout << "Optimal policy" << std::endl;
            else std::cout << "Random policy" << std::endl;
            this->print_state_values();
            break;
        }


        state_values = new_state_values;
        if (this->iteration <= 3) this->print_state_values();
        this->iteration++;
    }
}

void GridWorld::print_state_values() {
    std::cout.precision(2);
    std::cout << std::fixed;
    std::cout << "State values after " << this->iteration << " iterations. " << std::endl;
    for(int i = 0; i < this->world_size; i++) {
        for(int j = 0; j < this->world_size; j++) {
            std::cout <<  this->state_values[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

void GridWorld::write_results() {
    std::ofstream my_file;
    my_file.open ("state_values.csv");
    for (int i = 0; i < world_size; i++) {
        for (int j = 0; j < world_size; j++) {
            my_file << state_values[i][j];
            if (j != world_size - 1) my_file << ",";
        }
        my_file << "\n";
    }
}

void GridWorld::show_results() {
    write_results();

    std::string filename = "../plot_results.py";
    std::string command = "python ";
    command += filename;
    system(command.c_str());



}