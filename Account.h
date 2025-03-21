//
// Created by fpicc on 07/03/2025.
//

#ifndef PROGETTOLABPROG_ACCOUNT_H
#define PROGETTOLABPROG_ACCOUNT_H


#include <string>
#include <vector>
#include <memory>

//Forward declaration of User and Transaction classes to avoid circular dependencies
class User;
class AccountManager;
class Transaction;
enum accountType {checking_account, saving_account};
/*TODO implement joint accounts, a children class of Account that has two owners, because User.accounts is made up of unique_ptrs
maybe we can use a map of shared_ptrs as an extra field for a user.*/

class Account {
private:
    int id;
    std::string name;
    //TODO implement account types
    //enum accountType type;
    User* owner;
    int balance;
    std::vector <std::shared_ptr<Transaction>> transactions;
    AccountManager* manager;

public:
    //this constructor can be called unlike User's because AccountManager doesn't store shared_ptrs
    Account(std::string n, User* u, AccountManager* m);
    //this method should only be called by AccountManager with loadAccounts, otherwise it'll mess up the id of the rest of the acounts, because then id won't necessarily be a primary key
    Account(int i, std::string n, User* u, int b, AccountManager* m);

    std::string getName() const {
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

    User* getOwner() const {
        return owner;
    };

    int getId() const {
        return id;
    }

    void printInfo() const;

    /*accountType getType() const {
        return type;
    }

    void setType(accountType t){
        type = t;
    }*/

    void addTransaction(const std::shared_ptr<Transaction> t) {
        transactions.push_back(t);
    }
};


#endif //PROGETTOLABPROG_ACCOUNT_H
