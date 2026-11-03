#include "CheckingAccount.h"
#include <iostream>
#include <iomanip>
#include <limits>

// Default constructor
CheckingAccount::CheckingAccount()
    : BankAccount(), transactionFee(0.0) {}

// Parameter constructor
CheckingAccount::CheckingAccount(const std::string& accNum, const std::string& holderName, double initialBalance, double fee)
    : BankAccount(accNum, holderName, initialBalance), transactionFee(fee >= 0.0 ? fee : 0.0) {}

// Getter and setter
double CheckingAccount::getTransactionFee() const {
    return transactionFee;
}

void CheckingAccount::setTransactionFee(double fee) {
    if (fee >= 0.0) {
        transactionFee = fee;
    }
}

// Withdraw funds plus the fee, passing total to base class so it gets logged in history
bool CheckingAccount::withdraw(double amount) {
    if (amount <= 0.0) {
        return false;
    }
    double totalDeduction = amount + transactionFee;
    if (totalDeduction <= balance) {
        return BankAccount::withdraw(totalDeduction);
    }
    return false;
}

std::string CheckingAccount::getAccountType() const {
    return "Checking Account";
}

void CheckingAccount::printDetails() const {
    std::cout << "----------------------------------------\n";
    std::cout << "  Account Type    : " << getAccountType() << "\n";
    std::cout << "  Account Number  : " << accountNumber << "\n";
    std::cout << "  Holder Name     : " << accountHolderName << "\n";
    std::cout << "  Balance         : $" << std::fixed << std::setprecision(2) << balance << "\n";
    std::cout << "  Transaction Fee : $" << std::fixed << std::setprecision(2) << transactionFee << "\n";
    std::cout << "----------------------------------------\n";
}

std::unique_ptr<CheckingAccount> CheckingAccount::createCheckingAccountFromInput() {
    std::string accNum;
    std::string holderName;
    double initialBalance = 0.0;
    double fee = 0.0;

    std::cout << "Enter Checking Account Number: ";
    while (true) {
        if (std::getline(std::cin >> std::ws, accNum)) {
            size_t first = accNum.find_first_not_of(" \t\r\n");
            if (first != std::string::npos) {
                size_t last = accNum.find_last_not_of(" \t\r\n");
                accNum = accNum.substr(first, (last - first + 1));
                break;
            }
        }
        std::cout << "Account number cannot be empty. Enter Checking Account Number: ";
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
        std::cout << "Account holder name cannot be empty. Enter Account Holder Name: ";
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

    std::cout << "Enter Transaction Fee ($): ";
    while (true) {
        if (std::cin >> fee) {
            if (fee >= 0.0) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            std::cout << "Transaction fee cannot be negative. Enter Transaction Fee ($): ";
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid numeric amount: $";
        }
    }

    return std::make_unique<CheckingAccount>(accNum, holderName, initialBalance, fee);
}
