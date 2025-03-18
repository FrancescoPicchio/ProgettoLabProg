//
// Created by fpicc on 08/03/2025.
//

#ifndef PROGETTOLABPROG_USERMANAGER_H
#define PROGETTOLABPROG_USERMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <memory>
#include <string>
#include "User.h"

//handles loading and saving users to user.csv
class UserManager {
private:
    std::string filename;
    //TODO error handling in pieces of code that use users
    std::map<int, std::shared_ptr<User>> users;

public:
    UserManager(const std::string fn): filename(fn){};

    //to be used when the program starts to load all users from csv file onto the field users, returns true if loading is successful
    bool loadUsers();

    bool saveUser();

    // Function to get the map of users
    const std::map<int, std::shared_ptr<User>>& getUsers() const {
        return users;
    }

};


#endif //PROGETTOLABPROG_USERMANAGER_H
