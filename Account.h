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
class AppDataManager;
class Transaction;
/*TODO implement joint accounts, a children class of Account that has two owners, because User.accounts is made up of unique_ptrs
maybe we can use a map of shared_ptrs as an extra field for a user.*/

class Account {
private:
    int id;
    std::string name;
    //TODO implement account types
    //TODO implement associated banks for accounts, if two accounts make a transaction with different associated banks there's a fee
    User* owner;
    //FIXME should be a double and not a int maybe
    int balance;
    std::vector <std::shared_ptr<Transaction>> transactions;

public:
    Account(std::string n, User* u, AppDataManager* adm);
    //this method should only be called by AppDataManager with loadAccounts, otherwise it'll mess up the id of the rest of the acounts, because then id won't necessarily be a primary key
    Account(int i, std::string n, User* u, int b);

    std::string getName() const {
        return name;
    }

    void setBalance(int b){
        //FIXME should call AccountManager to update accounts.csv to its new balance
        balance = b;
    }

    int getBalance() const {
        return balance;
    }

    void addBalance(int b){
        //FIXME should call AccountManager to update accounts.csv to its new balance
        balance += b;
    }

    void removeBalance(int b){
        //FIXME should call AccountManager to update accounts.csv to its new balance
        balance -= b;
    }

    User* getOwner() const {
        return owner;
    };

    int getId() const {
        return id;
    }

    void printInfo() const;

    bool makeTransaction(Account *receiver, int amount, std::vector<Transaction*>* transaction_instances = nullptr);

    void addTransaction(const std::shared_ptr<Transaction> t) {
        transactions.push_back(t);
    }

    //Do not store this vector beyond the lifetime of the original shared_ptrs
    std::vector<Transaction*> getTransactions() const;

    void printTransactions() const;
};


#endif //PROGETTOLABPROG_ACCOUNT_H
