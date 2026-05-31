// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H__
#define INCLUDE_TRAIN_H__

class Train {
 public:
    Train();
    ~Train();

    void addCar(bool light);
    int getLength();
    int getOpCount() const;
    int getActualLength() const;
    void resetOpCount();

 private:
    struct Car {
        bool light;
        Car* next;
        Car* prev;

        explicit Car(bool lightState);
    };

    int countOp_;
    Car* first_;
    int length_;
};

#endif  // INCLUDE_TRAIN_H__
