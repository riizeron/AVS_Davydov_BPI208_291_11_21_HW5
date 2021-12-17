//
// Created by Вячеслав on 16.12.2021.
//

#include <iostream>
#include "Client.h"

// Constructor.
Client::Client(int id) {
    id_ = id;
}

// Print message that client book room.
void Client::bookRoom(std::ofstream &ofst) const {
    std::cout << "Client " << id_ << ": book room for the night in the hotel." << std::endl;
    ofst << "Client " << id_ << ": book room for the night in the hotel." << std::endl;

}

void Client::waitLog(std::ofstream &ofst) const {
    std::cout << "Client " << id_ << ": wait outside due to hotel is full." << std::endl << std::endl;
    ofst << "Client " << id_ << ": wait outside due to hotel is full." << std::endl << std::endl;
}

// Client leave the hotel.
void Client::leaveHotel(std::ofstream &ofst) const {
    std::cout << "Client " << id_ << ": leaves hotel." << std::endl;
    ofst << "Client " << id_ << ": leaves hotel." << std::endl;
}
