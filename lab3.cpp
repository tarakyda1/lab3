#include <iostream>
#include <string>

using namespace std;

class SimpleAccount {
protected:
    string owner_name;
    double initial_balance;
    double interest_rate;
    int years_existence;

public:
    SimpleAccount(string name, double balance, double rate, int years)
        : owner_name(name), initial_balance(balance), interest_rate(rate), years_existence(years) {}

    virtual double calculateBalance() {
        return initial_balance * (1 + interest_rate / 100 * years_existence);
    }

    virtual void printAccount() {
        cout << "Owner: " << owner_name << endl;
        cout << "Initial Balance: $" << initial_balance << endl;
        cout << "Interest Rate: " << interest_rate << "%" << endl;
        cout << "Years Existence: " << years_existence << endl;
        cout << "Balance: $" << calculateBalance() << endl;
    }
};

class PrivilegedAccount : public SimpleAccount {
private:
    double credit_interest_rate;

public:
    PrivilegedAccount(string name, double balance, double rate, int years, double credit_rate)
        : SimpleAccount(name, balance, rate, years), credit_interest_rate(credit_rate) {}

    double calculateBalance() override {
        double base_balance = SimpleAccount::calculateBalance();
        double available_credit = base_balance * (credit_interest_rate / 100);
        return base_balance + available_credit;
    }

    void printAccount() override {
        SimpleAccount::printAccount();
        cout << "Credit Interest Rate: " << credit_interest_rate << "%" << endl;
        cout << "Available Credit: $" << calculateBalance() - initial_balance << endl;
    }
};

int main() {
    SimpleAccount simple("John Doe", 1000.0, 5.0, 3);
    simple.printAccount();
    cout << endl;

    PrivilegedAccount privileged("Jane Smith", 2000.0, 6.0, 5, 10.0);
    privileged.printAccount();
    cout << endl;

    // Static polymorphism
    cout << "Using static polymorphism:" << endl;
    SimpleAccount* account1 = &simple;
    SimpleAccount* account2 = &privileged;

    account1->printAccount();
    cout << endl;
    account2->printAccount();
    cout << endl;

    // Dynamic polymorphism
    cout << "Using dynamic polymorphism:" << endl;
    SimpleAccount* accounts[2];
    accounts[0] = &simple;
    accounts[1] = &privileged;

    for (int i = 0; i < 2; ++i) {
        accounts[i]->printAccount();
        cout << endl;
    }

    return 0;
}
