#include <iostream>
#include <fstream>
#include "User.h"

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

    auto *u1 = new User("Gianni", "Rossi");
    auto *a1 = new Account("Conto Banca 1", checking_account, u1);
    a1->setBalance(300);
    auto *a2 = new Account("Conto Banca 2", checking_account, u1);
    a2->setBalance(500);
    u1->makeTransaction(a1, a2, 100);
    std::cout << "First account's balance is: " << a1->getBalance() << std::endl;
    std::cout << "Second account's balance is: " << a2->getBalance() << std::endl;
    delete u1;

    return 0;
}
