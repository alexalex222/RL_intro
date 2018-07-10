#include <iostream>
#include "gridstatus.h"
#include "player.h"
#include "human_player.h"
#include "judger.h"

void train(int episodes=20000) {
    Player player1;
    Player player2;
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
    Player player1(0.0);
    Player player2(0.0);
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


int main() {
    train();
    compete();
    return 0;
}