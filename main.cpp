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

    //small piece of code to test if loadUsers works
    auto *um = new UserManager("users.csv");
    um->loadUsers();
    const std::map<int, std::shared_ptr<User>>& users = um->getUsers();
    // .at(key) throws an exception if key doesn't exist
    std::string username1 = users.at(1)->getLegalName();
    std::cout << username1 << std::endl;
    std::string username2 = users.at(3)->getLegalName();
    std::cout << username2 << std::endl;

    std::shared_ptr<User> user = um->createUser("Sara", "Bianchi");
    std::cout << user->getLegalName() << std::endl;

    /*
    //small piece of code to test if loadAccounts works
    auto *am = new AccountManager("accounts.csv");
    am->loadAccounts(um->getUsers());
    //testing print function for a user
    users.at(1)->printAccounts();
    //testing print function for accounts
    const std::map<int, Account*>& accounts = am->getAccounts();
    accounts.at(1)->printInfo();
    accounts.at(2)->printInfo();

    //small piece of code to test if loadTransactions works
    auto *tm = new TransactionManager("transactions.csv");
    tm->loadTransactions(accounts);
    const std::vector<Transaction*> transactions = tm->getTransactions();
    transactions.at(0)->printInfo();
    transactions.at(1)->printInfo();
     */

    delete um;
    /*
    delete am;
    delete tm;
     */
    return 0;
}
