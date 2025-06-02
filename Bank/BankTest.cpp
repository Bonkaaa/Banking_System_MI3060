#include "Bank.h"
#include <iostream>
#include <cassert>
#include <sstream>
using namespace std;

// Test creating an account and showing all accounts
void test_create_and_show_account() {
    Bank bank;
    // Simulate user input for createAccount()
    // We'll use stringstream to simulate cin
    std::streambuf* orig_cin = std::cin.rdbuf();
    std::istringstream input("acc101\nJohn Doe\n1234\n1000\n");
    std::cin.rdbuf(input.rdbuf());

    bank.createAccount();

    std::cin.rdbuf(orig_cin); // Restore cin

    // Show all accounts (should print the account we just created)
    bank.showAllAccounts();
}

// Test finding an account by ID
void test_find_account_by_id() {
    Bank bank;
    std::streambuf* orig_cin = std::cin.rdbuf();
    std::istringstream input("acc102\nJane Smith\n5678\n2000\n");
    std::cin.rdbuf(input.rdbuf());

    bank.createAccount();

    std::cin.rdbuf(orig_cin);

    // Should print account info for acc102
    bank.findAccountByID("acc102");
    // Should print not found for a non-existent account
    bank.findAccountByID("notfound");
}

// Test showing account info
void test_show_account_info() {
    Bank bank;
    std::streambuf* orig_cin = std::cin.rdbuf();
    std::istringstream input("acc103\nAlice\n9999\n3000\n");
    std::cin.rdbuf(input.rdbuf());

    bank.createAccount();

    std::cin.rdbuf(orig_cin);

    // Should print detailed info for acc103
    bank.showAccountInfo("acc103");
}

int main() {
    cout << "Running Bank class tests...\n";
    test_create_and_show_account();
    test_find_account_by_id();
    test_show_account_info();
    cout << "All Bank tests completed.\n";
    return 0;
}