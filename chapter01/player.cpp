//
// Created by Kuilin Chen on 2018-06-16.
//

#include "player.h"

Player::Player(double s, double r):step_size(s), explore_rate(r) {}


void Player::setSymbol(int s) {
    symbol = s;
}

int Player::getSymbol() {
    return symbol;
}

