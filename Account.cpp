//
// Created by fpicc on 07/03/2025.
//

#include "Account.h"
#include "User.h"
#include "IdManager.h"
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
void Account::makeTransaction(Account *receiver, int amount, TransactionManager* tm) {
    //You can't send money you don't have
    if(this->getBalance() >= amount) {
        auto t =  std::make_shared<Transaction>(this, receiver, amount, tm);
        this->addTransaction(t);
        this->setBalance(this->getBalance() - amount);
        receiver->addTransaction(t);
        receiver->setBalance(receiver->getBalance() + amount);
        std::cout << "Transaction successful!" << std::endl;
        //Transaction is saved in makeTransaction instead of Transaction constructor
        tm->saveTransaction(t.get());
        //TODO implement updating balances on accounts.csv
    }
    else {
        std::cout << "Not enough money in your account." << std::endl;
    }
}
