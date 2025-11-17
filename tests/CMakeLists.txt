include(FetchContent)
#added this include because otherwise it gave an error (on VSCode) because DartConfiguration.tcl was missing
include(CTest)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip)
FetchContent_MakeAvailable(googletest)


add_executable(runTests AccountTest.cpp
        ../User.cpp
        ../Account.cpp
        ../Transaction.cpp
        ../IdUtil.cpp
        ../AppDataManager.cpp
        ../AppDataManager.h
        )

# Link GoogleTest to the test executable
target_link_libraries(runTests gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(runTests)
# Register the test
add_test(NAME runTests COMMAND runTests)