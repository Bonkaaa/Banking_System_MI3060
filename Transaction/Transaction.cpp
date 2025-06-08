#include "Transaction.h"
#include "../Account/Account.h"
#include "../Bank/Bank.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>
using namespace std;

TransactionNode* transactionHead = nullptr; // Initialize the head of the linked list
Account* currentAccount = nullptr; // Pointer to the currently logged-in account
Bank bank; // Assuming you have a Bank instance

// Constructor with parameters
Transaction::Transaction(
	const string& transID,
	const string& type,
	double amount,
	const string& timeStamp,
	const string& note,
	const string& fromID,
	const string& toID
)
	: transactionID(transID), transType(type), amount(amount), timestamp(timeStamp), note(note),
	  fromAccountID(fromID), toAccountID(toID) {}

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
void Transaction::addTransaction(
	const string& transID,
	const string& type,
	double amount,
	const string& timeStamp,
	const string& note,
	const string& fromID,
	const string& toID
) {
	// Create a new transaction object and add to the account's transaction history
	Transaction newTransaction(transID, type, amount, timeStamp, note, fromID, toID);

	TransactionNode* newNode = new TransactionNode(newTransaction);
	if (transactionHead == nullptr) {
		transactionHead = newNode;
	} else {
		TransactionNode* temp = ::transactionHead;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = newNode;
	}

	// Save the transaction to a file
	ofstream fout("transactions.txt", ios::app);
	if (fout.is_open()) {
		fout << transID << "," << type << "," << amount << "," << timeStamp << "," 
			 << note << "," << fromID << "," << toID << endl;
		fout.close();
	} else {
		cout << "Error opening file to save transaction.\n";
	}
}

// Display Function
// Display transaction history for a given fromAccountID
void Transaction::displayTransactionHistory(const string& fromID) {
	TransactionNode* temp = ::transactionHead;
    cout << "Lich su giao dich cua tai khoan " << fromID << endl;
    while (temp) {
        const Transaction& t = temp->transaction;
        if (t.getFromAccountID() == fromID) {
			if (t.getType() == "transfer") {
            	cout << "ID: " << t.getTransactionID()
                 	<< ", Loai giao dich: " << t.getType()
                 	<< ", So tien: " << t.getAmount()
                 	<< ", Thoi gian: " << t.getTimestamp()
                 	<< ", Ghi chu: " << t.getNote()
                 	<< ", Toi tai khoan: " << t.getToAccountID()
                 	<< endl;
			} else {
				cout << "ID: " << t.getTransactionID()
				 	<< ", Loai giao dich: " << t.getType()
				 	<< ", So tien: " << t.getAmount()
				 	<< ", Thoi gian: " << t.getTimestamp()
				 	<< ", Ghi chu: " << t.getNote()
				 	<< endl;
			}
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
	return Transaction(transID, "withdrawal", amount, timeStamp, note, fromAccountID, "");
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
string Transaction::getCurrentTime() {
	time_t now = time(0);
	tm* localtm = localtime(&now);
	char buffer[20];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtm);
	return string(buffer);
}
// Note: The getCurrentTime function formats the current time as "YYYY-MM-DD HH:MM:SS".

// Check if a transaction ID already exists
bool Transaction::isTransactionIDExists(const string& transID) {
    TransactionNode* temp = ::transactionHead;
    while (temp) {
        if (temp->transaction.getTransactionID() == transID) {
            return true; // Transaction ID already exists
        }
        temp = temp->next;
    }
    return false; // Transaction ID does not exist
}

// Clear the list of transactions
void Transaction::clearTransactionList() {
	TransactionNode* current = ::transactionHead;
	while (current) {
		TransactionNode* toDelete = current;
		current = current->next;
		delete toDelete; // Free memory
	}
	::transactionHead = nullptr; // Reset the head pointer
}

// Load transactions from a file
void Transaction::loadTransactionsFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Gặp lỗi khi load file\n";
        return;
    }

    clearTransactionList(); // Clear current list before loading

    string line;
    while (getline(fin, line)) {
        // Split the line by commas
        stringstream ss(line);
        string transID, type, amountStr, timeStamp, note, fromID, toID;

        getline(ss, transID, ',');
        getline(ss, type, ',');
        getline(ss, amountStr, ',');
        getline(ss, timeStamp, ',');
        getline(ss, note, ',');
        getline(ss, fromID, ',');
        getline(ss, toID, '\n');

        double amount = stod(amountStr);

        Transaction newTransaction(transID, type, amount, timeStamp, note, fromID, toID);

        // Add to linked list
        TransactionNode* newNode = new TransactionNode(newTransaction);
        if (transactionHead == nullptr) {
            transactionHead = newNode;
        } else {
            TransactionNode* temp = transactionHead;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }
    fin.close();
}

// Save transactions to a file
void Transaction::saveTransactionsToFile(const string& filename) {
	ofstream fout(filename);
	if (!fout.is_open()) {
		cout << "Gặp lỗi khi lưu vào file\n";
		return;
	}

	TransactionNode* temp = ::transactionHead;
	while (temp) {
		const Transaction& t = temp->transaction;
		fout << t.getTransactionID() << "," 
			 << t.getType() << "," 
			 << t.getAmount() << "," 
			 << t.getTimestamp() << "," 
			 << t.getNote() << "," 
			 << t.getFromAccountID() << "," 
			 << t.getToAccountID() << endl;
		temp = temp->next;
	}
	fout.close();
}