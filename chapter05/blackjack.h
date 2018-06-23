//
// Created by Kuilin Chen on 2018-06-19.
//

#ifndef CHAPTER05_BLACKJACK_H
#define CHAPTER05_BLACKJACK_H

#include <vector>

using std::vector;
using std::pair;

struct State {
public:
    bool usable_ace;
    int player_sum;
    int dealer_card;

    State() {
        int numAce = 0;
        this->player_sum = 0;
        this->usable_ace = false;

        while (this->player_sum < 12) {
            int card = getCard();
            if (card == 1) {
                numAce++;
                card = 11;
                this->usable_ace = true;
            }
            this->player_sum += card;
        }

        // if player's sum is larger than 21, he must hold at least one Ace. Two Aces are possible.
        if (this->player_sum > 21) {
            // use the Ace as 1 rather than 11
            this->player_sum -= 10;

            // if the player only has one Ace, then he does not have usable Ace any more.
            if (numAce == 1) {
                this->usable_ace = false;
            }
        }

        this->dealer_card = getCard();
    }

    State(bool u, int s, int c) {
        usable_ace = u;
        player_sum = s;
        dealer_card = c;
    }

private:
    int getCard()
    {
        int card = std::rand()%13 + 1;
        card = std::min(card, 10);
        return card;
    }

};

class GameResult {
public:
    State final_state;
    int reward;
    vector<pair<State, int>> player_trajectory;

    GameResult(State s, int r, vector<pair<State, int>> traj) {
        final_state = s;
        reward = r;
        player_trajectory = traj;
    }
};

class BlackJack {
private:
    int hit;
    int strike;
    vector<int> actions;
    vector<int> policy_player;
    vector<int> policy_dealer;
    vector<vector<double>> states_value_usable_ace;
    vector<vector<double>> states_value_no_usable_ace;


public:
    BlackJack();
    int getCard();
    int target_policy_player(State s);
    int behavior_policy_player(State s);
    GameResult play(int policy_type, State init_state=State(), int init_action=2);
    void monte_carlo_on_policy(int n);
    void monte_carlo_es(int n);

};


#endif //CHAPTER05_BLACKJACK_H
