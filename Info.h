//
// Created by Вячеслав on 16.12.2021.
//

#include "Client.h"
#include "Hotel.h"
#include <iosfwd>
#include <fstream>

#ifndef CSA_MULTITHREADING_HOTEL_INFO_H
#define CSA_MULTITHREADING_HOTEL_INFO_H


// Thread data.
struct Info {
public:
    // Client responsible for this stream.
    Client *client;
    // Hotel.
    Hotel *hotel;
};

#endif //CSA_MULTITHREADING_HOTEL_INFO_H
