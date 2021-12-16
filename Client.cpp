//
// Created by Вячеслав on 16.12.2021.
//

#include "stdio.h"
#include "Client.h"

// Constructor.
Client::Client(int id) {
    id_ = id;
}

// Print message about client move.
void Client::getClientMove(FILE *file_out) const {
    printf("Client %d: take room in the hotel.\n", id_);
    fprintf(file_out, "Client %d: take room in the hotel.\n", id_);
}

int Client::sleepTime(FILE *file_out) const {
    int milliseconds = flight_time_.get();
    printf("Client %d: book room for %d seconds.\n\n", id_, milliseconds);
    fprintf(file_out, "Client %d: book room for %d seconds.\n\n", id_, milliseconds);
    return milliseconds;
}

// Client leave the hotel.
void Client::leaveHotel(int *file_out) const {
    printf("Client %d: leaves hotel.\n", id_);
    fprintf(file_out, "Client %d: leaves the hotel.\n", id_);
}