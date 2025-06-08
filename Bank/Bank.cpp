#include "Bank.h"
#include "..\Account\Account.h"
#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

Bank::Bank() {}
Bank::~Bank() {}

// Create a new account
void Bank::createAccount() {
    string id, name, pin;
    double initialBalance;

    cout << "Nhập ID tài khoản (6 chữ số): ";
    while (true) {
        cin >> id;
        if (id.length() == 6 && all_of(id.begin(), id.end(), ::isdigit)) {
            break; // Valid ID
        } else {
            cout << "ID tài khoản phải là 6 chữ số. Vui lòng nhập lại: ";
        }
    }
    cout << "Nhập tên chủ tài khoản: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline from previous input
    getline(cin, name);
    cout << "Nhập mã PIN (4 chữ số): ";
    while (true) {
        cin >> pin;
        if (pin.length() == 4 && all_of(pin.begin(), pin.end(), ::isdigit)) {
            break; // Valid PIN
        } else {
            cout << "Mã PIN phải là 4 chữ số. Vui lòng nhập lại: ";
        }
    }
    cout << "Nhập số dư khởi tạo: ";
    cin >> initialBalance;

    string status = "Hoạt động"; // Default status for new accounts

    Account newAccount(id, name, pin, initialBalance, status);
    accountList.push_back(newAccount);
    cout << "Tài khoản đã được tạo thành công!" << endl;

    // Save to file 
    ofstream fout("accounts.txt", ios::app);
    if (fout.is_open()) {
        fout << id << "," << name << "," << pin << "," << initialBalance << status << endl;
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
    return nullptr; // Return nullptr if not found
}

// Show information of an account by ID
void Bank::showAccountInfo(const string& id) {
    for (const auto& account : accountList) {
        if (account.getID() == id) {
            cout << "ID tài khoản: " << account.getID() << endl;
            cout << "Tên chủ tài khoản: " << account.getOwnerName() << endl;
            cout << "Số dư: " << account.getBalance() << endl;
            cout << "Trạng thái: " << (account.isActive() ? "Hoạt động" : "Bị khoá") << endl;
            cout << "--------------------------------\n";
            return;
        }
    }
    cout << "Không tìm thấy tài khoản: " << id << endl;
    cout << "--------------------------------\n";
}

void Bank::showAllAccounts() {
    for (const auto& account : accountList) {
        cout << "--------------------------------\n";
        cout << "ID tài khoản " << account.getID() << ", Tên chủ tài khoản " << account.getOwnerName()
             << ", Số dư: " << account.getBalance() << ", Trạng thái: " << (account.isActive() ? "Hoạt động" : "Bị khoá") << endl;
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
        cout << "Gặp lỗi khi mở file\n";
        return;
    }

    for (const auto& account : accountList) {
        fout << account.getID() << "," << account.getOwnerName() << "," 
             << account.getPin() << "," << account.getBalance() << "," 
             << (account.isActive() ? "Hoạt động" : "Bị khoá") << "\n";
    }
    fout.close();
}