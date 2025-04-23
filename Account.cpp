//
// Created by fpicc on 07/03/2025.
//

#include "Account.h"
#include "User.h"
#include "IdUtil.h"
#include "Transaction.h"
#include "AppDataManager.h"
#include <fstream>
#include <sstream>

Account::Account(std::string n, User *u, AppDataManager* adm): name(n), owner(u), balance(0){
    id = generateNextId("account_id_tracker.csv");
    adm->addAccount(this);
}

Account::Account(int i, std::string n, User *u, int b): id(i), name(n), owner(u), balance(b){}

void Account::printInfo() const {
    std::cout << "id: " << id << ", name: " << name << ", owner: " << owner->getLegalName() << ", balance: " << balance << std::endl;
}

std::vector<Transaction*> Account::getTransactions() const {
    std::vector<Transaction*> raw_ptrs;
    for (const auto& sptr : transactions) {
        raw_ptrs.push_back(sptr.get());
    }
    return raw_ptrs;
};

//Passing transactionManager so that I can notify it when the transaction is created
bool Account::makeTransaction(Account *receiver, int amount) {
    //You can't send a negative amount of money
    if(amount <= 0){
        std::cout << "You've inputted a negative amount, please input a positive whole number" << std::endl;
        return false;
    }
    //You can't send money you don't have
    else if(this->getBalance() >= amount) {
        auto t =  std::make_shared<Transaction>(this, receiver, amount);
        addTransaction(t);
        setBalance(getBalance() - amount);
        receiver->addTransaction(t);
        receiver->setBalance(receiver->getBalance() + amount);
        if(!saveTransactionToCSV(t.get()))
            return false;
        if(updateBalanceCsv() && receiver->updateBalanceCsv()) {
            std::cout << "Transaction successful!" << std::endl;
            return true;
        }
        else
            return false;
        }
    else {
        std::cout << "Not enough money in your account." << std::endl;
        return false;
    }
}

void Account::printTransactions() const {
    std::cout << this->getName() << "'s transactions are:" << std::endl << std::endl;
    for(auto i : transactions){
        i->printInfo();
    }
}

bool Account::saveTransactionToCSV(Transaction *t) {
    std::ofstream file("transactions.csv", std::ios::app);
    if(!file.is_open()){
        std::cerr << "Error saving transaction " << " to transactions.csv" << std::endl;
        return false;
    }
    std::string data = std::to_string(t->getSender()->getId()) + ',' + std::to_string(t->getReceiver()->getId()) + ',' + std::to_string(t->getAmount());
    file << data << '\n';
    file.close();
    return true;
}

bool Account::updateBalanceCsv() const {
    std::ifstream original_file("accounts.csv");
    std::ofstream updated_file("accounts_temp.csv");
    std::string line, data;
    std::string temp_id_account, temp_name, temp_id_owner, temp_balance;
    std::ostringstream oss;

    while(std::getline(original_file, line)){
        std::stringstream ss(line);
        oss.str("");
        data = "";
        if(std::getline(ss, temp_id_account, ',') && std::getline(ss, temp_name, ',') && std::getline(ss, temp_id_owner, ',') && std::getline(ss, temp_balance, ',')){
            //checks if the current account is the same as this account
            if(std::stoi(temp_id_account) != id){
                //using oss to avoid having to concatenate in line a string with +, because it'd create many unecessary temporary strings
                oss << temp_id_account << ',' << temp_name << ',' << temp_id_owner << ',' << temp_balance;
                data.append(oss.str());
                updated_file << data << '\n';
            }
            else {
                //inputs updated balance if the temp_id matches with this account
                oss << temp_id_account << ',' << temp_name << ',' << temp_id_owner << ',' << balance;
                data.append(oss.str());
                updated_file << data << '\n';
            }
        }
        else {
            std::cerr << "Error reading line from accounts.csv when updating balance of " << name << std::endl;
            return false;
        }
    }
    //files must be closed before removing and renaming them
    original_file.close();
    updated_file.close();
    remove("accounts.csv");
    rename("accounts_temp.csv", "accounts.csv");
    return true;
}