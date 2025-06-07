#include "Bank.h"
#include "..\Account\Account.h"
#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

Bank::Bank() {}
Bank::~Bank() {}

// Create a new account
void Bank::createAccount() {
    string id, name, pin;
    double initialBalance;

    cout << "Nhap ID tai khoan: ";
    cin >> id;
    cout << "Nhap ten chu tai khoan: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline from previous input
    getline(cin, name);
    cout << "Nhap ma PIN (4 chu so): ";
    cin >> pin;
    cout << "Nhap so du khoi tao: ";
    cin >> initialBalance;

    Account newAccount(id, name, pin, initialBalance);
    accountList.push_back(newAccount);
    cout << "Tai khoan duoc khoi tao thanh cong.\n";

    // Save to file 
    ofstream fout("accounts.txt", ios::app);
    if (fout.is_open()) {
        fout << id << "," << name << "," << pin << "," << initialBalance << ",active\n";
        fout.close();
    } else {
        cout << "Error opening file to save account.\n";
    }
}

// Find account by ID, returns pointer to Account or nullptr if not found
Account* Bank::findAccountByID(const string& id) {
	for (auto& account : accountList) {
		if (account.getID() == id) {
			return &account;
            }
        }
    cout << "Khong tim thay tai khoan voi ID: " << id << endl;
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
    cout << "Khong tim thay tai khoan voi ID: " << id << endl;
    cout << "--------------------------------\n";
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

// Load accounts from a file
void Bank::loadAccountsFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Error opening file to load accounts.\n";
        return;
    }

    string line;
    while (getline(fin, line)) {
        // Split the line by commas
        stringstream ss(line);
        string id, name, pin, balanceStr, status;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, pin, ',');
        getline(ss, balanceStr, ',');
        getline(ss, status);

        double balance = stod(balanceStr);
        Account newAccount(id, name, pin, balance);
        if (status == "active") {
            newAccount.unlockAccount();
        } else {
            newAccount.lockAccount();
        }
        
        accountList.push_back(newAccount);
    }
    fin.close();
}