#include "Transaction.h"
#include <iostream>
#include <cassert>

using namespace std;

// Helper to visually check display output
void testDisplay(const Transaction& t, const string& expectedID, const string& expectedType, double expectedAmt) {
    cout << "\n--- Display Output ---" << endl;
    t.displayTransaction();
    cout << "----------------------" << endl;
    assert(t.getTransactionID() == expectedID);
    assert(t.getType() == expectedType);
    assert(t.getAmount() == expectedAmt);
}

int main() {
    // Test 1: Constructor and getters
    Transaction t1("T001", "deposit", 100.0, "2025-06-01 07:30:00", "Initial deposit", "A123", "");
    assert(t1.getTransactionID() == "T001");
    assert(t1.getType() == "deposit");
    assert(t1.getAmount() == 100.0);
    assert(t1.getTimestamp() == "2025-06-01 07:30:00");
    assert(t1.getNote() == "Initial deposit");
    assert(t1.getFromAccountID() == "A123");
    assert(t1.getToAccountID() == "");

    // Test 2: Timestamp defaults to now if empty (just check non-empty and length)
    Transaction t2("T002", "withdraw", 40.0, "", "ATM Withdrawal", "A123", "");
    assert(!t2.getTimestamp().empty() && t2.getTimestamp().length() == 19);

    // Test 3: Factory method - deposit
    Transaction t3 = Transaction::deposit("T003", "A555", 200.0, "2025-06-01 10:00:00", "Saving");
    assert(t3.getType() == "deposit");
    assert(t3.getFromAccountID() == "A555");
    assert(t3.getAmount() == 200.0);
    assert(t3.getTimestamp() == "2025-06-01 10:00:00");
    assert(t3.getNote() == "Saving");

    // Test 4: Factory method - withdraw
    Transaction t4 = Transaction::withdraw("T004", "A444", 50.0, "", "Groceries");
    assert(t4.getType() == "withdraw");
    assert(t4.getFromAccountID() == "A444");
    assert(t4.getNote() == "Groceries");

    // Test 5: Factory method - transfer
    Transaction t5 = Transaction::transfer("T005", "A100", "A200", 500.0, "2025-06-01 12:00:00", "Rent Payment");
    assert(t5.getType() == "transfer");
    assert(t5.getFromAccountID() == "A100");
    assert(t5.getToAccountID() == "A200");
    assert(t5.getAmount() == 500.0);
    assert(t5.getNote() == "Rent Payment");

    // Test 6: displayTransaction (manual check for console output)
    testDisplay(t1, "T001", "deposit", 100.0);
    testDisplay(t3, "T003", "deposit", 200.0);
    testDisplay(t4, "T004", "withdraw", 50.0);
    testDisplay(t5, "T005", "transfer", 500.0);

    // Test 7: Display omits empty fields
    Transaction t6("T006", "withdraw", 20.0, "2025-06-01 13:00:00", "", "A333", "");
    cout << "\nCheck that 'Note:' and 'To Account ID:' are NOT displayed below:" << endl;
    t6.displayTransaction();

    cout << "\nAll manual Transaction tests passed!" << endl;
    return 0;
}