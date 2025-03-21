//
// Created by fpicc on 08/03/2025.
//

#ifndef PROGETTOLABPROG_USERMANAGER_H
#define PROGETTOLABPROG_USERMANAGER_H


#include <map>
#include <memory>
#include <string>
#include "User.h"

//handles loading and saving users to user.csv
//maybe make UserManager a singleton to avoid issues
class UserManager {
private:
    std::string filename;
    //TODO error handling in pieces of code that use users to catch possible exceptions thrown by using a bad key
    std::map<int, std::unique_ptr<User>> users;

public:
    UserManager(const std::string fn): filename(fn){};

    //to be used when the program starts to load all users from csv file onto the field users, returns true if loading is successful
    bool loadUsers();

    //adds a new user to the csv file
    bool saveUser(std::unique_ptr<User> u);

    User* getUser(int id) const {
        return users.at(id).get(); //get() passes raw pointer without transferring ownership
    }

    //UserManager manages creating Users because otherwise when a new user is made it can't also be passed in the constructor to the UserManager to add it as a shared ptr to the map
    //FIXME for single resposibility principle this method should be implmented in a Factory class
    std::unique_ptr<User> createUser(const std::string& name, const std::string& surname);

};


#endif //PROGETTOLABPROG_USERMANAGER_H
