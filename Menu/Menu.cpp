#include "Menu.h"
#include "../Bank/Bank.h"
#include "../Account/Account.h"
#include "../Transaction/Transaction.h"
#include <vector>
#include <iostream>
#include <conio.h>
#include <window.h>

using namespace std;

int Menu::ShowArrowMenu(const vector<string>& options, const string& title) {
    int selected = 0;
    int key;

    while (true) {
        system("cls"); // Clear the console
        cout << title << endl;
        cout << "-------------------" << endl;

        for (int i = 0; i < options.size(); ++i) {
            if (i == selected) {
                cout << "> " << options[i] << " <" << endl; // Highlight selected option
            } else {
                cout << "  " << options[i] << endl;
            }
        }

        int ch = _getch();
        if (ch == 224) { // phím đặc biệt
            ch = _getch();
            if (ch == 72) { // lên
                if (selected > 0) selected--;
            } else if (ch == 80) { // xuống
                if (selected < optCount - 1) selected++;
            }
        } else if (ch == 13) { // Enter
            return selected;
        } else if (ch == 27) { // ESC (tuỳ chọn: return -1 để thoát)
            return -1;
        }
    }
}

// Main Menu
int Menu::MainMenu() {
    vector<string> options = {
        "Dang nhap",
        "Tao tai khoan",
        "Thoat"
    };
    return ShowArrowMenu(options, "========= Menu Ngan Hang =========");
}

// Admin Menu
int Menu::AdminMenu(const string& adminName) {
    vector<string> options = {
        "Xem danh sach tai khoan",
        "Tim kiem tai khoan",
        "Khoa/Mo tai khoan",
        "Dang xuat"
    };
    return ShowArrowMenu(options, "========= Menu Admin: " + adminName + " =========");
}

// User Menu
int Menu::UserMenu(const Account& account) {
    vector<string> options = {
        "Xem thong tin tai khoan",
        "Thuc hien giao dich",
        "Xem lich su giao dich",
        "Doi ma PIN",
        "Dang xuat"
    };
    return ShowArrowMenu(options, "========= Menu Nguoi Dung: " + account.getOwnerName() + " =========");
}

// Transaction Menu
int Menu::TransactionMenu(const Account& account) {
    vector<string> options = {
        "Nap tien",
        "Rut tien",
        "Chuyen khoan",
        "Quay lai"
    };
    return ShowArrowMenu(options, "========= Menu Giao Dich: " + account.getOwnerName() + " =========");
}

// Exit the application
void Menu::Exit() {
    cout << "Cam on ban da su dung dich vu cua chung toi!" << endl;
    cout << "Hen gap lai!" << endl;
    exit(0);
}

// Login function
void Menu::Login() {
    string accountID, pin;
    cout << "Nhap ID tai khoan: ";
    cin >> accountID;
    cout << "Nhap ma PIN: ";
    cin >> pin;

    Bank bank; // Assuming you have a Bank instance
    Account* account = bank.findAccountByID(accountID);

    if (account && account->verifyPin(pin)) {
        int choice = UserMenu(*account);
        switch (choice) {
            case 0: ViewAccountInfo(*account); break;
            case 1: TransactionMenu(*account); break;
            case 2: ViewTransactionsHistory(*account); break;
            case 3: ChangePin(*account); break;
            case 4: LogoutUser(*account); break;
        }
    } else {
        cout << "Dang nhap that bai! Vui long thu lai." << endl;
    }
}

// Create Account function
void Menu::CreateAccount() {
    bank.createAccount(id, name, pin, initialBalance);
}

// User Menu Functions
void ViewAccountInfo(const Account& account) {
    cout << "Thong tin tai khoan:" << endl;
	bank.showAccountInfo(account.getID());
	system("pause");
    UserMenu(account);
}

void ChangePin(const Account& account) {
    string newPin;
    cout << "Nhap ma PIN moi: ";
    cin >> newPin;
    account.changePin(newPin);
    cout << "Ma PIN da duoc thay doi thanh cong!" << endl;
	system("pause");
    UserMenu(account);
}

void ViewTransactionsHistory(const Account& account) {
    cout << "Lich su giao dich:" << endl;
	displayTransactionHistory(account.getID());
    // Assuming displayTransactionHistory is a function that shows the transaction history
    system("pause");
    UserMenu(account);
}

void LogoutUser(const Account& account) {
    cout << "Dang xuat thanh cong! Hen gap lai!" << endl;
	// Back to main menu or exit
    system("pause");
    MainMenu();
}

// Admin Menu Functions
void ViewAllAccounts() {
    bank.showAllAccounts();
	system("pause");
    AdminMenu("Admin"); // Assuming "Admin" is the admin name
}

void SearchAccount() {
    string id;
    cout << "Nhap ID tai khoan can tim: ";
    cin >> id;
    bank.showAccountInfo(id);
	system("pause");
    AdminMenu("Admin"); // Assuming "Admin" is the admin name
}

void LockUnlockAccount() {
    string id;
    cout << "Nhap ID tai khoan can khoa/mo: ";
    cin >> id;
    Account* account = bank.findAccountByID(id);
    if (account) {
        if (account->isActive()) {
            account->lockAccount();
            cout << "Tai khoan da duoc khoa." << endl;
        } else {
            account->unlockAccount();
            cout << "Tai khoan da duoc mo." << endl;
        }
    } else {
        cout << "Khong tim thay tai khoan voi ID: " << id << endl;
    }
}

void LogoutAdmin() {
    cout << "Dang xuat thanh cong!" << endl;
    // Back to main menu or exit
    system("pause");
    MainMenu();
}

// Transaction Menu Functions
void Deposit(const Account& account) {
    double amount;
	cout << "Nhap so tien nap: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "So tien nap phai lon hon 0!" << endl;
        return;
    cout << "Nhap so tien nap: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "So tien nap phai lon hon 0!" << endl;
        return;
	else {
		// Randomly generate a transaction ID for simplicity
		string transID;
		do {
			transID	 = "trans" + to_string(rand() % 10000); // Random transaction ID
		} while (Transaction.isTransactionIDExists(transID));
        Transaction newTransaction = Transaction::deposit(transID, account.getID(), amount);
        account.addTransaction(newTransaction.getType(), newTransaction.getAmount(), newTransaction.getTimestamp(), newTransaction.getNote(), newTransaction.getFromAccountID());
        cout << "Nap tien thanh cong!" << endl;
    }

    system("pause");
	UserMenu(account);
}

void Withdraw(const Account& account) {
    double amount;
    cout << "Nhap so tien rut: ";
    cin >> amount;

    if (amount <= 0 || amount > account.getBalance()) {
        cout << "So tien rut khong hop le!" << endl;
        return;
    }

    // Randomly generate a transaction ID for simplicity
    string transID = "trans"



