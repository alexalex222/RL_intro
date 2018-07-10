//
// Created by Kuilin Chen on 2018-06-16.
//

#include "player.h"

Player::Player(double stepSize, double exploreRate) {
    this->step_size = stepSize;
    this->explore_rate = exploreRate;
    this->states = std::vector<GridStatus>();
    this->symbol = 0;
    GridStatus init_state;
    this->all_states = GridStatus::getAllStates(init_state);
}

void Player::reset() {
    this->states = std::vector<GridStatus>();
}

void Player::setSymbol(int s) {
    this->symbol = s;
    for (auto i = all_states.begin(); i != all_states.end(); i++) {
        int hash = i->first;
        GridStatus state = i->second;
        if (state.isEnd()) {
            if (state.getWinner() == this->symbol) {
                this->estimations[hash] = 1.0;
            }
            else {
                this->estimations[hash] = 0.0;
            }
        }
        else {
            this->estimations[hash] = 0.5;
        }
    }
}

void Player::feedState(GridStatus state) {
    this->states.push_back(state);
}

void Player::feedReward(double reward) {
    if (this->states.empty()) return;
    vector<int> hashes;
    for (auto state : this->states) {
        hashes.push_back(state.getHash());
    }
    double target = reward;
    for (int i = static_cast<int>(hashes.size()) - 1; i >= 0; i--) {
        double value = this->estimations[hashes[i]] + this->step_size*(target - this->estimations[hashes[i]]);
        this->estimations[hashes[i]] = value;
        target = value;
    }
    this->states.clear();
}

vector<int> Player::takeAction() {
    vector<int> action; // i, j, symbol
    GridStatus state = states.back();
    vector<int> next_states;
    vector<pair<int, int>> next_positions;
    for (int i = 0; i < state.getRow(); i++) {
        for (int j = 0; j < state.getCol(); j++) {
            if (state.getData()[i][j] == 0) {
                next_positions.emplace_back(std::make_pair(i, j));
                next_states.push_back(state.nextStatus(i, j, this->symbol).getHash());
            }
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::binomial_distribution<int> binomial(1, this->explore_rate);
    if (binomial(gen) == 1) {
        std::shuffle(next_positions.begin(), next_positions.end(), gen);
        this->states.clear();
        action.push_back(next_positions[0].first);
        action.push_back(next_positions[0].second);
        action.push_back(this->symbol);
        return action;
    }


    multimap<double, pair<int, int>, std::greater<int>> values;
    for (size_t i = 0; i < next_states.size(); i++) {
        std::cout << next_states[i] << " " <<  this->estimations[next_states[i]] << std::endl;
        values.emplace(this->estimations[next_states[i]], next_positions[i]);
    }
    auto it = values.begin();
    action.push_back(it->second.first);
    action.push_back(it->second.second);
    action.push_back(this->symbol);
    return action;
}

void Player::savePolicy() {
    std::ofstream ofs("optimal_policy_" + std::to_string(this->symbol) + ".csv");
    for (auto it = this->estimations.begin(); it != estimations.end(); it++) {
        int hash = it->first;
        double reward = it->second;
        ofs << hash << " " << reward << "\n";
    }
    ofs.close();
}

void Player::loadPolicy() {
    std::ifstream ifs("optimal_policy_" + std::to_string(this->symbol) + ".csv");
    int hash;
    double reward;
    while (ifs >> hash >> reward) {
        this->estimations[hash] = reward;
    }
    ifs.close();
}