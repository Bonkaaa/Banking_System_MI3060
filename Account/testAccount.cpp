#include "Account.h"
#include <cassert>
#include <iostream>
using namespace std;

// Test account creation and getters
void test_account_creation() {
    Account acc("123", "John Doe", "4321", 100.0);
    assert(acc.getID() == "123");
    assert(acc.getOwnerName() == "John Doe");
    assert(acc.getBalance() == 100.0);
    assert(acc.isActive());
    cout << "Account creation test passed.\n";
}

// Test PIN verificationg++ Account\testAccount.cpp Account\Account.cpp -o testAccount.exe
void test_pin_verification() {
    Account acc("124", "Alice", "0000", 50.0);
    assert(acc.verifyPin("0000"));
    assert(!acc.verifyPin("1111"));
    cout << "PIN verification test passed.\n";
}

// Test PIN change
void test_change_pin() {
    Account acc("125", "Bob", "5555", 200.0);
    acc.changePin("1234");
    assert(acc.verifyPin("1234"));
    assert(!acc.verifyPin("5555"));
    cout << "Change PIN test passed.\n";
}

// Test lock and unlock account
void test_lock_unlock_account() {
    Account acc("126", "Carol", "9999", 300.0);
    acc.lockAccount();
    assert(!acc.isActive());
    acc.unlockAccount();
    assert(acc.isActive());
    cout << "Lock/unlock account test passed.\n";
}

int main() {
    test_account_creation();
    test_pin_verification();
    test_change_pin();
    test_lock_unlock_account();
    cout << "All Account class tests passed.\n";
    return 0;
}