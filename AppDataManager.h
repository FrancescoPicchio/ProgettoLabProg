//
// Created by fpicc on 17/04/2025.
//

#ifndef PROGETTOLABPROG_APPDATAMANAGER_H
#define PROGETTOLABPROG_APPDATAMANAGER_H

#include <map>
#include <vector>
#include <memory>
#include <string>
#include "User.h"
#include "Account.h"
#include "IdUtil.h"

//Handles loading object data from csv files, for User, Account and Transaction classes.
//Also stores all currently initiated Users and Accounts in maps. Transactions aren't stored because they can easily be fetched from the Account map.
//Also handles creating new users so to maintain a map of unique ptrs of them, for proper memory management.
class AppDataManager {
private:
    std::map<int, std::unique_ptr<User>> users;
    std::map<int, Account*> accounts;
    std::string usersFile = "users.csv";
    std::string accountsFile = "accounts.csv";
    std::string transactionsFile = "transactions.csv";
public:
    bool load_app_data();
    bool load_users();
    bool load_accounts();
    bool load_transactions();
    User* create_user(const std::string& n, const std::string& s);
    bool save_new_account_to_CSV(Account* a);
    bool save_transaction_to_CSV(Transaction *t);
    bool update_account_balance_CSV(Account* account);

    void add_account(Account* a){
        accounts[a->get_id()] = a;
    }
    const std::map<int, std::unique_ptr<User>>& get_users() const {
        return users;
    }
    const std::map<int, Account*>& get_accounts() const {
        return accounts;
    }
};


#endif //PROGETTOLABPROG_APPDATAMANAGER_H
