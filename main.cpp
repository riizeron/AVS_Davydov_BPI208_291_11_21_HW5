#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cstring>
#include "pthread.h"
#include <unistd.h>
#include <iostream>
#include "Info.h"

// Max amount of clients.
const int MAX_CLIENTS_NUMBER = 1000;

// Mutex for synchronization.
pthread_mutex_t mutex;
pthread_cond_t mut;


void errorMessage1() {
    printf("Incorrect command line!\n"
           "  Waited:\n"
           "     command -f input_file output_file\n"
           "  Or:\n"
           "     command -n <number1> output_file\n");
}

void errorMessage2() {
    printf("Incorrect qualifier value!\n"
           "  Waited:\n"
           "     command -f input_file output_file\n"
           "  Or:\n"
           "     command -n <number1> <number2> <number3> output_file\n");
}

void errorMessage3() {
    printf("Incorrect data format in the file!\n");
}

void errorMessage4() {
    printf("Incorrect number of clients. Set 0 < number <= %d\n", MAX_CLIENTS_NUMBER);
}


// Reads the number of clients wishing to book room in the hotel from the file.
// If the amount of data in the file is correct, then it returns true, otherwise false.
bool readArguments(FILE *file_in, int &clients_amount) {
    if (fscanf(file_in, "%d", &clients_amount) != EOF) {
        return true;
    }
    return false;
}


// Set data.
int setData(int argc, char *argv[], int &clients) {
    if (argc != 4) {
        errorMessage1();
        return 1;
    } else {
        if (!strcmp(argv[1], "-f")) {
            FILE *file_in = fopen(argv[2], "r");
            if (file_in == nullptr) {
                printf("Cannot find file with name %s\n", argv[2]);
                return 7;
            }
            if (!readArguments(file_in, clients)) {
                errorMessage3();
                return 3;
            }
            fclose(file_in);
        } else if (!strcmp(argv[1], "-n")) {
            clients = atoi(argv[2]);

        } else {
            errorMessage2();
            return 2;
        }
        if (clients <= 0 || clients > MAX_CLIENTS_NUMBER) {
            errorMessage4();
            return 4;
        }
    }
    return 0;
}


// Метод, используемый в многопоточности. Моделирует работу пчёл.
void *fillHotel(void *param) {
    auto *info = (Info *) param;

    // At one time, only one client can check into the hotel.
    pthread_mutex_lock(&mutex);
    //Clients check into the hotel until it is full.
    while (info->hotel->isFull()) {
        info->client->waitLog(info->output_path);
        pthread_cond_wait(&mut, &mutex);
    }
    info->client->bookLog(info->output_path);
    info->hotel->addClient();
    info->hotel->print(info->output_path);
    int sleep_milliseconds = info->client->getBookTime(info->output_path);
    pthread_mutex_unlock(&mutex);
    usleep(sleep_milliseconds);
    pthread_mutex_lock(&mutex);
    info->hotel->removeClient();
    info->client->leaveHotel(info->output_path);
    pthread_mutex_unlock(&mutex);

    pthread_cond_broadcast(&mut);
    return nullptr;
}


int main(int argc, char *argv[]) {
    std::cout<<std::endl;
    std::cout<<std::endl;
    // Start time.
    clock_t start_time = clock();

    int clients_amount;

    int result = setData(argc, argv, clients_amount);

    if (result) {
        return result;
    }

    FILE *file_out = fopen(argv[argc - 1], "w");

    auto *hotel = new Hotel();
    auto *threads = new pthread_t[clients_amount];
    auto *thread_info = new Info[clients_amount];

    // Thread creation.
    for (int i = 0; i < clients_amount; ++i) {
        thread_info[i] = {new Client(i + 1), hotel, file_out};
        pthread_create(&threads[i], nullptr, fillHotel, (void *) &thread_info[i]);
    }

    //Thread start time.
    clock_t thread_started_time = clock();

    // Waiting for threads to terminate.
    for (int i = 0; i < clients_amount; i++) {
        pthread_join(threads[i], nullptr);
    }

    fclose(file_out);
    for (int i = 0; i < clients_amount; ++i) {
        delete thread_info[i].client;
    }
    delete[] thread_info;
    delete[] threads;
    delete hotel;

    // Конечное время.
    clock_t end_time = clock();

    printf("Threads started: %.6f sec\n", (double) (thread_started_time - start_time) / CLOCKS_PER_SEC);
    printf("Time taken: %.6f sec\n", (double) (end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}