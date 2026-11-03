#include "SavingsAccount.h"
#include <iostream>
#include <iomanip>
#include <limits>

// Default constructor
SavingsAccount::SavingsAccount()
    : BankAccount(), interestRate(0.0) {}

// Parameter constructor
SavingsAccount::SavingsAccount(const std::string& accNum, const std::string& holderName, double initialBalance, double rate)
    : BankAccount(accNum, holderName, initialBalance), interestRate(rate >= 0.0 ? rate : 0.0) {}

// Getter and setter
double SavingsAccount::getInterestRate() const {
    return interestRate;
}

void SavingsAccount::setInterestRate(double rate) {
    if (rate >= 0.0) {
        interestRate = rate;
    }
}

// Calculate earned interest and add it through deposit so it logs to history
void SavingsAccount::calculateInterest() {
    double interest = balance * interestRate;
    if (interest > 0.0) {
        deposit(interest);
    }
}

std::string SavingsAccount::getAccountType() const {
    return "Savings Account";
}

void SavingsAccount::printDetails() const {
    std::cout << "----------------------------------------\n";
    std::cout << "  Account Type   : " << getAccountType() << "\n";
    std::cout << "  Account Number : " << accountNumber << "\n";
    std::cout << "  Holder Name    : " << accountHolderName << "\n";
    std::cout << "  Balance        : $" << std::fixed << std::setprecision(2) << balance << "\n";
    std::cout << "  Interest Rate  : " << std::fixed << std::setprecision(2) << (interestRate * 100.0) << "% (" << interestRate << " decimal)\n";
    std::cout << "----------------------------------------\n";
}

std::unique_ptr<SavingsAccount> SavingsAccount::createSavingsAccountFromInput() {
    std::string accNum;
    std::string holderName;
    double initialBalance = 0.0;
    double rate = 0.0;

    std::cout << "Enter Savings Account Number: ";
    while (true) {
        if (std::getline(std::cin >> std::ws, accNum)) {
            size_t first = accNum.find_first_not_of(" \t\r\n");
            if (first != std::string::npos) {
                size_t last = accNum.find_last_not_of(" \t\r\n");
                accNum = accNum.substr(first, (last - first + 1));
                break;
            }
        }
        std::cout << "Account number cannot be empty. Enter Savings Account Number: ";
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

    std::cout << "Enter Interest Rate (e.g., 0.05 for 5%): ";
    while (true) {
        if (std::cin >> rate) {
            if (rate >= 0.0) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            std::cout << "Interest rate cannot be negative. Enter Interest Rate: ";
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid numeric amount: ";
        }
    }

    return std::make_unique<SavingsAccount>(accNum, holderName, initialBalance, rate);
}
