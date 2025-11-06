#include <gtest/gtest.h>
#include "../User.h"
#include "../Account.h"

/*
class MockAccountManager : public AccountManager {
public:
    explicit MockAccountManager(std::string fn): AccountManager(fn) {}
    MOCK_METHOD(bool, saveAccount, (Account* acc), (override));
};

class MockUserManager : public UserManager {
public:
    explicit MockUserManager(std::string fn): UserManager(fn) {}
    MOCK_METHOD(bool, saveUser, (User* u), (override));
};

class UserTest : public ::testing::Test {
protected:
    MockUserManager* mock_um;
    User* user;
    std::string account_name;
    int balance;
    std::map<int, Account*>* accounts_map;
    MockAccountManager* mock_am;

    void SetUp() override {
        mock_um = new MockUserManager("test");
        user = new User("name", "surname", 1, mock_um);
        account_name = "conto test";
        balance = 1000;
        mock_am = new MockAccountManager("test");
    }

    void TearDown() override {
        delete user;
        delete mock_am;
    }
};

TEST_F(UserTest, TestSuccessfulAccountCreation){
    //Expects to make 0 call to the saveAccount method
    EXPECT_CALL(*mock_am, saveAccount(testing::_)).Times(0);
    bool result = user->open_account(1, account_name, balance, mock_am);
    //Check if account creation was successfull
    EXPECT_TRUE(result);
    //checks if Id was assigned correctly
    EXPECT_EQ(user->get_account(1)->get_id(), 1);
    //checks if account_name was assigned correctly
    EXPECT_EQ(user->get_account(1)->get_name(), account_name);
    //checks if account's owner was assigned correctly, by comparing the Ids of the user and owner field
    EXPECT_EQ(user->get_account(1)->get_owner()->get_id(), 1);
    //checks if balance was assigned correctly
    EXPECT_EQ(user->get_account(1)->get_balance(), 1000);
}
*/