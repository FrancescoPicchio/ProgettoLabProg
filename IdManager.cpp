//
// Created by fpicc on 19/03/2025.
//
#include "IdManager.h"

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