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
        void Login();
        void CreateAccount();
        void Exit();

        // Display the admin menu and handle user input
        static int AdminMenu(const string& adminName);
        // Admin menu function
        void ViewAllAccounts();
        void SearchAccount();
        void LockUnlockAccount();
        void LogoutAdmin();

        // Display the user menu for whose account is logged in
        static int UserMenu(const Account& account);
        // User menu function
        void ViewAccountInfo(const Account& account);
        void ChangePin(const Account& account);
        void ViewTransactionsHistory(const Account& account);
        void LogoutUser(const Account& account);

        // Display transaction menu
        static int TransactionMenu(const Account& account);
        // Transaction menu function
        void Deposit(const Account& account);
        void Withdraw(const Account& account);
        void Transfer(const Account& account);
        void BackToUserMenu(const Account& account);

        // Exit the application
        static void Exit();
};
#endif // MENU_H