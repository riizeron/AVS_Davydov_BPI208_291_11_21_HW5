//
// Created by Вячеслав on 16.12.2021.
//

#include "Client.h"
#include "Hotel.h"

#ifndef CSA_MULTITHREADING_HOTEL_INFO_H
#define CSA_MULTITHREADING_HOTEL_INFO_H


// Данные, передаваемые в поток.
struct Info {
    // Client responsible for this stream.
    Client *client;
    // Hotel.
    Hotel *hotel;

    // Output file.
    FILE *output_path;
};

#endif //CSA_MULTITHREADING_HOTEL_INFO_H
