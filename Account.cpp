//
// Created by fpicc on 07/03/2025.
//

#include "Account.h"
#include "User.h"


Account::Account(std::string n, accountType at, User *u): name(n), type(at), owner(u), balance(0){
    u->addAccount(this);
}

/*Account::~Account() {
    this->owner->removeAccount(this);
    for(auto i = transactions.begin(); i != transactions.end(); ++i) {
        delete *i;
    }
}*/
