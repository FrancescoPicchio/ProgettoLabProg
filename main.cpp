#include <iostream>
#include <fstream>
#include "User.h"
#include "AppDataManager.h"

//TODO Maybe add this inside the load_data function of AppDataManager
void load_data(const std::string& filename) {
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

void space_out_prints() {
    //Prints 5 newlines to help with legibility
    int i;
    for(i = 0; i < 5; i++) {
        std::cout << std::endl;
    }
}

std::string get_sanitized_name_input(){
    std::string new_name;
    bool name_is_not_valid = true;
    while(name_is_not_valid){
        if(!(std::cin >> new_name)){
            std::cout << "Invalid input." << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        else{
            //Removes commas to avoid issues with csv files. std::erase works only for C++20
            std::erase(new_name, ',');
            if(new_name.empty()){
                std::cout << "Invalid input." << std::endl;
                std::cin.clear();
                std::cin.ignore(1000, '\n'); 
            }
            else{
                name_is_not_valid = false;
            }
        }  
    }
    return new_name;
}


void make_new_transaction(AppDataManager* adm, Account* current_account){
    space_out_prints();
    std::cout << "Who do you want to send the money to? Give the Id of the account that'll receive the money" << std::endl;
    bool key_exists = false;
    int receiver_id;
    while(!key_exists) {
        //checks if input choice is actually an int and not something else
        while (!(std::cin >> receiver_id)) {
            std::cout << "Invalid input. Please input a positive integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        //checks if the id inputted exists in the map
        if (!(adm->get_accounts().find(receiver_id) != adm->get_accounts().end())) {
            std::cout << "The Id that you have inputted belongs to no Account. Please try a different Id" << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        } //Checks if the Account is trying to give itself money
        else if(current_account->get_id() == adm->get_accounts().at(receiver_id)->get_id()) {
            std::cout << "You can't transfer money to the same Account!" << std::endl;
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
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        amount_is_correct = current_account->make_transaction(adm->get_accounts().at(receiver_id), amount_for_transaction, adm);
    }
}

void deposit_to_account(Account* current_account, AppDataManager* adm){
    space_out_prints();
    std::cout << "How much would you like to deposit?" << std::endl;
    int deposit_amount = 0;
    while(!(std::cin >> deposit_amount && deposit_amount > 0)) {
        std::cout << "Invalid amount. Please input a positive integer." << std::endl;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
    current_account->add_balance(deposit_amount, adm);
}

//Executes the logic for a specific account, which entails mostly making a transaction with another account.
bool run_account_menu(AppDataManager* adm, Account* current_account){
    int input_choice;
    while(true){
        //TODO Add option to close an Account
        //Operations that can be made with a given Account
        std::cout << "You're accessing " << current_account->get_name() << " and its current balance is: " << current_account->get_balance() << std::endl << std::endl;
        std::cout << "Press 1 to make a new transaction, sending money from this Account to another" << std::endl;
        std::cout << "Press 2 to make a deposit on this Account" << std::endl;
        std::cout << "Press 3 to print out the transactions of this Account" << std::endl;
        std::cout << "Press 4 to print out the existing Accounts and their Owners" << std::endl;
        std::cout << "Press 5 to exit this Account and return to the User submenu" << std::endl;
        std::cout << "Press 0 to exit the program" << std::endl;
        if(!(std::cin >> input_choice)) {
            std::cout << "Invalid input, there's no choice associated with that number!" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            system("pause");
            space_out_prints();
            continue;
        }
        space_out_prints();
        //Makes a new transaction with another account
        if(input_choice == 1){
            make_new_transaction(adm, current_account);
        }
        else if(input_choice == 2){
            deposit_to_account(current_account, adm);
        }
        else if(input_choice == 3) {
            current_account->print_transactions();
            system("pause");
            space_out_prints();
        }
        else if(input_choice == 4) {
            space_out_prints();
            std::cout << "The currently existing Accounts are:" << std::endl;
            for(auto i : adm->get_accounts()){
                i.second->print_info();
            }
            system("pause");
            space_out_prints();
        }
        else if(input_choice == 5) {
            space_out_prints();
            return true;
        }
        else if(input_choice == 0) {
            return false;
        }
        else {
            space_out_prints();
            std::cout << "Please input a number associated with a choice." << std::endl;
            system("pause");
            space_out_prints();
        }
    }
}

//selects and access and Account for a User in the User menu
bool select_account(AppDataManager* adm, User* current_user){
    int current_account_id;
    if(!current_user->print_accounts()) {
            system("pause");
            space_out_prints();
            return false;
        }
        std::cout << "Please input the id of one of your Accounts to access it." << std::endl;
        space_out_prints();
        bool key_exists = false;
        while(!key_exists){
            //checks if input choice is actually an int and not something else
            while(!(std::cin >> current_account_id)) {
                std::cout << "Invalid input. Please input a positive integer." << std::endl;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
            //checks if the id inputted exists in the map 
            if(adm->get_accounts().find(current_account_id) != adm->get_accounts().end()){
                if(current_user->get_id() == adm->get_accounts().at(current_account_id)->get_owner()->get_id()) {
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
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
        }
        //The condition is true only if the program user chooses 0 in the Account submenu
        Account* current_account = adm->get_accounts().at(current_account_id);
        if(!(run_account_menu(adm, current_account))){
            return false;
        }
        else {
            return true;
        }
}

//Executes the logic once a program user has logged in, which consists of accessing an Account or opening a new one. 
//Returns false only if the User wants to exit the program.
bool run_user_menu(AppDataManager* adm, User* current_user){
    int input_choice;
    int current_account_id;
    while(true) {
        //TODO Add option to delete your User profile
        //Operations that can be made with a given User
        std::cout << std::endl << "You have logged in as " << current_user->get_legal_name() << ", you can:" << std::endl << std::endl;
        std::cout << "Press 1 access an Account you own." << std::endl;
        std::cout << "Press 2 to open a new Account for you." << std::endl;
        std::cout << "Press 3 to see the balance and Id for the Accounts you own." << std::endl;
        std::cout << "Press 4 to log out of current User." << std::endl;
        std::cout << "Press 0 to exit the program." << std::endl;
        if(!(std::cin >> input_choice)) {
            std::cout << "Invalid input, please input a number from the choices!" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            //resets the loop if the input is wrong, so it can print out the possible choices. Pauses to give the user time to read the error message
            system("pause");
            space_out_prints();
            continue;
        }
        space_out_prints();
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
            //TODO refactor this into a separate function
            std::cout << "Please input your new Account's name" << std::endl;
            std::string new_account_name = get_sanitized_name_input();
            Account* new_account = current_user->open_account(new_account_name, adm);
            current_account_id = new_account->get_id();
            std::cout << "New Account " << new_account->get_name() << " was created successfully." << std::endl;
            Account* current_account = adm->get_accounts().at(current_account_id);
            //accesses the Account submenu as the newly created user, condition is true only if the program user selects 0 from the Account submenu
            if(!(run_account_menu(adm, current_account))){
                return false;
            }
            else {
                continue;
            }
        }
        //prints out the current User's Accounts and their total balance
        else if(input_choice == 3){
            current_user->print_accounts();
            std::cout << "And their total balance is: " << current_user->get_total_balance() << std::endl;
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
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            //pauses until another input to give time to the user to read the error message
            system("pause");
            space_out_prints();
        }
    }
}


int main() {
    load_data("users.csv");
    load_data("accounts.csv");
    load_data("transactions.csv");
    load_data("user_id_tracker.csv");
    load_data("account_id_tracker.csv");
    space_out_prints();

    auto *adm = new AppDataManager();
    if(!adm->load_app_data()) {
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
            std::cout << "Invalid input. Please input a number among the ones in the options." << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        //Program user wants to create a new User object
        if(input_choice == 1) {
            //TODO Refactor this in a separate function
            std::cout << "What is the name of the user?" << std::endl;
            std::string name_input = get_sanitized_name_input();
            std::cout << "What is their surname?" << std::endl;
            std::string surname_input = get_sanitized_name_input();
            auto new_user = adm->create_user(name_input, surname_input);
            current_user_id = new_user->get_id();
            std::cout << "Congratulation. You have created the user " << new_user->get_legal_name() << "!" << std::endl;
            std::cout << "The new user's Id is " << current_user_id << ". Remember it if you'll want to access this user again." << std::endl;
            //pauses the program and gives time to read the id of the new User object
            system("pause");
            space_out_prints();
            //condition is true only if the program user has exited the User menu with a 0
            User* current_user = adm->get_users().at(current_user_id).get();
            if(!(run_user_menu(adm, current_user))){
                break;
            }
        }
        //Program user wants to access a User
        else if(input_choice == 2) {
            //TODO refactor this in a separate function
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
                if(adm->get_users().find(current_user_id) != adm->get_users().end()){
                    key_exists = true;
                }
                else {
                    std::cout << "The Id that you have inputted belongs to no User. Please try a different Id" << std::endl;
                     std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
            }
            User* current_user = adm->get_users().at(current_user_id).get();
            //condition is true only if the program user has exited the User menu with a 0
            if(!(run_user_menu(adm, current_user))){
                break;
            }
        }
        else if(input_choice == 3) {
            space_out_prints();
            std::cout << "The Users that currently exist are:" << std::endl;
            for(auto i = adm->get_users().begin(); i != adm->get_users().end(); i++){
                std::cout << i->second->get_legal_name() << " and their Id is: " << i->second->get_id() << std::endl;
            }
            system("pause");
            space_out_prints();
        }
        //ends the loop if input_choice is 0
        else if(input_choice == 0) {
            break;
        }
        //if the input isn't either 1 or 2 it resets the loop.
        else {
            std::cout << "Invalid input. Please input a number among the ones in the options." << std::endl;
            system("pause");
            space_out_prints();
        }
    }

    delete adm;
    return 0;
}
