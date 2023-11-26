#include <iostream>
#include <iomanip>
#include <string>

class Account {
protected:
    int accountNumber;
    std::string accountHolder;
    double balance;

public:
    Account(int accNumber, const std::string& accHolder, double initialBalance)
        : accountNumber(accNumber), accountHolder(accHolder), balance(initialBalance) {}

    virtual void displayDetails() const {
        std::cout << "Account Details for Account (ID: " << accountNumber << "):" << std::endl;
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "   Holder: " << accountHolder << std::endl;
        std::cout << "   Balance: $" << balance << std::endl;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposit of $" << amount << " successful." << std::endl;
        } else {
            std::cout << "Invalid deposit amount." << std::endl;
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            std::cout << "Withdrawal of $" << amount << " successful." << std::endl;
        } else {
            std::cout << "Invalid withdrawal amount or insufficient balance." << std::endl;
        }
    }

    friend void transfer(Account& from, Account& to, double amount) {
        from.withdraw(amount);
        to.deposit(amount);
        std::cout << "Transfer of $" << amount << " successful." << std::endl;
    }
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(int accNumber, const std::string& accHolder, double initialBalance, double interest)
        : Account(accNumber, accHolder, initialBalance), interestRate(interest) {}

    void displayDetails() const override {
        Account::displayDetails();
        std::cout << "   Interest Rate: " << std::fixed << std::setprecision(2) << interestRate * 100 << "%" << std::endl;
    }

    void withdraw(double amount) override {
        const double minimumBalance = 100.0;

        if (amount > 0 && (balance - amount) >= minimumBalance) {
            balance -= amount;
            std::cout << "Withdrawal of $" << amount << " successful." << std::endl;
        } else {
            std::cout << "Invalid withdrawal amount or insufficient balance (minimum balance: $"
                      << minimumBalance << ")." << std::endl;
        }
    }
};

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(int accNumber, const std::string& accHolder, double initialBalance, double overdraft)
        : Account(accNumber, accHolder, initialBalance), overdraftLimit(overdraft) {}

    void displayDetails() const override {
        Account::displayDetails();
        std::cout << "   Overdraft Limit: $" << overdraftLimit << std::endl;
    }

    void withdraw(double amount) override {
        if (amount > 0 && (balance - amount) >= -overdraftLimit) {
            balance -= amount;
            std::cout << "Withdrawal of $" << amount << " successful." << std::endl;
        } else {
            std::cout << "Invalid withdrawal amount or exceeded overdraft limit (limit: $"
                      << overdraftLimit << ")." << std::endl;
        }
    }
};

int main() {
    SavingsAccount savings(123, "John Doe", 1000.0, 0.02);
    CurrentAccount current(456, "Jane Smith", 2000.0, 500.0);

    savings.displayDetails();
    current.displayDetails();

    savings.deposit(500.0);
    current.withdraw(1000.0);

    std::cout << "Account Details after deposit and withdrawal:" << std::endl;
    savings.displayDetails();
    current.displayDetails();

    transfer(savings, current, 300.0);

    std::cout << "Account Details after transfer:" << std::endl;
    savings.displayDetails();
    current.displayDetails();

    return 0;
}
