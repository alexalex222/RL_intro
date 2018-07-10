//
// Created by Kuilin Chen on 2018-06-16.
//

#ifndef CHAPTER01_PLAYER_H
#define CHAPTER01_PLAYER_H


#include "gridstatus.h"
#include <vector>
#include <unordered_map>
#include <map>
#include <random>
#include <algorithm>
#include <fstream>
#include <string>

using std::vector;
using std::unordered_map;
using std::pair;
using std::multimap;

class Player {
protected:
    std::vector<GridStatus> allStates;
    std::unordered_map<int, double> estimations;
    double step_size;
    double explore_rate;
    vector<GridStatus> states;
    unordered_map<int, GridStatus> all_states;
    int symbol;

public:
    Player(double stepSize=0.1, double exploreRate=0.1);
    void reset();
    void setSymbol(int s);
    void feedState(GridStatus state);
    void feedReward(double reward);
    vector<int> takeAction();
    void savePolicy();
    void loadPolicy();
};


#endif //CHAPTER01_PLAYER_H
