#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include "../Account.h"
#include "../User.h"
#include "../AppDataManager.h"
#include "../Transaction.h"

class CSVLogicTest : public ::testing::Test {
protected:
    void SetUp() override {
        adm = new AppDataManager(usersTestFile, accountTestFile, transactionTestFile, userIdTrackerFile, accountIdTrackerFile);
    }
    void TearDown() override {
        delete adm;
        std::remove("users_test.csv");
        std::remove("accounts_test.csv");
        std::remove("transactions_test.csv");
        std::remove("user_id_tracker_test.csv");
        std::remove("account_id_tracker_test.csv");
    }

    AppDataManager* adm;
    std::string usersTestFile = "users_test.csv";
    std::string accountTestFile = "accounts_test.csv";
    std::string transactionTestFile = "transactions_test.csv";
    std::string userIdTrackerFile = "user_id_tracker_test.csv";
    std::string accountIdTrackerFile = "account_id_tracker_test.csv";
};

TEST_F(CSVLogicTest, SaveNewUserToCSV){
    auto user = adm->create_user("Andy", "Johnson");

    ASSERT_TRUE(std::filesystem::exists(usersTestFile));

    std::ifstream file(usersTestFile);
    std::string line;
    std::getline(file, line);
    file.close();

    std::string expected = "1,Andy,Johnson";
    ASSERT_EQ(line, expected);
}

TEST_F(CSVLogicTest, SaveNewAccountToCSV) {
    auto user =  User("Andy", "Johnson", 1);
    auto account =  Account(10, "AccountTest", &user, 500);

    ASSERT_TRUE(adm->save_new_account_to_CSV(&account));

    ASSERT_TRUE(std::filesystem::exists(accountTestFile));
    std::ifstream file(accountTestFile);
    std::string line;
    std::getline(file, line);
    file.close();

    std::string expected = "10,AccountTest,1,500";
    ASSERT_EQ(line, expected);
}

//TODO write test for save new transaction
TEST_F(CSVLogicTest, SaveNewTransactionToCSV) {
    auto user =  User("Andy", "Johnson", 1);
    auto account1 =  Account(1, "AccountTest1", &user, 500);
    auto account2 = Account(2, "AccountTest2", &user, 200);
    auto transaction = Transaction(&account1, &account2, 100);

    ASSERT_TRUE(adm->save_transaction_to_CSV(&transaction));

    ASSERT_TRUE(std::filesystem::exists(transactionTestFile));
    std::ifstream file(transactionTestFile);
    std::string line;
    std::getline(file, line);
    file.close();

    std::string expected = "1,2,100";
    ASSERT_EQ(line, expected);
}

//TODO write test for update account balance

//TODO maybe write a separate test file or fixture for the loads
//TODO write test for load users
//TODO write test for load accounts
//TODO write test for load transactions