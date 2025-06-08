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
        Account(const string& id, const string& name, const string& p, double initialBalance, const string& status)
            : accountID(id), ownerName(name), pin(p), balance(initialBalance), status(status) {}

        // Getters
        string getID() const;
        string getOwnerName() const;
        string getPin() const;
        double getBalance() const;
        bool isActive() const;

        // PIN Management
        bool verifyPin(const string& inputPIN) const;
        void changePin(string& newPIN);

        // Lock/Unlock Account
        void lockAccount();
        void unlockAccount();

        // Set balance
        void setBalance(double newBalance);

        // Check if account is locked
        bool isLocked() const;
};

#endif 

        