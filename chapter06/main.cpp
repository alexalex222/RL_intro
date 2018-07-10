#include <iostream>
#include "random_walk.h"
#include "grid_world.h"
#include "cliff_walk.h"
#include "windy_grid.h"


int main() {
    RandomWalk rw(0, 1, 5);
    rw.testLearning();
    return 0;
}