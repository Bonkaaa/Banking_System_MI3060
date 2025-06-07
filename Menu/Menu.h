#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "../Account/Account.h"
#include "../Bank/Bank.h"  
using namespace std;


class Menu {
    public:
        // Show arrow menu
        static int ShowArrowMenu(const vector<string>& options, const string& title = "Menu");

        // Display the main menu and handle user input
        static int MainMenu();
        // Main menu function
        static string Login();
        static int loginAdmin();
        static void CreateAccount();
        static void Exit();

        // Display the admin menu and handle user input
        static int AdminMenu(const string& adminName);
        // Admin menu function
        static void ViewAllAccounts();
        static void SearchAccount();
        static void LockUnlockAccount();

        // Display the user menu for whose account is logged in
        static int UserMenu(const Account& account);
        // User menu function
        static void ViewAccountInfo(const Account& account);
        static void ChangePin(Account& account);
        static void ViewTransactionsHistory(const Account& account);

        // Display transaction menu
        static int TransactionMenu(const Account& account);
        // Transaction menu function
        static void Deposit(Account& account);
        static void Withdraw(Account& account);
        static void Transfer(Account& account);

        static Bank bank; // Assuming you have a Bank instance

};
#endif // MENU_H