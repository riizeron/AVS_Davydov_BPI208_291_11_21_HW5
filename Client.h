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
    Random flight_time_ = Random(500, 1000);

public:
    // Constructor.
    explicit Client(int id);

    // Выводит сообщение о действии пчелы.
    void getClientMove(FILE *file_out) const;

    // Getting the time for which the client falls asleep.
    int sleepTime(FILE *file_out) const;

    // Client leave the hotel.
    void leaveHotel(FILE *file_out) const;
};


#endif //CSA_MULTITHREADING_HOTEL_CLIENT_H
