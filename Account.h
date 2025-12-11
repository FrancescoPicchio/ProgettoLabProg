#ifndef PROGETTOLABPROG_ACCOUNT_H
#define PROGETTOLABPROG_ACCOUNT_H


#include <string>
#include <vector>
#include <memory>

//Forward declaration of User and Transaction classes to avoid circular dependencies
class User;
class AppDataManager;
class Transaction;
/*TODO implement joint accounts, a children class of Account that has two owners, because User.accounts is made up of unique_ptrs
maybe we can use a map of shared_ptrs as an extra field for a user.*/

class Account {
private:
    int id;
    std::string name;
    User* owner;
    //FIXME should be a double and not an int, maybe
    int balance;
    std::vector <std::shared_ptr<Transaction>> transactions;

    //not 100% sure that this makes sense
    bool save_transaction_to_CSV(Transaction* t);
    bool update_balance_CSV() const;

public:
    Account(std::string n, User* u, AppDataManager* adm);
    //this method should only be called by AppDataManager with load_accounts, otherwise it'll mess up the id of the rest of the acounts, because then id won't necessarily be a primary key
    Account(int i, std::string n, User* u, int b);

    std::string get_name() const {
        return name;
    }

    int get_balance() const {
        return balance;
    }

    bool set_balance(int b, AppDataManager* adm);

    bool add_balance(int b, AppDataManager* adm);

    bool remove_balance(int b, AppDataManager* adm);

    User* get_owner() const {
        return owner;
    };

    int get_id() const {
        return id;
    }

    void print_info() const;

    bool make_transaction(Account *receiver, int amount, AppDataManager* adm);

    void add_transaction(const std::shared_ptr<Transaction> t) {
        transactions.push_back(t);
    }

    //Do not store this vector beyond the lifetime of the original shared_ptrs
    std::vector<Transaction*> get_transactions() const;

    void print_transactions() const;
};


#endif //PROGETTOLABPROG_ACCOUNT_H