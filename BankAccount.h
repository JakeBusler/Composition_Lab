#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <iostream>
#include <vector>
#include "Transaction.h"

class BankAccount {
protected:
    std::string accountNumber;
    std::string accountHolderName;
    double balance;

private:
    // Tracks all deposits and withdrawals
    std::vector<Transaction> transactionHistory;

public:
    // Constructors
    BankAccount();
    BankAccount(const std::string& accNum, const std::string& holderName, double initialBalance);

    // Destructor
    virtual ~BankAccount();

    // Copy operations
    BankAccount(const BankAccount& other);
    BankAccount& operator=(const BankAccount& other);

    // Getters
    std::string getAccountNumber() const;
    std::string getAccountHolderName() const;
    double getBalance() const;

    // Setters
    void setAccountHolderName(const std::string& name);

    // Banking actions
    void deposit(double amount);
    virtual bool withdraw(double amount);

    // Display methods
    virtual void printDetails() const;
    void printHistory() const;
    virtual std::string getAccountType() const;

    // Math and comparison overloads
    BankAccount& operator+=(double amount);
    BankAccount& operator-=(double amount);
    bool operator==(const BankAccount& other) const;
    bool operator<(const BankAccount& other) const;
    bool operator>(const BankAccount& other) const;

    // Helpers
    static void printAccount(const BankAccount& account);
    static BankAccount createAccountFromInput();
};

#endif // BANKACCOUNT_H
