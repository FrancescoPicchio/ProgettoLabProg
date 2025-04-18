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
#include "AppDataManager.h"

//forward declaration to avoid circular dependencies
class AppDataManager;

class User {
private:
        std::string name;
        std::string surname;
        int id;
        //changed map to map accounts to their ids instead of names, make sure it doesn't create problems
        std::map<int, std::unique_ptr<Account>> accounts;

public:
    //TODO check if removing the definition of the constructor without i changes anything
        User(const std::string& n, const std::string& s, int i): name(n), surname(s), id(i) {};

        void addAccount(std::unique_ptr<Account> a){
            accounts[a->getId()] = std::move(a);
        };

        //This should be the only way to create an account, otherwise there'll be problems with double deletion. accounts_map can be omitted
        Account* openAccount(std::string n, AppDataManager* adm);
        //TODO you can make User a friend class of Account to make it so only it can access its constructor

        Account* openAccount(int i, std::string n, int balance);

        //returns true if the User has at least one account, returns false if it doesn't have any accoutns
        bool printAccounts() const;

        std::string getLegalName() const{
            return name + " " + surname;
        }

        int getId() const {
            return id;
        }

        std::string getName() const {
            return name;
        }

        std::string getSurname() const {
            return surname;
        }

        //Do not store account beyond the lifetime of the original account unique_ptr
        Account* getAccount(int i) const;

        int getTotalBalance() const;
};


#endif //PROGETTOLABPROG_USER_H
