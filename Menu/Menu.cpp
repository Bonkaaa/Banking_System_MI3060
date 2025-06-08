#include "Menu.h"
#include "../Bank/Bank.h"
#include "../Account/Account.h"
#include "../Transaction/Transaction.h"
#include <vector>
#include <iostream>
#include <conio.h> // For menu navigation
#include <algorithm>

using namespace std;

Bank Menu::bank; // Initialize the static Bank instance

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
        cout << "-------------------" << endl;
        int ch = _getch();
        if (ch == 224) { // phím đặc biệt
            ch = _getch();
            if (ch == 72) { // lên
                if (selected > 0) selected--;
            } else if (ch == 80) { // xuống
                if (selected < options.size() - 1) selected++;
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
        "Doi ma PIN",
        "Xem lich su giao dich",
        "Thuc hien giao dich",
        "Dang xuat"
    };
    return ShowArrowMenu(options, "========= Menu Nguoi Dung: " + account.getOwnerName() + " =========");
}

// Transaction Menu
int Menu::TransactionMenu(const Account& account) {
    vector<string> options = {
        "Gui tien",
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
string Menu::Login() {
    string accountID, pin;
    cout << "Nhap ID tai khoan: ";
    while (true) {
        cin >> accountID;
        if (accountID.length() == 6 && all_of(accountID.begin(), accountID.end(), ::isdigit)) {
            break; // Valid ID length
        } else {
            cout << "ID tai khoan phai la 6 chu so. Vui long nhap lai: ";
        }
    }
    cout << "Nhap ma PIN: ";
    while (true) {
        cin >> pin;
        if (pin.length() == 4 && all_of(pin.begin(), pin.end(), ::isdigit)) {
            break; // Valid PIN length
        } else {
            cout << "Ma PIN phai la 4 chu so. Vui long nhap lai: ";
        }
    }

    Account* account = bank.findAccountByID(accountID);

    if (account && account->verifyPin(pin)) {
        return accountID; // Login successful, return account ID
    }
    else {
        cout << "ID tai khoan hoac ma PIN khong dung. Vui long thu lai." << endl;
        return "0"; // Login failed, return "0"
    }
}

// Admin Login function
int Menu::loginAdmin() {
    string adminID, adminPin;
    cout << "Nhap ID quan tri vien: ";
    cin >> adminID;
    cout << "Nhap ma PIN: ";
    cin >> adminPin;

    while (adminID != "admin" || adminPin != "admin123") {
        cout << "ID quan tri vien hoac ma PIN khong dung. Vui long thu lai." << endl;
        cout << "Nhap ID quan tri vien: ";
        cin >> adminID;
        cout << "Nhap ma PIN: ";
        cin >> adminPin;
    }
    cout << "Dang nhap thanh cong!" << endl;
    return 1; // Return 1 to indicate successful admin login
}


// Create Account function
void Menu::CreateAccount() {
    bank.createAccount();
    cout << "Tai khoan da duoc tao thanh cong!" << endl;
}

// User Menu Functions
void Menu::ViewAccountInfo(const Account& account) {
    cout << "Thong tin tai khoan:" << endl;
	bank.showAccountInfo(account.getID());
}

void Menu::ChangePin(Account& account) {

    // Check if the account is locked
    if (!account.isActive()) {
        cout << "Tai khoan cua ban da bi khoa. Khong the thay doi ma PIN." << endl;
        return;
    }

    string newPin;
    // Require the user to enter the old PIN first
    string oldPin;
    cout << "Nhap ma PIN cu: ";
    while (true) {
        cin >> oldPin;
        if (oldPin.length() == 4 && all_of(oldPin.begin(), oldPin.end(), ::isdigit) && account.verifyPin(oldPin)) {
            break; // Valid old PIN length
        } else {
            cout << "Ma PIN khong hop le. Vui long nhap lai: ";
        }
    }
    cout << "Nhap ma PIN moi: ";
    while (true) {
        cin >> newPin;
        if (newPin.length() == 4 && all_of(newPin.begin(), newPin.end(), ::isdigit)) {
            break; // Valid new PIN length
        } else {
            cout << "Ma PIN moi phai la 4 chu so. Vui long nhap lai: ";
        }
    }
    account.changePin(newPin);
    // Save the new PIN to the file (optional, depending on your design)
    bank.saveAccountsToFile("accounts.txt"); // Save accounts to file
    cout << "Ma PIN da duoc thay doi thanh cong!" << endl;
}

void Menu::ViewTransactionsHistory(const Account& account) {
    // Check if the account is locked
    if (!account.isActive()) {
        cout << "Tai khoan cua ban da bi khoa. Khong the xem lich su giao dich." << endl;
        return;
    }

    cout << "Lich su giao dich:" << endl;
    // Assuming Transaction class has a static method to display transaction history
    Transaction::displayTransactionHistory(account.getID());
}

// Admin Menu Functions
void Menu::ViewAllAccounts() {
    cout << "Danh sach tat ca tai khoan:" << endl;
    bank.showAllAccounts();
}

void Menu::SearchAccount() {
    string id;
    cout << "Nhap ID tai khoan can tim: ";
    while (true) {
        cin >> id;
        if (id.length() == 6 && all_of(id.begin(), id.end(), ::isdigit)) {
            break; // Valid ID length
        } else {
            cout << "ID tai khoan phai la 6 chu so. Vui long nhap lai: ";
        }
    }
    bank.showAccountInfo(id);
}

void Menu::LockUnlockAccount() {
    string id;
    cout << "Nhap ID tai khoan can khoa/mo: ";
    while (true) {
        cin >> id;
        if (id.length() == 6 && all_of(id.begin(), id.end(), ::isdigit)) {
            break; // Valid ID length
        } else {
            cout << "ID tai khoan phai la 6 chu so. Vui long nhap lai: ";
        }
    }
    Account* account = bank.findAccountByID(id);
    if (account) {
        if (account->isActive()) {
            account->lockAccount();
            cout << "Tai khoan da duoc khoa." << endl;
            // Save the updated account status to the file
            bank.saveAccountsToFile("accounts.txt"); // Save accounts to file
        } else {
            account->unlockAccount();
            cout << "Tai khoan da duoc mo." << endl;
            // Save the updated account status to the file
            bank.saveAccountsToFile("accounts.txt"); // Save accounts to file
        }
    } else {
        cout << "Khong tim thay tai khoan voi ID: " << id << endl;
    }
}

// Transaction Menu Functions
void Menu::Deposit(Account& account) {
    double amount;
	cout << "Nhap so tien gui: ";

    while (true) {
        cin >> amount;
        if (amount <= 0) {
            cout << "So tien gui phai lon hon 0. Vui long nhap lai: ";
        } else {
            break; // Valid amount
        }
    }
    string note;
    cout << "Nhap ghi chu (neu co): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, note);
	// Randomly generate a transaction ID for simplicity
	string transID;
	do {
		transID	 = "trans" + to_string(rand() % 100000); // Random transaction ID
	} while (Transaction::isTransactionIDExists(transID));

    // Get current timestamp
    string timestamp = Transaction::getCurrentTime();

    // Update account balance
    account.setBalance(account.getBalance() + amount);


    Transaction newTransaction = Transaction::deposit(transID, account.getID(), amount, timestamp, note);
    Transaction::addTransaction(transID, "Gui tien", amount, newTransaction.getTimestamp(), note, account.getID(), "");
        
    // Save bank account to file after deposit
    bank.saveAccountsToFile("accounts.txt"); // Save accounts to file
    Transaction::saveTransactionsToFile("transactions.txt"); // Save transactions to file

    // Display success message
    cout << "ID giao dich: " << transID << endl;
    cout << "Gui tien thanh cong vao tai khoan: " << account.getID() << "!" << endl;
    cout << "So du hien tai: " << account.getBalance() << endl;
}

void Menu::Withdraw(Account& account) {
    double amount;
    cout << "Nhap so tien rut: ";
    
    while (true) {
        cin >> amount;
        if (amount <= 0 || amount > account.getBalance()) {
            cout << "So tien rut phai lon hon 0 va khong vuot qua so du hien tai. Vui long nhap lai: ";
        } else {
            break; // Valid amount
        }
    }

    string note;
    cout << "Nhap ghi chu (neu co): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, note);
    // Randomly generate a transaction ID for simplicity
    string transID;
    do {
        transID = "trans" + to_string(rand() % 100000); // Random transaction ID
    } while (Transaction::isTransactionIDExists(transID));
    string timestamp = Transaction::getCurrentTime();

    // Update account balance
    account.setBalance(account.getBalance() - amount);

    Transaction newTransaction = Transaction::withdraw(transID, account.getID(), amount, timestamp, note);
    Transaction::addTransaction(transID, "Rut tien", amount, newTransaction.getTimestamp(), note, account.getID(), "");

    // Save bank account to file after deposit
    bank.saveAccountsToFile("accounts.txt"); // Save accounts to file
    Transaction::saveTransactionsToFile("transactions.txt"); // Save transactions to file

    // Display success message
    cout << "ID giao dich: " << transID << endl;
    cout << "Rut tien thanh cong tu tai khoan: " << account.getID() << "!" << endl;
    cout << "So du hien tai: " << account.getBalance() << endl;
}

void Menu::Transfer(Account& account) {
    string toAccountID;
    double amount;
    cout << "Nhap ID tai khoan chuyen khoan den: ";
    while (true) {
        cin >> toAccountID;
        if (toAccountID.length() == 6 && all_of(toAccountID.begin(), toAccountID.end(), ::isdigit) && toAccountID != account.getID()
            && bank.findAccountByID(toAccountID) != nullptr) {
            break; // Valid ID length
        } else {
            cout << "ID tai khoan khong hop le. Vui long nhap lai: ";
        }
    }

    cout << "Nhap so tien chuyen: ";
    while (true) {
        cin >> amount;
        if (amount <= 0 || amount > account.getBalance()) {
            cout << "So tien chuyen phai lon hon 0 va khong vuot qua so du hien tai. Vui long nhap lai: ";
        } else {
            break; // Valid amount
        }
    }

    string note;
    cout << "Nhap ghi chu (neu co): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, note);

    // Randomly generate a transaction ID for simplicity
    string transID;
    do {
        transID = "trans" + to_string(rand() % 100000); // Random transaction ID
    } while (Transaction::isTransactionIDExists(transID));
    string timestamp = Transaction::getCurrentTime();

    // Update account balances
    account.setBalance(account.getBalance() - amount);
    Account* toAccount = bank.findAccountByID(toAccountID);
    if (toAccount) {
        toAccount->setBalance(toAccount->getBalance() + amount);
    }

    Transaction newTransaction = Transaction::transfer(transID, account.getID(), toAccountID, amount, timestamp, note);
    Transaction::addTransaction(transID, "Chuyen khoan", amount, newTransaction.getTimestamp(), note, account.getID(), toAccountID);

    // Save bank account to file after deposit
    bank.saveAccountsToFile("accounts.txt"); // Save accounts to file
    Transaction::saveTransactionsToFile("transactions.txt"); // Save transactions to file

    // Display success message
    cout << "ID giao dich: " << transID << endl;
    cout << "Chuyen khoan thanh cong tu tai khoan " << account.getID() << " den tai khoan " << toAccountID << "!" << endl;
    cout << "So du hien tai: " << account.getBalance() << endl;
}



    



