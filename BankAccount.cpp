#include "BankAccount.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <chrono>
#include <ctime>
#include <sstream>

// Helper to grab the current time formatted nicely
static std::string getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm timeInfo{};
#if defined(_MSC_VER)
    localtime_s(&timeInfo, &now_c);
#else
    localtime_r(&now_c, &timeInfo);
#endif
    std::ostringstream oss;
    oss << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

// Default constructor
BankAccount::BankAccount()
    : accountNumber(""), accountHolderName(""), balance(0.0), transactionHistory() {}

// Parameter constructor
BankAccount::BankAccount(const std::string& accNum, const std::string& holderName, double initialBalance)
    : accountNumber(accNum),
      accountHolderName(holderName),
      balance(initialBalance >= 0.0 ? initialBalance : 0.0),
      transactionHistory() {}

// Copy constructor
BankAccount::BankAccount(const BankAccount& other)
    : accountNumber(other.accountNumber),
      accountHolderName(other.accountHolderName),
      balance(other.balance),
      transactionHistory(other.transactionHistory) {}

// Copy assignment
BankAccount& BankAccount::operator=(const BankAccount& other) {
    if (this != &other) {
        accountNumber = other.accountNumber;
        accountHolderName = other.accountHolderName;
        balance = other.balance;
        transactionHistory = other.transactionHistory;
    }
    return *this;
}

// Virtual destructor
BankAccount::~BankAccount() {}

// Getters
std::string BankAccount::getAccountNumber() const {
    return accountNumber;
}

std::string BankAccount::getAccountHolderName() const {
    return accountHolderName;
}

double BankAccount::getBalance() const {
    return balance;
}

// Setter
void BankAccount::setAccountHolderName(const std::string& name) {
    accountHolderName = name;
}

// Math assignment operators
BankAccount& BankAccount::operator+=(double amount) {
    if (amount > 0.0) {
        balance += amount;
    }
    return *this;
}

BankAccount& BankAccount::operator-=(double amount) {
    if (amount > 0.0 && amount <= balance) {
        balance -= amount;
    }
    return *this;
}

// Deposit funds and log transaction
void BankAccount::deposit(double amount) {
    if (amount > 0.0) {
        *this += amount;
        transactionHistory.push_back(Transaction("Deposit", amount, getCurrentTimestamp()));
    }
}

// Withdraw funds and log transaction
bool BankAccount::withdraw(double amount) {
    if (amount > 0.0 && amount <= balance) {
        *this -= amount;
        transactionHistory.push_back(Transaction("Withdrawal", amount, getCurrentTimestamp()));
        return true;
    }
    return false;
}

// Account type string
std::string BankAccount::getAccountType() const {
    return "Standard Account";
}

// Print account info
void BankAccount::printDetails() const {
    std::cout << "----------------------------------------\n";
    std::cout << "  Account Type   : " << getAccountType() << "\n";
    std::cout << "  Account Number : " << accountNumber << "\n";
    std::cout << "  Holder Name    : " << accountHolderName << "\n";
    std::cout << "  Balance        : $" << std::fixed << std::setprecision(2) << balance << "\n";
    std::cout << "----------------------------------------\n";
}

// Print every transaction logged for this account
void BankAccount::printHistory() const {
    std::cout << "\n=======================================================\n";
    std::cout << "  Transaction History for " << getAccountType() << " #" << accountNumber << "\n";
    std::cout << "  Holder: " << accountHolderName << "\n";
    std::cout << "=======================================================\n";
    if (transactionHistory.empty()) {
        std::cout << "  No transactions recorded yet.\n";
        std::cout << "=======================================================\n\n";
        return;
    }
    std::cout << std::left << std::setw(5)  << "#"
              << std::setw(15) << "Type"
              << std::setw(15) << "Amount"
              << std::setw(22) << "Timestamp" << "\n";
    std::cout << std::string(55, '-') << "\n";

    for (size_t i = 0; i < transactionHistory.size(); ++i) {
        std::cout << std::left << std::setw(5)  << (i + 1)
                  << std::setw(15) << transactionHistory[i].type
                  << "$" << std::fixed << std::setprecision(2) << std::setw(14) << transactionHistory[i].amount
                  << std::setw(22) << transactionHistory[i].timestamp << "\n";
    }
    std::cout << std::string(55, '-') << "\n";
    std::cout << "  Current Balance: $" << std::fixed << std::setprecision(2) << balance << "\n";
    std::cout << "=======================================================\n\n";
}

// Comparisons
bool BankAccount::operator==(const BankAccount& other) const {
    return accountNumber == other.accountNumber;
}

bool BankAccount::operator<(const BankAccount& other) const {
    return balance < other.balance;
}

bool BankAccount::operator>(const BankAccount& other) const {
    return balance > other.balance;
}

// Static helpers
void BankAccount::printAccount(const BankAccount& account) {
    account.printDetails();
}

BankAccount BankAccount::createAccountFromInput() {
    std::string accNum;
    std::string holderName;
    double initialBalance = 0.0;

    std::cout << "Enter Account Number: ";
    while (true) {
        if (std::getline(std::cin >> std::ws, accNum)) {
            size_t first = accNum.find_first_not_of(" \t\r\n");
            if (first != std::string::npos) {
                size_t last = accNum.find_last_not_of(" \t\r\n");
                accNum = accNum.substr(first, (last - first + 1));
                break;
            }
        }
        std::cout << "Account number cannot be empty. Please enter Account Number: ";
    }

    std::cout << "Enter Account Holder Name: ";
    while (true) {
        if (std::getline(std::cin, holderName)) {
            size_t first = holderName.find_first_not_of(" \t\r\n");
            if (first != std::string::npos) {
                size_t last = holderName.find_last_not_of(" \t\r\n");
                holderName = holderName.substr(first, (last - first + 1));
                break;
            }
        }
        std::cout << "Account holder name cannot be empty. Please enter Account Holder Name: ";
    }

    std::cout << "Enter Initial Balance ($): ";
    while (true) {
        if (std::cin >> initialBalance) {
            if (initialBalance >= 0.0) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            std::cout << "Initial balance cannot be negative. Enter Initial Balance ($): ";
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid numeric amount: $";
        }
    }

    return BankAccount(accNum, holderName, initialBalance);
}
