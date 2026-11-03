#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
#include "BankAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"

// Flush any bad input from cin
static void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Read non-empty string lines
static std::string getNonEmptyString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        if (std::getline(std::cin, value)) {
            size_t first = value.find_first_not_of(" \t\r\n");
            if (first != std::string::npos) {
                size_t last = value.find_last_not_of(" \t\r\n");
                return value.substr(first, (last - first + 1));
            }
        } else {
            return "";
        }
        std::cout << "Input cannot be empty. Please try again.\n";
    }
}

// Read and validate a positive double
static double getValidDouble(const std::string& prompt, bool allowZero = false) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if ((allowZero && value >= 0.0) || (!allowZero && value > 0.0)) {
                clearInputBuffer();
                return value;
            }
            std::cout << "Invalid amount. Value must be "
                      << (allowZero ? "greater than or equal to 0.00" : "strictly greater than 0.00")
                      << ".\n";
        } else {
            std::cout << "Invalid input. Please enter a number.\n";
        }
        clearInputBuffer();
    }
}

// Read and validate an integer option
static int getValidInt(const std::string& prompt, int minVal, int maxVal) {
    int choice;
    while (true) {
        std::cout << prompt;
        if (std::cin >> choice) {
            if (choice >= minVal && choice <= maxVal) {
                clearInputBuffer();
                return choice;
            }
            std::cout << "Please select an option between " << minVal << " and " << maxVal << ".\n";
        } else {
            std::cout << "Invalid input. Please enter a valid number.\n";
        }
        clearInputBuffer();
    }
}

// Find an account in our accounts vector by account number
static int findAccountIndex(const std::vector<std::unique_ptr<BankAccount>>& accounts, const std::string& accNum) {
    BankAccount target(accNum, "", 0.0);
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (*accounts[i] == target) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Menu display
static void displayMenu() {
    std::cout << "\n=========================================\n";
    std::cout << "     BANK ACCOUNT MANAGEMENT SYSTEM      \n";
    std::cout << "           (Composition Lab)             \n";
    std::cout << "=========================================\n";
    std::cout << "  1. Create New Account\n";
    std::cout << "  2. Deposit Funds\n";
    std::cout << "  3. Withdraw Funds\n";
    std::cout << "  4. View Transaction History (printHistory)\n";
    std::cout << "  5. Display Accrued Interest\n";
    std::cout << "  6. View Account Details\n";
    std::cout << "  7. Display All Accounts\n";
    std::cout << "  8. Compare Two Accounts\n";
    std::cout << "  9. Update Account Holder Name\n";
    std::cout << " 10. Polymorphic Withdrawal Example\n";
    std::cout << " 11. Exit\n";
    std::cout << "=========================================\n";
}

// Polymorphic demo from previous lab
static void runPolymorphismDemo() {
    std::cout << "\n=======================================================\n";
    std::cout << "           POLYMORPHIC WITHDRAWAL EXAMPLE              \n";
    std::cout << "=======================================================\n";

    auto checking = std::make_unique<CheckingAccount>("DEMO-CHK", "Demo User", 500.0, 2.50);
    auto savings = std::make_unique<SavingsAccount>("DEMO-SAV", "Demo User", 500.0, 0.05);

    BankAccount* basePtr1 = checking.get();
    BankAccount* basePtr2 = savings.get();

    std::cout << "Invoking basePtr1->withdraw(100.00) [Points to CheckingAccount]:\n";
    std::cout << "  Starting Balance: $" << basePtr1->getBalance() << "\n";
    bool res1 = basePtr1->withdraw(100.0);
    std::cout << "  Result: " << (res1 ? "SUCCESS" : "FAILED") << "\n";
    std::cout << "  New Balance: $" << basePtr1->getBalance()
              << " (Deducted $100.00 + $2.50 fee = $102.50)\n\n";

    std::cout << "Invoking basePtr2->withdraw(100.00) [Points to SavingsAccount]:\n";
    std::cout << "  Starting Balance: $" << basePtr2->getBalance() << "\n";
    bool res2 = basePtr2->withdraw(100.0);
    std::cout << "  Result: " << (res2 ? "SUCCESS" : "FAILED") << "\n";
    std::cout << "  New Balance: $" << basePtr2->getBalance()
              << " (Deducted $100.00 with no fee)\n";
    std::cout << "=======================================================\n";
}

// Automated challenge demonstration for Lab Part 3
static void runCompositionLabDemo() {
    std::cout << "========================================================\n";
    std::cout << "     COMPOSITION LAB: TRANSACTION HISTORY DEMO         \n";
    std::cout << "========================================================\n\n";

    // 1. Checking Account Demo
    std::cout << ">>> Step 1: Testing CheckingAccount with Composition <<<\n";
    CheckingAccount checking("CHK-1001", "Dick Butkis", 1000.00, 2.50);
    checking.printDetails();

    std::cout << "\n[Action] Depositing $250.00...\n";
    checking.deposit(250.00);

    std::cout << "[Action] Depositing $150.00...\n";
    checking.deposit(150.00);

    std::cout << "[Action] Withdrawing $100.00 (with $2.50 fee)...\n";
    checking.withdraw(100.00);

    std::cout << "[Action] Withdrawing $50.00 (with $2.50 fee)...\n";
    checking.withdraw(50.00);

    std::cout << "\nCalling checking.printHistory():\n";
    checking.printHistory();

    // 2. Savings Account Demo
    std::cout << ">>> Step 2: Testing SavingsAccount with Composition <<<\n";
    SavingsAccount savings("SAV-2001", "Dick Butkis", 2500.00, 0.05);
    savings.printDetails();

    std::cout << "\n[Action] Depositing $500.00...\n";
    savings.deposit(500.00);

    std::cout << "[Action] Withdrawing $200.00...\n";
    savings.withdraw(200.00);

    std::cout << "[Action] Depositing $100.00...\n";
    savings.deposit(100.00);

    std::cout << "[Action] Calculating interest (5% on current balance)...\n";
    savings.calculateInterest();

    std::cout << "\nCalling savings.printHistory():\n";
    savings.printHistory();

    std::cout << "========================================================\n";
    std::cout << "  Composition demonstration completed successfully!   \n";
    std::cout << "========================================================\n\n";
}

int main() {
    std::cout << std::fixed << std::setprecision(2);

    // Run the required automated transaction history demonstration first
    runCompositionLabDemo();

    // Interactive system setup
    std::vector<std::unique_ptr<BankAccount>> accounts;
    accounts.push_back(std::make_unique<CheckingAccount>("CHK-1001", "Dick Butkis", 1250.00, 2.50));
    accounts.push_back(std::make_unique<SavingsAccount>("SAV-2001", "Dick Butkis", 5000.00, 0.045));

    // Populate initial accounts with a couple sample transactions
    accounts[0]->deposit(300.00);
    accounts[0]->withdraw(150.00);
    accounts[1]->deposit(1000.00);

    std::cout << "Would you like to open the interactive banking menu? (y/n): ";
    std::string response;
    if (!(std::cin >> response) || (response != "y" && response != "Y")) {
        std::cout << "Exiting program. Goodbye!\n";
        return 0;
    }
    clearInputBuffer();

    bool running = true;
    while (running) {
        displayMenu();
        int choice = getValidInt("Enter your choice (1-11): ", 1, 11);
        std::cout << "\n";

        switch (choice) {
            case 1: { // Create New Account
                std::cout << "--- Create New Account ---\n";
                std::cout << " 1. Checking Account (with Fee)\n";
                std::cout << " 2. Savings Account (with Interest)\n";
                int typeChoice = getValidInt("Select Account Type (1-2): ", 1, 2);

                if (typeChoice == 1) {
                    auto newChecking = CheckingAccount::createCheckingAccountFromInput();
                    if (findAccountIndex(accounts, newChecking->getAccountNumber()) != -1) {
                        std::cout << "Error: Account number '" << newChecking->getAccountNumber() << "' already exists.\n";
                        break;
                    }
                    std::cout << "\nChecking Account created successfully!\n";
                    newChecking->printDetails();
                    accounts.push_back(std::move(newChecking));
                } else {
                    auto newSavings = SavingsAccount::createSavingsAccountFromInput();
                    if (findAccountIndex(accounts, newSavings->getAccountNumber()) != -1) {
                        std::cout << "Error: Account number '" << newSavings->getAccountNumber() << "' already exists.\n";
                        break;
                    }
                    std::cout << "\nSavings Account created successfully!\n";
                    newSavings->printDetails();
                    accounts.push_back(std::move(newSavings));
                }
                break;
            }

            case 2: { // Deposit Funds
                std::cout << "--- Deposit Funds ---\n";
                if (accounts.empty()) {
                    std::cout << "No accounts available.\n";
                    break;
                }
                std::string accNum = getNonEmptyString("Enter Account Number: ");
                int index = findAccountIndex(accounts, accNum);
                if (index == -1) {
                    std::cout << "Error: Account #" << accNum << " not found.\n";
                    break;
                }
                double amount = getValidDouble("Enter Deposit Amount ($): ", false);
                accounts[index]->deposit(amount);
                std::cout << "Deposited $" << amount << " into " << accounts[index]->getAccountType() << " #" << accNum << ".\n";
                std::cout << "New Balance: $" << accounts[index]->getBalance() << "\n";
                break;
            }

            case 3: { // Withdraw Funds
                std::cout << "--- Withdraw Funds ---\n";
                if (accounts.empty()) {
                    std::cout << "No accounts available.\n";
                    break;
                }
                std::string accNum = getNonEmptyString("Enter Account Number: ");
                int index = findAccountIndex(accounts, accNum);
                if (index == -1) {
                    std::cout << "Error: Account #" << accNum << " not found.\n";
                    break;
                }

                BankAccount* accPtr = accounts[index].get();
                auto checkingPtr = dynamic_cast<CheckingAccount*>(accPtr);
                if (checkingPtr) {
                    std::cout << "Note: Transaction fee of $" << checkingPtr->getTransactionFee() << " will apply.\n";
                }

                double amount = getValidDouble("Enter Withdrawal Amount ($): ", false);
                bool success = accPtr->withdraw(amount);
                if (success) {
                    std::cout << "Successfully withdrew $" << amount << " from account #" << accNum << ".\n";
                    std::cout << "New Balance: $" << accPtr->getBalance() << "\n";
                } else {
                    std::cout << "Error: Withdrawal failed due to insufficient funds.\n";
                }
                break;
            }

            case 4: { // View Transaction History
                std::cout << "--- View Transaction History ---\n";
                if (accounts.empty()) {
                    std::cout << "No accounts available.\n";
                    break;
                }
                std::string accNum = getNonEmptyString("Enter Account Number: ");
                int index = findAccountIndex(accounts, accNum);
                if (index == -1) {
                    std::cout << "Error: Account #" << accNum << " not found.\n";
                    break;
                }
                accounts[index]->printHistory();
                break;
            }

            case 5: { // Display Accrued Interest
                std::cout << "--- Calculate Interest ---\n";
                if (accounts.empty()) {
                    std::cout << "No accounts available.\n";
                    break;
                }
                std::string accNum = getNonEmptyString("Enter Savings Account Number: ");
                int index = findAccountIndex(accounts, accNum);
                if (index == -1) {
                    std::cout << "Error: Account #" << accNum << " not found.\n";
                    break;
                }

                auto savingsPtr = dynamic_cast<SavingsAccount*>(accounts[index].get());
                if (!savingsPtr) {
                    std::cout << "Error: Account #" << accNum << " is not a Savings Account.\n";
                    break;
                }

                double oldBal = savingsPtr->getBalance();
                savingsPtr->calculateInterest();
                double newBal = savingsPtr->getBalance();
                std::cout << "Interest calculated and deposited!\n";
                std::cout << "  Interest Added: $" << (newBal - oldBal) << "\n";
                std::cout << "  New Balance   : $" << newBal << "\n";
                break;
            }

            case 6: { // View Account Details
                std::cout << "--- View Account Details ---\n";
                if (accounts.empty()) {
                    std::cout << "No accounts available.\n";
                    break;
                }
                std::string accNum = getNonEmptyString("Enter Account Number: ");
                int index = findAccountIndex(accounts, accNum);
                if (index == -1) {
                    std::cout << "Error: Account #" << accNum << " not found.\n";
                    break;
                }
                accounts[index]->printDetails();
                break;
            }

            case 7: { // Display All Accounts
                std::cout << "--- All Registered Accounts ---\n";
                if (accounts.empty()) {
                    std::cout << "No accounts registered yet.\n";
                    break;
                }

                std::cout << std::left << std::setw(4)  << "#"
                          << std::setw(18) << "Account Type"
                          << std::setw(14) << "Account No."
                          << std::setw(20) << "Account Holder"
                          << std::right << std::setw(14) << "Balance ($)"
                          << std::setw(18) << "Fee / Rate" << "\n";
                std::cout << std::string(88, '-') << "\n";

                for (size_t i = 0; i < accounts.size(); ++i) {
                    std::string extraInfo = "-";
                    if (auto chk = dynamic_cast<CheckingAccount*>(accounts[i].get())) {
                        std::ostringstream ss;
                        ss << "Fee: $" << std::fixed << std::setprecision(2) << chk->getTransactionFee();
                        extraInfo = ss.str();
                    } else if (auto sav = dynamic_cast<SavingsAccount*>(accounts[i].get())) {
                        std::ostringstream ss;
                        ss << "Rate: " << std::fixed << std::setprecision(2) << (sav->getInterestRate() * 100.0) << "%";
                        extraInfo = ss.str();
                    }

                    std::cout << std::left << std::setw(4)  << (i + 1)
                              << std::setw(18) << accounts[i]->getAccountType()
                              << std::setw(14) << accounts[i]->getAccountNumber()
                              << std::setw(20) << accounts[i]->getAccountHolderName()
                              << std::right << std::setw(14) << accounts[i]->getBalance()
                              << std::setw(18) << extraInfo << "\n";
                }
                std::cout << std::string(88, '-') << "\n";
                std::cout << "Total Accounts: " << accounts.size() << "\n";
                break;
            }

            case 8: { // Compare Two Accounts
                std::cout << "--- Compare Two Accounts ---\n";
                if (accounts.size() < 2) {
                    std::cout << "You need at least 2 accounts to compare.\n";
                    break;
                }

                std::string accNum1 = getNonEmptyString("Enter First Account Number: ");
                int idx1 = findAccountIndex(accounts, accNum1);
                if (idx1 == -1) {
                    std::cout << "Error: Account #" << accNum1 << " not found.\n";
                    break;
                }

                std::string accNum2 = getNonEmptyString("Enter Second Account Number: ");
                int idx2 = findAccountIndex(accounts, accNum2);
                if (idx2 == -1) {
                    std::cout << "Error: Account #" << accNum2 << " not found.\n";
                    break;
                }

                const BankAccount& a1 = *accounts[idx1];
                const BankAccount& a2 = *accounts[idx2];

                std::cout << "\nComparison Results:\n";
                std::cout << "  Account 1: #" << a1.getAccountNumber() << " - Balance: $" << a1.getBalance() << "\n";
                std::cout << "  Account 2: #" << a2.getAccountNumber() << " - Balance: $" << a2.getBalance() << "\n\n";

                if (a1 == a2) {
                    std::cout << "  [==] Same account numbers.\n";
                } else {
                    std::cout << "  [==] Different account numbers.\n";
                }

                if (a1 < a2) {
                    std::cout << "  [<]  Account 1 has less balance than Account 2.\n";
                } else if (a1 > a2) {
                    std::cout << "  [>]  Account 1 has greater balance than Account 2.\n";
                } else {
                    std::cout << "  [==] Both accounts have the exact same balance.\n";
                }
                break;
            }

            case 9: { // Update Account Holder Name
                std::cout << "--- Update Account Holder Name ---\n";
                if (accounts.empty()) {
                    std::cout << "No accounts available.\n";
                    break;
                }

                std::string accNum = getNonEmptyString("Enter Account Number: ");
                int index = findAccountIndex(accounts, accNum);
                if (index == -1) {
                    std::cout << "Error: Account #" << accNum << " not found.\n";
                    break;
                }

                std::cout << "Current Name: " << accounts[index]->getAccountHolderName() << "\n";
                std::string newName = getNonEmptyString("Enter New Account Holder Name: ");
                accounts[index]->setAccountHolderName(newName);
                std::cout << "Account holder name updated to '" << newName << "'.\n";
                break;
            }

            case 10: { // Polymorphic Withdrawal
                runPolymorphismDemo();
                break;
            }

            case 11: { // Exit
                std::cout << "Exiting system. Have a good one!\n";
                running = false;
                break;
            }
        }
    }

    return 0;
}
