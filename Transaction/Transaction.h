#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
using namespace std;

class Transaction {
    private:
        string transactionID;
        string transType; // "deposit" or "withdrawal"
        double amount;

        // Time
        string timestamp; // Format: YYYY-MM-DD HH:MM:SS
        string note;

        string fromAccountID; // For transfer transactions
        string toAccountID; // For transfer transactions


    public:
        // Constructor
        Transaction(
            const string& transID,
            const string& type,
            double amt,
            const string& timeStamp,
            const string& note,
            const string& fromID,
            const string& toID
        );

        // Getters
        string getTransactionID() const;
        string getType() const;
        string getTimestamp() const;
        double getAmount() const;
        string getNote() const;
        string getFromAccountID() const;
        string getToAccountID() const;

        // Display Function
        static void displayTransactionHistory(const string& fromID);

        // Add a transaction to the account's transaction history
        static void addTransaction(
            const string& transID,
            const string& type,
            double amount,
            const string& timeStamp = "",
            const string& note = "",
            const string& fromID = "",
            const string& toID = ""
        );

        // Clear the list of transactions
        static void clearTransactionList();

        // Check if a transaction ID exists
		static bool isTransactionIDExists(const string& transID);

        // Load transactions from a file (not implemented here, but can be added later)
        static void loadTransactionsFromFile(const string& filename);

        // Save transactions to a file
        static void saveTransactionsToFile(const string& filename);

        // Transaction Functions
        static Transaction deposit(
            const string& transID,
            const string& fromAccountID,
            double amount,
            const string& timeStamp = "",
            const string& note = ""
        );
        static Transaction withdraw(
            const string& transID,
            const string& fromAccountID,
            double amount,
            const string& timeStamp = "",
            const string& note = ""
        );
        static Transaction transfer(
            const string& transID,
            const string& fromAccountID,
            const string& toAccountID,
            double amount,
            const string& timeStamp = "",
            const string& note = ""
        );

        // Get current time in the format YYYY-MM-DD HH:MM:SS
        static string getCurrentTime();
};

struct TransactionNode {
    Transaction transaction;
    TransactionNode* next;
    TransactionNode(const Transaction& trans) : transaction(trans), next(nullptr) {}
};

extern TransactionNode* transactionHead; // Global variable to hold the head of the transaction linked list


#endif // TRANSACTION_H