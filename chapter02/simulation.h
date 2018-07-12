//
// Created by Kuilin Chen on 2018-07-11.
//

#ifndef CHAPTER02_SIMULATION_H
#define CHAPTER02_SIMULATION_H

#include "bandit.h"

void bandit_simulation(unsigned long episodes, vector<vector<Bandit>> &bandits,
                       vector<vector<double>> &best_action_counts, vector<vector<double>> &average_rewards)
{
    if ( bandits.empty()) return;
    size_t bandit_types = bandits.size();
    size_t n_bandits = bandits.back().size();
    best_action_counts = vector<vector<double>>(bandit_types, vector<double>(episodes, 0));
    average_rewards = vector<vector<double>>(bandit_types, vector<double>(episodes, 0.0));
    for (size_t bandit_ind = 0; bandit_ind < bandit_types; bandit_ind++) {
        vector<Bandit> bandit = bandits[bandit_ind];
        for (size_t i = 0; i < n_bandits; i++) {
            for (int t = 0; t < episodes; t++) {
                int action = bandit[i].getAction();
                double reward = bandit[i].takeAction(action);
                average_rewards[bandit_ind][t] += reward;
                if (action == bandit[i].getBestAction()) {
                    best_action_counts[bandit_ind][t] += 1;
                }
            }
        }

        for (size_t t = 0; t < episodes; t++) {
            best_action_counts[bandit_ind][t] = best_action_counts[bandit_ind][t]/ static_cast<double>(n_bandits);
            average_rewards[bandit_ind][t] = average_rewards[bandit_ind][t]/ static_cast<double>(n_bandits);
        }
    }
}

void epsilon_greedy(size_t n_bandits, unsigned long episodes) {
    std::cout << "Epsilon greedy..." << std::endl;
    vector<double> epsilons {0.0, 0.1, 0.01};
    vector<vector<Bandit>> bandits;
    for (auto ep : epsilons) {
        vector<Bandit> one_type_bandits;
        for (int i = 0; i < n_bandits; i++) {
            // k_arm, explore_rate, step, init, use_sample_average, ucb, gradient, gradient_baseline, true_reward
            Bandit one_bandit(10, ep, 0.1, 0.0, true, 0, false, false, 0.0);
            one_type_bandits.push_back(one_bandit);
        }
        bandits.push_back(one_type_bandits);
    }
    vector<vector<double>> best_action_counts;
    vector<vector<double>> average_rewards;
    bandit_simulation(episodes, bandits, best_action_counts, average_rewards);

    std::cout << "Writing data to file..." << std::endl;
    std::ofstream ofs_counts("epsilon_greedy_best_action_count.csv");
    std::ofstream ofs_rewards("epsilon_greedy_average_rewards.csv");
    for (size_t i = 0; i < epsilons.size(); i++) {
        double ep = epsilons[i];
        string column_name = "epsilon" + std::to_string(ep);
        ofs_counts << column_name;
        ofs_rewards << column_name;
        if (i == epsilons.size() - 1) {
            ofs_counts << "\n";
            ofs_rewards << "\n";
        }
        else {
            ofs_counts << ",";
            ofs_rewards << ",";
        }
    }
    for (size_t episode = 0; episode < episodes; episode++)
    {
        for (size_t i = 0; i < bandits.size(); i++)
        {
            ofs_counts << best_action_counts[i][episode];
            ofs_rewards << average_rewards[i][episode];
            if (i == bandits.size() - 1) {
                ofs_counts << "\n";
                ofs_rewards << "\n";
            }
            else {
                ofs_counts << ",";
                ofs_rewards << ",";
            }
        }
    }

    ofs_counts.close();
    ofs_rewards.close();
}

void opt_init_values(unsigned long n_bandits, unsigned long episodes) {
    std::cout << "Optimistic initial values..." << std::endl;
    vector<double> init_values {5.0, 0.0};
    vector<vector<Bandit>> bandits;
    for (auto init : init_values) {
        vector<Bandit> one_type_bandits;
        for (int i = 0; i < n_bandits; i++) {
            Bandit one_bandit(10, 0.0, 0.1, init, false, 0, false, false, 0.0);
            one_type_bandits.push_back(one_bandit);
        }
        bandits.push_back(one_type_bandits);
    }

    vector<vector<double>> best_action_counts;
    vector<vector<double>> average_rewards;
    bandit_simulation(episodes, bandits, best_action_counts, average_rewards);

    std::cout << "Writing data to file..." << std::endl;
    std::ofstream ofs_counts("opt_init_best_action_count.csv");
    std::ofstream ofs_rewards("opt_init_average_rewards.csv");
    ofs_counts << "epsilon = 0 q = 5" << "," << "epsilon = 0.1 q = 0" << "\n";
    ofs_rewards << "epsilon = 0 q = 5" << "," << "epsilon = 0.1 q = 0" << "\n";


    for (size_t episode = 0; episode < episodes; episode++)
    {
        for (size_t i = 0; i < bandits.size(); i++)
        {
            ofs_counts << best_action_counts[i][episode];
            ofs_rewards << average_rewards[i][episode];
            if (i == bandits.size() - 1) {
                ofs_counts << "\n";
                ofs_rewards << "\n";
            }
            else {
                ofs_counts << ",";
                ofs_rewards << ",";
            }
        }
    }

    ofs_counts.close();
    ofs_rewards.close();
}

void ucb(unsigned long n_bandits, unsigned long episodes) {
    std::cout << "UCB..." << std::endl;
    vector<vector<Bandit>> bandits;
    vector<Bandit> type_bandits1;
    vector<Bandit> type_bandits2;
    vector<int> ucbs {2, 0};


    for (int i = 0; i < n_bandits; i++) {
        // k_arm, explore_rate, step, init, use_sample_average, ucb, gradient, gradient_baseline, true_reward
        Bandit bandit1(10, 0.0, 0.1, 0.0, false, ucbs[0], false, false, 0.0);
        Bandit bandit2(10, 0.1, 0.1, 0.0, false, ucbs[1], false, false, 0.0);

        type_bandits1.push_back(bandit1);
        type_bandits2.push_back(bandit2);
    }

    bandits.push_back(type_bandits1);
    bandits.push_back(type_bandits2);

    vector<vector<double>> best_action_counts;
    vector<vector<double>> average_rewards;
    bandit_simulation(episodes, bandits, best_action_counts, average_rewards);

    std::cout << "Writing data to file..." << std::endl;
    std::ofstream ofs_counts("ucb_best_action_count.csv");
    std::ofstream ofs_rewards("ucb_average_rewards.csv");
    ofs_counts << "UCB = 2" << "," << "epsilon greedy epsilon = 0.1" << "\n";
    ofs_rewards << "UCB = 2" << "," << "epsilon greedy epsilon = 0.1" << "\n";


    for (size_t episode = 0; episode < episodes; episode++)
    {
        for (size_t i = 0; i < bandits.size(); i++)
        {
            ofs_counts << best_action_counts[i][episode];
            ofs_rewards << average_rewards[i][episode];
            if (i == bandits.size() - 1) {
                ofs_counts << "\n";
                ofs_rewards << "\n";
            }
            else {
                ofs_counts << ",";
                ofs_rewards << ",";
            }
        }
    }

    ofs_counts.close();
    ofs_rewards.close();
}

void gradientBandit(unsigned long n_bandits, unsigned long episodes) {
    std::cout << "Gradient methods..." << std::endl;
    vector<vector<Bandit>> bandits;
    vector<Bandit> type_bandits1;
    vector<Bandit> type_bandits2;
    vector<Bandit> type_bandits3;
    vector<Bandit> type_bandits4;
    for (int i = 0; i < n_bandits; i++) {
        // k_arm, explore_rate, step, init, use_sample_average, ucb, gradient, gradient_baseline, true_reward
        Bandit bandit1(10, 0.0, 0.1, 0.0, false, 0, true, true, 4.0);
        Bandit bandit2(10, 0.0, 0.1, 0.0, false, 0, true, false, 4.0);
        Bandit bandit3(10, 0.0, 0.4, 0.0, false, 0, true, true, 4.0);
        Bandit bandit4(10, 0.0, 0.4, 0.0, false, 0, true, false, 4.0);

        type_bandits1.push_back(bandit1);
        type_bandits2.push_back(bandit2);
        type_bandits3.push_back(bandit3);
        type_bandits4.push_back(bandit4);
    }



    bandits.push_back(type_bandits1);
    bandits.push_back(type_bandits2);
    bandits.push_back(type_bandits3);
    bandits.push_back(type_bandits4);

    vector<vector<double>> best_action_counts;
    vector<vector<double>> average_rewards;
    bandit_simulation(episodes, bandits, best_action_counts, average_rewards);

    std::cout << "Writing data to file..." << std::endl;
    std::ofstream ofs_counts("gradient_best_action_count.csv");
    std::ofstream ofs_rewards("gradient_average_rewards.csv");
    ofs_counts << "alpha = 0.1 with baseline" << "," << "alpha = 0.1 without baseline" << ",";
    ofs_counts << "alpha = 0.4 with baseline" << "," << "alpha = 0.4 without baseline" << "\n";
    ofs_rewards << "alpha = 0.1 with baseline" << "," << "alpha = 0.1 without baseline" <<  ",";
    ofs_rewards << "alpha = 0.4 with baseline" << "," << "alpha = 0.4 without baseline" << "\n";

    for (size_t episode = 0; episode < episodes; episode++)
    {
        for (size_t i = 0; i < bandits.size(); i++)
        {
            ofs_counts << best_action_counts[i][episode];
            ofs_rewards << average_rewards[i][episode];
            if (i == bandits.size() - 1) {
                ofs_counts << "\n";
                ofs_rewards << "\n";
            }
            else {
                ofs_counts << ",";
                ofs_rewards << ",";
            }
        }
    }

    ofs_counts.close();
    ofs_rewards.close();
}

#endif //CHAPTER02_SIMULATION_H
