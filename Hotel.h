//
// Created by Вячеслав on 16.12.2021.
//

#ifndef CSA_MULTITHREADING_HOTEL_HOTEL_H
#define CSA_MULTITHREADING_HOTEL_HOTEL_H


class Hotel {
private:
    // Hotel capacity.
    int capacity_;
    // Current amount of occupied rooms.
    int occupied_count_;

public:
    // Constructor.
    explicit Hotel(int capacity = 30);

    // Check if all hotel rooms are occupied.
    bool isFull() const;

    // Adding and removing a client.
    void addClient();

    void removeClient();


    // Output info about current state of holel.
    void print(FILE *file_out) const;
};


#endif //CSA_MULTITHREADING_HOTEL_HOTEL_H
