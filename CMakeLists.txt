cmake_minimum_required(VERSION 3.30)
project(progettoLabProg)

set(CMAKE_CXX_STANDARD 20)

# Add the tests
enable_testing()
add_subdirectory(tests)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

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
        IdUtil.h
        IdUtil.cpp
        tests/runAllTests.cpp)

# Link GoogleTest to the test executable
target_link_libraries(progettoLabProg gtest gtest_main gmock gmock_main)



