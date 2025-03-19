#include <iostream>
#include <fstream>
#include "User.h"
#include "UserManager.h"

//TODO maybe make this a method for all the manager classes
void loadData(const std::string& filename) {
    std::ifstream file(filename);  // Try to open the file
    if (!file) {  // If file doesn't exist
        std::ofstream newFile(filename);  // Create the file
        if (newFile) {
            std::cout << filename << "' created successfully.\n";
        } else {
            std::cerr << "Error creating file '" << filename << "'.\n"; //cerr is used for error messages
            file.close();
        }
    } else {
        std::cout << filename << " has been loaded.\n";
        file.close(); //TODO actually load the data
    }
}

void spaceOutPrints() {
    //Prints 20 newlines to "clear" the console, helping with readability
    int i;
    for(i = 0; i < 15; i++) {
        std::cout << std::endl;
    }
}


int main() {
    loadData("users.csv");
    loadData("accounts.csv");
    loadData("transactions.csv");
    spaceOutPrints();

    //small piece of code to test if loadusers() works
    auto *um = new UserManager("users.csv");
    um->loadUsers();
    const std::map<int, std::shared_ptr<User>>& users = um->getUsers();
    // .at(key) throws an exception if key doesn't exist
    std::string username1 = users.at(1)->getLegalName();
    std::cout << username1 << std::endl;
    std::string username2 = users.at(3)->getLegalName();
    std::cout << username2 << std::endl;

    /*
    auto *u1 = new User("Gianni", "Rossi");
    auto *a1 = new Account("Conto Banca 1", checking_account, u1);
    a1->setBalance(300);
    auto *a2 = new Account("Conto Banca 2", checking_account, u1);
    a2->setBalance(500);
    u1->makeTransaction(a1, a2, 100);
    std::cout << "First account's balance is: " << a1->getBalance() << std::endl;
    std::cout << "Second account's balance is: " << a2->getBalance() << std::endl;
    delete u1;*/
    delete um;

    return 0;
}
