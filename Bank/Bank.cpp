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

    Account newAccount(id, name, pin, initialBalance, "active");
    accountList.push_back(newAccount);
    cout << "Tai khoan duoc khoi tao thanh cong.\n";

    // Save to file 
    ofstream fout("accounts.txt", ios::app);
    if (fout.is_open()) {
        fout << id << "," << name << "," << pin << "," << initialBalance << ",active\n";
        fout.close();
    } else {
        cout << "Gap loi khi moi file\n";
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
            cout << "ID tai khoan: " << account.getID() << endl;
            cout << "Ten chu tai khoan: " << account.getOwnerName() << endl;
            cout << "So du: " << account.getBalance() << endl;
            cout << "Trang thai: " << (account.isActive() ? "Hoat dong" : "Bi khoa") << endl;
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
        cout << "ID tai khoan: " << account.getID() << ", Ten chu tai khoan: " << account.getOwnerName()
             << ", So du: " << account.getBalance() << ", Trang thai: " << (account.isActive() ? "Hoat dong" : "Bi khoa") << endl;
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
        cout << "Gap loi khi mo file\n";
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
        Account newAccount(id, name, pin, balance, status);
        accountList.push_back(newAccount);
    }
    fin.close();
}

void Bank::saveAccountsToFile(const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "Gap loi khi mo file de luu tai khoan\n";
        return;
    }

    for (const auto& account : accountList) {
        fout << account.getID() << "," << account.getOwnerName() << "," 
             << account.getPin() << "," << account.getBalance() << "," 
             << (account.isActive() ? "Hoat dong" : "Bi khoa") << "\n";
    }
    fout.close();
}