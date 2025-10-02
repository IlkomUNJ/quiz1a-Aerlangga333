#include <iostream>
#include <vector>
#include <string>
#include "bank_customer.h"
#include "buyer.h"
#include "seller.h"
#include <algorithm>

using namespace std;

enum PrimaryPrompt { LOGIN, REGISTER, EXIT, ADMIN_LOGIN };
enum RegisterPrompt { CREATE_BUYER, CREATE_SELLER, BACK };

// Database sementara
vector<Buyer> buyers;
vector<Seller> sellers;
vector<BankCustomer> bankAccounts;

const string ADMIN_USERNAME = "root";
const string ADMIN_PASSWORD = "toor";

// ===== Submenu Buyer =====
void buyerMenu(Buyer &buyer) {
    int choice;
    bool running = true;
    while (running) {
        cout << "\n=== Buyer Menu (" << buyer.getName() << ") ===\n";
        cout << "1. Check Account Status\n";
        cout << "2. Upgrade Account to Seller\n";
        cout << "3. Logout\n";
        cout << "Select option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                buyer.printInfo();
                break;
            case 2: {
                cout << "Enter Seller ID: ";
                int sid; cin >> sid;
                sellers.push_back(Seller(buyer, sid));
                cout << "Buyer upgraded to Seller!\n";
                break;
            }
            case 3:
                cout << "Logging out...\n";
                running = false;
                break;
            default:
                cout << "Invalid option.\n";
                break;
        }
    }
}

// ===== Submenu Seller =====
void sellerMenu(Seller &seller) {
    int choice;
    bool running = true;
    while (running) {
        cout << "\n=== Seller Menu ===\n";
        cout << "1. Check Inventory\n";
        cout << "2. Add Item\n";
        cout << "3. Exit\n";
        cout << "Select option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                seller.printInventory();
                break;
            case 2:
                cout << "Feature Add Item belum diimplementasi penuh.\n";
                break;
            case 3:
                running = false;
                break;
            default:
                cout << "Invalid option.\n";
                break;
        }
    }
}

void adminMenu() {
    int choice;
    bool running = true;
    while (running) {
        cout << "\n=== Admin Menu ===\n";
        cout << "1. View All Buyers\n";
        cout << "2. View All Sellers\n";
        cout << "3. Search Buyer/Seller\n";
        cout << "4. Create Buyer\n";
        cout << "5. Create Seller\n";
        cout << "6. Remove Buyer/Seller by ID\n";
        cout << "7. Back to Main Menu\n";
        cout << "Select option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                for (auto &b : buyers) b.printInfo();
                break;
            case 2:
                for (auto &s : sellers) s.printInventory();
                break;
            case 3: {
                cout << "Enter name to search: ";
                string key; cin >> key;
                bool found = false;
                for (auto &b : buyers) {
                    if (b.getName() == key) {
                        b.printInfo(); found = true;
                    }
                }
                for (auto &s : sellers) {
                    if (s.getName() == key) {
                        cout << "Seller found: " << s.getName() << endl;
                        s.printInventory(); found = true;
                    }
                }
                if (!found) cout << "No match found!\n";
                break;
            }
            case 4: {
                int id; string name;
                cout << "Enter Buyer ID: "; cin >> id;
                cout << "Enter Buyer Name: "; cin >> name;
                BankCustomer acc(id, name, 0.0);
                bankAccounts.push_back(acc);
                buyers.push_back(Buyer(id, name, &bankAccounts.back()));
                cout << "Buyer created.\n";
                break;
            }
            case 5: {
                if (buyers.empty()) {
                    cout << "No buyer exists, cannot create seller!\n";
                    break;
                }
                int sid;
                cout << "Enter Seller ID: "; cin >> sid;
                sellers.push_back(Seller(buyers[0], sid));
                cout << "Seller created.\n";
                break;
            }
            case 6: {
                cout << "Enter Buyer/Seller ID to remove: ";
                int rid; cin >> rid;
                buyers.erase(remove_if(buyers.begin(), buyers.end(),
                    [rid](Buyer &b){ return b.getId() == rid; }), buyers.end());
                sellers.erase(remove_if(sellers.begin(), sellers.end(),
                    [rid](Seller &s){ return s.getId() == rid; }), sellers.end());
                cout << "Removed.\n";
                break;
            }
            case 7:
                running = false;
                break;
            default:
                cout << "Invalid option.\n";
                break;
        }
    }
}

// ===== MAIN PROGRAM =====
int main() {
    PrimaryPrompt prompt = LOGIN;
    RegisterPrompt regPrompt = CREATE_BUYER;
    string username, password;

    while (prompt != EXIT) {
        cout << "\n=== Main Menu ===\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "4. Admin Login\n";
        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);

        switch (prompt) {
            case LOGIN: {
                cout << "Enter username: ";
                cin >> username;
                bool found = false;

                for (auto &b : buyers) {
                    if (b.getName() == username) {
                        buyerMenu(b);
                        found = true;
                        break;
                    }
                }
                for (auto &s : sellers) {
                    if (s.getName() == username) {
                        sellerMenu(s);
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "You're not registered account yet!\n";
                }
                break;
            }

            case REGISTER: {
                cout << "\n=== Register Menu ===\n";
                cout << "1. Create Buyer Account\n";
                cout << "2. Create Seller Account (must be Buyer first)\n";
                cout << "3. Back\n";
                int regChoice;
                cin >> regChoice;
                regPrompt = static_cast<RegisterPrompt>(regChoice - 1);

                switch (regPrompt) {
                    case CREATE_BUYER: {
                        int id; string name;
                        cout << "Enter Buyer ID: "; cin >> id;
                        cout << "Enter Buyer Name: "; cin >> name;
                        BankCustomer acc(id, name, 0.0);
                        bankAccounts.push_back(acc);
                        buyers.push_back(Buyer(id, name, &bankAccounts.back()));
                        cout << "Buyer registered.\n";
                        break;
                    }
                    case CREATE_SELLER: {
                        if (buyers.empty()) {
                            cout << "You must register as Buyer first!\n";
                            break;
                        }
                        int sid;
                        cout << "Enter Seller ID: "; cin >> sid;
                        sellers.push_back(Seller(buyers[0], sid));
                        cout << "Seller registered.\n";
                        break;
                    }
                    case BACK:
                        break;
                    default:
                        cout << "Invalid option.\n";
                        break;
                }
                break;
            }

            case EXIT:
                cout << "Exiting...\n";
                break;

            case ADMIN_LOGIN: {
                cout << "Username: "; cin >> username;
                cout << "Password: "; cin >> password;
                if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
                    cout << "Admin logged in.\n";
                    adminMenu();
                } else {
                    cout << "Invalid admin credentials.\n";
                }
                break;
            }

            default:
                cout << "Invalid option.\n";
                break;
        }
    }

    return 0;
}