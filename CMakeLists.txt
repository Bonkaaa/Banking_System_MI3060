cmake_minimum_required(VERSION 3.10)
project(BankingSystem)

set(CMAKE_CXX_STANDARD 17)

# Add all source files
set(SOURCES
    main.cpp
    Account/Account.cpp
    Bank/Bank.cpp
    Transaction/Transaction.cpp
    Menu/Menu.cpp
)

# Add include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/Account
    ${CMAKE_SOURCE_DIR}/Bank
    ${CMAKE_SOURCE_DIR}/Transaction
    ${CMAKE_SOURCE_DIR}/Menu
)

add_executable(BankingSystem ${SOURCES})

# Include directories for testing
target_include_directories(BankingSystem PRIVATE
    ${CMAKE_SOURCE_DIR}/Account
    ${CMAKE_SOURCE_DIR}/Bank
    ${CMAKE_SOURCE_DIR}/Transaction
    ${CMAKE_SOURCE_DIR}/Menu
)



