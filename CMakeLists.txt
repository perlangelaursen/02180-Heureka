cmake_minimum_required(VERSION 3.3)
project(02180_Heureka)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Heureka/Heureka/main.cpp)

add_executable(02180_Heureka ${SOURCE_FILES})