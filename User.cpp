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
}

void User::printAccounts() const {
    //prints account names and their associated balance
    std::cout << getLegalName() + "'s accounts are: " << std::endl;
    for(auto i = accounts.begin(); i != accounts.end(); ++i) {
        std::string s = std::to_string(i->second->getBalance());
        std::cout << i->second->getName() + " with balance: " + s << std::endl;
    }
};

Account* User::getAccount(int i) const {
    return accounts.at(i).get();
}