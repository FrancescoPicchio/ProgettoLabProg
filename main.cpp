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
    for(i = 0; i < 5; i++) {
        std::cout << std::endl;
    }
}

//executes the logic once a program user has logged in. Returns false only if the user wants to exit the program
bool runUserMenu(Managers managers, int current_user_id, std::map<int, std::unique_ptr<User>>& user_instances, std::map<int, Account*>& account_instances, std::vector<Transaction*>& transaction_instances){
    //Operations that can be made with a given User
    std::cout << "You have accessed as " << user_instances.at(current_user_id)->getLegalName() << ", you can:" << std::endl;
    std::cout << "Press 1 access an Account you own." << std::endl;
    std::cout << "Press 2 to open a new Account for you." << std::endl;
    std::cout << "Press 3 to see the balance and Id for the Accounts you own." << std::endl;
    std::cout << "Press 4 to log out of current User." << std::endl;
    std::cout << "Press 0 to exit the program." << std::endl;
    //TODO make the logic for these operations
    return true;
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
        }
        //ends the loop if input_choice is 0
        else if(input_choice == 0) {
            break;
        }
        //if the input isn't either 1 or 2 it resets the loop
        else {
            continue;
        }
        if(!(runUserMenu(managers, current_user_id, user_instances, account_instances, transaction_instances))){
            break;
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
