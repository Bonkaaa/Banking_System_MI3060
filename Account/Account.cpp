#include "Account.h"
#include <iostream>
#include <cassert>
using namespace std;


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

string Account::getPin() const {
    return pin;
}

bool Account::isActive() const {
    return (status == "Hoat dong") ? true : false; // Assuming "Hoat dong" means active
}

// PIN Management
bool Account::verifyPin(const string& inputPIN) const {
    return pin == inputPIN;
}

void Account::changePin(string& newPIN) {
    pin = newPIN;
}

// Lock/Unlock Account
void Account::lockAccount() {
    status = "Bi khoa"; // Assuming "Hoat dong" means active and "Inactive" means locked
}  

void Account::unlockAccount() {
    status = "Hoat dong"; // Assuming "Hoat dong" means active
}

void Account::setBalance(double newBalance) {
    assert(newBalance >= 0); // Ensure balance cannot be negative
    balance = newBalance;
}