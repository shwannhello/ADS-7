// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : countOp(0), first(nullptr), current(nullptr) {}
Train::~Train() {
    if (!first) return;
    Car* temp = first->next;
    while (temp != first) {
        Car* next = temp->next;
        delete temp;
        temp = next;
    }
    delete first;
}
void Train::addCar(bool light) {
    Car* newCar = new Car{ light, nullptr, nullptr };
    if (!first) {
        first = newCar;
        first->next = first;
        first->prev = first;
        current = first;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}
int Train::getLength() {
    if (!first) return 0;
    resetOps();
    current = first;
    if (!current->light) {
        current->light = true;
    }
    int length = 0;
    bool found = false;
    while (!found) {
        while (true) {
            current = current->next;
            countOp++;
            length++;
            if (current->light) {
                current->light = false;
                break;
            }
        }
        int steps = 0;
        while (steps < length) {
            current = current->prev;
            countOp++;
            steps++;
        }
        if (!current->light) {
            found = true;
        } else {
            length = 0;
        }
    }
    return length;
}
int Train::getOpCount() {
    return countOp;
}
void Train::resetOps() {
    countOp = 0;
}
