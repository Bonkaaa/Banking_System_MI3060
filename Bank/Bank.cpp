#include "Bank.h"
#include "..\Account\Account.h"
#include <iostream>
#include <limits>
using namespace std;

Bank::Bank() {}
Bank::~Bank() {}

// Create a new account
void Bank::createAccount() {
    string id, name, pin;
    double initialBalance;

    cout << "Enter Account ID: ";
    cin >> id;
    cout << "Enter Owner Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline from previous input
    getline(cin, name);
    cout << "Enter PIN: ";
    cin >> pin;
    cout << "Enter Initial Balance: ";
    cin >> initialBalance;

    Account newAccount(id, name, pin, initialBalance);
    accountList.push_back(newAccount);
    cout << "Account created successfully.\n";
}

// Find account by ID, returns pointer to Account or nullptr if not found
Account* Bank::findAccountByID(const string& id) {
	for (auto& account : accountList) {
		if (account.getID() == id) {
			return &account;
            }
        }
    return nullptr; // Not found
}

// Show information of an account by ID
void Bank::showAccountInfo(const string& id) {
    for (const auto& account : accountList) {
        if (account.getID() == id) {
            cout << "Account ID: " << account.getID() << endl;
            cout << "Owner Name: " << account.getOwnerName() << endl;
            cout << "Balance: " << account.getBalance() << endl;
            cout << "Status: " << (account.isActive() ? "Active" : "Inactive") << endl;
            cout << "--------------------------------\n";
            return;
        }
    }
}

void Bank::showAllAccounts() {
    cout << "All Accounts:\n";
    for (const auto& account : accountList) {
        cout << "--------------------------------\n";
        cout << "Account ID: " << account.getID() << ", Owner Name: " << account.getOwnerName()
             << ", Balance: " << account.getBalance() << ", Status: " << (account.isActive() ? "Active" : "Inactive") << endl;
    }
    cout << "--------------------------------\n";
}

const vector<Account>& Bank::getAccountList() const {
    return accountList;
}

int main() {
    return 0; // Placeholder for main function, can be expanded for testing or user interaction
}