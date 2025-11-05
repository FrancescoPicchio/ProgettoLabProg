#include <iostream>
#include <fstream>
#include "User.h"
#include "AppDataManager.h"

//TODO Maybe add this inside the LoadData function of AppDataManager
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


bool make_new_transaction(AppDataManager* adm, Account* current_account){
    //TODO finish implementing that choice as a function
    return true;
}

//Executes the logic for a specific account, which entails mostly making a transaction with another account.
bool runAccountMenu(AppDataManager* adm, Account* current_account){
    int input_choice;
    //TODO add option to make a deposit to an account
    while(true){
        std::cout << "You're accessing " << current_account->getName() << " and its current balance is: " << current_account->getBalance() << std::endl;
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
            
        }
        else if(input_choice == 2) {
            current_account->printTransactions();
            system("pause");
            spaceOutPrints();
        }
        else if(input_choice == 3) {
            spaceOutPrints();
            std::cout << "The currently existing Accounts are:" << std::endl;
            for(auto i : adm->getAccounts()){
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

//selects and access and Account for a User in the User menu
bool select_account(AppDataManager* adm, User* current_user){
    int current_account_id;
    if(!current_user->printAccounts()) {
            system("pause");
            spaceOutPrints();
            return false;
        }
        std::cout << "Please input the id of one of your Accounts to access it." << std::endl;
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
            if(adm->getAccounts().find(current_account_id) != adm->getAccounts().end()){
                if(current_user->getId() == adm->getAccounts().at(current_account_id)->getOwner()->getId()) {
                    key_exists = true;
                }
                else{
                    std::cout << "The Account Id that you've inputted belongs to another User. Please try a different Id";
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
        Account* current_account = adm->getAccounts().at(current_account_id);
        if(!(runAccountMenu(adm, current_account))){
            return false;
        }
        else {
            return true;
        }
}

//Executes the logic once a program user has logged in, which consists of accessing an Account or opening a new one. 
//Returns false only if the User wants to exit the program.
bool runUserMenu(AppDataManager* adm, User* current_user){
    int input_choice;
    int current_account_id;
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
            //resets the loop if the input is wrong, so it can print out the possible choices. Pauses to give the user time to read the error message
            system("pause");
            spaceOutPrints();
            continue;
        }
        spaceOutPrints();
        //Access account logic
        if(input_choice == 1){
            if(select_account(adm, current_user)){
                continue;
            }
            else {
                return false;
            }
        }
        //Opens a new Account for the User
        else if(input_choice == 2){
            std::cout << "Please input your new Account's name" << std::endl;
            std::string new_account_name;
            while(!(std::cin >> new_account_name)){
                std::cout << "Invalid input.";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
            Account* new_account = current_user->openAccount(new_account_name, adm);
            current_account_id = new_account->getId();
            std::cout << "New Account " << new_account->getName() << " was created successfully." << std::endl;
            Account* current_account = adm->getAccounts().at(current_account_id);
            //accesses the Account submenu as the newly created user, condition is true only if the program user selects 0 from the Account submenu
            if(!(runAccountMenu(adm, current_account))){
                return false;
            }
            else {
                continue;
            }
        }
        //prints out the current User's Accounts and their total balance
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
        //returns to main and quits the program
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

    auto *adm = new AppDataManager();
    if(!adm->loadAppData()) {
        std::cout << "There was a problem loading the data" << std::endl;
        return 0;
    }
    //initialized at a value different from all those present in the next while loop
    int input_choice;
    //variables to keep track of the user that is being used at the moment
    int current_user_id;

    std::cout << "Welcome. This program simulates a bank system." << std::endl << "You can create a User, who can open an Account" << std::endl << "and make a transaction with that Account." << std::endl << std::endl;

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
            std::cout << "What is the name of the user?" << std::endl;
            std::string name_input;
            while(!(std::cin >> name_input)){
                std::cout << "Invalid input. Please input a string." << std::endl;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
            std::cout << "What is their surname?" << std::endl;
            std::string surname_input;
            while(!(std::cin >> surname_input)){
                std::cout << "Invalid input. Please input a string." << std::endl;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
            auto new_user = adm->createUser(name_input, surname_input);
            current_user_id = new_user->getId();
            std::cout << "Congratulation. You have created the user " << new_user->getLegalName() << "!" << std::endl;
            std::cout << "The new user's Id is " << current_user_id << ". Remember it if you'll want to access this user again." << std::endl;
            //pauses the program and gives time to read the id of the new User object
            system("pause");
            spaceOutPrints();
            //condition is true only if the program user has exited the User menu with a 0
            User* current_user = adm->getUsers().at(current_user_id).get();
            if(!(runUserMenu(adm, current_user))){
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
                     std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
                //checks if the id inputted exists in the map.
                //In C++ 20 can also use .contains method
                if(adm->getUsers().find(current_user_id) != adm->getUsers().end()){
                    key_exists = true;
                }
                else {
                    std::cout << "The Id that you have inputted belongs to no User. Please try a different Id" << std::endl;
                     std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
            }
            User* current_user = adm->getUsers().at(current_user_id).get();
            //condition is true only if the program user has exited the User menu with a 0
            if(!(runUserMenu(adm, current_user))){
                break;
            }
        }
        else if(input_choice == 3) {
            spaceOutPrints();
            std::cout << "The Users that currently exist are:" << std::endl;
            for(auto i = adm->getUsers().begin(); i != adm->getUsers().end(); i++){
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
            std::cout << "Invalid input. Please input a number among the ones in the options." << std::endl;
            system("pause");
            spaceOutPrints();
        }
    }

    delete adm;
    return 0;
}
