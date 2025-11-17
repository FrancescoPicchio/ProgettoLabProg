#include <gtest/gtest.h>
#include "../Account.h"
#include "../User.h"
#include "../AppDataManager.h"
#include "../Transaction.h"

class AccountTest : public ::testing::Test {
protected:
    void SetUp() override {
        adm = new AppDataManager();
        //initializes the csv files correctly
        adm->load_app_data();
        user = adm->create_user("Jhon", "Doe");
        account1 = new Account("Account1", user, adm);
        account2 = new Account("Account2", user, adm);
    }

    void TearDown() override {
        delete account1;
        delete account2;
        delete user;
        delete adm;
        //cleans up csv files that were initialized with AppDataManager
        remove("accounts.csv");
        remove("users.csv");
        remove("transactions.csv");
        remove("account_id_tracker.csv");
        remove("user_id_tracker.csv");
    }

    Account* account1;
    Account* account2;
    User* user;
    AppDataManager* adm;
};

TEST_F(AccountTest, ConstructorTest) {
    EXPECT_EQ(account1->get_name(), "Account1");
    EXPECT_EQ(account1->get_balance(), 0);
    EXPECT_EQ(account1->get_owner(), user);
    EXPECT_EQ(account1->get_id(), 1);
}


TEST_F(AccountTest, TransactionTest) {
    account1->set_balance(1000, adm);
    account2->set_balance(0, adm);
    
    // Valid transaction
    EXPECT_TRUE(account1->make_transaction(account2, 500, adm));
    EXPECT_EQ(account1->get_balance(), 500);
    EXPECT_EQ(account2->get_balance(), 500);
    
    // Invalid transaction - insufficient funds
    EXPECT_FALSE(account1->make_transaction(account2, 1000, adm));
    
    // Invalid transaction - negative amount
    EXPECT_FALSE(account1->make_transaction(account2, -100, adm));
}

TEST_F(AccountTest, GetTransactionsTest) {
    account1->set_balance(1000, adm);
    account2->set_balance(0, adm);
    
    account1->make_transaction(account2, 500, adm);
    
    auto transactions1 = account1->get_transactions();
    auto transactions2 = account2->get_transactions();
    
    EXPECT_EQ(transactions1.size(), 1);
    EXPECT_EQ(transactions2.size(), 1);
}