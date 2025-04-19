//
// Created by fpicc on 07/03/2025.
//

#include "User.h"
#include <memory>
#include <fstream>
#include "IdUtil.h"


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
}

Account* User::openAccount(std::string n, AppDataManager* adm) {
    std::unique_ptr<Account> new_account = std::make_unique<Account>(n, this, adm);
    //storing the raw pointer beause using std::move makes new_account a nullptr
    Account* account_raw_ptr = new_account.get();
    if(!saveNewAccountToCSV(account_raw_ptr))
        return nullptr;
    accounts[new_account->getId()] = std::move(new_account);
    return account_raw_ptr;
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

bool User::saveNewAccountToCSV(Account *a) {
    std::ofstream file("accounts.csv", std::ios::app);
    if(!file.is_open()){
        std::cerr << "Error saving account " << a->getName() << " to accounts.csv" << std::endl;
        return false;
    }
    std::string data = std::to_string(a->getId()) + ',' + a->getName() + ',' + std::to_string(a->getOwner()->getId()) + ',' + std::to_string(a->getBalance());
    file << data << '\n';
    file.close();
    return true;
}