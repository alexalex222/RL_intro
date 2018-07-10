//
// Created by Kuilin Chen on 2018-07-07.
//

#ifndef CHAPTER01_HUMAN_PLAYER_H
#define CHAPTER01_HUMAN_PLAYER_H


#include "gridstatus.h"
#include "player.h"
#include <iostream>

class HumanPlayer: public Player {
public:
    HumanPlayer(double s, double r);
    void reset() override;
    void setSymbol(int s) override;
    void feedState(GridStatus state) override;
    void feedReward(double reward) override ;
    vector<int> takeAction() override;

};


#endif //CHAPTER01_HUMAN_PLAYER_H
