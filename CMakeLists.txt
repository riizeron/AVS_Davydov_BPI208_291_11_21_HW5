cmake_minimum_required(VERSION 3.20)
project(CSA_Multithreading_Hotel)

set(CMAKE_CXX_STANDARD 23)

add_executable(CSA_Multithreading_Hotel main.cpp Hotel.h Hotel.cpp Client.h Client.cpp Random.h Random.cpp Info.h)
