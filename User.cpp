//
// Created by fpicc on 07/03/2025.
//

#include "User.h"
#include <memory>
#include <fstream>
#include "IdUtil.h"


bool User::print_accounts() const {
    if(accounts.empty()){
        std::cout << "This user hasn't opened an account yet." << std::endl;
        return false;
    }
    //prints account names and their associated balance
    std::cout << get_legal_name() + "'s accounts are: " << std::endl;
    for(auto i = accounts.begin(); i != accounts.end(); ++i) {
        std::string s = std::to_string(i->second->get_balance());
        std::cout << i->second->get_name() + " with balance: " + s << ". Account's Id is " << i->second->get_id() << std::endl;
    }
    return true;
}

Account* User::open_account(std::string n, AppDataManager* adm) {
    std::unique_ptr<Account> new_account = std::make_unique<Account>(n, this, adm);
    //storing the raw pointer beause using std::move makes new_account a nullptr
    Account* account_raw_ptr = new_account.get();
    if(!save_new_account_to_CSV(account_raw_ptr))
        return nullptr;
    accounts[new_account->get_id()] = std::move(new_account);
    return account_raw_ptr;
}


Account* User::get_account(int i) const {
    return accounts.at(i).get();
}

int User::get_total_balance() const {
    int total_balance = 0;
    for(auto i = accounts.begin(); i != accounts.end(); i++){
        total_balance += i->second->get_balance();
    }
    return total_balance;
}

bool User::save_new_account_to_CSV(Account *a) {
    std::ofstream file("accounts.csv", std::ios::app);
    if(!file.is_open()){
        std::cerr << "Error saving account " << a->get_name() << " to accounts.csv" << std::endl;
        return false;
    }
    std::string data = std::to_string(a->get_id()) + ',' + a->get_name() + ',' + std::to_string(a->get_owner()->get_id()) + ',' + std::to_string(a->get_balance());
    file << data << '\n';
    file.close();
    return true;
}