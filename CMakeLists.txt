cmake_minimum_required(VERSION 3.10)
project(BankingSystem)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
    main.cpp
        Account/*.cpp
        Bank/*.cpp
        Transaction/*.cpp
        Menu/*.cpp
)

add_executable(BankingSystem ${SOURCES})



