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

// Admin Menu
int Menu::AdminMenu(const string& adminName) {
    vector<string> options = {
        "Xem danh sách tài khoản",
        "Tìm kiếm tài khoản",
        "Mở/Khoá tài khoản",
        "Đăng xuất"
    };
    return ShowArrowMenu(options, "========= Menu Admin: " + adminName + " =========");
}

// User Menu
int Menu::UserMenu(const Account& account) {
    vector<string> options = {
        "Xem thông tin tài khoản",
        "Đổi mã PIN",
        "Xem lịch sử giao dịch",
        "Thực hiện giao dịch",
        "Đăng xuất"
    };
    return ShowArrowMenu(options, "========= Menu Người Dùng: " + account.getOwnerName() + " =========");
}

// Transaction Menu
int Menu::TransactionMenu(const Account& account) {
    vector<string> options = {
        "Gửi tiền",
        "Rút tiền",
        "Chuyển khoản",
        "Quay lại"
    };
    return ShowArrowMenu(options, "========= Menu Giao Dịch: " + account.getOwnerName() + " =========");
}

// Exit the application
void Menu::Exit() {
    exit(0);
}

// Login function
string Menu::Login() {
    string accountID, pin;
    cout << "Nhập ID tài khoản (6 chữ số): ";
    while (true) {
        cin >> accountID;
        // Check if the account ID is exactly 6 digits long and consists only of digits and is not occupied
        if (accountID.length() == 6 && all_of(accountID.begin(), accountID.end(), ::isdigit)) {
            break; // Valid ID length
        } else {
            cout << "ID tài khoản không hợp lệ. Vui lòng nhập lại: ";
        }
    }
    cout << "Nhập mã PIN (4 chữ số): ";
    while (true) {
        cin >> pin;
        if (pin.length() == 4 && all_of(pin.begin(), pin.end(), ::isdigit)) {
            break; // Valid PIN length
        } else {
            cout << "Mã PIN không hợp lệ. Vui lòng nhập lại: ";
        }
    }

    Account* account = bank.findAccountByID(accountID);

    if (account && account->verifyPin(pin)) {
        return accountID; // Login successful, return account ID
    }
    else {
        cout << "ID tài khoản hoặc mã PIN không đúng. Vui lòng thử lại" << endl;
        return "0"; // Login failed, return "0"
    }
}

// Admin Login function
int Menu::loginAdmin() {
    string adminID, adminPin;
    cout << "Nhập ID quản trị viên: ";
    cin >> adminID;
    cout << "Nhập mã PIN: ";
    cin >> adminPin;

    while (adminID != "admin" || adminPin != "admin123") {
        cout << "ID quản trị viên hoặc mã PIN không đúng, Vui lòng thử lại!" << endl;
        cout << "Nhập ID quản trị viên: ";
        cin >> adminID;
        cout << "Nhập mã PIN: ";
        cin >> adminPin;
    }
    cout << "Đăng nhập thành công!" << endl;
    return 1; // Return 1 to indicate successful admin login
}


// Create Account function
void Menu::CreateAccount() {
    bank.createAccount();
}

// User Menu Functions
void Menu::ViewAccountInfo(const Account& account) {
    cout << "Thông tin tài khoản: " << endl;
	bank.showAccountInfo(account.getID());
}

void Menu::ChangePin(Account& account) {

    // Check if the account is locked
    if (!account.isActive()) {
        cout << "Tài khoản của bạn đã bị khóa. Không thể thay đổi mã PIN." << endl;
        return;
    }

    string newPin;
    // Require the user to enter the old PIN first
    string oldPin;
    cout << "Nhập mã PIN cũ: ";
    while (true) {
        cin >> oldPin;
        if (oldPin.length() == 4 && all_of(oldPin.begin(), oldPin.end(), ::isdigit) && account.verifyPin(oldPin)) {
            break; // Valid old PIN length
        } else {
            cout << "Mà PIN không hợp lệ. Vui lòng nhập lại: ";
        }
    }
    cout << "Nhập mã PIN mới (4 chữ số): ";
    while (true) {
        cin >> newPin;
        if (newPin.length() == 4 && all_of(newPin.begin(), newPin.end(), ::isdigit)) {
            break; // Valid new PIN length
        } else {
            cout << "Mã PIN mới phải là 4 chu so. Vui lòng nhập lại: ";
        }
    }
    account.changePin(newPin);
    // Save the new PIN to the file (optional, depending on your design)
    bank.saveAccountsToFile("accounts.txt"); // Save accounts to file
    cout << "Mã PIN đã được thay đổi thành công!" << endl;
}

void Menu::ViewTransactionsHistory(const Account& account) {
    // Check if the account is locked
    if (!account.isActive()) {
        cout << "Tài khoản của bạn đã bị khóa. Không thể xem lịch sử giao dịch." << endl;
        return;
    }

    cout << "Lịch sử giao dịch:" << endl;
    // Assuming Transaction class has a static method to display transaction history
    Transaction::displayTransactionHistory(account.getID());
}

// Admin Menu Functions
void Menu::ViewAllAccounts() {
    cout << "Danh sách tất cả tài khoản:" << endl;
    bank.showAllAccounts();
}

void Menu::SearchAccount() {
    string id;
    cout << "Nhập ID tài khoản cần tìm: ";
    while (true) {
        cin >> id;
        if (id.length() == 6 && all_of(id.begin(), id.end(), ::isdigit)) {
            break; // Valid ID length
        } else {
            cout << "ID tài khoản phải là 6 chữ số. Vui lòng nhập lại: ";
        }
    }
    bank.showAccountInfo(id);
}

void Menu::LockUnlockAccount() {
    string id;
    cout << "Nhập ID tài khoản cần khóa/mở: ";
    while (true) {
        cin >> id;
        if (id.length() == 6 && all_of(id.begin(), id.end(), ::isdigit)) {
            break; // Valid ID length
        } else {
            cout << "ID tài khoản phải là 6 chữ số. Vui lòng nhập lại: ";
        }
    }
    Account* account = bank.findAccountByID(id);
    if (account) {
        if (account->isActive()) {
            account->lockAccount();
            cout << "Tài khoản đã được khoá." << endl;
            // Save the updated account status to the file
            bank.saveAccountsToFile("accounts.txt"); // Save accounts to file
        } else {
            account->unlockAccount();
            cout << "Tài khoản đã được mở" << endl;
            // Save the updated account status to the file
            bank.saveAccountsToFile("accounts.txt"); // Save accounts to file
        }
    } else {
        cout << "Không tìm thấy ID tài khoản " << id << endl;
    }
}

// Transaction Menu Functions
void Menu::Deposit(Account& account) {
    double amount;
	cout << "Nhập số tiền gửi: ";

    while (true) {
        cin >> amount;
        if (amount <= 0) {
            cout << "Số tiền gửi phải lớn hơn 0. Vui lòng nhập lại: ";
        } else {
            break; // Valid amount
        }
    }
    string note;
    cout << "Nhập ghi chú (nếu có): ";
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
    Transaction::addTransaction(transID, "Gửi tiền", amount, newTransaction.getTimestamp(), note, account.getID(), "");
        
    // Save bank account to file after deposit
    bank.saveAccountsToFile("accounts.txt"); // Save accounts to file
    Transaction::saveTransactionsToFile("transactions.txt"); // Save transactions to file

    // Display success message
    cout << "ID giao dịch: " << transID << endl;
    cout << "Gửi tiền thành công vào tài khoản: " << account.getID() << "!" << endl;
    cout << "Số dư hiện tại: " << account.getBalance() << endl;
}

void Menu::Withdraw(Account& account) {
    double amount;
    cout << "Nhập số tiền rút: ";
    
    while (true) {
        cin >> amount;
        if (amount <= 0 || amount > account.getBalance()) {
            cout << "Số tiền rút phải lớn hơn 0 va không vượt quá số dư hiện tại. Vui lòng nhập lại: ";
        } else {
            break; // Valid amount
        }
    }

    string note;
    cout << "Nhập ghi chú (nếu có): ";
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
    Transaction::addTransaction(transID, "Rút tiền", amount, newTransaction.getTimestamp(), note, account.getID(), "");

    // Save bank account to file after deposit
    bank.saveAccountsToFile("accounts.txt"); // Save accounts to file
    Transaction::saveTransactionsToFile("transactions.txt"); // Save transactions to file

    // Display success message
    cout << "ID giao dịch " << transID << endl;
    cout << "Rút tiền thành công khỏi tài khoản: " << account.getID() << "!" << endl;
    cout << "Số dư hiện tại: " << account.getBalance() << endl;
}

void Menu::Transfer(Account& account) {
    string toAccountID;
    double amount;
    cout << "Nhập ID tài khoản chuyển khoản đến: ";
    while (true) {
        cin >> toAccountID;
        if (toAccountID.length() == 6 && all_of(toAccountID.begin(), toAccountID.end(), ::isdigit) && toAccountID != account.getID()
            && bank.findAccountByID(toAccountID) != nullptr) {
            break; // Valid ID length
        } else {
            cout << "ID tài khoản không hợp lệ. Vui lòng nhập lại: ";
        }
    }

    cout << "Nhập số tiền chuyển khoản: ";
    while (true) {
        cin >> amount;
        if (amount <= 0 || amount > account.getBalance()) {
            cout << "Số tiền rút phải lớn hơn 0 va không vượt quá số dư hiện tại. Vui lòng nhập lại: ";
        } else {
            break; // Valid amount
        }
    }

    string note;
    cout << "Nhập ghi chú (nếu có): ";
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
    Transaction::addTransaction(transID, "Chuyển khoản", amount, newTransaction.getTimestamp(), note, account.getID(), toAccountID);

    // Save bank account to file after deposit
    bank.saveAccountsToFile("accounts.txt"); // Save accounts to file
    Transaction::saveTransactionsToFile("transactions.txt"); // Save transactions to file

    // Display success message
    cout << "ID giao dịch " << transID << endl;
    cout << "Chuyen khoan thanh cong tu tai khoan " << account.getID() << " đến tài khoản " << toAccountID << "!" << endl;
    cout << "Số dư hiện tại " << account.getBalance() << endl;
}