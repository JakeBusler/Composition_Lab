cmake_minimum_required(VERSION 3.15)
project(Composition_Lab CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Composition_Lab
    main.cpp
    BankAccount.h
    BankAccount.cpp
    CheckingAccount.h
    CheckingAccount.cpp
    SavingsAccount.h
    SavingsAccount.cpp
    Transaction.h
)
