//
// Created by fpicc on 08/03/2025.
//

#include "AccountManager.h"

//maybe take userManager as argument instead of map to be sure to have the correct map
bool AccountManager::loadAccounts( const std::map<int, std::unique_ptr<User>>& users) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file " << filename << std::endl;
        return false;
    }

    std::string line;
    std::string id_account_str, name, id_owner_str, balance_str;
    //owner id and balance are gotten directly as int type because they're at the end of the line
    int id_account, id_owner, balance;
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        //lines have to be formatted id_account, name, id_owner, balance. Important that id_account is first for faster lookups
        if(std::getline(ss, id_account_str, ',') && std::getline(ss, name, ',') && std::getline(ss, id_owner_str, ',') && std::getline(ss, balance_str, ',')) {
            id_account = std::stoi(id_account_str);
            id_owner = std::stoi(id_owner_str);
            balance = std::stoi(balance_str);
            //.get() converts shared_ptr to normal ptr
            auto *account = new Account(id_account, name, users.at(id_owner).get(), balance, this);
            accounts[id_account] = account;
        }else {
            std::cerr << "Error reading line: " << line << std::endl;
            continue; //skip lines with wrong formatting
        }
    }

    file.close();
    return true;
}

bool AccountManager::saveAccount( Account* a) {
    accounts.insert(std::make_pair(a->getId(), a));
    std::ofstream file(filename, std::ios::app);
    if(!file.is_open()){
        std::cerr << "Error saving account " << a->getName() << " to accounts.csv" << std::endl;
        return false;
    }
    std::string data = std::to_string(a->getId()) + ',' + a->getName() + ',' + std::to_string(a->getOwner()->getId()) + ',' + std::to_string(a->getBalance());
    file << data << std::endl;
    file.close();
    return true;
}