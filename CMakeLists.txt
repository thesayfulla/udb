cmake_minimum_required(VERSION 3.10)
project(udb)

set(CMAKE_C_STANDARD 99)

add_executable(udb main.c input.c db.c)
