// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr), length(0) {}

Train::~Train() {
    if (!first) return;
    
    Car* current = first;
    Car* nextCar;
    
    do {
        nextCar = current->next;
        delete current;
        current = nextCar;
    } while (current != first);
}

void Train::addCar(bool light) {
    Car* newCar = new Car(light);
    
    if (!first) {
        first = newCar;
        first->next = first;
        first->prev = first;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
    
    length++;
}

void Train::resetOpCount() {
    countOp = 0;
}

int Train::getOpCount() const {
    return countOp;
}

int Train::getActualLength() const {
    return length;
}

int Train::getLength() {
    if (!first) return 0;
    
    countOp = 0;

    first->light = true;
    Car* current = first;
    int steps = 0;
    
    while (true) {
        current = current->next;
        countOp++;
        steps++;

        if (!current->light) {
            current->light = true;
            steps = 0;
        }
        else {
            Car* checker = current;
            bool allOn = true;

            for (int i = 0; i < steps; i++) {
                checker = checker->prev;
                countOp++;
                if (!checker->light) {
                    allOn = false;
                    break;
                }
            }
            
            if (allOn && steps > 0) {
                return steps;
            }
        }
    }
}
