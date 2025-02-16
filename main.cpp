#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <unordered_set>

using namespace std;

// Function to hash passwords (basic security, can be improved with bcrypt/OpenSSL)
size_t hashPassword(const string& password) {
    hash<string> hasher;
    return hasher(password);
}

// Function to display the available items
void displayItems(const map<string, double>& items) {
    cout << "\nAvailable Items:\n";
    cout << left << setw(15) << "Item" << "Price ($)\n";
    cout << "-------------------------\n";
    for (const auto& item : items) {
        cout << left << setw(15) << item.first << fixed << setprecision(2) << item.second << endl;
    }
}

int main() {
    map<string, double> items = {
        {"Laptop", 1200.00},
        {"Smartphone", 800.00},
        {"Headphones", 150.00},
        {"Tablet", 600.00},
        {"Smartwatch", 250.00}
    };

    string storedUsername, storedPassword;
    string username, password;
    string country, city, houseAddress;
    map<string, int> cart; // Stores item name and quantity
    double totalAmount = 0.0;
    static int userCounter = 1; // Counter to track user numbers

    cout << "Welcome to the Shopping Application!\n";
    cout << "Create your account:\n";
    cout << "Enter a username: ";
    getline(cin, storedUsername);
    cout << "Enter a password: ";
    getline(cin, storedPassword);
    size_t hashedPassword = hashPassword(storedPassword);
    cout << "Account created successfully!\n\n";

    // Login loop
    bool loggedIn = false;
    while (!loggedIn) {
        cout << "Login to your account:\n";
        cout << "Enter your username: ";
        getline(cin, username);
        cout << "Enter your password: ";
        getline(cin, password);

        if (username == storedUsername && hashPassword(password) == hashedPassword) {
            loggedIn = true;
            cout << "Login successful!\n";
        } else {
            cout << "Incorrect username or password. Try again.\n";
        }
    }

    cout << "\nEnter your shipping details:\n";
    cout << "Country: "; getline(cin, country);
    cout << "City: "; getline(cin, city);
    cout << "House Address: "; getline(cin, houseAddress);

    char choice;
    do {
        cout << "\n1. Display Items\n";
        cout << "2. Search Item\n";
        cout << "3. Add Item to Cart\n";
        cout << "4. Remove Item from Cart\n";
        cout << "5. View Cart\n";
        cout << "6. Checkout\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Prevents input issues

        switch (choice) {
            case '1':
                displayItems(items);
                break;
            case '2': {
                string searchItem;
                cout << "Enter item name: ";
                getline(cin, searchItem);
                auto it = items.find(searchItem);
                if (it != items.end()) {
                    cout << searchItem << " is available for $" << fixed << setprecision(2) << it->second << endl;
                } else {
                    cout << "Item not found.\n";
                }
                break;
            }
            case '3': {
                string itemToAdd;
                int quantity;
                cout << "Enter item name: ";
                getline(cin, itemToAdd);
                if (items.find(itemToAdd) != items.end()) {
                    cout << "Enter quantity: ";
                    cin >> quantity;
                    cin.ignore(); // Clear input buffer
                    if (quantity > 0) {
                        cart[itemToAdd] += quantity; // Add or update quantity
                        totalAmount += items[itemToAdd] * quantity;
                        cout << quantity << " " << itemToAdd << "(s) added to cart.\n";
                    } else {
                        cout << "Quantity must be greater than 0.\n";
                    }
                } else {
                    cout << "Item not found.\n";
                }
                break;
            }
            case '4': {
                string itemToRemove;
                int quantity;
                cout << "Enter item name: ";
                getline(cin, itemToRemove);
                if (cart.find(itemToRemove) != cart.end()) {
                    cout << "Enter quantity to remove: ";
                    cin >> quantity;
                    cin.ignore(); // Clear input buffer
                    if (quantity > 0 && quantity <= cart[itemToRemove]) {
                        cart[itemToRemove] -= quantity;
                        totalAmount -= items[itemToRemove] * quantity;
                        if (cart[itemToRemove] == 0) {
                            cart.erase(itemToRemove); // Remove item if quantity is 0
                        }
                        cout << quantity << " " << itemToRemove << "(s) removed from cart.\n";
                    } else {
                        cout << "Invalid quantity.\n";
                    }
                } else {
                    cout << "Item not found in cart.\n";
                }
                break;
            }
            case '5':
                cout << "\nYour Cart:\n";
                for (const auto& item : cart) {
                    cout << "- " << item.first << " (Quantity: " << item.second << ") - $" 
                         << fixed << setprecision(2) << items[item.first] * item.second << "\n";
                }
                cout << "Total: $" << fixed << setprecision(2) << totalAmount << "\n";
                break;
            case '6': {
                if (cart.empty()) {
                    cout << "Your cart is empty. Add items before checkout.\n";
                    break;
                }
                cout << "\nProcessing checkout...\n";
                ofstream userFile("users.txt", ios::app);
                if (userFile.is_open()) {
                    userFile << "User " << userCounter++ << ":\n";                                  
                    userFile << "Username: " << storedUsername << "\n";
                    userFile << "Shipping: " << country << ", " << city << ", " << houseAddress << "\n";
                    userFile << "Items:\n";
                    for (const auto& item : cart) {
                        userFile << "  - " << item.first << " (Quantity: " << item.second << ") - $" 
                                 << items[item.first] * item.second << "\n";
                    }
                    userFile << "Total: $" << totalAmount << "\n\n";
                    userFile.close();
                }
                cout << "Order placed successfully!\n";
                cout << "Shipping Details:\n";
                cout << "Username: " << storedUsername << "\n";
                cout << "Country: " << country << "\n";
                cout << "City: " << city << "\n";
                cout << "Address: " << houseAddress << "\n";
                cout << "Total Amount: $" << totalAmount << "\n";
                cart.clear();
                totalAmount = 0.0;
                break;
            }
            case '7':
                cout << "Exiting. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != '7');

    return 0;
}
