//
// Created by Kuilin Chen on 2018-07-10.
//

#include "bandit.h"

Bandit::Bandit(int k_arm, double explore_rate, double step, double init, bool use_sample_avg, int ucb, bool g,
               bool g_bl, double true_r):
        k(k_arm), epsilon(explore_rate), step_size(step), initial(init), sample_averages(use_sample_avg),
        ucb_param(ucb), gradient(g), gradient_baseline(g_bl), true_reward(true_r)
{
    // k_arm, explore_rate, step, init, use_sample_average, ucb, gradient, gradient_baseline, true_reward
    this-> time = 0;
    this->indices = vector<int>(k, 0);
    this->q_true = vector<double>(k, 0.0);
    this->q_est = vector<double>(k, 0.0);
    this->action_count = vector<int>(k, 0);
    this->action_prob = vector<double>(k, 0.0);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> d(0.0,1.0);
    for (int i = 0; i < k; i++) {
        indices[i] = i;
        q_true[i] = d(gen) + true_reward;
        q_est[i] = initial;
    }

    auto best_reward = static_cast<double>(INT_MIN);
    for (int i = 0; i < k; i++) {
        if (q_true[i] > best_reward) {
            best_reward = q_true[i];
            best_action = i;
        }
    }
}

int Bandit::getAction() {
    // explore
    if (this->epsilon > 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::binomial_distribution<int> d(1, this->epsilon);
        if (d(gen) == 1) {
            return indices[rand()%k];
        }
    }

    // exploit
    double best_value = static_cast<double>(INT_MIN);
    int best_action;
    if (this->ucb_param != 0) {
        vector<double> ucb_est(k, 0.0);
        for (int i = 0; i < k; i++) {
            ucb_est[i] = q_est[i] + static_cast<double>(ucb_param)*sqrt(log(time + 1)/(action_count[i] + 1));
        }

        for (int i = 0; i < k; i++) {
            if (ucb_est[i] > best_value) {
                best_value = ucb_est[i];
                best_action = i;
            }
        }
        return best_action;
    }

    if (gradient) {
        vector<double> exp_est(k, 0.0);
        double sum_est = 0.0;
        for (int i = 0; i < k; i++) {
            exp_est[i] = exp(q_est[i]);
            sum_est += exp_est[i];
        }
        for (int i ;i < k; i++) {
            action_prob[i] = exp_est[i]/sum_est;
        }
        return weight_random_choice(indices, action_prob);
    }

    return 999;
}

double Bandit::takeAction(int action) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> d(0.0,1.0);
    double reward = d(gen) + q_true[action];
    this->time += 1;
    double time_t = static_cast<double>(time);
    average_reward = (time_t - 1.0)/time_t*average_reward + reward/time_t;
    action_count[action] += 1;

    if (sample_averages) {
        // update estimations using sample average
        q_est[action] += 1.0/action_count[action]*(reward - q_est[action]);
    }
    else if (gradient) {
        vector<double> one_hot(k, 0.0);
        one_hot[action] = 1.0;
        double base_line = 0.0;
        if (gradient_baseline) {
            base_line = average_reward;
        }

        for (int i = 0; i < k; i++) {
            q_est[i] += step_size*(reward - base_line)*(one_hot[i] - action_prob[i]);
        }
    }
    else {
        // update the estimation using hte constant step size
        q_est[action] += step_size*(reward - q_est[action]);
    }

    return reward;
}

int Bandit::weight_random_choice(vector<int> &pool, vector<double> &prob) {
    assert(pool.size() == prob.size() && "weight size is not compatible with pool size!");
    double weight_sum = 0.0;
    for (auto p : prob) {
        weight_sum += p;
    }
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> dis(0.0, weight_sum);
    double rnd = dis(gen);
    for (size_t i = 0; i < prob.size(); i++) {
        if (rnd < prob[i]) return static_cast<int>(i);
        rnd -= prob[i];
    }
    return static_cast<int>(rand()%prob.size());
}

int Bandit::getBestAction() {
    return best_action;
}

