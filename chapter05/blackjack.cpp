//
// Created by Kuilin Chen on 2018-06-19.
//

#include "blackjack.h"

BlackJack::BlackJack() {
    hit = 0;
    strike = 1;
    actions.push_back(hit);
    actions.push_back(strike);
    policy_player = vector<int>(22, 0);
    for (int i = 12; i < 20; i++) policy_player[i] = hit;
    policy_player[20] = strike;
    policy_player[21] = strike;

    policy_dealer = vector<int>(22, 0);
    for (int i = 12; i < 17; i++) policy_dealer[i] = hit;
    for (int i = 17; i < 22; i++) policy_dealer[i] = strike;

    states_value_usable_ace = vector<vector<double>>(10, vector<double>(10, 0.0));
    states_value_no_usable_ace = vector<vector<double>>(10, vector<double>(10, 0.0));
}

int BlackJack::getCard() {
    int card = std::rand()%13 + 1;
    card = std::min(card, 10);
    return card;
}

int BlackJack::target_policy_player(State s) {
    return this->policy_player[s.player_sum];
}

int BlackJack::behavior_policy_player(State s) {
    int usable_ace = s.usable_ace;
}



GameResult BlackJack::play(int policy_type, State init_state, int init_action) {
    int action = 0;
    vector<pair<State, int>> player_trajectory;
    bool usable_ace_player = init_state.usable_ace;
    int player_sum = init_state.player_sum;
    int dealer_card1 = init_state.dealer_card;
    int dealer_card2 = getCard();

    State s = init_state;

    // dealer sum and usable Ace
    bool usable_ace_dealer = false;
    int dealer_sum = 0;
    if ((dealer_card1 == 1) && (dealer_card2 != 1)) {
        dealer_sum = dealer_sum + 11 + dealer_card2;
        usable_ace_dealer = true;
    }
    else if ((dealer_card1 != 1) && (dealer_card2 == 1)) {
        dealer_sum = dealer_sum + 11 + dealer_card1;
        usable_ace_dealer = true;
    }
    else if ((dealer_card1 == 1) && (dealer_card2 == 1)) {
        dealer_sum += 12;
        usable_ace_dealer = true;
    }
    else {
        dealer_sum = dealer_sum + dealer_card1 + dealer_card2;
    }

    // player's turn
    while (true) {
        if (init_action <= 1) {
            action = init_action;
            init_action = 2;
        }
        else {
            // get action based on current sum
            if (policy_type == 1) {
                action = policy_player[s.player_sum];
            }
            else {
                if (std::rand()%2) action = strike;
                else action = hit;
            }
        }

        // track player's trajectory for importance sampling
        player_trajectory.emplace_back(std::make_pair(s, action));

        if (action == this->strike) {
            break;
        }
        else {
            // if hit, get a new card
            player_sum += getCard();

            // player busts
            if (player_sum > 21) {
                if (usable_ace_player) {
                    player_sum -= 10;
                    usable_ace_player = false;
                }
                else {
                    // otherwise, player loses
                    return GameResult(s, -1, player_trajectory);
                }
            }
        }
    }

    // dealer's turn
    while (true) {
        action = this->policy_dealer[dealer_sum];
        if (action == this->strike) {
            break;
        }

        // if hit, get a new card
        int new_card = getCard();
        if (new_card == 1 && dealer_sum + 11 < 21) {
            dealer_sum += 11;
            usable_ace_dealer = true;
        }
        else {
            dealer_sum += new_card;
        }

        if (dealer_sum > 21) {
            if (usable_ace_dealer) {
                dealer_sum -= 10;
                usable_ace_dealer = false;
            }
            else {
                // otherwise, dealer loses
                return GameResult(s, 1, player_trajectory);
            }
        }
    }

    // no one gets 21, compare the sum
    if (player_sum > dealer_sum) {
        // player wins
        return GameResult(s, 1, player_trajectory);
    }
    else if (player_sum == dealer_sum) {
        // tie
        return GameResult(s, 0, player_trajectory);
    }
    else {
        // dealer wins
        return GameResult(s, 0, player_trajectory);
    }
}

void BlackJack::monte_carlo_on_policy(int n) {
    vector<vector<double>> states_usable_ace(10, vector<double>(10, 0));
    vector<vector<double>> states_usable_ace_count(10, vector<double>(10, 1.0));
    vector<vector<double>> states_no_usable_ace(10, vector<double>(10, 0));
    vector<vector<double>> states_no_usable_ace_count(10, vector<double>(10, 1.0));

    for (int i = 0; i < n; i++) {
        GameResult gr = play(1);
        for (auto t : gr.player_trajectory) {
            int player_sum = t.first.player_sum;
            player_sum -= 12;
            int dealer_card = t.first.dealer_card;
            dealer_card -= 1;
            if (t.first.usable_ace) {
                states_usable_ace_count[player_sum][dealer_card] += 1;
                states_usable_ace[player_sum][dealer_card] += gr.reward;
            }
            else {
                states_no_usable_ace_count[player_sum][dealer_card] += 1;
                states_no_usable_ace[player_sum][dealer_card] += gr.reward;
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            this->states_value_no_usable_ace[i][j] = states_usable_ace[i][j]/states_usable_ace_count[i][j];
            this->states_value_no_usable_ace[i][j] = states_no_usable_ace[i][j]/states_no_usable_ace_count[i][j];
        }
    }
}

void BlackJack::monte_carlo_es(int n) {
    // player_sum, dealer_card, usable_ace, action
    double state_action_tot_reward[10][10][2][2];
    double state_action_count[10][10][2][2];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 2; l++) {
                    state_action_count[i][j][k][l] = 1.0;
                    state_action_tot_reward[i][j][k][l] = 0.0;
                }
            }
        }
    }


}