//
// Created by fpicc on 17/04/2025.
//

#include "AppDataManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

//returns true only if it loads all the data from the different classes correctly
bool AppDataManager::loadAppData() {
    return (loadUsers() && loadAccounts() && loadTransactions());
}

bool AppDataManager::loadUsers() {
    std::ifstream file(usersFile);
    if (!file.is_open()) {
        std::cerr << "Could not open the file " << usersFile << std::endl;
        return false;
    }

    std::string line;
    std::string name, surname, id_str;
    int id;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        //lines have to be formatted "id,name,surname" without the quotes. Important id first to make it easier to lookup ids faster
        //the >> operator for stringstream automatically converts string into int
        if (std::getline(ss, id_str, ',') && std::getline(ss, name, ',') && std::getline(ss, surname, ',')) {
            //converts string into int
            id = std::stoi(id_str);
            // Create a new user and add to the map (using id as the key)
            auto user = std::make_unique<User>(name, surname, id);
            users[id] = std::move(user);
        } else {
            std::cerr << "Error reading line: " << line << std::endl;
            continue; //skips lines with wrong formatting
        }
    }

    file.close();
    return true;
}

bool AppDataManager::loadAccounts() {
    std::ifstream file(accountsFile);
    if (!file.is_open()) {
        std::cerr << "Could not open the file " << accountsFile << std::endl;
        return false;
    }

    std::string line;
    //getline() only works with strings
    std::string id_account_str, name, id_owner_str, balance_str;
    int id_account, id_owner, balance;
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        //lines have to be formatted "id_account, name, id_owner, balance" without the quotes. Important that id_account is first for faster lookups
        if(std::getline(ss, id_account_str, ',') && std::getline(ss, name, ',') && std::getline(ss, id_owner_str, ',') && std::getline(ss, balance_str, ',')) {
            id_account = std::stoi(id_account_str);
            id_owner = std::stoi(id_owner_str);
            balance = std::stoi(balance_str);
            auto *account = users.at(id_owner)->openAccount(id_account, name, balance);
            accounts[id_account] = account;
        }else {
            std::cerr << "Error reading line: " << line << std::endl;
            continue; //skip lines with wrong formatting
        }
    }

    file.close();
    return true;
}

bool AppDataManager::loadTransactions() {
    std::ifstream file(transactionsFile);
    if(!file.is_open()) {
        std::cerr << "Could not open the file " << transactionsFile << std::endl;
        return false;
    }

    std::string line;
    std::string id_sender_str, id_receiver_str, amount_str;
    int id_sender, id_receiver, amount;
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        //lines have to be formatted "id_sender, id_receiver, amount" without the quotes
        if(std::getline(ss, id_sender_str, ',') && std::getline(ss, id_receiver_str, ',') && std::getline(ss, amount_str, ',')) {
            id_sender = std::stoi(id_sender_str);
            id_receiver = std::stoi(id_receiver_str);
            amount = std::stoi(amount_str);
            auto t =  std::make_shared<Transaction>(accounts.at(id_sender), accounts.at(id_receiver), amount);
            accounts.at(id_sender)->addTransaction(t);
            accounts.at(id_receiver)->addTransaction(t);
        }else {
            std::cerr << "Error reading line: " << line << std::endl;
            continue; //skips lines with wrong formatting
        }
    }

    file.close();
    return true;
}

User* AppDataManager::createUser(const std::string &n, const std::string &s) {
    int id = generateNextId("user_id_tracker.csv");
    auto new_user = std::make_unique<User>(n, s, id);
    User* raw_new_user_ptr = new_user.get();

    //saves the new user in the csv file
    std::ofstream file(usersFile, std::ios::app);
    if(!file.is_open()){
        std::cerr << "Error saving user " << new_user->getLegalName() << "to users.csv file" << std::endl;
        return nullptr;
    }
    std::string data = std::to_string(new_user->getId()) + ',' + new_user->getName() + ',' + new_user->getSurname();
    file << data;
    file.close();

    users[new_user->getId()] = std::move(new_user);
    return raw_new_user_ptr;
}