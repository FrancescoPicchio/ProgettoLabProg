//
// Created by fpicc on 07/03/2025.
//

#ifndef PROGETTOLABPROG_TRANSACTION_H
#define PROGETTOLABPROG_TRANSACTION_H

#include <memory>
#include <iostream>

//forward declaration of TransactionManager to avoid circular dependecy
class TransactionManager;
class Account;


class Transaction {
private:
    Account* sender;
    Account* receiver;
    int amount;
    TransactionManager* manager;
    //TODO
    //int fee = 0; //TODO implement fee, it should be different depending if the transaction is between accounts of the same user or not, and maybe other stuff

public:
    //Never call this directly, always use makeTransaction
    Transaction(Account* s, Account* r, int a, TransactionManager* tm): sender(s), receiver(r), amount(a), manager(tm){}

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

    void printInfo() const;

};


#endif //PROGETTOLABPROG_TRANSACTION_H
