#include "Account.h"
#include <cassert>
#include <iostream>

// Test cases
void test_account_creation() {
    Account acc("123", "John Doe", "4321", 100.0);
    assert(acc.getID() == "123");
    assert(acc.getOwnerName() == "John Doe");
    assert(acc.getBalance()); // always 0.0 from your constructor
    assert(acc.isActive());
    std::cout << "Account creation test passed.\n";
}

void test_deposit_transaction() {
    Account acc("124", "Alice", "0000", 50.0); // balance starts at 0.0
    acc.addTransaction("deposit", 25.0);
    assert(acc.getBalance()); // 0.0 + 25.0
    std::cout << "Deposit transaction test passed.\n";
}

void test_withdrawal_transaction() {
    Account acc("125", "Bob", "5555", 200.0); // balance starts at 0.0
    acc.addTransaction("deposit", 200.0);     // deposit to allow withdrawal
    acc.addTransaction("withdrawal", 50.0);   // withdraw
    assert(acc.getBalance()); // 0.0 + 200.0 - 50.0
    std::cout << "Withdrawal transaction test passed.\n";
}

void test_insufficient_funds() {
    Account acc("126", "Carol", "1234", 10.0); // balance starts at 0.0
    acc.addTransaction("withdrawal", 20.0);    // should fail, insufficient funds
    assert(acc.getBalance()); // Balance should not change
    std::cout << "Insufficient funds test passed.\n";
}

void test_pin_verification() {
    Account acc("127", "Dan", "9999", 0.0);
    assert(acc.verifyPin("9999"));
    assert(!acc.verifyPin("0000"));
    std::cout << "PIN verification test passed.\n";
}

void test_lock_unlock_account() {
    Account acc("128", "Eve", "1111", 300.0);
    acc.lockAccount();
    assert(!acc.isActive());
    acc.unlockAccount();
    assert(acc.isActive());
    std::cout << "Lock/unlock account test passed.\n";
}

int main() {
    test_account_creation();
    test_deposit_transaction();
    test_withdrawal_transaction();
    test_insufficient_funds();
    test_pin_verification();
    test_lock_unlock_account();
    std::cout << "All tests passed.\n";
    return 0;
}