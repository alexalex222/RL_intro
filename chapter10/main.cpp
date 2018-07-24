#include <iostream>

#include "iht.h"

class Circle {
private:
    double x;
    double y;
    double r;

public:
    Circle(double pos_x, double pos_y, double radius) {
        x = pos_x;
        y = pos_y;
        r = radius;
        std::cout << "Circle constructor called..." << std::endl;
    }

    int getHash() {
        return static_cast<int>(x * 100 + y * 10 + r);
    }
};


int main() {
    std::cout << "program starts..." << std::endl;
    Circle c1(1, 1, 1);
    Circle c2(1, 2, 1);
    Circle c3(1, 2, 3);
    IHT<Circle> iht(3);
    int result = iht.getIndex(c1, false);
    result = iht.getIndex(c2, false);
    result = iht.getIndex(c1, true);
    std::cout << iht << std::endl;
    return 0;
}