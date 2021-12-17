//
// Created by Вячеслав on 16.12.2021.
//

#include <cstdio>
#include "Client.h"

// Constructor.
Client::Client(int id) {
    id_ = id;
}

// Print message about client move.
void Client::bookLog(FILE *output_path) const {
    printf("Client %d: take room in the hotel.\n", id_);
    fprintf(output_path, "Client %d: take room in the hotel.\n", id_);
}

void Client::waitLog(FILE *output_path) const {
    printf("Client %d: wait outside due to hotel is full.\n\n", id_);
    fprintf(output_path, "Client %d: wait outside due to hotel is full.\n\n", id_);
}

int Client::getBookTime(FILE *output_path) const {
    int time = book_time_.get();
    printf("Client %d: book room for %d seconds.\n\n", id_, time);
    fprintf(output_path, "Client %d: book room for %d seconds.\n\n", id_, time);
    return time;
}

// Client leave the hotel.
void Client::leaveHotel(FILE *output_path) const {
    printf("Client %d: leaves hotel.\n\n", id_);
    fprintf(output_path, "Client %d: leaves the hotel.\n\n", id_);
}
