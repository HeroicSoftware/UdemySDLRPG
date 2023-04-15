cmake_minimum_required(VERSION 3.21)
project(RPGSDL2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RPGSDL2
        main.cpp
        PlayerCharacter.cpp
        PlayerCharacter.h
        Puzzles.cpp
        Puzzles.h)
