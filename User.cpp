//
// Created by fpicc on 07/03/2025.
//

#include "User.h"
#include <memory>
#include "IdUtil.h"
#include "UserManager.h"
#include "TransactionManager.h"


bool User::printAccounts() const {
    if(accounts.empty()){
        std::cout << "This user hasn't opened an account yet." << std::endl;
        return false;
    }
    //prints account names and their associated balance
    std::cout << getLegalName() + "'s accounts are: " << std::endl;
    for(auto i = accounts.begin(); i != accounts.end(); ++i) {
        std::string s = std::to_string(i->second->getBalance());
        std::cout << i->second->getName() + " with balance: " + s << ". Account's Id is " << i->second->getId() << std::endl;
    }
    return true;
};

Account* User::openAccount(std::string n, AppDataManager* adm) {
    std::unique_ptr<Account> new_account = std::make_unique<Account>(n, this, adm);
    //storing the raw pointer beause using std::move makes new_account a nullptr
    Account* raw_ptr = new_account.get();
    accounts[new_account->getId()] = std::move(new_account);
    return raw_ptr;
}

Account* User::openAccount(int i, std::string n, int balance) {
    std::unique_ptr<Account> new_account = std::make_unique<Account>(i, n, this, balance);
    Account* raw_ptr = new_account.get();
    accounts[new_account->getId()] = std::move(new_account);
    return raw_ptr;
}

Account* User::getAccount(int i) const {
    return accounts.at(i).get();
}

int User::getTotalBalance() const {
    int total_balance = 0;
    for(auto i = accounts.begin(); i != accounts.end(); i++){
        total_balance += i->second->getBalance();
    }
    return total_balance;
}