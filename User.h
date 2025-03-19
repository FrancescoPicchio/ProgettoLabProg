//
// Created by fpicc on 07/03/2025.
//

#ifndef PROGETTOLABPROG_USER_H
#define PROGETTOLABPROG_USER_H


#include <string>
#include <map>
#include <iostream>
#include <memory>
#include "Account.h"
#include "Transaction.h"
#include "IdManager.h"

class User {
private:
        std::string name;
        std::string surname;
        int id;
        std::map<std::string, std::unique_ptr<Account>> accounts;

public:
        User(std::string n, std::string s): name(n), surname(s){
            id = generateNextId("user_id_tracker.csv");
        }

        //TODO implement way to check if id is already taken, and maybe not let anything besides UserManager use this constructor
        User(std::string n, std::string s, int i): name(n), surname(s), id(i) {};

        void addAccount(Account *a){
            accounts.insert(std::make_pair(a->getName(), std::unique_ptr<Account>(a)));
        };

        void removeAccount(Account* a){
            accounts.erase(a->getName());
        };

        void printAccounts () const;

        std::string getLegalName() const{
            return name + " " + surname;
        }

        void makeTransaction(Account* sender, Account* receiver, int amount);
};


#endif //PROGETTOLABPROG_USER_H
