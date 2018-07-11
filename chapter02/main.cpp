#include <iostream>
#include "bandit.h"
#include "simulation.h"




int main() {
    epsilon_greedy(2000, 1000);
    opt_init_values(2000, 1000);
    ucb(2000, 1000);
    gradientBandit(2000, 1000);
    return 0;
}