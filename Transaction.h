//
// Created by fpicc on 07/03/2025.
//

#ifndef PROGETTOLABPROG_TRANSACTION_H
#define PROGETTOLABPROG_TRANSACTION_H

#include "Account.h"

class Transaction {
private:
    Account* sender;
    Account* receiver;
    int amount;
    int fee = 0; //TODO implement fee, it should be different depending if the transaction is between accounts of the same user or not, and maybe other stuff
public:
    Transaction(Account* s, Account* r, int a): sender(s), receiver(r), amount(a){}

    int getAmount() const {
        return amount;
    }

    Account* getSender() const {
        return sender;
    }

    Account* getReceiver() const {
        return receiver;
    }

};


#endif //PROGETTOLABPROG_TRANSACTION_H
