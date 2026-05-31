// Copyright 2021 NNTU-CS
#include "train.h"

Train::Car::Car(bool lightState, Car* nextCar, Car* prevCar)
    : light(lightState), next(nextCar), prev(prevCar) {}

Train::Train() : countOp_(0), first_(nullptr), length_(0) {}

Train::~Train() {
    if (!first_) return;

    Car* current = first_;
    Car* nextCar;

    do {
        nextCar = current->next;
        delete current;
        current = nextCar;
    } while (current != first_);
}

void Train::addCar(bool light) {
    Car* newCar = new Car(light, nullptr, nullptr);

    if (!first_) {
        first_ = newCar;
        first_->next = first_;
        first_->prev = first_;
    } else {
        Car* last = first_->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first_;
        first_->prev = newCar;
    }

    length_++;
}

void Train::resetOpCount() {
    countOp_ = 0;
}

int Train::getOpCount() const {
    return countOp_;
}

int Train::getActualLength() const {
    return length_;
}

int Train::getLength() {
    if (!first_) return 0;

    countOp_ = 0;

    first_->light = true;
    Car* current = first_;
    int steps = 0;

    while (true) {
        current = current->next;
        countOp_++;
        steps++;

        if (!current->light) {
            current->light = true;
            steps = 0;
        } else {
            Car* checker = current;
            bool allOn = true;

            for (int i = 0; i < steps; i++) {
                checker = checker->prev;
                countOp_++;
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
