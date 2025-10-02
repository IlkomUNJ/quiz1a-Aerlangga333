#ifndef SELLER_H
#define SELLER_H

#include "buyer.h"
#include "item.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Seller : public Buyer {
private:
    int sellerId;
    vector<Item> items;

public:
    Seller(Buyer buyer, int sellerId)
        : Buyer(buyer.getId(), buyer.getName(), buyer.getAccount()),
          sellerId(sellerId) {}

    void addNewItem(int newId, const string& newName, int newQuantity, double newPrice) {
        Item newItem(newId, newName, newQuantity, newPrice);
        items.push_back(newItem);
    }

    void updateItem(int itemId, const string& newName, int newQuantity, double newPrice) {
        for (auto& item : items) {
            if (item.getId() == itemId) {
                item.alterItemById(itemId, newName, newQuantity, newPrice);
            }
        }
    }

    void makeItemVisibleToCustomer(int itemId) {
        for (auto& item : items) {
            if (item.getId() == itemId) {
                item.setDisplay(true);
                break;
            }
        }
    }

    void printInventory() const {
    if (items.empty()) {
        cout << "No items available in inventory." << endl;
        return;
    }

    cout << "=== Seller Inventory ===" << endl;
    for (const auto& item : items) {
        cout << "ID: " << item.getId()
             << " | Name: " << item.getName()
             << " | Quantity: " << item.getQuantity()
             << " | Price: $" << item.getPrice()
             << endl;
    }
    cout << "========================" << endl;
}
};

#endif // SELLER