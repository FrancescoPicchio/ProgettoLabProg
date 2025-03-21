//
// Created by fpicc on 07/03/2025.
//

#include "Account.h"
#include "User.h"
#include "IdManager.h"
#include "AccountManager.h"


Account::Account(std::string n, User *u, AccountManager* m): name(n), owner(u), balance(0), manager(m){
    u->addAccount(this);
    id = generateNextId("account_id_tracker.csv");
    m->saveAccount(this);
}

Account::Account(int i, std::string n, User *u, int b, AccountManager* m): id(i), name(n), owner(u), balance(b), manager(m){
    u->addAccount(this);
}

void Account::printInfo() const {
    std::cout << "id: " << id << ", name: " << name << ", owner: " << owner->getLegalName() << ", balance: " << balance << std::endl;
}
