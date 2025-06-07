#include "Account/Account.h"
#include "Bank/Bank.h"
#include "Transaction/Transaction.h"
#include "Menu/Menu.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Initialize the bank
    Menu menu;

    // Load accounts from file (if needed)
    Menu::bank.loadAccountsFromFile("accounts.txt");
    // Load transactions from file (if needed)
    Transaction::loadTransactionsFromFile("transactions.txt");

    int userLoginStatus = 0; // 0: Not logged in, 1: User logged in, 2: Admin logged in
    int adminStatus = 0; // 0: Not logged in, 1: Admin logged in

    vector<string> mainMenuOptions = {
        "Dang nhap",
        "Dang nhap admin",
        "Tao tai khoan",
        "Thoat"
    };

    while (true) {
        // Main menu loop
        string accountID;
        Account* account = nullptr;
        int choice = Menu::ShowArrowMenu(mainMenuOptions, "Main Menu");
        switch (choice) {
            case 0: // Dang nhap
                accountID = menu.Login();
                account = Menu::bank.findAccountByID(accountID);
                if (account) {
                    // User logged in, show user menu
                    userLoginStatus = 1; // User logged in
                    int userMenuChoice = menu.UserMenu(*account);
                    switch (userMenuChoice) {
                        case 0: // View account info
                            menu.ViewAccountInfo(*account);
                            break;
                        case 1: // Change PIN
                            menu.ChangePin(*account);
                            break;
                        case 2: // View transaction history
                            menu.ViewTransactionsHistory(*account);
                            break;
                        case 3: // Transaction menu
                        {
                            int transactionChoice = Menu::TransactionMenu(*account);
                            switch (transactionChoice) {
                                case 0: // Deposit
                                    menu.Deposit(*account);
                                    break;
                                case 1: // Withdraw
                                    menu.Withdraw(*account);
                                    break;
                                case 2: // Transfer
                                    menu.Transfer(*account);
                                    break;
                                default:
                                    cout << "Lua chon khong hop le." << endl;
                            }
                            break;
                        }
                        default:
                            cout << "Lua chon khong hop le." << endl;
                    }
                } else {
                    cout << "Tai khoan khong ton tai hoac mat mat khau!" << endl;
                }
                break;
            case 1: // Dang nhap admin
                adminStatus = menu.loginAdmin();
                if (adminStatus == 1) {
                    userLoginStatus = 2; // Admin logged in
                    int adminMenuChoice = menu.AdminMenu("Admin");
                    switch (adminMenuChoice) {
                        case 0: // View all accounts
                            menu.ViewAllAccounts();
                            break;
                        case 1: // Search account
                            menu.SearchAccount();
                            break;
                        case 2: // Lock/Unlock account
                            menu.LockUnlockAccount();
                            break;
                        default:
                            cout << "Lua chon khong hop le." << endl;
                    }
                } else {
                    cout << "Dang nhap that bai! Ban khong phai la admin!" << endl;
                }
                break;
            case 2: // Tao tai khoan
                Menu::bank.createAccount();
                break;
            case 3: // Thoat
                cout << "Cam on ban da su dung chuong trinh!" << endl;
                Transaction::clearTransactionList(); // Clear transactions before exiting
                return 0;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    }
}