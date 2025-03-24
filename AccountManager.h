//
// Created by fpicc on 08/03/2025.
//

#ifndef PROGETTOLABPROG_ACCOUNTMANAGER_H
#define PROGETTOLABPROG_ACCOUNTMANAGER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include "UserManager.h"
#include "Account.h"

//handles loading and saving users to a accounts.csv
//maybe make AccountManager a singleton to avoid issues
class AccountManager {
private:
    std::string filename;
    //used a normal pointer because accounts should only be deleted if their user is deleted
    //std::map<int, Account*> accounts;

public:
    AccountManager(const std::string fn): filename(fn){};

    //Method to read accounts from a file and returns true if accounts loaded successfully and populates the map accounts
    bool loadAccounts(const std::map<int, std::unique_ptr<User>>& users, std::map<int, Account*>& accounts);

    //Method to save a new account to the CSV file
    bool saveAccount(Account* acc);

    //Method to update the account's balance if it changes
    bool updateAccountBalance(Account* a) const;
};


#endif //PROGETTOLABPROG_ACCOUNTMANAGER_H
