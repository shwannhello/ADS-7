// Copyright 2022 NNTU-CS
#include <iostream>
#include "train.h"

int main() {
    const int lengths[] = {2, 5, 10, 20, 30};
    int num_tests = 5;

    for (int i = 0; i < num_tests; ++i) {
        int n = lengths[i];

        std::cout << "Test: train with " << n
            << " cars" << std::endl;

        //all lights off
        Train train1;
        for (int j = 0; j < n; ++j) {
            train1.addCar(false);
        }
        int len1 = train1.getLength();
        int ops1 = train1.getOpCount();

        //all lights on
        Train train2;
        for (int j = 0; j < n; ++j) {
            train2.addCar(true);
        }
        int len2 = train2.getLength();
        int ops2 = train2.getOpCount();

        //random
        Train train3;
        for (int j = 0; j < n; ++j) {
            if (j % 2 == 0) {
                train3.addCar(true);
            } else {
                train3.addCar(false);
            }
        }
        int len3 = train3.getLength();
        int ops3 = train3.getOpCount();

        std::cout << "All off: length=" << len1
            << ", operations=" << ops1 << std::endl;
        std::cout << "All on: length=" << len2
            << ", operations=" << ops2 << std::endl;
        std::cout << "Random: length=" << len3
            << ", operations=" << ops3 << std::endl;
    }
    return 0;
}
