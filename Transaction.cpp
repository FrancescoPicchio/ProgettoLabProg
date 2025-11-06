//
// Created by fpicc on 07/03/2025.
//

#include "Transaction.h"
#include "Account.h"

void Transaction::print_info() const {
    //TODO handle what happens if one of the original accounts is deleted
    std::cout << "Sender: " << sender->get_name() << ", Receiver: " << receiver->get_name() << ", Amount: " << amount << std::endl;
}