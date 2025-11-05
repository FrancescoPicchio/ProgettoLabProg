cmake_minimum_required(VERSION 3.30)
project(progettoLabProg)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

add_executable(progettoLabProg
    main.cpp
    User.cpp User.h
    Account.cpp Account.h
    Transaction.cpp Transaction.h
    IdUtil.cpp IdUtil.h
    AppDataManager.cpp AppDataManager.h
)

# GoogleTest only for tests
enable_testing()
add_subdirectory(tests)


