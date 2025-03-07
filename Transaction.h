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
};


#endif //PROGETTOLABPROG_TRANSACTION_H
