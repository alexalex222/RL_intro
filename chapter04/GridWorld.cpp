//
// Created by Kuilin Chen on 2018-06-16.
//

#include "GridWorld.h"

GridWorld::GridWorld(int size) {
    this->world_size = size;
    this->action_prob = 0.25;
    this->reward = -1;
    this->actions.push_back('U');
    this->actions.push_back('D');
    this->actions.push_back('R');
    this->actions.push_back('L');
    this->state_values = vector<vector<double>>(this->world_size, vector<double>(this->world_size, 0));
    this->iteration = 0;

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if ((i == 0 && j == 0) || (i == size - 1 && j == size - 1)) continue;
            states.push_back(pair<int, int>(i, j));
        }
    }
}

pair<int, int> GridWorld::next_state(pair<int, int> state, char action) {
    int i = state.first;
    int j = state.second;

    if (i == 0 && action == 'U') return state;
    if (i == this->world_size - 1 && action == 'D') return state;
    if (j == 0 && action == 'L') return state;
    if (j == this->world_size - 1 && action == 'R') return state;

    if (action == 'U') return pair<int, int>(i - 1, j);

    else if (action == 'D') return pair<int, int>(i + 1, j);
    else if (action == 'R') return pair<int, int>(i, j+1);
    else if (action == 'L') return pair<int, int>(i, j - 1);

    return state;
}

void GridWorld::compute_state_values(double tolerance, bool in_place) {
    vector<vector<double>> new_state_values(this->world_size, vector<double>(this->world_size, 0.0));
    while (true) {
        vector<vector<double>>* values = &(this->state_values);
        if (in_place) values = &new_state_values;


        for(vector<pair<int, int>>::iterator s = this->states.begin(); s != this->states.end(); s++) {
            int i = s->first;
            int j = s->second;
            double value = 0;
            for (vector<char>::iterator a = this->actions.begin(); a != this->actions.end(); a++) {
                pair<int, int> next_state = this->next_state(*s, *a);
                value += this->action_prob*(this->reward + (*values)[next_state.first][next_state.second]);
            }
            new_state_values[i][j] = value;
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
    std::cout << "State values under random policy after " << this->iteration << " iterations. " << std::endl;
    for(int i = 0; i < this->world_size; i++) {
        for(int j = 0; j < this->world_size; j++) {
            std::cout <<  this->state_values[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

int GridWorld::get_iteration() {
    return this->iteration;
}