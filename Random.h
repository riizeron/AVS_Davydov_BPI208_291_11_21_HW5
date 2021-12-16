//
// Created by Вячеслав on 16.12.2021.
//

#include <stdlib.h>
#include <time.h>

#ifndef CSA_MULTITHREADING_HOTEL_RANDOM_H
#define CSA_MULTITHREADING_HOTEL_RANDOM_H


class Random {
private:
    // Bottom bound.
    int min_;
    // Upper bound.
    int max_;

public:
    Random(int min, int max) {
        min_ = min;
        max_ = max;
        // System time random initialization.
        srand(static_cast<unsigned int>(time(0)));
    }

    // Getting a random number.
    int get() const {
        return rand() % (max_ - min_ + 1) + min_;
    }
};


#endif //CSA_MULTITHREADING_HOTEL_RANDOM_H
