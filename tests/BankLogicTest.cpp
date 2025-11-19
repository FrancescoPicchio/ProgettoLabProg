#include <gtest/gtest.h>
#include "../Account.h"
#include "../User.h"
#include "../AppDataManager.h"
#include "../Transaction.h"

//FIXME Change BankLogicTest class name and file name to something more appropriate
//for example BusinessLogicTest
class BankLogicTest : public ::testing::Test {
protected:
    void SetUp() override {
        adm = new AppDataManager(usersTestFile, accountTestFile, transactionTestFile, userIdTrackerFile, accountIdTrackerFile);
        //initializes the csv files correctly
        adm->load_app_data();
        userA = adm->create_user("Andy", "Doe");
        userB = adm->create_user("Beatrice", "Smith");
        accountA1 = userA->open_account("AndyFirstAccount", adm);
        accountA2 = userA->open_account("AndySecondAccount", adm);
        accountB = userB->open_account("BeatriceAccount", adm);
    }

    void TearDown() override {
        delete adm;
        //cleans up csv files that were initialized with AppDataManager
        std::remove("users_test.csv");
        std::remove("accounts_test.csv");
        std::remove("transactions_test.csv");
        std::remove("user_id_tracker_test.csv");
        std::remove("account_id_tracker_test.csv");
    }

    Account* accountA1;
    Account* accountA2;
    Account* accountB;
    User* userA;
    User* userB;
    AppDataManager* adm;
    std::string usersTestFile = "users_test.csv";
    std::string accountTestFile = "accounts_test.csv";
    std::string transactionTestFile = "transactions_test.csv";
    std::string userIdTrackerFile = "user_id_tracker_test.csv";
    std::string accountIdTrackerFile = "account_id_tracker_test.csv";
};

TEST_F(BankLogicTest, UserConstructorTest) {
    EXPECT_EQ(userA->get_legal_name(), "Andy Doe");
    EXPECT_EQ(userA->get_name(), "Andy");
    EXPECT_EQ(userA->get_surname(), "Doe");
    EXPECT_EQ(userA->get_id(), 1);
    EXPECT_EQ(userA->get_total_balance(), 0);
    EXPECT_EQ(userA->get_account(accountA1->get_id()), accountA1);
}

TEST_F(BankLogicTest, AccountConstructorTest) {
    EXPECT_EQ(accountA1->get_name(), "AndyFirstAccount");
    EXPECT_EQ(accountA1->get_balance(), 0);
    EXPECT_EQ(accountA1->get_owner(), userA);
    EXPECT_EQ(accountA1->get_id(), 1);
}

TEST_F(BankLogicTest, TransactionConstructionTest) {
    accountA1->set_balance(300, adm);
    accountB->set_balance(0, adm);

    EXPECT_TRUE(accountA1->make_transaction(accountB, 200, adm));
    EXPECT_EQ(accountA1->get_balance(), 100);
    EXPECT_EQ(accountB->get_balance(), 200);

    EXPECT_FALSE(accountB->make_transaction(accountA1, 0, adm));
    EXPECT_EQ(accountA1->get_balance(), 100);
    EXPECT_EQ(accountB->get_balance(), 200);

    accountA2->set_balance(500, adm);

    EXPECT_FALSE(accountA1->make_transaction(accountA2, 1000, adm));
    EXPECT_EQ(accountA1->get_balance(), 100);
    EXPECT_EQ(accountA2->get_balance(), 500);

    EXPECT_FALSE(accountA2->make_transaction(accountA1, -100, adm));
    EXPECT_EQ(accountA1->get_balance(), 100);
    EXPECT_EQ(accountA2->get_balance(), 500);
}