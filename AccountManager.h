//
// Created by fpicc on 08/03/2025.
//

#ifndef PROGETTOLABPROG_ACCOUNTMANAGER_H
#define PROGETTOLABPROG_ACCOUNTMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Account.h"
/*
//handles loading and saving users to a accounts.csv
class AccountManager {
private:
    std::string filename;

public:
    AccountManager(const std::string fn): filename(fn){};

    // Method to read accounts from a file and return them as a vector of Account objects
    std::vector<Account> loadAccounts() {
        std::vector<Account> accounts;
        std::ifstream file(filename);
        std::string line;

        //FIXME chatgpt answer, has incorrect account fields and can't add an owner to the account, because it only stores its name/id
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            int accountID;
            std::string ownerName;
            double balance;

            // Parse CSV line
            std::getline(ss, ownerName, ',');
            ss >> accountID;
            ss.ignore(1, ','); // Ignore the comma
            ss >> balance;
        }
        return accounts;
    }

    //FIXME chatgpt answer, has incorrect account fields
    // Method to save a new account to the CSV file
    void saveAccount(const Account& acc) {
        std::ofstream file(filename, std::ios::app);
        file << acc.accountID << "," << acc.ownerName << "," << acc.balance << "\n";
    }
};
*/

#endif //PROGETTOLABPROG_ACCOUNTMANAGER_H
