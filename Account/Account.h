#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Account {
    private:

        string accountID;
        string ownerName;
        double balance;
        string pin;
        string status; // "active" or "inactive"

    public:
        // Constructor and Destructor
        Account(const string& id, const string& name, const string& p, double initialBalance)
            : accountID(id), ownerName(name), balance(initialBalance), pin(p), status("active") {}

        ~Account();

        // Getters
        string getID() const;
        string getOwnerName() const;
        double getBalance() const;
        bool isActive() const;

        // PIN Management
        bool verifyPin(const string& inputPIN) const;
        void changePin(const string& newPIN);

        // Lock/Unlock Account
        void lockAccount();
        void unlockAccount();

};
#endif