#include "Transaction.h"
#include <cassert>
#include <iostream>
using namespace std;

void test_transaction_constructor_and_getters() {
    Transaction t("T001", "deposit", 1000.0, "2025-06-01 10:00:00", "Initial deposit", "A001", "");
    assert(t.getTransactionID() == "T001");
    assert(t.getType() == "deposit");
    assert(t.getAmount() == 1000.0);
    assert(t.getTimestamp() == "2025-06-01 10:00:00");
    assert(t.getNote() == "Initial deposit");
    assert(t.getFromAccountID() == "A001");
    assert(t.getToAccountID() == "");
    cout << "test_transaction_constructor_and_getters passed.\n";
}

void test_addTransaction_and_isTransactionIDExists() {
    // Add a transaction
    Transaction::addTransaction("T002", "withdraw", 500.0, "2025-06-01 11:00:00", "ATM withdraw", "A002", "");
    assert(Transaction::isTransactionIDExists("T002"));
    assert(!Transaction::isTransactionIDExists("T999"));
    cout << "test_addTransaction_and_isTransactionIDExists passed.\n";
}

void test_deposit_withdraw_transfer_static() {
    Transaction d = Transaction::deposit("T003", "A003", 200.0, "2025-06-01 12:00:00", "Deposit note");
    assert(d.getType() == "deposit");
    assert(d.getAmount() == 200.0);
    assert(d.getFromAccountID() == "A003");
    assert(d.getToAccountID() == "");

    Transaction w = Transaction::withdraw("T004", "A004", 150.0, "2025-06-01 13:00:00", "Withdraw note");
    assert(w.getType() == "withdraw");
    assert(w.getAmount() == 150.0);
    assert(w.getFromAccountID() == "A004");
    assert(w.getToAccountID() == "");

    Transaction t = Transaction::transfer("T005", "A005", "A006", 300.0, "2025-06-01 14:00:00", "Transfer note");
    assert(t.getType() == "transfer");
    assert(t.getAmount() == 300.0);
    assert(t.getFromAccountID() == "A005");
    assert(t.getToAccountID() == "A006");

    cout << "test_deposit_withdraw_transfer_static passed.\n";
}

void test_displayTransactionHistory() {
    // Add transactions for account A007
    Transaction::addTransaction("T006", "deposit", 100.0, "2025-06-01 15:00:00", "Deposit for A007", "A007", "");
    Transaction::addTransaction("T007", "withdraw", 50.0, "2025-06-01 16:00:00", "Withdraw for A007", "A007", "");
    cout << "Output of displayTransactionHistory for A007 (visual check):\n";
    Transaction::displayTransactionHistory("A007");
    cout << "test_displayTransactionHistory completed (visual check).\n";
}

int main() {
    test_transaction_constructor_and_getters();
    test_addTransaction_and_isTransactionIDExists();
    test_deposit_withdraw_transfer_static();
    test_displayTransactionHistory();
    cout << "All Transaction class tests passed.\n";
    return 0;
}