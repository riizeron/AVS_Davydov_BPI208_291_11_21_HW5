cmake_minimum_required(VERSION 3.16)
project(CSA_Multithreading_Hotel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pthread")

add_executable(main main.cpp Hotel.h Hotel.cpp Client.h Client.cpp Info.h)
