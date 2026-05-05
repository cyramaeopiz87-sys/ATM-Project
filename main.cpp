#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class Account {
private:
    int id;
    string name;
    int pin;
    double balance;

public:
    // Constructor to initialize account
    Account(int i, string n, int p, double b) {
        id = i;
        name = n;
        pin = p;
        balance = b;
    }

    // Get account name
    string getName() { return name; }

    // Get account PIN
    int getPin() { return pin; }

    // Show current balance
    void checkBalance() {
        cout << "Current Balance: " << balance << endl;
    }

    // Add money to account
    void deposit(double amount) {
        balance += amount;
        cout << "Deposit successful!\n";
    }

    // Withdraw money (with validation)
    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!";
        } else {
            balance -= amount;
            cout << "Withdrawal successful!";
        }
    }

    // Change account PIN
    void changePin(int newPin) {
        pin = newPin;
        cout << "PIN changed successfully!";
    }

    // Save account data to file
    void displayData(ofstream &out) {
        out << id << " " << name << " " << pin << " " << balance << endl;
    }
};

// ATM system class
class ATM {
private:
    vector<Account> accounts; // list of all accounts

public:
    // Load accounts from file
    void loadAccounts() {
        ifstream in("accounts.txt");
        int id, pin;
        string name;
        double balance;

        // Read data from file
        while (in >> id >> name >> pin >> balance) {
            accounts.push_back(Account(id, name, pin, balance));
        }
        in.close();
    }

    // Save updated accounts back to file
    void saveAccounts() {
        ofstream out("accounts.txt");
        for (int i = 0; i < accounts.size(); i++) {
            accounts[i].displayData(out);
        }
        out.close();
    }

    // Login function
    Account* login() {
        string name;
        int pin;

        cout << "Enter Account Name: ";
        cin >> name;
        cout << "Enter PIN: ";
        cin >> pin;

        // Check if account exists
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].getName() == name && accounts[i].getPin() == pin) {
                cout << "Login successful!";
                return &accounts[i];
            }
        }

        cout << "Invalid credentials!\n";
        return NULL;
    }

    
    void menu(Account* acc) {
        int choice;
        double amount;
        int newPin;

        do {
            cout << " ATM MENU ";
            cout << " 1. Check Balance ";
            cout << " 2. Deposit ";
            cout << " 3. Withdraw ";
            cout << " 4. Change PIN ";
            cout << " 5. Exit ";
            cout << "Choose: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    acc->checkBalance(); // show balance
                    break;
                case 2:
                    cout << "Enter amount: ";
                    cin >> amount;
                    acc->deposit(amount); // deposit money
                    break;
                case 3:
                    cout << "Enter amount: ";
                    cin >> amount;
                    acc->withdraw(amount); // withdraw money
                    break;
                case 4:
                    cout << "Enter new PIN: ";
                    cin >> newPin;
                    acc->changePin(newPin); // change pin
                    break;
                case 5:
                    cout << "Thank you!\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
            }

        } while (choice != 5);
    }
};


int main() {
    ATM atm;

    atm.loadAccounts(); // load data from file

    Account* user = atm.login(); // user login

    if (user != NULL) {
        atm.menu(user);   // show menu
        atm.saveAccounts(); // save updates
    }

    return 0;
}
