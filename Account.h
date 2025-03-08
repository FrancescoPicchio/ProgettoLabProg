//
// Created by fpicc on 07/03/2025.
//

#ifndef PROGETTOLABPROG_ACCOUNT_H
#define PROGETTOLABPROG_ACCOUNT_H


#include <string>
#include <vector>
#include <memory>

//Forward declaration of User and Transaction classes to avoid circular dependencies
class User;
class Transaction;
enum accountType {checking_account, saving_account};

class Account {
private:
    std::string name; //TODO make sure that the name is unique
    enum accountType type;
    User* owner;
    int balance;
    std::vector <std::shared_ptr<Transaction>> transactions;

public:
    Account(std::string n, accountType at, User* u);
    //~Account();

    std::string getName() {
        return name;
    }

    void setBalance(int b){
        balance = b;
    }

    int getBalance() const {
        return balance;
    }

    void addBalance(int b){
        balance += b;
    }

    void removeBalance(int b){
        balance -= b;
    }

    User* getOwner() const {
        return owner;
    };

    accountType getType() const {
        return type;
    }

    void setType(accountType t){
        type = t;
    }

    void addTransaction(const std::shared_ptr<Transaction>& t) {
        transactions.push_back(t);
    }
};


#endif //PROGETTOLABPROG_ACCOUNT_H
