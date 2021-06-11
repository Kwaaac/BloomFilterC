cmake_minimum_required(VERSION 3.16)
project(BloomFilterC C)

set(CMAKE_C_STANDARD 90)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ansi -pedantic")

set(PROJECT_HEADERS
        bitarray.h
        filter.h
        hashtable.h)

set(PROJECT_SOURCES
        main.c
        bitarray.c
        filter.c
        hashtable.c)

set(PROJECT_SOURCES_FALSE
        test_false_positive.c
        bitarray.c
        filter.c
        hashtable.c)

set(PROJECT_HEADERS_TEST
        bitarray.h
        filter.h)

set(PROJECT_SOURCES_TEST
        test.c
        bitarray.c
        filter.c)

add_executable(MAIN ${PROJECT_SOURCES} ${PROJECT_HEADERS})

add_executable(TEST_FALSE_POSITIVE ${PROJECT_SOURCES_FALSE} ${PROJECT_HEADERS})

add_executable(TEST ${PROJECT_SOURCES_TEST} ${PROJECT_HEADERS_TEST})

target_link_libraries(MAIN m)
target_link_libraries(TEST m)
target_link_libraries(TEST_FALSE_POSITIVE m)

