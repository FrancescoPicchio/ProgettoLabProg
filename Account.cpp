//
// Created by fpicc on 07/03/2025.
//

#include "Account.h"
#include "User.h"
#include "IdUtil.h"
#include "Transaction.h"
#include "AppDataManager.h"

Account::Account(std::string n, User *u, AppDataManager* adm): name(n), owner(u), balance(0){
    id = generateNextId("account_id_tracker.csv");
    adm->addAccount(this);
}

Account::Account(int i, std::string n, User *u, int b): id(i), name(n), owner(u), balance(b){}

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
bool Account::makeTransaction(Account *receiver, int amount, std::vector<Transaction*>* transaction_instances) {
    //You can't send a negative amount of money
    if(amount <= 0){
        std::cout << "You've inputted a negative amount, please input a positive whole number" << std::endl;
        return false;
    }
    //You can't send money you don't have
    else if(this->getBalance() >= amount) {
        auto t =  std::make_shared<Transaction>(this, receiver, amount);
        addTransaction(t);
        setBalance(getBalance() - amount);
        receiver->addTransaction(t);
        receiver->setBalance(receiver->getBalance() + amount);
        std::cout << "Transaction successful!" << std::endl;
        //Transaction is saved in makeTransaction instead of Transaction constructor
        //FIXME should call save to csv
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