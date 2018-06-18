//
// Created by Kuilin Chen on 2018-06-16.
//

#ifndef CHAPTER01_PLAYER_H
#define CHAPTER01_PLAYER_H


#include "gridstatus.h"
#include <vector>
#include <unordered_map>

class Player {
private:
    std::vector<GridStatus> allStates;
    std::unordered_map<int, int> estimations;
    double stepSize;
    double exploreRate;
    std::vector<GridStatus> states;
    int symbol;

public:
    Player(double stepSize=0.1, double exploreRate=0.1);
    void reset();
    void setSymbol();


};


#endif //CHAPTER01_PLAYER_H
