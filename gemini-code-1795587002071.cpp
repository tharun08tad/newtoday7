#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

// Base custom exception class
class BankException : public exception
{
protected:
    string message;

public:
    BankException(string msg)
    {
        message = msg;
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

// Derived exception class
class InsufficientFundsException : public BankException
{
public:
    InsufficientFundsException()
        : BankException("Error: Insufficient balance for withdrawal.")
    {
    }
};

// Another derived exception class
class InvalidAmountException : public BankException
{
public:
    InvalidAmountException()
        : BankException("Error: Amount must be greater than zero.")
    {
    }
};

class BankAccount
{
private:
    string name;
    double balance;

public:
    BankAccount(string n, double b)
    {
        name = n;
        balance = b;
    }

    void deposit(double amount)
    {
        if (amount <= 0)
            throw InvalidAmountException();

        balance += amount;
    }

    void withdraw(double amount)
    {
        // Validate first before modifying the balance
        if (amount <= 0)
            throw InvalidAmountException();

        if (amount > balance)
            throw InsufficientFundsException();

        // State changes only after all checks succeed
        balance -= amount;
    }

    void display()
    {
        cout << "Account Holder: " << name << endl;
        cout << "Balance: Rs. " << balance << endl;
    }
};

int main()
{
    string name;
    double balance, depAmount, withAmount1, withAmount2;

    cout << "Enter Account Holder Name: ";
    getline(cin, name);

    cout << "Enter Initial Balance: ";
    cin >> balance;

    BankAccount account(name, balance);

    cout << "\nInitial Account Details:" << endl;
    account.display();

    try
    {
        cout << "\nEnter amount to deposit: ";
        cin >> depAmount;
        cout << "Depositing Rs. " << depAmount << "..." << endl;
        account.deposit(depAmount);

        cout << "\nEnter first amount to withdraw: ";
        cin >> withAmount1;
        cout << "Withdrawing Rs. " << withAmount1 << "..." << endl;
        account.withdraw(withAmount1);

        cout << "\nEnter second amount to withdraw: ";
        cin >> withAmount2;
        cout << "Withdrawing Rs. " << withAmount2 << "..." << endl;
        account.withdraw(withAmount2);
    }
    catch (const InsufficientFundsException &e)
    {
        cout << e.what() << endl;
    }
    catch (const InvalidAmountException &e)
    {
        cout << e.what() << endl;
    }
    catch (const BankException &e)
    {
        cout << "Bank Exception: " << e.what() << endl;
    }
    catch (const exception &e)
    {
        cout << "General Exception: " << e.what() << endl;
    }

    cout << "\nFinal Account Details:" << endl;
    account.display();

    return 0;
}