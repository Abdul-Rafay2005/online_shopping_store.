#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm> // for std::find
#include <functional> // for std::hash
#include <cstdlib> // for system("cls") or system("clear")

using namespace std;

// Function to hash passwords (basic security)
size_t hashPassword(const string& password) {
    hash<string> hasher;
    return hasher(password);
}

// Function to display the available items
void displayItems(const map<string, double>& items) {
    cout << "Available Items:\n";
    for (const auto& item : items) {
        cout << item.first << " - $" << item.second << endl;
    }
}

// Function to clear the screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    // Predefined items with their prices
    map<string, double> items = {
        {"Laptop", 1200.00},
        {"Smartphone", 800.00},
        {"Headphones", 150.00},
        {"Tablet", 600.00},
        {"Smartwatch", 250.00}
    };

    // User credentials
    string storedUsername, storedPassword;
    string username, password;
    string country, city, houseAddress;
    vector<string> cart;
    double totalAmount = 0.0;

    // Step 1: Create a username and password
    cout << "Welcome to the Shopping Application!\n";
    cout << "Create your account:\n";
    cout << "Enter a username: ";
    cin >> storedUsername;
    cout << "Enter a password: ";
    cin >> storedPassword;
    size_t hashedPassword = hashPassword(storedPassword); // Hash the password
    cout << "Account created successfully!\n\n";

    // Step 2: Login
    bool loggedIn = false;
    while (!loggedIn) {
        cout << "Login to your account:\n";
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        if (username == storedUsername && hashPassword(password) == hashedPassword) {
            loggedIn = true;
            cout << "Login successful!\n";
        } else {
            cout << "Incorrect username or password. Please try again.\n";
        }
    }

    // Step 3: Set location details
    cout << "\nPlease enter your location details:\n";
    cout << "Country: ";
    cin.ignore(); // To ignore the newline character left by previous input
    getline(cin, country);
    cout << "City: ";
    getline(cin, city);
    cout << "House Address: ";
    getline(cin, houseAddress);

    // Shopping loop
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

        switch (choice) {
            case '1': {
                clearScreen();
                displayItems(items);
                break;
            }
            case '2': {
                clearScreen();
                string searchItem;
                cout << "Enter the item name to search: ";
                cin.ignore();
                getline(cin, searchItem);

                if (items.find(searchItem) != items.end()) {
                    cout << searchItem << " is available for $" << items[searchItem] << endl;
                } else {
                    cout << "Item not found.\n";
                }
                break;
            }
            case '3': {
                clearScreen();
                string itemToAdd;
                cout << "Enter the item name to add to cart: ";
                cin.ignore();
                getline(cin, itemToAdd);

                auto it = items.find(itemToAdd);
                if (it != items.end()) {
                    cart.push_back(itemToAdd);
                    totalAmount += it->second;
                    cout << itemToAdd << " added to cart.\n";
                } else {
                    cout << "Item not found.\n";
                }
                break;
            }
            case '4': {
                clearScreen();
                if (cart.empty()) {
                    cout << "Your cart is empty.\n";
                } else {
                    string itemToRemove;
                    cout << "Enter the item name to remove from cart: ";
                    cin.ignore();
                    getline(cin, itemToRemove);

                    auto it = find(cart.begin(), cart.end(), itemToRemove);
                    if (it != cart.end()) {
                        totalAmount -= items[itemToRemove];
                        cart.erase(it);
                        cout << itemToRemove << " removed from cart.\n";
                    } else {
                        cout << "Item not found in cart.\n";
                    }
                }
                break;
            }
            case '5': {
                clearScreen();
                cout << "Items in your cart:\n";
                for (const string& item : cart) {
                    cout << item << " - $" << items[item] << endl;
                }
                cout << "Total Amount: $" << totalAmount << endl;
                break;
            }
            case '6': {
                clearScreen();
                cout << "Checking out...\n";
                cout << "Items in your cart:\n";
                for (const string& item : cart) {
                    cout << item << " - $" << items[item] << endl;
                }
                cout << "Total Amount: $" << totalAmount << endl;
                cout << "Shipping to:\n";
                cout << "Country: " << country << endl;
                cout << "City: " << city << endl;
                cout << "House Address: " << houseAddress << endl;
                cout << "Thank you for shopping with us!\n";

                // Save purchase history to users.txt
                ofstream userFile("users.txt", ios::app);
                if (userFile.is_open()) {
                    static int userCounter = 1; // Counter to track user numbers
                    userFile << "User " << userCounter++ << ":\n";
                    userFile << "Username: " << storedUsername << "\n";
                    userFile << "Country: " << country << "\n";
                    userFile << "City: " << city << "\n";
                    userFile << "Address: " << houseAddress << "\n";
                    userFile << "Items Purchased:\n";
                    for (const string& item : cart) {
                        userFile << "  - " << item << " - $" << items[item] << "\n";
                    }
                    userFile << "Total Amount: $" << totalAmount << "\n\n";
                    userFile.close();
                } else {
                    cout << "Unable to save user data.\n";
                }

                cart.clear();
                totalAmount = 0.0;
                break;
            }
            case '7': {
                cout << "Exiting the application. Goodbye!\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != '7');

    return 0;
}
