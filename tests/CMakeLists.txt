include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)


add_executable(runAllTests runAllTests.cpp AccountTest.cpp
        ../User.cpp
        ../Account.cpp
        ../Transaction.cpp
        ../IdUtil.cpp
        ../AppDataManager.cpp
        ../AppDataManager.h)

# Link GoogleTest to the test executable
target_link_libraries(runAllTests gtest gtest_main gmock gmock_main)

# Register the test
add_test(NAME runAllTests COMMAND runAllTests)