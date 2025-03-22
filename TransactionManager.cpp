//
// Created by fpicc on 08/03/2025.
//

#include "TransactionManager.h"
#include "User.h"

bool TransactionManager::loadTransactions(const std::map<int, Account*>& accounts, std::vector<Transaction*>& transactions) {
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
            auto t =  std::make_shared<Transaction>(accounts.at(id_sender), accounts.at(id_receiver), amount, this);
            accounts.at(id_sender)->addTransaction(t);
            accounts.at(id_receiver)->addTransaction(t);
            transactions.push_back(t.get());
        }else {
            std::cerr << "Error reading line: " << line << std::endl;
            continue; //skips lines with wrong formatting
        }
    }

    file.close();
    return true;
}

//TODO add the option to add transaction to transactions vector when this method is called
bool TransactionManager::saveTransaction(Transaction* t){
    std::ofstream file(filename, std::ios::app);
    if(!file.is_open()){
        std::cerr << "Error saving transaction " << " to transactions.csv" << std::endl;
        return false;
    }
    std::string data = std::to_string(t->getSender()->getId()) + ',' + std::to_string(t->getReceiver()->getId()) + ',' + std::to_string(t->getAmount());
    file << data << std::endl;
    file.close();
    return true;
}