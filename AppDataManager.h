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
    bool loadAppData();
    bool loadUsers();
    bool loadAccounts();
    bool loadTransactions();
    //creates and saves to csv a new user
    User* createUser(const std::string& n, const std::string& s);
    void addAccount(Account* a){
        accounts[a->getId()] = a;
    }
    const std::map<int, std::unique_ptr<User>>& getUsers() const {
        return users;
    }
    const std::map<int, Account*>& getAccounts() const {
        return accounts;
    }
};


#endif //PROGETTOLABPROG_APPDATAMANAGER_H
