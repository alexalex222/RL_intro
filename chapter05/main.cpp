#include <iostream>
#include "blackjack.h"
#include "infinitevariance.h"

int random_policy(State s) {
    return 1;
}

int es_policy(State s) {
    return 2;
}

int test_policy(int (*policy_func)(State), bool print) {
    int result = 0;
    State s1;
    if (print) {
        result = (*policy_func)(s1);
        std::cout << result << std::endl;
    }
    return result;
}

int main() {
    monte_carlo_sample();
    return 0;
}