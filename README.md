# 🍽️ Smart Restaurant Chatbot System (C++)

A console-based restaurant management and chatbot system developed in C++.  
This project allows customers to interact with a chatbot, browse the menu, search for food items, place orders, and receive recommendations — while administrators can efficiently manage menu items and monitor all orders.

---

## 🚀 Project Overview

Managing customer orders manually can be time-consuming and inefficient.  
This system automates restaurant interactions by providing a chatbot-driven interface for customers and a management panel for administrators.

The application uses file handling to ensure that all menu updates and customer orders are permanently stored and available across program runs.

---

## ✨ Key Features

### 👤 Customer Panel
- 🤖 Chat with a rule-based chatbot
- 🍔 Get food recommendations based on mood/keywords
- 📋 View complete menu with categories
- 🔍 Search menu items using keywords
- 🛒 Order multiple items with quantity selection
- 💵 Automatic bill calculation
- 🔁 Suggest previously ordered items
- 🎨 ASCII art for interactive experience

---

### 🔐 Admin Panel
- Password-protected access (`admin123`)
- ➕ Add new menu items
- ✏️ Modify item prices
- ❌ Delete menu items
- 📊 View full menu
- 📦 View all customer orders with timestamps

---

## 💾 Data Persistence

- All data is stored in a single file: `data.txt`
- File contains two sections:
  - `#MENU`
  - `#ORDERS`
- Data is:
  - Loaded automatically on program start
  - Saved automatically on updates and exit

---

## 🛠️ Technologies Used

- **C++**
- File Handling (`fstream`)
- Structures & Arrays
- String Manipulation (`cstring`)
- Control Flow (loops, conditions, switch)
- Time Handling (`ctime`)

---

## 📂 Project Structure

```
Restaurant_Project/
│
├── restaurant_chatbot.cpp   # Main source code
├── data.txt                 # Stores menu and orders
├── Screenshots/             # Project images
│   ├── main_menu.png
│   ├── chatbot.png
│   ├── admin_panel.png
│   └── data_file.png
├── README.md
└── LICENSE
```

---

## ▶️ How to Run

1. Download or clone the repository
2. Open the project in any C++ compiler:
   - VS Code
   - CodeBlocks
   - Dev-C++
3. Compile and run `restaurant_chatbot.cpp`
4. Choose:
   - **Customer Mode**
   - **Admin Mode** (Password: `admin123`)

---

## 📸 Screenshots

### 🏠 Main Menu
<img width="1820" height="719" alt="Menu" src="https://github.com/user-attachments/assets/e08e3edc-03dd-4249-860a-45ac8f59549c" />


### 🤖 Customer Chatbot
<img width="1741" height="635" alt="Customer Chatbot" src="https://github.com/user-attachments/assets/865b0587-f32e-4cca-acea-ea6c4123d8c5" />


### 🔐 Admin Panel
<img width="1822" height="662" alt="Admin Panel" src="https://github.com/user-attachments/assets/ad74efb3-10a1-410b-bfb4-c9820e49a99e" />


### 💾 Data File
<img width="1920" height="645" alt="data txt contents" src="https://github.com/user-attachments/assets/ac7a6226-a89f-4f81-81b1-afaf7028dbb6" />


---

## 💡 Future Improvements

- GUI-based version (Qt / Flutter)
- Database integration (MySQL)
- Smarter AI chatbot using NLP
- Online ordering & delivery system
- User authentication system

---

## 🎯 Learning Outcomes

This project helped in understanding:
- Real-world problem solving using C++
- File-based data persistence
- Modular programming with functions
- Struct-based data management
- Building interactive console applications

---

## 👩‍💻 Author

- Unzah Ayaz  


---

## ⭐ Support

If you found this project useful, consider giving it a ⭐ on GitHub!
