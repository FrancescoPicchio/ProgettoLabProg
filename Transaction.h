#ifndef PROGETTOLABPROG_TRANSACTION_H
#define PROGETTOLABPROG_TRANSACTION_H

#include <memory>
#include <iostream>
#include <ctime>

//added forward declaration to avoid circular dependency
class Account;


class Transaction {
private:
    Account* sender;
    Account* receiver;
    int amount;
    std::string date;

public:
    //Never call this directly, always use make_transaction
    Transaction(Account* s, Account* r, int a): sender(s), receiver(r), amount(a){
        //initializes transaction with current time
        std::time_t now = std::time(nullptr);
        date = std::ctime(&now);
        //ctime returns a string with a newline character at the end, this gets rid of it
        date = date.substr(0,date.length()-1);
    }

    //no setters because once a transaction is created you shouldn't be able to modify it
    int get_amount() const {
        return amount;
    }

    Account* get_sender() const {
        return sender;
    }

    Account* get_receiver() const {
        return receiver;
    }

    void print_info() const;

    void print_date() const {
        std::cout << "Date: " << date;
    }

    std::string get_date() const {
        return date;
    }

};


#endif //PROGETTOLABPROG_TRANSACTION_H
