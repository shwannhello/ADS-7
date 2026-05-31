// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
    Car* newCar = new Car{light, nullptr, nullptr};

    if (!first) {
        first = newCar;
        newCar->next = first;
        newCar->prev = first;
    } else {
        newCar->next = first;
        newCar->prev = first->prev;
        first->prev->next = newCar;
        first->prev = newCar;
    }
}

int Train::getLength() {
    if (!first) {
        return 0;
    }

    countOp = 0;
    first->light = true;
    Car* current = first;

    while (true) {
        int steps = 0;

        do {
            current = current->prev;
            countOp++;
            steps++;
        } while (!current->light);

        current->light = false;

        for (int i = 0; i < steps; ++i) {
            current = current->next;
            countOp++;
        }

        if (!first->light) {
            int length = steps;
            return length;
        }
    }
}

int Train::getOpCount() {
    return countOp;
}
