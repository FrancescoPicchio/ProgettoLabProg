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
    while(true){
        std::cout << "You're accessing " << account_instances.at(current_account_id) << " and its current balance is: " << account_instances.at(current_account_id)->getBalance() << std::endl;
        std::cout << "Press 1 to make a new transaction, sending money from this account to another" << std::endl;
        std::cout << "Press 2 to print out the transactions regarding this account" << std::endl;
        std::cout << "Press 3 to exit this account and return to the User submenu" << std::endl;
        if(!(std::cin >> input_choice)) {
            std::cout << "Invalid input, there's no choice associated with that number!" << std::endl << std::endl;
            //clears the input of the error thrown and resets the input
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            //resets the loop if the input is wrong, so it can print out the possible choices
            continue;
        }
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
                if (account_instances.contains(receiver_id)) {
                    key_exists = true;
                } else {
                    std::cout << "The Id that you have inputted belongs to no Account. Please try a different Id";
                    //clears the input of the error thrown and resets the input
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
            }
            bool amount_is_positive, enough_money_in_account = false;
            int amount_for_transaction;/*
            //TODO check if logic makes sense
            while(!(amount_is_positive && enough_money_in_account)){
                std::cout << "How much money do you want to send?" << std::endl;
                while (!(std::cin >> amount_for_transaction)) {
                    std::cout << "Invalid input. Please input a positive integer." << std::endl;
                    //clears the input of the error thrown and resets the input
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
            }
            //account_instances.at(current_account_id)->makeTransaction(account_instances.at(receiver_id),);*/
        }
    }
}

//executes the logic once a program user has logged in. Returns false only if the user wants to exit the program. Managers and current_user_id are const because they shouldn't be modified
bool runUserMenu(const Managers& managers, const int current_user_id, std::map<int, std::unique_ptr<User>>& user_instances, std::map<int, Account*>& account_instances, std::vector<Transaction*>& transaction_instances){
    int input_choice;
    //keeps track of the last selected account
    int current_account_id;
    while(true) {
        //Operations that can be made with a given User
        std::cout << "You have logged in as " << user_instances.at(current_user_id)->getLegalName() << ", you can:"
                  << std::endl;
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
            std::cout << "Press any button to continue." << std::endl;
            system("pause");
            spaceOutPrints();
            continue;
        }
        //Access account logic
        if(input_choice == 1){
            std::cout << "Please input the id of one of your Accounts to access it" << std::endl;
            user_instances.at(current_user_id)->printAccounts();
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
                if(account_instances.contains(current_account_id)){
                    if(user_instances.at(current_user_id)->getId() == account_instances.at(current_account_id)->getOwner()->getId()) {
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
            //TODO check if the Account exists and is owned by the User
            //TODO runAccountMenu where you get to the submenu for the account
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
            std::cout << "New Account" << new_account->getName() << "created successfully." << std::endl;
            //TODO either access runAccountMenu or continue to let the user select a new choice
        }
        //prints out the current User's accounts and their total balance
        else if(input_choice == 3){
            std::cout << user_instances.at(current_user_id)->getLegalName() << "'s accounts are:" << std::endl;
            user_instances.at(current_user_id)->printAccounts();
            std::cout << "And their total balance is:" << user_instances.at(current_user_id)->getTotalBalance() << std::endl;
            //gives user time to see their accounts and balance
            std::cout << "Press any button to return to the previous menu." << std::endl;
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
            std::cout << "Press any button to continue." << std::endl;
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

    //loads users from csv file and prepares a map to store all users
    auto *um = new UserManager("users.csv");
    std::map<int, std::unique_ptr<User>> user_instances;
    um->loadUsers(user_instances);

    //loads accounts and makes a map of the accounts
    auto *am = new AccountManager("accounts.csv");
    std::map<int, Account*> account_instances;
    am->loadAccounts(user_instances, account_instances);

    //loads the transactions and makes a vector of them
    auto *tm = new TransactionManager("transactions.csv");
    std::vector<Transaction*> transaction_instances;
    tm->loadTransactions(account_instances, transaction_instances);

    Managers managers = {um, am, tm};

    //initialized at a value different from all those present in the next while loop
    int input_choice;
    //variables to keep track of the user or account that is being used at the moment
    int current_user_id;
    int current_account_id;

    std::cout << "Welcome, this program simulates a bank system. You can create a User, who can open an Account" << std::endl << "and make a transaction with that Account." << std::endl << std::endl;

    while(true){
        std::cout << "Press 1 to access an existing User using its id, press 2 to create a new User, or press 0 to exit the program." << std::endl;
        while(!(std::cin >> input_choice)) {
            std::cout << "Invalid input. Please input either 1 to access an existing User, 2 to create a new one or 0 to exit the program." << std::endl;
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
                //checks if the id inputted exists in the map
                if(user_instances.contains(current_user_id)){
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
        //ends the loop if input_choice is 0
        else if(input_choice == 0) {
            break;
        }
        //if the input isn't either 1 or 2 it resets the loop
        else {
            std::cout << "Invalid input. Please input either 1 to access an existing User, 2 to create a new one or 0 to exit the program." << std::endl;
        }


    }

    /*
    //small piece of code to test if loadUsers works
    // .at(key) throws an exception if key doesn't exist
    std::string username1 = user_instances.at(1)->getLegalName();
    std::cout << username1 << std::endl;
    std::string username2 = user_instances.at(3)->getLegalName();
    std::cout << username2 << std::endl;



    //small piece of code to test if loadAccounts works
    //testing print function for a user
    user_instances.at(1)->printAccounts();
    //testing print function for accounts
    account_instances.at(1)->printInfo();
    account_instances.at(2)->printInfo();



    //small piece of code to test if loadTransactions works
    transaction_instances.at(0)->printInfo();
    transaction_instances.at(1)->printInfo();*/


    delete um;
    delete am;
    delete tm;
    return 0;
}
