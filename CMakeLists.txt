cmake_minimum_required(VERSION 3.16)
project(BloomFilterC C)

set(CMAKE_C_STANDARD 90)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ansi -pedantic-errors")

set(PROJECT_HEADERS
        bitarray.h
        filter.h
        hashtable.h)

set(PROJECT_SOURCES
        main.c
        bitarray.c
        filter.c
        hashtable.c)

add_executable(MAIN ${PROJECT_SOURCES} ${PROJECT_HEADERS})
