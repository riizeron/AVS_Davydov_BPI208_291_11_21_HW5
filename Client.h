//
// Created by Вячеслав on 16.12.2021.
//

#ifndef CSA_MULTITHREADING_HOTEL_CLIENT_H
#define CSA_MULTITHREADING_HOTEL_CLIENT_H


#include "Random.h"

class Client {
private:
    // Client id.
    int id_;
    Random book_time_ = Random(2000, 5000);

public:
    // Constructor.
    explicit Client(int id);

    // Print message when client booked a room.
    void bookLog(FILE *output_path) const;

    // Print message when hotel is full and client has to sleep outside.
    void waitLog(FILE *output_path) const;
    // Getting the time for which the client falls asleep.
    int getBookTime(FILE *output_path) const;

    // Client leave the hotel.
    void leaveHotel(FILE *output_path) const;
};


#endif //CSA_MULTITHREADING_HOTEL_CLIENT_H
