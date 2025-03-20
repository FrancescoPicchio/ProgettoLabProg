//
// Created by fpicc on 08/03/2025.
//

#include "TransactionManager.h"

bool TransactionManager::loadTransactions(const std::map<int, Account*>& accounts) {
    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cerr << "Could not open the file " << filename << std::endl;
        return false;
    }

    std::string line;
    std::string id_sender_str, id_receiver_str, amount_str;
    int id_sender, id_receiver, amount;
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        //lines have to be formatted id_sender, id_receiver, amount
        if(std::getline(ss, id_sender_str, ',') && std::getline(ss, id_receiver_str, ',') && std::getline(ss, amount_str, ',')) {
            id_sender = std::stoi(id_sender_str);
            id_receiver = std::stoi(id_receiver_str);
            amount = std::stoi(amount_str);
            auto *transaction = new Transaction(accounts.at(id_sender), accounts.at(id_receiver), amount);
            transactions.push_back(transaction);
        }else {
            std::cerr << "Error reading line: " << line << std::endl;
            continue; //skips lines with wrong formatting
        }
    }

    file.close();
    return true;
}