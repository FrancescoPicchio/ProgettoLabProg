//
// Created by fpicc on 08/03/2025.
//

#include "UserManager.h"

bool UserManager::loadUsers() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file " << filename << std::endl;
        return false;
    }

    std::string line;
    std::string name, surname, id_str;
    int id;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        //lines have to be formatted id,name,surname. Important id first to make it easier to lookup ids faster
        //the >> operator for stringstream automatically converts string into int
        if (std::getline(ss, id_str, ',') && std::getline(ss, name, ',') && std::getline(ss, surname, ',')) {
            //converts string into int
            id = std::stoi(id_str);
            // Create a new user and add to the map (using id as the key)
            auto user = std::make_shared<User>(name, surname, id);
            users[id] = user;
        } else {
            std::cerr << "Error reading line: " << line << std::endl;
            continue; //skips lines with wrong formatting
        }
    }

    file.close();
    return true;
}