#ifndef BANK_H
#define BANK_H

#include "bank_customer.h"
#include <iostream>
#include <vector>
using namespace std;

class Bank {
private:
    string name;
    vector<BankCustomer> accounts;
    int customerCount;

public:
    Bank(const string& name) : name(name), customerCount(0) {}

    void addCustomer(const BankCustomer& customer) {
        accounts.push_back(customer);
        customerCount++;
    }

    BankCustomer* findCustomerById(int id) {
        for (auto &c : accounts) {
            if (c.getId() == id) return &c;
        }
        return nullptr;
    }

    void printAllCustomers() const {
        for (const auto &c : accounts) {
            c.printInfo();
            cout << "----------------------\n";
        }
    }

    int getCustomerCount() const { return customerCount; }
};

#endif // BANK_H