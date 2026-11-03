#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "BankAccount.h"
#include <memory>

class CheckingAccount : public BankAccount {
private:
    double transactionFee;

public:
    // Constructors
    CheckingAccount();
    CheckingAccount(const std::string& accNum, const std::string& holderName, double initialBalance, double fee);

    // Destructor
    ~CheckingAccount() override = default;

    // Getter and Setter
    double getTransactionFee() const;
    void setTransactionFee(double fee);

    // Overridden methods
    bool withdraw(double amount) override;
    void printDetails() const override;
    std::string getAccountType() const override;

    // Helper to build account from user input
    static std::unique_ptr<CheckingAccount> createCheckingAccountFromInput();
};

#endif // CHECKINGACCOUNT_H
