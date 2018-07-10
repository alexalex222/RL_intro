//
// Created by Kuilin Chen on 2018-07-10.
//

#ifndef CHAPTER01_AI_PLAYER_H
#define CHAPTER01_AI_PLAYER_H

#include "player.h"


class AiPlayer: public Player {
protected:
    std::vector<GridStatus> allStates;
    std::unordered_map<int, double> estimations;
    vector<GridStatus> states;
    unordered_map<int, GridStatus> all_states;


public:
    AiPlayer(double stepSize=0.1, double exploreRate=0.1);
    void reset() override;
    void setSymbol(int s) override;
    void feedState(GridStatus state) override;
    void feedReward(double reward) override;
    vector<int> takeAction() override;
    void savePolicy();
    void loadPolicy();
};


#endif //CHAPTER01_AI_PLAYER_H
