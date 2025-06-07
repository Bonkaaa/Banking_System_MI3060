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
    return status == "Hoat dong";
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
    status = "Khoa";
}  

void Account::unlockAccount() {
    status = "Hoat dong";
}

