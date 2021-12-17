//
// Created by Вячеслав on 16.12.2021.
//

#include <iostream>
#include "Hotel.h"

// Constructor.
Hotel::Hotel() {
    capacity_ = 30;
    occupied_count_ = 0;
}

// Is the hotel full.
bool Hotel::isFull() const {
    return occupied_count_ == capacity_;
}

// Adding a client.
void Hotel::addClient() {
    ++occupied_count_;
}

// Print state of hotel.
void Hotel::print(std::ofstream &ofst) const {
    std::cout << "Hotel: full for " << occupied_count_ << '/' << capacity_ << " rooms." << std::endl << std::endl;
    ofst << "Client " << 5 << ": book room for the night in the hotel." << std::endl;
    ofst << "Hotel: full for " << occupied_count_ << '/' << capacity_ << " rooms." << std::endl << std::endl;
}

void Hotel::removeClient() {
    --occupied_count_;
}
