//
// Created by Вячеслав on 16.12.2021.
//

#ifndef CSA_MULTITHREADING_HOTEL_HOTEL_H
#define CSA_MULTITHREADING_HOTEL_HOTEL_H


#include <iosfwd>
#include <fstream>

class Hotel {
private:
    // Hotel capacity.
    int capacity_;
    // Current amount of occupied rooms.
    int occupied_count_;

public:
    // Constructor.
    explicit Hotel();

    // Check if all hotel rooms are occupied.
    [[nodiscard]] bool isFull() const;

    // Adding and removing a client.
    void addClient();

    void removeClient();


    // Output info about current state of hotel.
    void print(std::ofstream&) const;
};


#endif //CSA_MULTITHREADING_HOTEL_HOTEL_H
