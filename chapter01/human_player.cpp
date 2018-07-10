//
// Created by Kuilin Chen on 2018-07-07.
//

#include "human_player.h"

HumanPlayer::HumanPlayer(double s, double r):Player(s, r) {}

void HumanPlayer::reset() {}

void HumanPlayer::setSymbol(int s) {
    this->symbol = s;
}

void HumanPlayer::feedState(GridStatus state) {
    this->current_state = state;
}

void HumanPlayer::feedReward(double reward) {}

vector<int> HumanPlayer::takeAction() {
    std::cout << "Input your position:" << std::endl;
    int pos;
    std::cin >> pos;
    pos--;
    int i = pos/(this->current_state.getCol());
    int j = pos%(this->current_state.getRow());
    if (this->current_state.getData()[i][j] != 0) {
        return this->takeAction();
    }
    return vector<int> {i, j, this->symbol};
}