// Copyright 2022 NNTU-CS
#ifndef TRAIN_H_
#define TRAIN_H_

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

#endif  // TRAIN_H_
