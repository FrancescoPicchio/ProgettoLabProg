//
// Created by fpicc on 07/03/2025.
//

#include "User.h"
#include <memory>
#include "IdManager.h"
#include "UserManager.h"

User::User(std::string n, std::string s, UserManager* m): name(n), surname(s), manager(m){
    id = generateNextId("user_id_tracker.csv");
}

void User::printAccounts() const {
    //prints account names and their associated balance
    std::cout << getLegalName() + "'s accounts are: " << std::endl;
    for(auto i = accounts.begin(); i != accounts.end(); ++i) {
        std::string s = std::to_string(i->second->getBalance());
        std::cout << i->second->getName() + " with balance: " + s << std::endl;
    }
};

//Passing transactionManager so that I can notify it when the transaction is created
void User::makeTransaction(Account *sender, Account *receiver, int amount, TransactionManager* tm) {
    //Only the owner of the account can send money from it
    if(this->id == sender->getOwner()->getId()) {
        //You can't send money you don't have
        if(sender->getBalance() >= amount) {
            auto t =  std::make_shared<Transaction>(sender, receiver, amount);
            sender->addTransaction(t);
            sender->setBalance(sender->getBalance() - amount);
            receiver->addTransaction(t);
            receiver->setBalance(receiver->getBalance() + amount);
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