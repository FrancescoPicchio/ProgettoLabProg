//
// Created by fpicc on 07/03/2025.
//

#ifndef PROGETTOLABPROG_USER_H
#define PROGETTOLABPROG_USER_H


#include <string>
#include <map>
#include <iostream>
#include "Account.h"

class User {
private:
        std::string name;
        std::string surname;
        std::map<std::string, Account*> accounts;

public:
        User(std::string n, std::string s): name(n), surname(s){}
        void addAccount(Account *a){
            accounts[a->getName()] = a;
        };
        void removeAccount(Account* a){
            accounts.erase(a->getName());
        };
        void printAccounts(){
            //prints account names and their associated balance
            std::cout << getLegalName() + "'s accounts are: " << std::endl;
            for(auto i = accounts.begin(); i != accounts.end(); ++i) {
                std::string s = std::to_string(i->second->getBalance());
                std::cout << i->second->getName() + "with balance:" + s << std::endl;
            }
        };
        std::string getLegalName(){
            return name + " " + surname;
        }
        ~User();
};


#endif //PROGETTOLABPROG_USER_H
