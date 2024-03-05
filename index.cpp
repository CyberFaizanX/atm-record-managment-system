#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>
using namespace std;

const string USER_DATA_FILE = "user_data.txt";

struct Account {
    string username;
    string password;
    double balance;
};

void displayMenu(Account& currentAccount);

void createAccount() {
    cout << "Create a new account" << endl;
    string username, password;
    double balance;

    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    cout << "Enter your initial balance: ";
    cin >> balance;

    ofstream file(USER_DATA_FILE.c_str(), ios::app);
    if (file.is_open()) {
        file << username << " " << password << " " << balance << endl;
        cout << "Account created successfully!" << endl;
        file.close();
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

void login(Account& account) {
    cout << "Login to your account" << endl;
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    ifstream file(USER_DATA_FILE.c_str());
    if (file.is_open()) {
        string storedUsername, storedPassword;
        double balance;
        bool found = false;

        while (file >> storedUsername >> storedPassword >> balance) {
            if (storedUsername == username && storedPassword == password) {
                cout << "Login successful!" << endl;
                account.username = username;
                account.password = password;
                account.balance = balance;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Invalid username or password. Please try again." << endl;
        }

        file.close();
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

void deposit(Account& account) {
    double depositAmount;
    cout << "Enter the deposit amount: $";
    while (!(cin >> depositAmount) || depositAmount < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid amount: $";
    }
    account.balance += depositAmount;
    cout << "Deposit successful. Your new balance: $" << account.balance << endl;
}

void withdraw(Account& account) {
    double withdrawAmount;
    cout << "Enter the withdrawal amount: $";
    while (!(cin >> withdrawAmount) || withdrawAmount < 0 || withdrawAmount > account.balance) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (withdrawAmount < 0)
            cout << "Invalid input. Please enter a positive amount: $";
        else
            cout << "Insufficient balance or invalid amount. Please enter a valid amount: $";
    }
    account.balance -= withdrawAmount;
    cout << "Withdrawal successful. Your new balance: $" << account.balance << endl;
}

void displayMenu(Account& currentAccount) {
    int choice;
    do {
        cout << endl << "\t\t\t******************* ATM Menu *******************"<< endl<<endl;
        cout         << "\t\t\t*             1. Check Balance                 *"<< endl;
        cout         << "\t\t\t*             2. Deposit Money                 *"<< endl;
        cout         << "\t\t\t*             3. Withdraw Money                *"<< endl;
        cout         << "\t\t\t*             4. Create Another Account        *"<< endl;
        cout		 << "\t\t\t*             5. Clear screen                  *"<<endl;
		cout         << "\t\t\t*             6. Exit                          *"<< endl<<endl;
        cout         << "\t\t\t************************************************" << endl<<endl;
        cout         << "Enter your choice (1-5): ";

        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            cout << "Enter your choice (1-5): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1:
                cout << "Your Balance: $" << currentAccount.balance << endl;
                break;
            case 2:
                deposit(currentAccount);
                break;
            case 3:
                withdraw(currentAccount);
                break;
            case 4:
                createAccount();
                break;
            case 5:
				system("cls");
				break;    
            case 6:
                cout << "Exiting ATM. Thank you for using our services!" << endl;
                break;
        }
    } while (choice != 6);
}

int main() {
    int choice;
    Account currentAccount;

    do {
        cout << "ATM System Menu" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 3) {
            cout << "Invalid input. Please enter a number between 1 and 3." << endl;
            cout << "Enter your choice: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                login(currentAccount);
                if (!currentAccount.username.empty()) {
                    displayMenu(currentAccount);
                }
                break;
            case 3:
                cout << "Exiting ATM system. Goodbye!" << endl;
                break;
        }
    } while (choice != 3);

    return 0;
}

