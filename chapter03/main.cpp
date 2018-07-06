#include <iostream>
#include "gridworld.h"

int main() {
    GridWorld g = GridWorld(5);
    g.compute_state_values(1e-4, true, false);
    g.show_results();

    return 0;
}