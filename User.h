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

//forward declaration to avoid circular dependencies
class UserManager;
class TransactionManager;

class User {
private:
        std::string name;
        std::string surname;
        int id;
        //changed map to map accounts to their ids instead of names, make sure it doesn't create problems
        std::map<int, std::unique_ptr<Account>> accounts;
        UserManager* manager;

public:
        //should only be called by the UserManager, otherwise it won't be added to the users map of UserManager
        User(std::string n, std::string s, UserManager* m);

        User(const std::string& n, const std::string& s, int i, UserManager* m): name(n), surname(s), id(i), manager(m) {};

        void addAccount(std::unique_ptr<Account> a){
            accounts[a->getId()] = std::move(a);
        };

        //This should be the only way to create an account, otherwise there'll be problems with double deletion. accounts_map can be omitted
        Account* openAccount(std::string name, AccountManager* m, std::map<int, Account*>* accounts_map = nullptr);
        //TODO you can make User a friend class of Account to make it so only it can access its constructor

        Account* openAccount(int id, std::string name, int balance, AccountManager* m);

        void printAccounts() const;

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
