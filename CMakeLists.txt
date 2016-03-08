cmake_minimum_required(VERSION 3.3)
project(02180_Heureka)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Heureka/Heureka/main.cpp Heureka/Heureka/Point.cpp Heureka/Heureka/Point.h Heureka/Heureka/State.h Heureka/Heureka/Debug/Pathfinding.cpp Heureka/Heureka/Debug/Pathfinding.h)

add_executable(02180_Heureka ${SOURCE_FILES})