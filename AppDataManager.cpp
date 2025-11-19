//
// Created by fpicc on 17/04/2025.
//

#include "AppDataManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

//creates csv files if they didn't exist
void AppDataManager::load_csv_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {  
        std::ofstream newFile(filename);
        if (newFile) {
            //Initializes the id counter for the id counter files to 0
            if(filename == userIdTrackerFile || filename == accountIdTrackerFile){
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

void AppDataManager::load_all_csv_files(){
    load_csv_file(accountsFile);
    load_csv_file(usersFile);
    load_csv_file(transactionsFile);
    load_csv_file(accountIdTrackerFile);
    load_csv_file(userIdTrackerFile);
}

//returns true only if it loads all the data from the different classes correctly
bool AppDataManager::load_app_data() {
    load_all_csv_files();

    bool usersLoaded = load_users();
    bool accountsLoaded = load_accounts();
    bool transactionsLoaded = load_transactions();

    if (!usersLoaded) std::cerr << "[Error] Failed to load users\n";
    if (!accountsLoaded) std::cerr << "[Error] Failed to load accounts\n";
    if (!transactionsLoaded) std::cerr << "[Error] Failed to load transactions\n";

    return usersLoaded && accountsLoaded && transactionsLoaded;
}

bool AppDataManager::load_users() {
    std::ifstream file(usersFile);
    if (!file.is_open()) {
        std::cerr << "Could not open the file " << usersFile << std::endl;
        return false;
    }
    std::string line;
    std::string name, surname, id_str;
    int id;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        //lines have to be formatted "id,name,surname" without the quotes. Important id first to make it easier to lookup ids faster
        //the >> operator for stringstream automatically converts string into int
        if (std::getline(ss, id_str, ',') && std::getline(ss, name, ',') && std::getline(ss, surname, ',')) {
            //converts string into int
            id = std::stoi(id_str);
            // Create a new user and add to the map (using id as the key)
            auto user = std::make_unique<User>(name, surname, id);
            users[id] = std::move(user);
        } else {
            std::cerr << "Error reading line: " << line << std::endl;
            continue; //skips lines with wrong formatting
        }
    }
    file.close();
    return true;
}

bool AppDataManager::load_accounts() {
    std::ifstream file(accountsFile);
    if (!file.is_open()) {
        std::cerr << "Could not open the file " << accountsFile << std::endl;
        return false;
    }
    std::string line;
    //getline() only works with strings
    std::string id_account_str, name, id_owner_str, balance_str;
    int id_account, id_owner, balance;
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        //lines have to be formatted "id_account, name, id_owner, balance" without the quotes. Important that id_account is first for faster lookups
        if(std::getline(ss, id_account_str, ',') && std::getline(ss, name, ',') && std::getline(ss, id_owner_str, ',') && std::getline(ss, balance_str, ',')) {
            id_account = std::stoi(id_account_str);
            id_owner = std::stoi(id_owner_str);
            balance = std::stoi(balance_str);
            std::unique_ptr<Account> account = std::make_unique<Account>(id_account, name, users[id_owner].get(), balance);
            //add account before using std::move otherwise you won't be able to access account
            accounts[id_account] = account.get();
            users[id_owner]->add_account(std::move(account));
        }else {
            std::cerr << "Error reading line: " << line << std::endl;
            continue; //skip lines with wrong formatting
        }
    }
    file.close();
    return true;
}

bool AppDataManager::load_transactions() {
    std::ifstream file(transactionsFile);
    if(!file.is_open()) {
        std::cerr << "Could not open the file " << transactionsFile << std::endl;
        return false;
    }
    std::string line;
    std::string id_sender_str, id_receiver_str, amount_str;
    int id_sender, id_receiver, amount;
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        //lines have to be formatted "id_sender, id_receiver, amount" without the quotes
        if(std::getline(ss, id_sender_str, ',') && std::getline(ss, id_receiver_str, ',') && std::getline(ss, amount_str, ',')) {
            id_sender = std::stoi(id_sender_str);
            id_receiver = std::stoi(id_receiver_str);
            amount = std::stoi(amount_str);
            auto t =  std::make_shared<Transaction>(accounts.at(id_sender), accounts.at(id_receiver), amount);
            accounts.at(id_sender)->add_transaction(t);
            accounts.at(id_receiver)->add_transaction(t);
        }else {
            std::cerr << "Error reading line: " << line << std::endl;
            continue; //skips lines with wrong formatting
        }
    }
    file.close();
    return true;
}

User* AppDataManager::create_user(const std::string &n, const std::string &s) {
    int id = generate_next_id(userIdTrackerFile);
    auto new_user = std::make_unique<User>(n, s, id);
    User* raw_new_user_ptr = new_user.get();

    //saves the new user in the csv file
    std::ofstream file(usersFile, std::ios::app);
    if(!file.is_open()){
        std::cerr << "Error saving user " << new_user->get_legal_name() << "to users.csv file" << std::endl;
        return nullptr;
    }
    std::string data = std::to_string(new_user->get_id()) + ',' + new_user->get_name() + ',' + new_user->get_surname();
    file << data << '\n';
    file.close();

    users[new_user->get_id()] = std::move(new_user);
    return raw_new_user_ptr;
}

bool AppDataManager::save_new_account_to_CSV(Account *a) {
    std::ofstream file(accountsFile, std::ios::app);
    if(!file.is_open()){
        std::cerr << "Error saving account " << a->get_name() << " to accounts.csv" << std::endl;
        return false;
    }
    std::string data = std::to_string(a->get_id()) + ',' + a->get_name() + ',' + std::to_string(a->get_owner()->get_id()) + ',' + std::to_string(a->get_balance());
    file << data << '\n';
    file.close();
    return true;
}


bool AppDataManager::save_transaction_to_CSV(Transaction *t) {
    std::ofstream file(transactionsFile, std::ios::app);
    if(!file.is_open()){
        std::cerr << "Error saving transaction " << " to transactions.csv" << std::endl;
        return false;
    }
    std::string data = std::to_string(t->get_sender()->get_id()) + ',' + std::to_string(t->get_receiver()->get_id()) + ',' + std::to_string(t->get_amount());
    file << data << '\n';
    file.close();
    return true;
}

bool AppDataManager::update_account_balance_CSV(Account* account) {
    // Load all accounts into memory, update one the rewrite the CSV file
    std::vector<std::string> lines;
    std::ifstream infile(accountsFile);
    std::string current_line;

    while (std::getline(infile, current_line)) {
        std::stringstream ss(current_line);
        int id;
        char comma;
        ss >> id >> comma;

        if (id == account->get_id()) {
            current_line = std::to_string(account->get_id()) + "," + account->get_name() + "," + std::to_string(account->get_owner()->get_id()) + "," + std::to_string(account->get_balance());
        }
        lines.push_back(current_line);
    }

    infile.close();

    std::ofstream outfile(accountsFile, std::ios::trunc);
    for (const auto& l : lines)
        outfile << l << '\n';
    outfile.close();

    return true;
}
