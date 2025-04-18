add_executable(runAllTests runAllTests.cpp AccountTest.cpp
        ../User.cpp
        ../Account.cpp
        ../Transaction.cpp
        ../AccountManager.cpp
        ../UserManager.cpp
        ../TransactionManager.cpp
        ../IdUtil.cpp
        ../AppDataManager.cpp
        ../AppDataManager.h)

# Link GoogleTest to the test executable
target_link_libraries(runAllTests gtest gtest_main gmock gmock_main)

# Register the test
add_test(NAME runAllTests COMMAND runAllTests)