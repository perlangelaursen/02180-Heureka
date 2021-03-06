cmake_minimum_required(VERSION 3.3)
project(02180_Heureka)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
    Heureka/Heureka/main.cpp
        Heureka/Heureka/Point.cpp
        Heureka/Heureka/Point.h
        Heureka/Heureka/State.h
        Heureka/Heureka/Pathfinding.cpp
        Heureka/Heureka/Pathfinding.h
        Heureka/Heureka/PathfindingDriver.cpp
        Heureka/Heureka/PathfindingDriver.h
        Heureka/Heureka/Literal.h
        Heureka/Heureka/Literal.cpp
        Heureka/Heureka/Clause.cpp
        Heureka/Heureka/Clause.h
        Heureka/Heureka/KnowledgeBase.cpp
        Heureka/Heureka/KnowledgeBase.h
        Heureka/Heureka/InferenceDriver.cpp
        Heureka/Heureka/InferenceDriver.h)

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

add_executable(02180_Heureka ${SOURCE_FILES})