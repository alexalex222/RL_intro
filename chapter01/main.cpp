#include <iostream>
#include "gridstatus.h"
#include "player.h"
#include "human_player.h"
#include "judger.h"
#include "ai_player.h"

void train(int episodes=20000) {
    AiPlayer player1;
    AiPlayer player2;
    Judger judger(player1, player2);
    double player1_win = 0.0;
    double player2_win = 0.0;
    for (int i = 0; i < episodes; i++) {

        int winner = judger.play();
        if (winner == 1) player1_win = player1_win + 1.0;
        if (winner == -1) player2_win = player2_win + 1.0;
        judger.reset();
    }
    std::cout << "Training: " << std::endl;
    std::cout << "Player1 win probability: " << (player1_win/ static_cast<double>(episodes)) << std::endl;
    std::cout << "Player2 win probability: " << (player2_win/ static_cast<double>(episodes)) << std::endl;
    player1.savePolicy();
    player2.savePolicy();
}

void compete(int episodes=500) {
    AiPlayer player1(0.1, 0.0);
    AiPlayer player2(0.1, 0.0);
    Judger judger(player1, player2, false);
    player1.loadPolicy();
    player2.loadPolicy();
    double player1_win = 0.0;
    double player2_win = 0.0;
    for (int i = 0; i < episodes; i++) {
        int winner = judger.play();
        if (winner == 1) player1_win = player1_win + 1.0;
        if (winner == -1) player2_win = player2_win + 1.0;
        judger.reset();

    }
    std::cout << "AI competing: " << std::endl;
    std::cout << "Player1 win probability: " << (player1_win/ static_cast<double>(episodes)) << std::endl;
    std::cout << "Player2 win probability: " << (player2_win/ static_cast<double>(episodes)) << std::endl;
}

void user_play() {
    AiPlayer player1(0.1, 0.0);
    HumanPlayer player2(0.1, 0.1);
    Judger judger(player1, player2, false);
    player1.loadPolicy();
    int winner = judger.play(true);
    if (winner == player2.getSymbol()) std::cout << "Win" << std::endl;
    else if (winner == player1.getSymbol()) std::cout << "Lose" << std::endl;
    else std::cout << "Tie" << std::endl;
}

int main() {
    //train();
    //compete();
    user_play();
    return 0;
}