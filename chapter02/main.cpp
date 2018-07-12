#include <iostream>
#include <string>
#include "bandit.h"
#include "simulation.h"



int main() {
    epsilon_greedy(2000, 1000);
    opt_init_values(2000, 1000);
    ucb(2000, 1000);
    gradientBandit(2000, 1000);

    std::string filename = "../plot_results.py";
    std::string command = "python ";
    command += filename;
    system((command + " epsilon_greedy  opt_init  ucb gradient").c_str());
    return 0;
}