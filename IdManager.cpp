//
// Created by fpicc on 19/03/2025.
//
#include <fstream>
#include "IdManager.h"

//FIXME this implementation of managing ids doesn't work nicely if we have no id tracker file but have got an already initialized objects saved.
//a way to fix this could be to add to the object manager classes a counter that keeps track of highest id found yet and at the end updates the id tracker to that value
int generateNextId(const std::string& filename) {
    std::ifstream file(filename);
    int lastId = 0;
    if (!(file >> lastId)) { //if reading fails default to 0
        lastId = 0;
    }
    int newId = lastId + 1;  // Compute the new ID
    file.close();

    // Open file in truncate mode to overwrite with the new ID
    std::ofstream outFile(filename, std::ios::trunc);
    outFile << newId;
    outFile.close();

    return newId;
}