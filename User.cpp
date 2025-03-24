//
// Created by fpicc on 07/03/2025.
//

#include "User.h"
#include <memory>
#include "IdManager.h"
#include "UserManager.h"
#include "TransactionManager.h"

User::User(std::string n, std::string s, UserManager* m): name(n), surname(s), manager(m){
    id = generateNextId("user_id_tracker.csv");
    m->saveUser(this);
}

void User::printAccounts() const {
    if(accounts.empty()){
        std::cout << "This user hasn't opened an account yet." << std::endl;
        return;
    }
    //prints account names and their associated balance
    std::cout << getLegalName() + "'s accounts are: " << std::endl;
    for(auto i = accounts.begin(); i != accounts.end(); ++i) {
        std::string s = std::to_string(i->second->getBalance());
        std::cout << i->second->getName() + " with balance: " + s << ". Account's Id is " << i->second->getId() << std::endl;
    }
};

Account* User::openAccount(std::string name, AccountManager* m, std::map<int, Account*>* accounts_map) {
    std::unique_ptr<Account> new_account = std::make_unique<Account>(name, this, m);
    //storing the raw pointer beause using std::move makes new_account a nullptr
    Account* raw_ptr = new_account.get();
    accounts[new_account->getId()] = std::move(new_account);
    if(accounts_map != nullptr) {
        (*accounts_map)[raw_ptr->getId()] = raw_ptr;
    }
    return raw_ptr;
}

Account* User::openAccount(int id, std::string name, int balance, AccountManager* m) {
    std::unique_ptr<Account> new_account = std::make_unique<Account>(id, name, this, balance, m);
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