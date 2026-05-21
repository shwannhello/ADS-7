// Copyright 2021 NNTU-CS
#include "train.h"


Train::Car::Car(bool lightState) : light(lightState),
                                    next(nullptr),
                                    prev(nullptr) {}


Train::Train() : first(nullptr),
                 startCar(nullptr),
                 countOp(0),
                 length(0) {}


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


int Train::getOpCount() const {
    return countOp;
}


void Train::resetOpCount() {
    countOp = 0;
}


int Train::getTrainLength() const {
    return length;
}


int Train::getLength() {
    if (!first) return 0;

    countOp = 0;


    Car* current = first;
    Car* startCar = first;


    bool startLightWasOn = current->light;
    if (current->light) {
        current->light = false;
    }

    int result = 0;
    bool found = false;

    while (!found) {
        int steps = 0;
        Car* marker = current;

        do {
            marker = marker->next;
            countOp++;
            steps++;
        } while (marker != current && marker->light);

        if (marker == startCar && !marker->light) {
            found = true;
            result = steps;
            break;
        }


        marker->light = true;


        Car* backMarker = marker;
        while (backMarker != current) {
            backMarker = backMarker->prev;
            countOp++;  // переход назад
            backMarker->light = false;
        }

        current = marker;
    }

    if (startLightWasOn) {
        startCar->light = true;
    }

    return result;
}
