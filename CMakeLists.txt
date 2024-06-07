cmake_minimum_required(VERSION 3.10)
project(udb)

set(CMAKE_C_STANDARD 99)

add_executable(udb 
    src/main.c 
    src/input.c 
    src/db.c
)
