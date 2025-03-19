//
// Created by fpicc on 07/03/2025.
//

#include "User.h"
#include <memory>

void User::printAccounts() const {
    //prints account names and their associated balance
    std::cout << getLegalName() + "'s accounts are: " << std::endl;
    for(auto i = accounts.begin(); i != accounts.end(); ++i) {
        std::string s = std::to_string(i->second->getBalance());
        std::cout << i->second->getName() + "with balance:" + s << std::endl;
    }
};

void User::makeTransaction(Account *sender, Account *receiver, int amount) {
    //Only the owner of the account can send money from it
    if(this->id == sender->getOwner()->id) {
        //You can't send money you don't have
        if(sender->getBalance() >= amount) {
            auto *t = new Transaction(sender, receiver, amount);
            sender->setBalance(sender->getBalance() - amount);
            sender->addTransaction(std::make_shared<Transaction>(*t));
            receiver->setBalance(receiver->getBalance() + amount);
            receiver->addTransaction(std::make_shared<Transaction>(*t));
            std::cout << "Transaction successful!" << std::endl;
            //TODO implement saving transaction to transactions.csv and updating balances on accounts.csv
        }
        else {
            std::cout << "Not enough money in your account." << std::endl;
        }
    }
    else {
        std::cout << "You can't send money from an account you don't own!" << std::endl;
    }
}