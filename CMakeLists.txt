cmake_minimum_required(VERSION 3.28)
project(diskscape C)

set(CMAKE_C_STANDARD 11)

add_executable(diskscape main.c
        diskscape.c
        diskscape.h)
