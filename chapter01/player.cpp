//
// Created by Kuilin Chen on 2018-06-16.
//

#include "player.h"

Player::Player(double setupSize, double exploreRate) {
    this->stepSize = setupSize;
    this->exploreRate = exploreRate;
    this->states = std::vector<GridStatus>();
    this->symbol = 0;
}

void Player::reset() {
    this->states = std::vector<GridStatus>();
}