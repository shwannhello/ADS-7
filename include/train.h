// Copyright 2022 NNTU-CS
#ifndef TRAIN_H
#define TRAIN_H

class Train {
private:
    struct Car {
        bool light;
        Car* next;
        Car* prev;
        
        Car(bool lightState) : light(lightState), next(nullptr), prev(nullptr) {}
    };
    
    Car* first;
    Car* startCar;
    int countOp;
    int length;
    
public:
    Train();
    ~Train();
    
    void addCar(bool light);
    int getLength();
    int getOpCount() const { return countOp; }
    void resetOpCount() { countOp = 0; }
    int getTrainLength() const { return length; }
};

#endif
