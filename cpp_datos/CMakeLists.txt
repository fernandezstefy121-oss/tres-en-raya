cmake_minimum_required(VERSION 4.3)
project(cpp_datos)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cpp_datos
        main.cpp
        nodo.h)
