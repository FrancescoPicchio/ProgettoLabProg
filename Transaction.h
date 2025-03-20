//
// Created by fpicc on 07/03/2025.
//

#ifndef PROGETTOLABPROG_TRANSACTION_H
#define PROGETTOLABPROG_TRANSACTION_H

#include "Account.h"
#include <memory>
#include <iostream>


class Transaction {
private:
    Account* sender;
    Account* receiver;
    int amount;
    //int fee = 0; //TODO implement fee, it should be different depending if the transaction is between accounts of the same user or not, and maybe other stuff

public:
    Transaction(Account* s, Account* r, int a): sender(s), receiver(r), amount(a){
        sender->addTransaction(std::make_shared<Transaction>(*this));
        receiver->addTransaction(std::make_shared<Transaction>(*this));

    }

    //no setters because once a transaction is created you shouldn't be able to modify it
    int getAmount() const {
        return amount;
    }

    Account* getSender() const {
        return sender;
    }

    Account* getReceiver() const {
        return receiver;
    }

    void printInfo() const {
        std::cout << "sender: " << sender->getName() << ", receiver: " << receiver->getName() << ", amount: " << amount << std::endl;
    }

};


#endif //PROGETTOLABPROG_TRANSACTION_H
