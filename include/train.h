// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H__
#define INCLUDE_TRAIN_H__

class Train {
 private:
    struct Car {
        bool light;
        Car* next;
        Car* prev;

        explicit Car(bool lightState);
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
    int getOpCount() const;
    void resetOpCount();
    int getTrainLength() const;
};

#endif  // INCLUDE_TRAIN_H__
