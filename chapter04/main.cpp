#include <iostream>
#include "GridWorld.h"
#include "gambler.h"

void testGridWord(int size) {
    GridWorld g1 = GridWorld(size);
    g1.compute_state_values(0.0001, true);
    std::cout << "In-place:" << std::endl;


    GridWorld g2 = GridWorld(size);
    g2.compute_state_values(0.0001, false);
    std::cout << "Synchronous:" << std::endl;

}

void testGambler(int g) {
    Gambler p = Gambler(g);
    p.get_optimal_policy();
    p.show();
}

int main() {
    //testGridWord(4);
    testGambler(100);
    return 0;
}