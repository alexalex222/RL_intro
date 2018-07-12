//
// Created by Kuilin Chen on 2018-07-12.
//

#include "maze.h"

Maze::Maze(int height, int width, int factor): GridWorld(height, width) {
    start_state.push_back(std::make_pair<int, int>(2, 0));
    goal_state.push_back(std::make_pair<int, int>(0, 8));

    obstacles.push_back(std::make_pair<int, int>(1, 2));
    obstacles.push_back(std::make_pair<int, int>(2, 2));
    obstacles.push_back(std::make_pair<int, int>(3, 2));
    obstacles.push_back(std::make_pair<int, int>(0, 7));
    obstacles.push_back(std::make_pair<int, int>(1, 7));
    obstacles.push_back(std::make_pair<int, int>(2, 7));
    obstacles.push_back(std::make_pair<int, int>(4, 5));

    max_step = INT_MAX;
    if (factor == 1) resolution = 1;
    else {
        start_state = extend_state(start_state[0], factor);
        goal_state = extend_state(goal_state[0], factor);
        vector<pair<int, int>> new_obstacles_temp;
        for (auto ob : obstacles) {
            vector<pair<int, int>> extended_obstacles = extend_state(ob, factor);
            new_obstacles_temp.insert(new_obstacles_temp.end(), extended_obstacles.begin(), extended_obstacles.end());
        }
        obstacles = new_obstacles_temp;
        resolution = factor;
    }
}

vector<pair<int, int>> Maze::extend_state(pair<int, int> state, int factor) {
    vector<pair<int, int>> new_states;
    pair<int, int> new_state(state.first*factor, state.second*factor);
    for (int i = 0; i < factor; i++) {
        for (int j = 0; j < factor; j++) {
            new_states.push_back(std::make_pair<int, int>(new_state.first + i, new_state.second + j));
        }
    }
    return new_states;
}

pair<int, int> Maze::takeAction(pair<int, int> state, int action) {
    int i = state.first;
    int j = state.second;
    int ii = 0;
    int jj = 0;

    if (action == action_up) {
        ii = std::max(i - 1, 0);
        jj = j;
    }
    if (action == action_down) {
        ii = std::max(std::min(i + 1, world_height - 1), 0);
        jj = j;
    }
    if (action == action_left) {
        ii = std::max(i, 0);
        jj = std::max(j - 1, 0);
    }
    if (action == action_right) {
        ii = std::max(i, 0);
        jj = std::min(j + 1, world_width - 1);
    }
    pair<int, int> new_state(ii, jj);
    if (std::find(obstacles.begin(), obstacles.end(), new_state) != obstacles.end()) {
        new_state = state;
    }
    if (std::find(goal_state.begin(), goal_state.end(), new_state) != goal_state.end()) {
        this->current_reward = 1.0
    }
    else this->current_reward = 0.0;

}