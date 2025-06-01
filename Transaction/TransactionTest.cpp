#include "Transaction.h"
#include <iostream>
#include <cassert>
using namespace std;

void testTransactionConstructor() {
    Transaction t("T001", "deposit", 1000.0, "2025-06-01 10:00:00", "Initial deposit", "A001", "");
    assert(t.getTransactionID() == "T001");
    assert(t.getType() == "deposit");
    assert(t.getAmount() == 1000.0);
    assert(t.getTimestamp() == "2025-06-01 10:00:00");
    assert(t.getNote() == "Initial deposit");
    assert(t.getFromAccountID() == "A001");
    assert(t.getToAccountID() == "");
    cout << "testTransactionConstructor passed.\n";
}

void testDepositStaticFunction() {
    Transaction t = Transaction::deposit("T002", "A002", 500.0, "2025-06-01 11:00:00", "Deposit note");
    assert(t.getTransactionID() == "T002");
    assert(t.getType() == "deposit");
    assert(t.getAmount() == 500.0);
    assert(t.getTimestamp() == "2025-06-01 11:00:00");
    assert(t.getNote() == "Deposit note");
    assert(t.getFromAccountID() == "A002");
    assert(t.getToAccountID() == "");
    cout << "testDepositStaticFunction passed.\n";
}

void testWithdrawStaticFunction() {
    Transaction t = Transaction::withdraw("T003", "A003", 200.0, "2025-06-01 12:00:00", "Withdraw note");
    assert(t.getTransactionID() == "T003");
    assert(t.getType() == "withdraw");
    assert(t.getAmount() == 200.0);
    assert(t.getTimestamp() == "2025-06-01 12:00:00");
    assert(t.getNote() == "Withdraw note");
    assert(t.getFromAccountID() == "A003");
    assert(t.getToAccountID() == "");
    cout << "testWithdrawStaticFunction passed.\n";
}

void testTransferStaticFunction() {
    Transaction t = Transaction::transfer("T004", "A004", "A005", 300.0, "2025-06-01 13:00:00", "Transfer note");
    assert(t.getTransactionID() == "T004");
    assert(t.getType() == "transfer");
    assert(t.getAmount() == 300.0);
    assert(t.getTimestamp() == "2025-06-01 13:00:00");
    assert(t.getNote() == "Transfer note");
    assert(t.getFromAccountID() == "A004");
    assert(t.getToAccountID() == "A005");
    cout << "testTransferStaticFunction passed.\n";
}

void testDisplayTransaction() {
    Transaction t("T005", "deposit", 1500.0, "2025-06-01 14:00:00", "Display test", "A006", "");
    cout << "Output of displayTransaction (visual check):\n";
    t.displayTransaction();
    cout << "testDisplayTransaction completed (visual check).\n";
}

int main() {
    testTransactionConstructor();
    testDepositStaticFunction();
    testWithdrawStaticFunction();
    testTransferStaticFunction();
    testDisplayTransaction();
    cout << "All Transaction tests passed.\n";
    return 0;
}