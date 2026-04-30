#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <cctype>
using namespace std;

//==========================
// STRUCTS
//==========================

// Structure to hold menu item information
struct MenuItem {
    int id;             // Unique ID of the menu item
    char name[50];      // Name of the item
    float price;        // Price in Rs
    char category[30];  // Category: Starter, Main, Dessert, Beverage
};

// Structure to hold customer order information
struct CustomerOrder {
    string name;    // Customer's name
    int itemId;     // ID of the item ordered
    int quantity;   // Quantity ordered
    float total;    // Total price for this item
    string date;    // Order date and time
};

//==========================
// GLOBAL VARIABLES
//==========================

MenuItem menu[100];       // Array to store menu items
int menuCount = 0;        // Number of items in the menu

CustomerOrder orders[100]; // Array to store orders
int orderCount = 0;        // Number of orders

const string DATA_FILE = "data.txt"; // File to persist menu and orders

//==========================
// FUNCTION DECLARATIONS
//==========================
void loadData();
void saveData();
void showMenu();
void addMenuItem();
void modifyPrice();
void deleteItem();
void takeOrder(string customerName);
void saveOrder(string customerName, float total, int lastItemId, int qty);
float getPriceById(int id);
void searchFood();
void chatbotResponse(char input[], string customerName);
void asciiArt(string food);
void customerMenu();
void adminPanel();
int getLastOrderItemId(string customerName);
void viewOrders();

//==========================
// LOAD DATA FROM FILE
//==========================
void loadData() {
    ifstream fin(DATA_FILE);
    menuCount = 0;
    orderCount = 0;

    if (!fin) {
        // File does not exist: Load default menu
        menuCount = 10;
        menu[0] = {1, "Margherita Pizza", 500, "Main"};
        menu[1] = {2, "BBQ Burger", 350, "Main"};
        menu[2] = {3, "Spicy Chicken Wings", 400, "Starter"};
        menu[3] = {4, "French Fries", 200, "Starter"};
        menu[4] = {5, "Chocolate Lava Cake", 250, "Dessert"};
        menu[5] = {6, "Cold Coffee", 150, "Beverage"};
        menu[6] = {7, "Vanilla Ice Cream", 180, "Dessert"};
        menu[7] = {8, "Veg Salad", 220, "Starter"};
        menu[8] = {9, "Chicken Biryani", 450, "Main"};
        menu[9] = {10, "Soft Drink", 100, "Beverage"};
        return;
    }

    // Flags to differentiate between reading menu and orders
    string line;
    bool readingMenu = false;
    bool readingOrders = false;

    while (getline(fin, line)) {
        if (line == "#MENU") { readingMenu = true; readingOrders = false; continue; }
        if (line == "#ORDERS") { readingOrders = true; readingMenu = false; continue; }
        if (line.empty()) continue;

        if (readingMenu) {
            // Parse menu line: id,name,price,category
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);

            int id = stoi(line.substr(0, pos1));
            string n = line.substr(pos1 + 1, pos2 - pos1 - 1);
            float price = stof(line.substr(pos2 + 1, pos3 - pos2 - 1));
            string cat = line.substr(pos3 + 1);

            strcpy(menu[menuCount].name, n.c_str());
            menu[menuCount].id = id;
            menu[menuCount].price = price;
            strcpy(menu[menuCount].category, cat.c_str());
            menuCount++;
        }
        else if (readingOrders) {
            // Parse order line: name,itemId,quantity,total,date
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);
            size_t pos4 = line.find(',', pos3 + 1);

            CustomerOrder o;
            o.name = line.substr(0, pos1);
            o.itemId = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            o.quantity = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            o.total = stof(line.substr(pos3 + 1, pos4 - pos3 - 1));
            o.date = line.substr(pos4 + 1);

            orders[orderCount++] = o;
        }
    }
    fin.close();
}

//==========================
// SAVE DATA TO FILE
//==========================
void saveData() {
    ofstream fout(DATA_FILE);

    // Save menu
    fout << "#MENU\n";
    for (int i = 0; i < menuCount; i++) {
        fout << menu[i].id << "," << menu[i].name << "," << menu[i].price << "," << menu[i].category << "\n";
    }

    // Save orders
    fout << "#ORDERS\n";
    for (int i = 0; i < orderCount; i++) {
        fout << orders[i].name << "," << orders[i].itemId << "," << orders[i].quantity
             << "," << orders[i].total << "," << orders[i].date << "\n";
    }
    fout.close();
}

//==========================
// SHOW MENU
//==========================
void showMenu() {
    cout << "\n--- MENU ---\n";
    for (int i = 0; i < menuCount; i++) {
        cout << menu[i].id << ". " << menu[i].name
             << " (" << menu[i].category << ") - Rs " << menu[i].price << endl;
    }
}

//==========================
// SEARCH FOOD
//==========================
void searchFood() {
    char search[50];
    cin.ignore();
    cout << "\nEnter keyword to search: ";
    cin.getline(search, 50);

    cout << "\nSearch Results:\n";
    int found = 0;

    for (int i = 0; i < menuCount; i++) {
        if (strstr(menu[i].name, search) != nullptr) {
            cout << menu[i].id << ". " << menu[i].name
                 << " (" << menu[i].category << ") - Rs " << menu[i].price << endl;
            found = 1;
        }
    }

    if (!found)
        cout << "No matching items.\n";
}

//==========================
// ASCII ART
//==========================
void asciiArt(string food) {
    // Display simple ASCII art for certain food items
    if (food == "Pizza") {
        cout << R"(
       ______
      /     /\
     /     /  \
    /_/----\
    |     |    |
    |     |    |
        )" << endl;
    }
    else if (food == "Burger") {
        cout << R"(
     _______
    /       \
   |  ??   |
    \_/
        )" << endl;
    }
    else if (food == "Coffee") {
        cout << R"(
      ( (
       ) )
     ........
     |      |]
     \      /
      `----'
        )" << endl;
    }
}

//==========================
// GET PRICE BY ID
//==========================
float getPriceById(int id) {
    for (int i = 0; i < menuCount; i++)
        if (menu[i].id == id) return menu[i].price;
    return -1; // invalid ID
}

//==========================
// GET LAST ORDER ITEM ID
//==========================
int getLastOrderItemId(string customerName) {
    for (int i = orderCount - 1; i >= 0; i--) {
        if (orders[i].name == customerName) return orders[i].itemId;
    }
    return -1; // no previous order
}

//==========================
// TAKE ORDER
//==========================
void takeOrder(string customerName) {
    int id, qty;
    float total = 0;
    int lastItemId = -1;

    cout << "\nEnter item ID to order (0 to stop):\n";
    while (true) {
        cout << "ID: ";
        cin >> id;
        if (id == 0) break;

        float price = getPriceById(id);
        if (price == -1) {
            cout << "Invalid ID.\n";
            continue;
        }

        cout << "Quantity: ";
        cin >> qty;

        total += price * qty;
        cout << "Added to order.\n";

        lastItemId = id;
        saveOrder(customerName, total, lastItemId, qty); // Save each item immediately
    }

    cout << "\nYour total bill: Rs " << total << endl;
    saveData(); // persist data
}

//==========================
// SAVE ORDER
//==========================
void saveOrder(string customerName, float total, int lastItemId, int qty) {
    time_t now = time(0);
    char* dt = ctime(&now); // get current date and time

    CustomerOrder o;
    o.name = customerName;
    o.itemId = lastItemId;
    o.quantity = qty;
    o.total = total;
    o.date = dt;

    orders[orderCount++] = o; // add to orders array
}

//==========================
// CHATBOT RESPONSE
//==========================
void chatbotResponse(char input[], string customerName) {
    char temp[200];
    strcpy(temp, input);

    // Convert input to lowercase for case-insensitive matching
    for (int i = 0; temp[i]; i++) temp[i] = tolower(temp[i]);

    int lastItemId = getLastOrderItemId(customerName);

    if (strstr(temp, "hi") || strstr(temp, "hello")) {
        cout << "Bot: Hello " << customerName << "! Welcome to FoodBot.\n";
    }
    else if (strstr(temp, "hungry")) {
        cout << "Bot: You seem hungry! How about a delicious Burger?\n";
        asciiArt("Burger");
    }
    else if (strstr(temp, "recommend")) {
        cout << "Bot: Let me recommend… BBQ Burger is amazing today!\n";
        asciiArt("Burger");
    }
    else if (strstr(temp, "sweet") || strstr(temp, "sad")) {
        cout << "Bot: Our Chocolate Lava Cake will cheer you up!\n";
    }
    else if (strstr(temp, "happy")) {
        cout << "Bot: You're happy! Celebrate with a Pizza!\n";
        asciiArt("Pizza");
    }
    else if (strstr(temp, "stressed")) {
        cout << "Bot: Feeling stressed? A Cold Drink will help you relax.\n";
    }
    else if (strstr(temp, "spicy")) {
        cout << "Bot: You might enjoy our Spicy Chicken Wings today!\n";
    }
    else if (strstr(temp, "bye")) {
        cout << "Bot: Goodbye! Have a tasty day!\n";
    }
    else if (lastItemId != -1) {
        cout << "Bot: Hey " << customerName << "! Last time you ordered item ID " << lastItemId
             << ". Want to order it again?\n";
    }
    else {
        cout << "Bot: I didn't understand, but I can show you the menu.\n";
        showMenu();
    }
}

//==========================
// ADMIN FUNCTIONS
//==========================
void addMenuItem() {
    MenuItem m;
    cout << "Enter ID: ";
    cin >> m.id;
    cin.ignore();
    cout << "Enter Name: ";
    cin.getline(m.name, 50);
    cout << "Enter Price: ";
    cin >> m.price;
    cin.ignore();
    cout << "Enter Category: ";
    cin.getline(m.category, 30);

    menu[menuCount++] = m;
    saveData(); // persist changes
    cout << "Item added!\n";
}

void modifyPrice() {
    int id;
    float newPrice;
    cout << "Enter ID to modify: ";
    cin >> id;

    for (int i = 0; i < menuCount; i++) {
        if (menu[i].id == id) {
            cout << "New Price: ";
            cin >> newPrice;
            menu[i].price = newPrice;
            saveData(); // persist changes
            cout << "Price updated!\n";
            return;
        }
    }
    cout << "ID not found.\n";
}

void deleteItem() {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    int newCount = 0;
    for (int i = 0; i < menuCount; i++) {
        if (menu[i].id != id) {
            menu[newCount++] = menu[i]; // copy non-deleted items
        }
    }

    if (newCount == menuCount) {
        cout << "ID not found.\n";
        return;
    }

    menuCount = newCount;
    saveData(); // persist changes
    cout << "Item deleted.\n";
}

//==========================
// VIEW ORDERS
//==========================
void viewOrders() {
    cout << "\n--- All Orders ---\n";
    if (orderCount == 0) {
        cout << "No orders placed yet.\n";
        return;
    }

    for (int i = 0; i < orderCount; i++) {
        cout << "Customer: " << orders[i].name
             << " | Item ID: " << orders[i].itemId
             << " | Quantity: " << orders[i].quantity
             << " | Total: Rs " << orders[i].total
             << " | Date: " << orders[i].date
             << "\n---------------------\n";
    }
}

//==========================
// CUSTOMER MENU
//==========================
void customerMenu() {
    string customerName;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, customerName);

    int choice;
    char msg[200];

    do {
        cout << "\n--- CUSTOMER CHATBOT ---\n";
        cout << "1. Talk to Bot\n2. Show Menu\n3. Search Food\n4. Order Food\n5. Exit\n";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1:
                cout << "You: ";
                cin.getline(msg, 200);
                chatbotResponse(msg, customerName);
                break;
            case 2: showMenu(); break;
            case 3: searchFood(); break;
            case 4: takeOrder(customerName); break;
            case 5: break;
            default: cout << "Invalid choice.\n"; break;
        }

    } while (choice != 5);
}

//==========================
// ADMIN PANEL
//==========================
void adminPanel() {
    string pass;
    cout << "Enter Admin Password: ";
    cin >> pass;

    if (pass != "admin123") {
        cout << "Wrong password.\n";
        return;
    }

    int choice;
    do {
        cout << "\n--- ADMIN PANEL ---\n";
        cout << "1. Add Item\n2. Modify Price\n3. Delete Item\n4. View Menu\n5. View Orders\n6. Exit\n";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: addMenuItem(); break;
            case 2: modifyPrice(); break;
            case 3: deleteItem(); break;
            case 4: showMenu(); break;
            case 5: viewOrders(); break;
            case 6: break;
            default: cout << "Invalid choice.\n"; break;
        }

    } while (choice != 6);
}

//==========================
// MAIN FUNCTION
//==========================
int main() {
    loadData(); // Load menu + orders from file

    int choice;
    do {
        cout << "\n===== RESTAURANT CHATBOT SYSTEM =====\n";
        cout << "1. Customer\n2. Admin\n3. Exit\n";
        cin >> choice;

        switch(choice) {
            case 1: customerMenu(); break;
            case 2: adminPanel(); break;
            case 3: break;
            default: cout << "Invalid choice.\n"; break;
        }

    } while (choice != 3);
cout << "\nThank you for using the Restaurant Chatbot System. Goodbye!\n";
    saveData(); // Save everything on exit
    return 0;
}
