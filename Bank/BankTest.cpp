#include "Bank.h"
#include <iostream>
#include <cassert>
#include <sstream>
using namespace std;

// Helper to simulate user input for createAccount
void simulateInput(const std::string& input) {
    static std::istringstream iss;
    iss.str(input);
    iss.clear();
    std::cin.rdbuf(iss.rdbuf());
}

void test_createAccount_and_findAccountByID() {
    Bank bank;
    // Simulate input: id, name, pin, initialBalance
    simulateInput("acc101\nJohn Doe\n1234\n1000\n");
    bank.createAccount();

    Account* acc = bank.findAccountByID("acc101");
    assert(acc != nullptr);
    assert(acc->getID() == "acc101");
    assert(acc->getOwnerName() == "John Doe");
    assert(acc->getBalance() == 1000.0);
    assert(acc->isActive());
    cout << "test_createAccount_and_findAccountByID passed.\n";
}

void test_showAccountInfo() {
    Bank bank;
    simulateInput("acc102\nJane Smith\n5678\n2000\n");
    bank.createAccount();

    cout << "Output of showAccountInfo (should display Jane Smith):\n";
    bank.showAccountInfo("acc102");
    cout << "test_showAccountInfo completed (visual check).\n";
}

void test_showAllAccounts() {
    Bank bank;
    simulateInput("acc201\nAlice\n1111\n500\nacc202\nBob\n2222\n600\n");
    bank.createAccount();
    bank.createAccount();

    cout << "Output of showAllAccounts (should display Alice and Bob):\n";
    bank.showAllAccounts();
    cout << "test_showAllAccounts completed (visual check).\n";
}

void test_findAccountByID_not_found() {
    Bank bank;
    simulateInput("acc301\nEve\n3333\n700\n");
    bank.createAccount();

    Account* acc = bank.findAccountByID("notfound");
    assert(acc == nullptr);
    cout << "test_findAccountByID_not_found passed.\n";
}

int main() {
    test_createAccount_and_findAccountByID();
    test_showAccountInfo();
    test_showAllAccounts();
    test_findAccountByID_not_found();
    cout << "All Bank class tests completed.\n";
    return 0;
}