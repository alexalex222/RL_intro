//
// Created by Kuilin Chen on 2018-06-23.
//

#pragma once

#include <random>
#include <vector>
#include <math.h>
#include <iostream>
#include <chrono>

#define ACTION_BACK 0
#define ACTION_END 1

using std::vector;

int behavior_policy() {
    // construct a trivial random generator engine from a time-based seed:
    unsigned seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    std::default_random_engine generator(seed);
    std::binomial_distribution<int> distribution(1,0.5);
    int action = distribution(generator);
    return action;
}

int target_policy() {
    return ACTION_BACK;
}

int play(vector<int>& trajectory) {
    // construct a trivial random generator engine from a time-based seed:
    unsigned seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    std::default_random_engine generator(seed);
    std::binomial_distribution<int> distribution(1,0.9);
    while (true) {
        int action = behavior_policy();
        trajectory.push_back(action);
        if (action == ACTION_END) return 0;
        if (distribution(generator) == 0) return 1;
    }
}

void monte_carlo_sample() {
    int runs = 10;
    int episodes = 100000;
    for (int run = 0; run < runs; run++) {
        std::cout << "Current run: " << run + 1 << std::endl;
        vector<double> sum_rewards(1, 0.0);
        vector<double> estimation;
        double importance_ratio;
        for (int episode = 0; episode < episodes; episode++) {
            vector<int> trajectory;
            int reward = play(trajectory);
            if (trajectory.back() == ACTION_END) importance_ratio = 0.0;
            else importance_ratio = 1.0/(pow(0.5, static_cast<double>(trajectory.size())));
            estimation.push_back((sum_rewards.back() + importance_ratio*reward)/(episode + 1));
            sum_rewards.push_back(sum_rewards.back() + importance_ratio*reward);

            if (episode+1 == 1) std::cout << "Estimation: " << estimation.back() << std::endl;
            //if (episode+1 == 1) std::cout << "Total reward: " << sum_rewards.back() << std::endl;
            if (episode+1 == 10) std::cout << "Estimation: " << estimation.back() << std::endl;
            //if (episode+1 == 10) std::cout << "Total reward: " << sum_rewards.back() << std::endl;
            if (episode+1 == 100) std::cout << "Estimation: " << estimation.back() << std::endl;
            //if (episode+1 == 100) std::cout << "Total reward: " << sum_rewards.back() << std::endl;
            if (episode+1 == 1000) std::cout << "Estimation: " << estimation.back() << std::endl;
            //if (episode+1 == 1000) std::cout << "Total reward: " << sum_rewards.back() << std::endl;
            if (episode+1 == 10000) std::cout << "Estimation: " << estimation.back() << std::endl;
            //if (episode+1 == 10000) std::cout << "Total reward: " << sum_rewards.back() << std::endl;
            if (episode+1 == 10000) std::cout << "Estimation: " << estimation.back() << std::endl;
            //if (episode+1 == 10000) std::cout << "Total reward: " << sum_rewards.back() << std::endl;
        }
    }
}