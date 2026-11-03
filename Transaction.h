#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

// Simple struct to hold a single transaction record
struct Transaction {
    std::string type;
    double amount;
    std::string timestamp;

    Transaction() : type(""), amount(0.0), timestamp("") {}

    Transaction(const std::string& t, double a, const std::string& ts)
        : type(t), amount(a), timestamp(ts) {}
};

#endif // TRANSACTION_H
