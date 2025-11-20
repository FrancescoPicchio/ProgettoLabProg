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
    std::string usersFile;
    std::string accountsFile;
    std::string transactionsFile;
    std::string user_id_tracker_test_file;
    std::string account_id_tracker_test_file;
public:
    //Use custom file names when testing, for safety
    AppDataManager(std::string uf="users.csv", std::string af="accounts.csv", std::string tf="transactions.csv", std::string uidf="user_id_tracker.csv", std::string aidf="account_id_tracker.csv"){
        usersFile = uf;
        accountsFile = af;
        transactionsFile = tf;
        user_id_tracker_test_file = uidf;
        account_id_tracker_test_file = aidf;
    }

    void load_csv_file(const std::string& filename);
    void load_all_csv_files();
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

    std::string getAccountIdTrackerFileName(){
        return account_id_tracker_test_file;
    }
};


#endif //PROGETTOLABPROG_APPDATAMANAGER_H
