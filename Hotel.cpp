//
// Created by Вячеслав on 16.12.2021.
//

#include "stdio.h"
#include "Hotel.h"

// Constructor.
int Hotel::Hotel(int capacity = 30) {
    capacity_ = capacity;
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

// Вывод информации о горшке.
void Hotel::print(FILE *file_out) const {
    printf("Hotel: full for %d/%d rooms.\n", occupied_count_, capacity_);
    fprintf(file_out, "Hotel: full for %d/%d rooms.\n", occupied_count_, capacity_);
}

void Hotel::removeClient() {
    --occupied_count_;
}
