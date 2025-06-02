#include "Transaction.h"
#include <iostream>
using namespace std;

Transaction::Transaction(
	const string& transID,
	const string& type,
	double amt,
	const string& timeStamp,
	const string& note,
	const string& fromID,
	const string& toID
) : transactionID(transID), transType(type), amount(amt), note(note), fromAccountID(fromID), toAccountID(toID) {
	if (timeStamp.empty()) {
		timestamp = getCurrentTime();
	} else {
		timestamp = timeStamp;
	}
};

// Getters
string Transaction::getTransactionID() const {
	return transactionID;
}
string Transaction::getType() const {
	return transType;
}
string Transaction::getTimestamp() const {
	return timestamp;
}
double Transaction::getAmount() const {
	return amount;
}
string Transaction::getNote() const {
	return note;
}
string Transaction::getFromAccountID() const {
	return fromAccountID;
}
string Transaction::getToAccountID() const {
	return toAccountID;
}

// Add transaction to the account's transaction history
void addTransaction(
	const string& type,
	double amount,
	const string& timeStamp,
	const string& note,
	const string& fromID,
	const string& toID
) {
	// Create a new transaction object and add to the account's transaction history
	Transaction newTransaction(transactionID, type, amount, timeStamp, note, fromID, toID);

	TransactionNode* newNode = new TransactionNode(newTransaction);
	if (transactionHead == nullptr) {
        transactionHead = newNode;
    } else {
        TransactionNode* temp = transactionHead;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Display Function
// Display transaction history for a given fromAccountID
void displayTransactionHistory(const string& fromID) {
    TransactionNode* temp = transactionHead;
    cout << "Transaction History for Account: " << fromID << endl;
    while (temp) {
        const Transaction& t = temp->transaction;
        if (t.getFromAccountID() == fromID) {
            cout << "ID: " << t.getTransactionID()
                 << ", Type: " << t.getType()
                 << ", Amount: " << t.getAmount()
                 << ", Timestamp: " << t.getTimestamp()
                 << ", Note: " << t.getNote()
                 << ", To: " << t.getToAccountID()
                 << endl;
        }
        temp = temp->next;
    }
}

// Transaction Functions
Transaction Transaction::deposit(
	const string& transID,
	const string& fromAccountID,
	double amount,
	const string& timeStamp,
	const string& note
) {
	return Transaction(transID, "deposit", amount, timeStamp, note, fromAccountID, "");
}

Transaction Transaction::withdraw(
	const string& transID,
	const string& fromAccountID,
	double amount,
	const string& timeStamp,
	const string& note
) {
	return Transaction(transID, "withdraw", amount, timeStamp, note, fromAccountID, "");
}

Transaction Transaction::transfer(
	const string& transID,
	const string& fromAccountID,
	const string& toAccountID,
	double amount,
	const string& timeStamp,
	const string& note
) {
	return Transaction(transID, "transfer", amount, timeStamp, note, fromAccountID, toAccountID);
}

// Helper function to get the current time in the required format
string Transaction::getCurrentTime() const {
	time_t now = time(0);
	tm* localtm = localtime(&now);
	char buffer[20];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtm);
	return string(buffer);
}
// Note: The getCurrentTime function formats the current time as "YYYY-MM-DD HH:MM:SS".

// Check if a transaction ID already exists
bool Transaction::isTransactionIDExists(const string& transID) const {
    TransactionNode* temp = transactionHead;
    while (temp) {
        if (temp->transaction.getTransactionID() == transID) {
            return true; // Transaction ID already exists
        }
        temp = temp->next;
    }
    return false; // Transaction ID does not exist
}