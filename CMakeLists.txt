cmake_minimum_required(VERSION 3.30)
project(progettoLabProg)

set(CMAKE_CXX_STANDARD 20)

add_executable(progettoLabProg main.cpp
        User.cpp
        User.h
        Account.cpp
        Account.h
        Transaction.cpp
        Transaction.h
        AccountManager.cpp
        AccountManager.h
        UserManager.cpp
        UserManager.h
        TransactionManager.cpp
        TransactionManager.h
        IdManager.h
        IdManager.cpp)


