//
// Created by Вячеслав on 16.12.2021.
//

#ifndef CSA_MULTITHREADING_HOTEL_CLIENT_H
#define CSA_MULTITHREADING_HOTEL_CLIENT_H

#include <fstream>
#include <iosfwd>
class Client {
private:
    // Client id.
    int id_;

public:
    // Constructor.
    explicit Client(int);
    // Print message that client book room.
    void bookRoom(std::ofstream&) const;
    // Print message when hotel is full and client has to sleep outside.
    void waitLog(std::ofstream&) const;
    // Client leave the hotel.
    void leaveHotel(std::ofstream&) const;
};


#endif //CSA_MULTITHREADING_HOTEL_CLIENT_H
