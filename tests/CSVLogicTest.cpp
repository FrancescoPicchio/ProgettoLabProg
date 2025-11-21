#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include "../Account.h"
#include "../User.h"
#include "../AppDataManager.h"
#include "../Transaction.h"

namespace { //added to avoid conflicts with other similarly named functions in test suite
    std::string getLineFromCSV(std::string filename){
        std::ifstream file(filename);
        std::string line;
        std::getline(file, line);
        file.close();
        return line;
    }
}

class CSVLogicTest : public ::testing::Test {
protected:
    void SetUp() override {
        adm = new AppDataManager(user_test_file, accounts_test_file, transactions_test_file, user_id_tracker_test_file, account_id_tracker_test_file);
    }
    void TearDown() override {
        delete adm;
        std::filesystem::remove(user_test_file);
        std::filesystem::remove(accounts_test_file);
        std::filesystem::remove(transactions_test_file);
        std::filesystem::remove(user_id_tracker_test_file);
        std::filesystem::remove(account_id_tracker_test_file);
    }

    AppDataManager* adm;
    std::string user_test_file = "users_test.csv";
    std::string accounts_test_file = "accounts_test.csv";
    std::string transactions_test_file = "transactions_test.csv";
    std::string user_id_tracker_test_file = "user_id_tracker_test.csv";
    std::string account_id_tracker_test_file = "account_id_tracker_test.csv";
};

TEST_F(CSVLogicTest, SaveNewUserToCSV){
    auto user = adm->create_user("Andy", "Johnson");

    std::ifstream file(user_test_file);
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

    auto line = getLineFromCSV(accounts_test_file);
    std::string expected = "10,AccountTest,1,500";
    ASSERT_EQ(line, expected);
}

TEST_F(CSVLogicTest, SaveNewTransactionToCSV) {
    auto user =  User("Andy", "Johnson", 1);
    auto account1 =  Account(1, "AccountTest1", &user, 500);
    auto account2 = Account(2, "AccountTest2", &user, 200);
    auto transaction = Transaction(&account1, &account2, 100);

    ASSERT_TRUE(adm->save_transaction_to_CSV(&transaction));

    auto line = getLineFromCSV(transactions_test_file);
    std::string expected = "1,2,100";
    ASSERT_EQ(line, expected);
}

TEST_F(CSVLogicTest, UpdatingBalanceToCSV) {
    auto user = User("Andy", "Johnson", 1);
    auto account = user.open_account("AccountTest", adm);

    //Testing for correct inputs
    ASSERT_TRUE(account->set_balance(200,adm));
    auto line = getLineFromCSV(accounts_test_file);
    std::string expected = "1,AccountTest,1,200";
    ASSERT_EQ(line, expected);

    ASSERT_TRUE(account->add_balance(300,adm));
    line = getLineFromCSV(accounts_test_file);
    expected = "1,AccountTest,1,500";
    ASSERT_EQ(line, expected);

    ASSERT_TRUE(account->remove_balance(100,adm));
    line = getLineFromCSV(accounts_test_file);
    expected = "1,AccountTest,1,400";
    ASSERT_EQ(line, expected);

    //Testing for wrong input
    ASSERT_FALSE(account->add_balance(-200,adm));
    line = getLineFromCSV(accounts_test_file);
    ASSERT_EQ(line, expected);

    ASSERT_FALSE(account->remove_balance(-200,adm));
    line = getLineFromCSV(accounts_test_file);
    ASSERT_EQ(line, expected);

    ASSERT_FALSE(account->remove_balance(10000,adm));
    line = getLineFromCSV(accounts_test_file);
    ASSERT_EQ(line, expected);

    ASSERT_FALSE(account->add_balance(0,adm));
    line = getLineFromCSV(accounts_test_file);
    ASSERT_EQ(line, expected);

    ASSERT_FALSE(account->remove_balance(0,adm));
    line = getLineFromCSV(accounts_test_file);
    ASSERT_EQ(line, expected);
}

//TODO maybe write a separate test file or fixture for the loads
//TODO write test for load users
//TODO write test for load accounts
//TODO write test for load transactions