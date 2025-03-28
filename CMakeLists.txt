cmake_minimum_required(VERSION 3.30)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled1 main.cpp
        graph.h
        graph_loader.cpp
        graph_loader.h
        menu.cpp
        algorithms.cpp
        menu.h
        algorithms.h)
