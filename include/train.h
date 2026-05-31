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
    
    int countOp;
    Car* first;
    int length;
    
public:
    Train();
    ~Train();
    
    void addCar(bool light);
    int getLength();
    int getOpCount() const;
    int getActualLength() const;
    void resetOpCount();
};

#endif // TRAIN_H
