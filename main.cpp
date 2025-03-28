#include <iostream>
#include <fstream>
#include <memory>
#include "User.h"
#include "UserManager.h"
#include "AccountManager.h"
#include "TransactionManager.h"
//created to avoid passing three arguments to runUserSession()
struct Managers {
    UserManager* userManager;
    AccountManager* accountManager;
    TransactionManager* transactionManager;
};


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
            std::cerr << "Error creating file '" << filename << "'.\n";
            file.close();
        }
    } else {
        std::cout << filename << " has been loaded.\n";
        file.close();
    }
}

void spaceOutPrints() {
    //Prints 5 newlines to help with legibility
    int i;
    for(i = 0; i < 5; i++) {
        std::cout << std::endl;
    }
}


//executes the logic for a specific account, which is pretty much making a transaction with another account.
bool runAccountMenu(const Managers& managers, const int current_account_id, std::map<int, std::unique_ptr<User>>& user_instances, std::map<int, Account*>& account_instances, std::vector<Transaction*>& transaction_instances){
    int input_choice;
    Account* current_account = account_instances.at(current_account_id);
    while(true){
        std::cout << "You're accessing " << current_account->getName() << " and its current balance is: " << account_instances.at(current_account_id)->getBalance() << std::endl;
        std::cout << "Press 1 to make a new transaction, sending money from this account to another" << std::endl;
        std::cout << "Press 2 to print out the transactions of this account" << std::endl;
        std::cout << "Press 3 to print out the existing Accounts and their Owners" << std::endl;
        std::cout << "Press 4 to exit this Account and return to the User submenu" << std::endl;
        std::cout << "Press 0 to exit the program" << std::endl;
        if(!(std::cin >> input_choice)) {
            std::cout << "Invalid input, there's no choice associated with that number!" << std::endl << std::endl;
            //clears the input of the error thrown and resets the input
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            system("pause");
            spaceOutPrints();
            //resets the loop if the input is wrong, so it can print out the possible choices
            continue;
        }
        spaceOutPrints();
        //FIXME refactor so this if is a function
        //Makes a new transaction with another account
        if(input_choice == 1){
            spaceOutPrints();
            std::cout << "Who do you want to send the money to? Give the Id of the account that'll receive the money" << std::endl;
            bool key_exists = false;
            int receiver_id;
            while(!key_exists) {
                //checks if input choice is actually an int and not something else
                while (!(std::cin >> receiver_id)) {
                    std::cout << "Invalid input. Please input a positive integer." << std::endl;
                    //clears the input of the error thrown and resets the input
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
                //checks if the id inputted exists in the map
                if (!(account_instances.find(receiver_id) != account_instances.end())) {
                    std::cout << "The Id that you have inputted belongs to no Account. Please try a different Id" << std::endl;
                    //clears the input of the error thrown and resets the input
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                } //Checks if the Account is trying to give itself money
                else if(current_account->getId() == account_instances.at(receiver_id)->getId()) {
                    std::cout << "You can't transfer money to the same Account!" << std::endl;
                    //clears the input of the error thrown and resets the input
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                } else {
                    key_exists = true;
                }
            }
            bool amount_is_correct = false;
            int amount_for_transaction;
            //Only exits the loop once it has assured that the amount of money is positive and there's enough money in the sender account
            while(!(amount_is_correct)){
                std::cout << "How much money do you want to send?" << std::endl;
                while (!(std::cin >> amount_for_transaction)) {
                    std::cout << "Invalid input. Please input a positive integer." << std::endl;
                    //clears the input of the error thrown and resets the input
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
                amount_is_correct = current_account->makeTransaction(account_instances.at(receiver_id), amount_for_transaction, managers.transactionManager, &transaction_instances);
            }
        }
        else if(input_choice == 2) {
            current_account->printTransactions();
            system("pause");
            spaceOutPrints();
        }
        else if(input_choice == 3) {
            spaceOutPrints();
            std::cout << "The currently existing Accounts are:" << std::endl;
            for(auto i : account_instances){
                i.second->printInfo();
            }
            system("pause");
            spaceOutPrints();
        }
        else if(input_choice == 4) {
            spaceOutPrints();
            return true;
        }
        else if(input_choice == 0) {
            return false;
        }
        else {
            spaceOutPrints();
            std::cout << "Please input a number associated with a choice." << std::endl;
            system("pause");
            spaceOutPrints();
        }
    }
}

//executes the logic once a program user has logged in. Returns false only if the user wants to exit the program. Managers and current_user_id are const because they shouldn't be modified
bool runUserMenu(const Managers& managers, const int current_user_id, std::map<int, std::unique_ptr<User>>& user_instances, std::map<int, Account*>& account_instances, std::vector<Transaction*>& transaction_instances){
    int input_choice;
    //keeps track of the last selected account
    int current_account_id;
    User* current_user = user_instances.at(current_user_id).get();
    while(true) {
        //Operations that can be made with a given User
        std::cout << std::endl << "You have logged in as " << current_user->getLegalName() << ", you can:" << std::endl;
        std::cout << "Press 1 access an Account you own." << std::endl;
        std::cout << "Press 2 to open a new Account for you." << std::endl;
        std::cout << "Press 3 to see the balance and Id for the Accounts you own." << std::endl;
        std::cout << "Press 4 to log out of current User." << std::endl;
        std::cout << "Press 0 to exit the program." << std::endl;
        if(!(std::cin >> input_choice)) {
            std::cout << "Invalid input, please input a number from the choices!" << std::endl << std::endl;
            //clears the input of the error thrown and resets the input
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            //resets the loop if the input is wrong, so it can print out the possible choices. Pauses to give the user time to read the error message, because this is an if and not a while
            system("pause");
            spaceOutPrints();
            continue;
        }
        spaceOutPrints();
        //FIXME refactor so this is all a function
        //Access account logic
        if(input_choice == 1){
            std::cout << "Please input the id of one of your Accounts to access it" << std::endl;
            current_user->printAccounts();
            bool key_exists = false;
            while(!key_exists){
                //checks if input choice is actually an int and not something else
                while(!(std::cin >> current_account_id)) {
                    std::cout << "Invalid input. Please input a positive integer." << std::endl;
                    //clears the input of the error thrown and resets the input
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
                //checks if the id inputted exists in the map 
                if(account_instances.find(current_account_id) != account_instances.end()){
                    if(current_user->getId() == account_instances.at(current_account_id)->getOwner()->getId()) {
                        key_exists = true;
                    }
                    else{
                        std::cout << "The Account Id that you've inputted belongs to another User. Please try a different Id";
                        //clears the input of the error thrown and resets the input
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                    }
                }
                else {
                    std::cout << "The Id that you have inputted belongs to no Account. Please try a different Id";
                    //clears the input of the error thrown and resets the input
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
            }
            //The condition is true only if the program user chooses 0 in the Account submenu
            if(!(runAccountMenu(managers, current_account_id, user_instances, account_instances, transaction_instances))){
                return false;
            }
            else {
                continue;
            }
        }
        else if(input_choice == 2){
            std::cout << "Please input how you want your new Account to be called" << std::endl;
            std::string new_account_name;
            while(!(std::cin >> new_account_name)){
                std::cout << "Invalid input.";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
            Account* new_account = user_instances.at(current_user_id)->openAccount(new_account_name, managers.accountManager, &account_instances);
            current_account_id = new_account->getId();
            std::cout << "New Account " << new_account->getName() << " was created successfully." << std::endl;
            //accesses the Account submenu as the newly created user, condition is true only if the program user selects 0 from the Account submenu
            if(!(runAccountMenu(managers, current_account_id, user_instances, account_instances, transaction_instances))){
                return false;
            }
            else {
                continue;
            }
        }
        //prints out the current User's accounts and their total balance
        else if(input_choice == 3){
            current_user->printAccounts();
            std::cout << "And their total balance is: " << current_user->getTotalBalance() << std::endl;
            //gives user time to see their accounts and balance
            system("pause");
            continue;
        }
        //returns to main loop and stays in the loop
        else if(input_choice == 4){
            return true;
        }
        //returns to main and exits the loop
        else if(input_choice == 0){
            return false;
        }
        //This is to cover the case where the input type is correct, but there is no choice associated with that number
        else {
            std::cout << "Invalid input, there's no choice associated with that number!" << std::endl << std::endl;
            //clears the input of the error thrown and resets the input
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            //pauses until another input to give time to the user to read the error message
            system("pause");
            spaceOutPrints();
        }
    }
}



int main() {
    loadData("users.csv");
    loadData("accounts.csv");
    loadData("transactions.csv");
    loadData("user_id_tracker.csv");
    loadData("account_id_tracker.csv");
    spaceOutPrints();

    //could probably avoid making the managers pointers, and just pass them as references to avoid having to manually delete them

    //loads users from csv file and prepares a map to store all users
    auto *um = new UserManager("users.csv");
    std::map<int, std::unique_ptr<User>> user_instances;
    um->loadUsers(user_instances);

    //loads accounts and makes a map of the accounts
    auto *am = new AccountManager("accounts.csv");
    //You could refactor the code to not need/use this vector, because you can just access accounts from the accounts field of a User
    std::map<int, Account*> account_instances;
    am->loadAccounts(user_instances, account_instances);

    //loads the transactions and makes a vector of them
    //FIXME refactor to not include this vector, because it's quite useless. Given that we can already access all of the transactions from account_instances
    auto *tm = new TransactionManager("transactions.csv");
    std::vector<Transaction*> transaction_instances;
    tm->loadTransactions(account_instances, transaction_instances);

    Managers managers = {um, am, tm};

    //initialized at a value different from all those present in the next while loop
    int input_choice;
    //variables to keep track of the user that is being used at the moment
    int current_user_id;

    std::cout << "Welcome, this program simulates a bank system. You can create a User, who can open an Account" << std::endl << "and make a transaction with that Account." << std::endl << std::endl;

    while(true){
        std::cout << "Press 1 to create a new User\nPress 2 to access an existing User using its id\nPress 3 to print out the existing users\nPress 0 to exit the program." << std::endl;
        while(!(std::cin >> input_choice)) {
            std::cout << "Invalid input. Please input a number among the ones the options." << std::endl;
            //clears the input of the error thrown and resets the input
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        //Program user wants to create a new User object
        if(input_choice == 1) {
            std::cout << "You want to create a new User? What is their name?" << std::endl;
            std::string name_input;
            while(!(std::cin >> name_input)){
                std::cout << "Invalid input. Please input a string." << std::endl;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
            std::cout << "Now, what is their surname?" << std::endl;
            std::string surname_input;
            while(!(std::cin >> surname_input)){
                std::cout << "Invalid input. Please input a string." << std::endl;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
            //creates new user and adds it to the map of the current instances of users
            auto new_user = std::make_unique<User>(name_input, surname_input, um);
            current_user_id = new_user->getId();
            user_instances[new_user->getId()] = std::move(new_user);
            std::cout << "Congrats, you have created the user " << user_instances[current_user_id]->getLegalName() << "!" << std::endl;
            std::cout << "The new user's Id is " << current_user_id << ", remember it if you'll want to access this user again." << std::endl;
            std::cout << "Press any key to continue." << std::endl;
            //pauses the program and gives time to read the id of the new User object
            system("pause");
            spaceOutPrints();
            //condition is true only if the program user has exited the User menu with a 0
            if(!(runUserMenu(managers, current_user_id, user_instances, account_instances, transaction_instances))){
                break;
            }
        }
        //Program user wants to access a
        else if(input_choice == 2) {
            std::cout << "Please input the Id for the user you want to access as" << std::endl;
            bool key_exists = false;
            while(!key_exists){
                //checks if input choice is actually an int and not something else
                while(!(std::cin >> current_user_id)) {
                    std::cout << "Invalid input. Please input a positive integer." << std::endl;
                    //clears the input of the error thrown and resets the input
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
                //checks if the id inputted exists in the map.
                //In C++ 20 can also use .contains method
                if(user_instances.find(current_user_id) != user_instances.end()){
                    key_exists = true;
                }
                else {
                    std::cout << "The Id that you have inputted belongs to no User. Please try a different Id";
                    //clears the input of the error thrown and resets the input
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
            }
            //condition is true only if the program user has exited the User menu with a 0
            if(!(runUserMenu(managers, current_user_id, user_instances, account_instances, transaction_instances))){
                break;
            }
        }
        else if(input_choice == 3) {
            spaceOutPrints();
            std::cout << "The Users that currently exist are:" << std::endl;
            for(auto i = user_instances.begin(); i != user_instances.end(); i++){
                std::cout << i->second->getLegalName() << " and their Id is: " << i->second->getId() << std::endl;
            }
            system("pause");
            spaceOutPrints();
        }
        //ends the loop if input_choice is 0
        else if(input_choice == 0) {
            break;
        }
        //if the input isn't either 1 or 2 it resets the loop.
        else {
            std::cout << "Invalid input. Please input a number among the ones the options." << std::endl;
            system("pause");
            spaceOutPrints();
        }
    }

    delete um;
    delete am;
    delete tm;
    return 0;
}
