//
// Created by fpicc on 07/03/2025.
//

#ifndef PROGETTOLABPROG_TRANSACTION_H
#define PROGETTOLABPROG_TRANSACTION_H

#include <memory>
#include <iostream>
#include <ctime>

//forward declaration of TransactionManager to avoid circular dependency
class TransactionManager;
class Account;


class Transaction {
private:
    Account* sender;
    Account* receiver;
    int amount;
    std::string date;
    //int fee = 0; //TODO implement fee, it should be different depending on if the transaction is between accounts of the same user or not, and maybe other stuff

public:
    //Never call this directly, always use makeTransaction
    Transaction(Account* s, Account* r, int a): sender(s), receiver(r), amount(a){
        //initializes transaction with current time
        std::time_t now = std::time(nullptr);
        date = std::ctime(&now);
        //ctime returns a string with a newline character at the end, this gets rid of it
        date = date.substr(0,date.length()-1);
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

    void printInfo() const;

    void printDate() const {
        std::cout << "Date: " << date;
    }

    std::string getDate() const {
        return date;
    }

};


#endif //PROGETTOLABPROG_TRANSACTION_H
