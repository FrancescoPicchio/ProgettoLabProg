//
// Created by fpicc on 08/03/2025.
//

#ifndef PROGETTOLABPROG_TRANSACTIONMANAGER_H
#define PROGETTOLABPROG_TRANSACTIONMANAGER_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Transaction.h"

class TransactionManager {
private:
    std::string filename;
    //std::vector<Transaction*> transactions;
public:
    TransactionManager(const std::string fn): filename(fn){};

    //populates the vector of transactions with the ones saved in transactions.csv
    bool loadTransactions(const std::map<int, Account*>& accounts, std::vector<Transaction*>& transactions);

    bool saveTransaction(Transaction* t);

    /*
    const std::vector<Transaction*> getTransactions() const {
        return transactions;
    }*/
};


#endif //PROGETTOLABPROG_TRANSACTIONMANAGER_H
