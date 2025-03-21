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
        //only declare a new user as a shared_ptr, so it can be managed by the UserManager
        User(std::string n, std::string s, UserManager* m);

        User(std::string n, std::string s, int i, UserManager* m): name(n), surname(s), id(i), manager(m) {};

        //FIXME Should be a CreateUser method, otherwise it won't be able to pass itself as a unique_ptr when called in the Account Constructor
        //FIXME CreateUser for the single responsibility principle should be done by an Account Factory instead of Users
        void addAccount(Account *a){
            accounts.insert(std::make_pair(a->getId(), std::unique_ptr<Account>(a)));
        };

        void removeAccount(Account* a){
            accounts.erase(a->getId());
        };

        void printAccounts () const;

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

        void makeTransaction(Account* sender, Account* receiver, int amount, TransactionManager* tm);
};


#endif //PROGETTOLABPROG_USER_H
