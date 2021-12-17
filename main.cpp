#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <iosfwd>
#include <cstring>
#include <unistd.h>
#include "Info.h"

// Max amount of clients.
const int MAX_CLIENTS_NUMBER = 1000;
// Max night duration.
const int MAX_NIGHT_DURATION = 10000;

// Mutexes for synchronization.
// std::mutex reception;
pthread_mutex_t mutex;
// std::condition_variable condition;
pthread_cond_t mut;
std::ofstream ofst;
int night_duration;


void errMessage1() {
    std::cout << "Incorrect command line!\n"
                 "  Waited:\n"
                 "     command -f input_file output_file\n"
                 "  Or:\n"
                 "     command -n <clients_amount> <night_duration> output_file\n";
}

void errMessage2(const char *input_file_path) {
    std::cout << "FileNotFoundException. Cannot find this file: "<< input_file_path << std::endl;
}

void errMessage4() {
    std::cout << "Incorrect qualifier value!\n"
                 "  Waited:\n"
                 "     command -f input_path output_path\n"
                 "  Or:\n"
                 "     command -n <clients_amount> <night_duration> output_file\n";
}

void errMessage3() {
    std::cout << "Incorrect file input data.\n";
}

void errMessage5(int clients_amount) {
    std::cout << "Incorrect number of clients = "
              << clients_amount
              << ". Set 0 < number <= "
              << MAX_CLIENTS_NUMBER << std::endl;
}

void errMessage6() {
    std::cout << "Incorrect night duration = "
              << night_duration
              << ". Set 0 < number <= "
              << MAX_NIGHT_DURATION << std::endl;
}


// Reads the number of clients wishing to book room in the hotel from the file.
// If the amount of data in the file is correct, then it returns true, otherwise false.
bool readArguments(std::ifstream &ifst, int &clients_amount) {
    if (!ifst.eof()) {
        ifst >> clients_amount;
        if (!ifst.eof()) {
            ifst >> night_duration;
            return true;
        }
    }
    return false;
}


// Set data.
int setData(int argc, char *argv[], int &clients_amount) {
    if (argc != 4 && argc != 5) {
        errMessage1();
        return 1;
    } else {
        if (argc == 4 && !strcmp(argv[1], "-f")) {
            std::ifstream ifst(argv[2]);
            // FILE *file_in = fopen(argv[2], "r");
            if (ifst.eof()) {
                errMessage2(argv[2]);
                return 2;
            }
            if (!readArguments(ifst, clients_amount)) {
                errMessage3();
                return 3;
            }
            // fclose(file_in);
        } else if (argc == 5 && !strcmp(argv[1], "-n")) {
            clients_amount = atoi(argv[2]);
            night_duration = atoi(argv[3]);
        } else {
            errMessage4();
            return 4;
        }
        if (clients_amount <= 0 || clients_amount > MAX_CLIENTS_NUMBER) {
            errMessage5(clients_amount);
            return 5;
        }
        if (night_duration <= 0 || night_duration > MAX_NIGHT_DURATION) {
            errMessage6();
            return 6;
        }
    }
    return 0;
}


// Метод, используемый в многопоточности. Моделирует работу пчёл.
void *settleHotel(void *params) {
    auto *info = (Info *) params;

    // At one time, only one client can check into the hotel.
    pthread_mutex_lock(&mutex);
    // reception.lock();
    //Clients check into the hotel until it is full.
    while (info->hotel->isFull()) {
        info->client->waitLog(ofst);
        // condition.wait(u_lock);
        pthread_cond_wait(&mut, &mutex);
    }

    // std::unique_lock<std::mutex> u_lock{reception};
    // condition.wait(u_lock, [&info] { return info->hotel->isFull(); });

    info->client->bookRoom(ofst);
    info->hotel->addClient();
    info->hotel->print(ofst);
    pthread_mutex_unlock(&mutex);
    // reception.unlock();

    // The client spends the night in the room.
    // std::this_thread::sleep_for(std::chrono::milliseconds(night_duration));
    usleep(night_duration);

    pthread_mutex_lock(&mutex);
    // reception.lock();
    info->client->leaveHotel(ofst);
    info->hotel->removeClient();
    info->hotel->print(ofst);
    // Notify people spending the night on the street
    // that there is a free space in the hotel
    // reception.unlock();
    // condition.notify_all();
    pthread_cond_broadcast(&mut);
    pthread_mutex_unlock(&mutex);


    return nullptr;

}


int main(int argc, char *argv[]) {
    // Start time.
    clock_t start_time = clock();

    int clients_amount;
    int result = setData(argc, argv, clients_amount);

    if (result) {
        return result;
    }

    // FILE *file_out = fopen(argv[argc - 1], "w");
    ofst.open(argv[argc - 1]);
    auto *hotel = new Hotel();
    auto *thread_pool = new std::thread[clients_amount];
    Info *infos = new Info[clients_amount];


    // Thread creation.
    for (int i = 0; i < clients_amount; ++i) {
        infos[i] = {new Client(i + 1), hotel};
        thread_pool[i] = std::thread(settleHotel, &infos[i]);
    }

    //Thread start time.
    clock_t thread_started_time = clock();

    // Waiting for threads to terminate.
    for (int i = 0; i < clients_amount; i++) {
        thread_pool[i].join();
    }

    // Flush memory.
    for (int i = 0; i < clients_amount; ++i) {
        delete infos[i].client;
    }
    delete[] infos;
    delete[] thread_pool;
    delete hotel;

    // Check time.
    clock_t end_time = clock();

    printf("Threads started: %.6f sec\n", (double) (thread_started_time - start_time) / CLOCKS_PER_SEC);
    printf("Time taken: %.6f sec\n", (double) (end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}