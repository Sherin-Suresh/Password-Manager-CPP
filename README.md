# 🔐 Password Manager — C++

A secure, CLI-based Password Manager built in **C++** using core concepts like Object-Oriented Programming, STL, File Handling, and XOR Encryption. All passwords are stored locally in an encrypted file and protected by a master password.

---

## 📌 Features

- 🔑 **Master Password Protection** — Vault locks/unlocks with one master password
- ➕ **Add Password** — Save site name, username & password
- 👁️ **View Password** — Search and retrieve a specific entry
- 📋 **View All** — Display all saved passwords in a clean table
- ✏️ **Update Password** — Modify existing credentials
- 🗑️ **Delete Password** — Remove an entry from the vault
- 💾 **Encrypted File Storage** — Data saved in `vault.dat` using XOR encryption
- 🔁 **Persistent Storage** — Passwords remain saved between sessions

---

## 🛠️ Tech Stack

| Concept | Usage |
|---|---|
| **OOP (Classes)** | `PasswordEntry` and `PasswordManager` classes |
| **STL Map** | Stores site → entry pairs for fast lookup |
| **File Handling** | Read/write encrypted data to `vault.dat` |
| **XOR Encryption** | Scrambles data before saving to file |

---

## 📁 Project Structure

```
PasswordManager/
├── password_manager.cpp   # Main source code
├── vault.dat              # Auto-generated encrypted storage file
└── README.md              # Project documentation
```

---

## ▶️ How to Run

### Prerequisites
- g++ compiler (MinGW for Windows)

### Steps

```bash
# Step 1: Clone the repository
git clone https://github.com/Sherin-Suresh/Password-Manager-CPP.git

# Step 2: Navigate into the folder
cd Password-Manager-CPP

# Step 3: Compile
g++ password_manager.cpp -o password_manager

# Step 4: Run
./password_manager        # Linux / Mac
password_manager.exe      # Windows
```

---

## 🎮 Usage

```
=============================================
     Welcome to Password Manager (C++)
=============================================

No vault found. Let's create one!
Set your master password: ****

╔══════════════════════════════╗
║      🔐 PASSWORD VAULT       ║
╠══════════════════════════════╣
║  1. Add Password             ║
║  2. View a Password          ║
║  3. View All Passwords       ║
║  4. Update a Password        ║
║  5. Delete a Password        ║
║  6. Save & Exit              ║
╚══════════════════════════════╝
```

### Example

```
Enter Site/App Name  : Instagram
Enter Username/Email : myemail@gmail.com
Enter Password       : insta@123

✓ Password saved for 'Instagram'!
```

---

## 🔒 How Encryption Works

All data is encrypted using **XOR Encryption** before being written to `vault.dat`:

```cpp
string xorEncryptDecrypt(const string& text, char key = '#') {
    string result = text;
    for (char& c : result) {
        c = c ^ key;  // XOR each character with the key
    }
    return result;
}
```

> XOR is a symmetric operation — the same function both encrypts and decrypts. Without the key, the raw file is unreadable. ✅

---

## 📚 Concepts Demonstrated

- ✅ Object-Oriented Programming (Classes, Encapsulation)
- ✅ STL `map` for efficient key-value storage
- ✅ File I/O (`fstream`) for persistent data
- ✅ XOR-based encryption for data security
- ✅ CLI menu-driven application design

---

## 👩‍💻 Author

**Sherin Suresh**  
BCA Final Year | Christ Academy Institute for Advanced Studies, Bangalore  
📧 tosherinsuresh1438@gmail.com  
🔗 [LinkedIn](https://www.linkedin.com/in/sherinsuresh) | [GitHub](https://github.com/Sherin-Suresh)

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).
