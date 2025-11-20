#include "Account.h"
#include "User.h"
#include "IdUtil.h"
#include "Transaction.h"
#include "AppDataManager.h"
#include <fstream>
#include <sstream>

Account::Account(std::string n, User *u, AppDataManager* adm): name(n), owner(u), balance(0){
    id = generate_next_id(adm->getAccountIdTrackerFileName());
    adm->add_account(this);
}

Account::Account(int i, std::string n, User *u, int b): id(i), name(n), owner(u), balance(b){}

void Account::print_info() const {
    std::cout << "id: " << id << ", name: " << name << ", owner: " << owner->get_legal_name() << ", balance: " << balance << std::endl;
}

std::vector<Transaction*> Account::get_transactions() const {
    std::vector<Transaction*> raw_ptrs;
    for (const auto& sptr : transactions) {
        raw_ptrs.push_back(sptr.get());
    }
    return raw_ptrs;
};

/*
//Passing transactionManager so that I can notify it when the transaction is created
bool Account::make_transaction(Account *receiver, int amount, AppDataManager* adm) {
    //You can't send a negative amount of money
    if(amount <= 0){
        std::cout << "You've inputted a negative amount, please input a positive whole number" << std::endl;
        return false;
    }
    //You can't send money you don't have
    else if(get_balance() >= amount) {
        auto t =  std::make_shared<Transaction>(this, receiver, amount);
        add_transaction(t);
        remove_balance(amount, adm);
        receiver->add_transaction(t);
        receiver->add_balance(amount, adm);
        if(!adm->save_transaction_to_CSV(t.get())){
            std::cout << "There was a problem updating transactions.csv." << std::endl;
            return false;
        }
        else{
            return true;
        }
        }
    else {
        std::cout << "Not enough money in your account." << std::endl;
        return false;
    }
}*/

bool Account::make_transaction(Account *receiver, int amount, AppDataManager* adm) {
    int receiver_original_balance = receiver->get_balance();
    int sender_original_balance = get_balance();
    if(receiver->add_balance(amount, adm) && remove_balance(amount, adm)){
        auto t =  std::make_shared<Transaction>(this, receiver, amount);
        add_transaction(t);
        receiver->add_transaction(t);
        if(!adm->save_transaction_to_CSV(t.get())){
            std::cout << "There was a problem updating transactions.csv." << std::endl;
            return false;
        }
        else{
            return true;
        }
        }
    else {
        //resets balance of accounts, in case only one of them couldn't change their balance
        receiver->set_balance(receiver_original_balance, adm);
        set_balance(sender_original_balance, adm);
        return false;
    }
}

void Account::print_transactions() const {
    std::cout << get_name() << "'s transactions are:" << std::endl << std::endl;
    for(auto i : transactions){
        i->print_info();
    }
}

bool Account::set_balance(int b, AppDataManager* adm){
    balance = b;
    return adm->update_account_balance_CSV(this);
}

bool Account::add_balance(int b, AppDataManager* adm){
    if(b <= 0){
        std::cout << "You've inputted a negative amount, please input a positive whole number" << std::endl;
        return false;
    }
    else{
        balance += b;
        if(adm->update_account_balance_CSV(this)){
            return true;
        }
        else 
            return false;
    }
}

bool Account::remove_balance(int b, AppDataManager* adm){
    if(b <= 0){
        std::cout << "You've inputted a negative amount, please input a positive whole number" << std::endl;
        return false;
    }
    else if(get_balance() < b) {
        std::cout << "Not enough money in your account." << std::endl;
        return false;
    }
    else {
        balance -= b;
        if(adm->update_account_balance_CSV(this)){
            return true;
        }
        else
            return false;
    }
}