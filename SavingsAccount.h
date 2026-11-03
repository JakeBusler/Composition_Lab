#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "BankAccount.h"
#include <memory>

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    // Constructors
    SavingsAccount();
    SavingsAccount(const std::string& accNum, const std::string& holderName, double initialBalance, double rate);

    // Destructor
    ~SavingsAccount() override = default;

    // Getter and Setter
    double getInterestRate() const;
    void setInterestRate(double rate);

    // Calculate and add interest
    void calculateInterest();

    // Overridden methods
    void printDetails() const override;
    std::string getAccountType() const override;

    // Helper to build account from user input
    static std::unique_ptr<SavingsAccount> createSavingsAccountFromInput();
};

#endif // SAVINGSACCOUNT_H
