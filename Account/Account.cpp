#include "Account.h"
#include <iostream>
#include <cassert>
using namespace std;


Account::~Account() {
}  

// Getters
string Account::getID() const {
    return accountID;
}

string Account::getOwnerName() const {
    return ownerName;
}

double Account::getBalance() const {
    return balance;
}

bool Account::isActive() const {
    return status == "active";
}

// PIN Management
bool Account::verifyPin(const string& inputPIN) const {
    return pin == inputPIN;
}

void Account::changePin(const string& newPIN) {
    pin = newPIN;
}

// Lock/Unlock Account
void Account::lockAccount() {
    status = "inactive";
}  

void Account::unlockAccount() {
    status = "active";
}

// Transaction Management
// void Account::addTransaction(const string& type, double amount) {
//     if (type != "deposit" && type != "withdrawal") {
//         cout << "Invalid transaction type." << endl;
//         return;
//     }
//
//     if (type == "withdrawal" && amount > balance) {
//         cout << "Insufficient funds for withdrawal." << endl;
//         return;
//     }
//
//     if (type == "withdrawal") {
//         balance -= amount;
//     } else if (type == "deposit") {
//         balance += amount;
//     }
//
//     TransactionNode* newNode = new TransactionNode(type, amount);
//     if (transactionHead == nullptr) {
//         transactionHead = newNode;
//     } else {
//         TransactionNode* temp = transactionHead;
//         while (temp->next) {
//             temp = temp->next;
//         }
//         temp->next = newNode;
//     }
// }

// void Account::displayTransactions() const {
//     if (!transactionHead) {
//         cout << "No transactions available." << endl;
//         return;
//     }
//
//     TransactionNode* temp = transactionHead;
//     cout << "Transactions for account " << accountID << ":" << endl;
//     cout << "---------------------------------" << endl;
//     while (temp) {
//         cout << temp->type << ": " << temp->amount << endl;
//         temp = temp->next;
//     }
// }

