//
// Created by fpicc on 07/03/2025.
//

#include "Account.h"
#include "User.h"


Account::Account(std::string n, User *u): name(n), owner(u), balance(0){
    u->addAccount(this);
}

Account::Account(int i, std::string n, User *u, int b): id(i), name(n), owner(u), balance(b){
    u->addAccount(this);
}
