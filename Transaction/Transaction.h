#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
using namespace std;

class Transaction;

struct TransactionNode {
    Transaction transaction;
    TransactionNode* next;
    TransactionNode(const Transaction& trans) : transaction(trans), next(nullptr) {}
};

class Transaction {
    private:
        string transactionID;
        string transType; // "deposit" or "withdrawal"
        double amount;

        // Time
        string timestamp; // Format: YYYY-MM-DD HH:MM:SS
        string note;

        // Helper function to get the current time in the required format
        string getCurrentTime() const;

        string fromAccountID; // For transfer transactions
        string toAccountID; // For transfer transactions

        TransactionNode* transactionHead; // Pointer to the head of the linked list

    public:
        // Constructor
        Transaction(
            const string& transID,
            const string& type,
            double amt,
            const string& timeStamp = "",
            const string& note = "",
            const string& fromID = "",
            const string& toID = ""
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
        void displayTransaction() const;

        // Add a transaction to the account's transaction history
        void addTransaction(
            const string& type,
            double amount,
            const string& timeStamp = "",
            const string& note = "",
            const string& fromID = "",
            const string& toID = ""
        );

		bool isTransactionIDExists(const string& transID) const;


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

};

#endif // TRANSACTION_H