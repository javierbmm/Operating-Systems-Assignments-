cmake_minimum_required(VERSION 3.14)
project(G1_F1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(G1_F1
        commandsActions.c
        commandsActions.h
        fileManager.c
        fileManager.h
        main.c
        parsingInputs.c
        parsingInputs.h
        types.h)
