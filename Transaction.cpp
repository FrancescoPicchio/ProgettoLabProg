//
// Created by fpicc on 07/03/2025.
//

#include "Transaction.h"
#include "TransactionManager.h"
#include "Account.h"

void Transaction::printInfo() const {
    //TODO handle what happens if one of the original accounts is deleted
    std::cout << "sender: " << sender->getName() << ", receiver: " << receiver->getName() << ", amount: " << amount << std::endl;
}