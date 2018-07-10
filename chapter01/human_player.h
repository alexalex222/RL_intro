//
// Created by Kuilin Chen on 2018-07-07.
//

#ifndef CHAPTER01_HUMAN_PLAYER_H
#define CHAPTER01_HUMAN_PLAYER_H


#include "gridstatus.h"
#include <iostream>

class HumanPlayer {
private:
    double step_size;
    double explore_rate;
    GridStatus current_state;
    int symbol;

public:
    HumanPlayer(double s, double r);
    void reset();
    void setSymbol(int s);
    void feedState(GridStatus state);
    void feedReward(double reward);
    vector<int> takeAction();

};


#endif //CHAPTER01_HUMAN_PLAYER_H
