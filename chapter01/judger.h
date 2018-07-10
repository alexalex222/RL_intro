//
// Created by Kuilin Chen on 2018-06-16.
//
#pragma once

#include <vector>
#include <unordered_map>
#include "player.h"
#include "gridstatus.h"

using std::vector;
using std::unordered_map;


class Judger
{
private:
    Player* p1;
    Player* p2;
    bool feedback;
    Player* current_player;
    int p1_symbol;
    int p2_symbol;
    GridStatus current_state;
    unordered_map<int, GridStatus> all_states;

public:
    Judger(Player& player1, Player& player2, bool fb=true);
    void giveReward();
    void feedCurrentState();
    void reset();
    int play(bool show=false);

};

