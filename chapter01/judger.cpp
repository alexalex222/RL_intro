//
// Created by Kuilin Chen on 2018-06-16.
//

#include "judger.h"

Judger::Judger(Player& player1, Player& player2, bool fb): p1(&player1), p2(&player2), feedback(fb), current_player(nullptr) {
    p1_symbol = 1;
    p2_symbol = -1;
    p1->setSymbol(p1_symbol);
    p2->setSymbol(p2_symbol);
    current_state = GridStatus();
    all_states = GridStatus::getAllStates(current_state);

}

void Judger::giveReward() {
    if (current_state.getWinner() == p1_symbol) {
        p1->feedReward(1);
        p2->feedReward(0);
    }
    else if (current_state.getWinner() == p2_symbol) {
        p1->feedReward(0);
        p2->feedReward(1);
    }
    else {
        p1->feedReward(0.5);
        p2->feedReward(0.5);
    }
}

void Judger::feedCurrentState() {
    p1->feedState(current_state);
    p2->feedState(current_state);
}

void Judger::reset() {
    p1->reset();
    p2->reset();
    current_state = GridStatus();
    current_player = nullptr;
}

int Judger::play(bool show) {
    this->reset();
    this->feedCurrentState();
    while (true) {
        if (current_player == p1) current_player = p2;
        else current_player = p1;
        if (show) current_state.show();
        vector<int> action = current_player->takeAction();
        int i = action[0];
        int j = action[1];
        int symbol = action [2];
        current_state = current_state.nextStatus(i, j, symbol);
        int hash_value = current_state.getHash();
        bool is_end = current_state.isEnd();
        //bool is_end = all_states[hash_value].isEnd();
        feedCurrentState();
        if (is_end) {
            if (feedback) {
                this->giveReward();
            }
            return current_state.getWinner();
        }
    }
}