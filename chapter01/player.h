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
    double step_size;
    double explore_rate;
    GridStatus current_state;
    int symbol;
public:
    Player(double s, double r);
    virtual void reset() = 0;   // pure virtual function
    virtual void setSymbol(int s);
    virtual void feedState(GridStatus state) = 0;   //pure virtual function
    virtual void feedReward(double reward) = 0; //pure virtual function
    virtual vector<int> takeAction() = 0;   // pure virtual function
    int getSymbol();
};




#endif //CHAPTER01_PLAYER_H
