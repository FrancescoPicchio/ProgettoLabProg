//
// Created by fpicc on 07/03/2025.
//

#ifndef PROGETTOLABPROG_ACCOUNT_H
#define PROGETTOLABPROG_ACCOUNT_H


#include <string>

//Forward declaration of User class to avoid circular dependencies
class User;

enum accountType {checking_account, saving_account};

class Account {
private:
    std::string name;
    enum accountType type;
    User* owner;
    int balance;

public:
    Account(std::string n, accountType at, User* u): name(n), type(at), owner(u), balance(0){}
    ~Account(); //TODO fai distruttore

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

    const User* getOwner(){
        return owner;
    }

    accountType getType() const {
        return type;
    }

    void setType(accountType t){
        type = t;
    }

};


#endif //PROGETTOLABPROG_ACCOUNT_H
