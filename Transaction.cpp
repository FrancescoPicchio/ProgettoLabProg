#include "Transaction.h"
#include "Account.h"

void Transaction::print_info() const {
    std::cout << "Sender: " << sender->get_name() << ", Receiver: " << receiver->get_name() << ", Amount: " << amount << std::endl;
}