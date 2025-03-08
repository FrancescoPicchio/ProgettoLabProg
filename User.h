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

class User {
private:
        std::string name;
        std::string surname;
        int id;
        //inline lets the variable be defined immediately
        static int inline numberOfUsers = 0; //TODO load numberOfUsers from file correctly
        std::map<std::string, std::unique_ptr<Account>> accounts;

public:
        User(std::string n, std::string s): name(n), surname(s){
            id = numberOfUsers++;
        }

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

        //~User(); //TODO make the destructor properly
};


#endif //PROGETTOLABPROG_USER_H
