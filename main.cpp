#include "Account/Account.h"
#include "Bank/Bank.h"
#include "Transaction/Transaction.h"
#include "Menu/Menu.h"
#include <iostream>
#include <vector>
#include <conio.h> // For _getch()
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
                    bool stayInUserMenu = true;
                    // User logged in, show user menu
                    userLoginStatus = 1; // User logged in
                    while (stayInUserMenu) {
                        int userMenuChoice = menu.UserMenu(*account);
                        switch (userMenuChoice) {
                            case 0: // View account info
                                menu.ViewAccountInfo(*account);
                                cout << "Nhan phim bat ky de tiep tuc..." << endl;
                                getch();
                                break;
                            case 1: // Change PIN
                                menu.ChangePin(*account);
                                cout << "Nhan phim bat ky de tiep tuc..." << endl;
                                getch();
                                break;
                            case 2: // View transaction history
                                menu.ViewTransactionsHistory(*account);
                                cout << "Nhan phim bat ky de tiep tuc..." << endl;
                                getch();
                                break;
                            case 3: // Transaction menu
                            {
                                int transactionChoice = Menu::TransactionMenu(*account);
                                switch (transactionChoice) {
                                    case 0: // Deposit
                                        menu.Deposit(*account);
                                        cout << "Nhan phim bat ky de tiep tuc..." << endl;
                                        getch();
                                        break;
                                    case 1: // Withdraw
                                        menu.Withdraw(*account);
                                        cout << "Nhan phim bat ky de tiep tuc..." << endl;
                                        getch();
                                        break;
                                    case 2: // Transfer
                                        menu.Transfer(*account);
                                        cout << "Nhan phim bat ky de tiep tuc..." << endl;
                                        getch();
                                        break;
                                    default:
                                        cout << "Lua chon khong hop le." << endl;
                                        break;
                                }
                            }
                            case 4: // Logout
                                stayInUserMenu = false;
                                userLoginStatus = 0; // Reset user login status
                                account = nullptr; // Clear account pointer
                                cout << "Da dang xuat khoi tai khoan." << endl;
                                cout << "Nhan phim bat ky de ve menu chinh..." << endl;
                                getch();
                                break;
                        }
                    }
                } else {
                    cout << "Dang nhap that bai. Vui long thu lai." << endl;
                    userLoginStatus = 0; // Reset user login status
                    cout << "Nhan phim bat ky de ve menu chinh..." << endl;
                    getch();
                }
                break;
            case 1: // Dang nhap admin
                adminStatus = menu.loginAdmin();
                if (adminStatus == 1) {
                    bool stayInAdminMenu = true;
                    // Admin logged in, show admin menu
                    while (stayInAdminMenu) {
                        int adminMenuChoice = menu.AdminMenu("Admin");
                        switch (adminMenuChoice) {
                            case 0: // View all accounts
                                menu.ViewAllAccounts();
                                cout << "Nhan phim bat ky de tiep tuc..." << endl;
                                getch();
                                break;
                            case 1: // Search account
                                menu.SearchAccount();
                                cout << "Nhan phim bat ky de tiep tuc..." << endl;
                                getch();
                                break;
                            case 2: // Lock/Unlock account
                                menu.LockUnlockAccount();
                                cout << "Nhan phim bat ky de tiep tuc..." << endl;
                                getch();
                                break;
                            case 3: // Logout
                                stayInAdminMenu = false;
                                adminStatus = 0; // Reset admin login status
                                cout << "Da dang xuat khoi tai khoan admin." << endl;
                                cout << "Nhan phim bat ky de ve menu chinh..." << endl;
                                getch();
                                break;
                        }
                    }
                } else {
                    cout << "Dang nhap admin that bai. Vui long thu lai." << endl;
                    adminStatus = 0; // Reset admin login status
                    cout << "Nhan phim bat ky de ve menu chinh..." << endl;
                    getch();
                }
                break;
            case 2: // Tao tai khoan
                menu.CreateAccount();
                cout << "Nhan phim bat ky de ve menu chinh..." << endl;
                getch();
                break;
            case 3: // Thoat
                Transaction::saveTransactionsToFile("transactions.txt"); // Save transactions to file
                Menu::bank.saveAccountsToFile("accounts.txt"); // Save accounts to file
                Transaction::clearTransactionList(); // Clear transaction list
                Menu::Exit();
            default:
                cout << "Lua chon khong hop le. Vui long thu lai." << endl;
                break;      
        }
    }
}