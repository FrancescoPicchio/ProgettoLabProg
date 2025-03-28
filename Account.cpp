//
// Created by fpicc on 07/03/2025.
//

#include "Account.h"
#include "User.h"
#include "IdUtil.h"
#include "AccountManager.h"
#include "Transaction.h"


Account::Account(std::string n, User *u, AccountManager* m): name(n), owner(u), balance(0), manager(m){
    id = generateNextId("account_id_tracker.csv");
    m->saveAccount(this);
}

Account::Account(int i, std::string n, User *u, int b, AccountManager* m): id(i), name(n), owner(u), balance(b), manager(m){}

void Account::printInfo() const {
    std::cout << "id: " << id << ", name: " << name << ", owner: " << owner->getLegalName() << ", balance: " << balance << std::endl;
}

std::vector<Transaction*> Account::getTransactions() const {
    std::vector<Transaction*> raw_ptrs;
    for (const auto& sptr : transactions) {
        raw_ptrs.push_back(sptr.get());
    }
    return raw_ptrs;
};

//Passing transactionManager so that I can notify it when the transaction is created
bool Account::makeTransaction(Account *receiver, int amount, TransactionManager* tm, std::vector<Transaction*>* transaction_instances) {
    //You can't send a negative amount of money
    if(amount <= 0){
        std::cout << "You've inputted a negative amount, please input a positive whole number" << std::endl;
        return false;
    }
    //You can't send money you don't have
    else if(this->getBalance() >= amount) {
        auto t =  std::make_shared<Transaction>(this, receiver, amount, tm);
        addTransaction(t);
        setBalance(getBalance() - amount);
        receiver->addTransaction(t);
        receiver->setBalance(receiver->getBalance() + amount);
        std::cout << "Transaction successful!" << std::endl;
        //Transaction is saved in makeTransaction instead of Transaction constructor
        //FIXME transactions are saved to csv file even if account balance isn't changed to csv file
        tm->saveTransaction(t.get());
        if(transaction_instances){
            transaction_instances->push_back(t.get());
        }
        //TODO implement updating balances on accounts.csv
        return true;
        }
    else {
        std::cout << "Not enough money in your account." << std::endl;
        return false;
    }
}

void Account::printTransactions() const {
    std::cout << this->getName() << "'s transactions are:" << std::endl << std::endl;
    for(auto i : transactions){
        i->printInfo();
    }
}