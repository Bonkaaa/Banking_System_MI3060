#ifndef BANK_H
#define BANK_H

#include <vector>
#include <string>
#include <iostream>
#include "..\Account\Account.h"
using namespace std;

class Bank {
    private:
    vector<Account> accountList;

    public:
        // Constructor & Destructor
        Bank();
        ~Bank();

        // Create a new account
        void createAccount();

        // Find account by ID, returns pointer to Account or nullptr if not found

        // Show information of an account by ID
        void showAccountInfo(const string& id);

        // Show all accounts' information (admin only)
        void showAllAccounts();

        // (Optional) Getter for account list, if needed
        const vector<Account>& getAccountList() const;
};

#endif // BANK_H