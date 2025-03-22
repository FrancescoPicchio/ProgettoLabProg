//
// Created by fpicc on 08/03/2025.
//

#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool UserManager::loadUsers(std::map<int, std::unique_ptr<User>>& users) {
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
        //lines have to be formatted "id,name,surname" without the quotes. Important id first to make it easier to lookup ids faster
        //the >> operator for stringstream automatically converts string into int
        if (std::getline(ss, id_str, ',') && std::getline(ss, name, ',') && std::getline(ss, surname, ',')) {
            //converts string into int
            id = std::stoi(id_str);
            // Create a new user and add to the map (using id as the key)
            auto user = std::make_unique<User>(name, surname, id, this);
            users[id] = std::move(user);
        } else {
            std::cerr << "Error reading line: " << line << std::endl;
            continue; //skips lines with wrong formatting
        }
    }

    file.close();
    return true;
}

bool UserManager::saveUser(std::unique_ptr<User> u) {
    //std::ios::app lets you write to the file without having to truncate the rest
    std::ofstream file(filename, std::ios::app);
    if(!file.is_open()){
        std::cerr << "Error saving user " << u->getLegalName() << "to users.csv file" << std::endl;
        return false;
    }
    std::string data = std::to_string(u->getId()) + ',' + u->getName() + ',' + u->getSurname();
    file << data << std::endl;
    file.close();
    return true;
}

/*
std::unique_ptr<User> UserManager::createUser(const std::string& name, const std::string& surname) {
    auto user = std::make_unique<User>(name, surname, this);
    users[user->getId()] = std::move(user);  // Store in map
    return user;
}*/