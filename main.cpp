#include <iostream>
#include <fstream>
#include <memory>
#include "User.h"
#include "UserManager.h"
#include "AccountManager.h"
#include "TransactionManager.h"

void loadData(const std::string& filename) {
    std::ifstream file(filename);  // Try to open the file
    if (!file) {  // If file doesn't exist
        std::ofstream newFile(filename);  // Create the file
        if (newFile) {
            //initializes id counter if it didn't exist
            if(filename == "user_id_tracker.csv" || filename == "account_id_tracker.csv"){
                newFile << "0";
            }
            std::cout << filename << " created successfully.\n";
        } else {
            std::cerr << "Error creating file '" << filename << "'.\n"; //cerr is used for error messages
            file.close();
        }
    } else {
        std::cout << filename << " has been loaded.\n";
        file.close();
    }
}

void spaceOutPrints() {
    //Prints 20 newlines to "clear" the console, helping with readability
    int i;
    for(i = 0; i < 8; i++) {
        std::cout << std::endl;
    }
}


int main() {
    loadData("users.csv");
    loadData("accounts.csv");
    loadData("transactions.csv");
    loadData("user_id_tracker.csv");
    loadData("account_id_tracker.csv");
    spaceOutPrints();

    //loads users from csv file and prepares a map to store all users
    auto *um = new UserManager("users.csv");
    std::map<int, std::unique_ptr<User>> users;
    um->loadUsers(users);

    //loads accounts and makes a map of the accounts
    auto *am = new AccountManager("accounts.csv");
    std::map<int, Account*> accounts;
    am->loadAccounts(users, accounts);

    //loads the transactions and makes a vector of them
    auto *tm = new TransactionManager("transactions.csv");
    std::vector<Transaction*> transactions;
    tm->loadTransactions(accounts, transactions);

    /*
    while(true){
        std::cout << "Welcome, this program simulates a bank system. You can create a User, who can";
    }*/

    /*
    //small piece of code to test if loadUsers works
    // .at(key) throws an exception if key doesn't exist
    std::string username1 = users.at(1)->getLegalName();
    std::cout << username1 << std::endl;
    std::string username2 = users.at(3)->getLegalName();
    std::cout << username2 << std::endl;



    //small piece of code to test if loadAccounts works
    //testing print function for a user
    users.at(1)->printAccounts();
    //testing print function for accounts
    accounts.at(1)->printInfo();
    accounts.at(2)->printInfo();



    //small piece of code to test if loadTransactions works
    transactions.at(0)->printInfo();
    transactions.at(1)->printInfo();

    */
    delete um;
    delete am;
    delete tm;
    return 0;
}
