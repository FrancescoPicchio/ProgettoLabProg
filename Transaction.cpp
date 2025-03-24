//
// Created by fpicc on 07/03/2025.
//

#include "Transaction.h"
#include "TransactionManager.h"
#include "Account.h"

void Transaction::printInfo() const {
    //TODO handle what happens if one of the original accounts is deleted
    std::cout << "Sender: " << sender->getName() << ", Receiver: " << receiver->getName() << ", Amount: " << amount << std::endl;
}