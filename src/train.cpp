// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr), length(0) {}

Train::~Train() {
    if (!first) return;
    Car *current = first;
    do {
        Car *next = current->next;
        delete current;
        current = next;
    } while (current != first);
}

void Train::addCar(bool light) {
    Car *newCar = new Car{light, nullptr, nullptr};

    if (!first) {
        first = newCar;
        first->next = first;
        first->prev = first;
    } else {
        Car *last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
    length++;
}

int Train::getActualLength() {
    return length;
}

int Train::getOpCount() {
    return countOp;
}

void Train::resetOpCount() {
    countOp = 0;
}

int Train::getLength() {
    if (!first) return 0;

    countOp = 0;

    first->light = true;
    Car *current = first;
    int steps = 0;

    while (true) {
        while (true) {
            current = current->next;
            countOp++;
            steps++;
    
            if (!current->light) {
                break;
            }
        }
  
        current->light = true;

        int backSteps = 0;
        while (backSteps < steps) {
            current = current->prev;
            countOp++;
            backSteps++;
 
            if (current == first) {
                Car *check = first;
                bool allOn = true;
                int checkSteps = 0;
                while (checkSteps <= steps) {
                    if (!check->light) {
                        allOn = false;
                        break;
                    }
                    check = check->next;
                    checkSteps++;
                }

                if (allOn) {
                    return steps + 1;
                }
                break;
            }
        }

        steps = 0;
    }
}
