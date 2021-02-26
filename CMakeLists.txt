cmake_minimum_required(VERSION 3.17)
project(Sleeping_Barber_Problem)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(Sleeping_Barber_Problem main.cpp Hairdresser.cpp Hairdresser.h)