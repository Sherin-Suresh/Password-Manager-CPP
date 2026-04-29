#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

string xorEncryptDecrypt(const string& text, char key = '#') {
    string result = text;
    for (char& c : result) {
        c = c ^ key;  // XOR each character
    }
    return result;
}

class PasswordEntry {
public:
    string siteName;
    string username;
    string password;

    PasswordEntry() {}
    PasswordEntry(string site, string user, string pass)
        : siteName(site), username(user), password(pass) {}

    void display() const {
        cout << left
             << setw(20) << siteName
             << setw(25) << username
             << password << endl;
    }
};


private:
    map<string, PasswordEntry> vault;   // site -> entry
    string filename = "vault.dat";      // encrypted storage file
    string masterPassword;

public:

    // ----------- Master Password Setup -----------
    void setMasterPassword(const string& pwd) {
        masterPassword = pwd;
    }

    bool verifyMasterPassword(const string& pwd) {
        return masterPassword == pwd;
    }

    // ----------- Add a Password Entry -----------
    void addPassword() {
        string site, user, pass;

        cout << "\n  Enter Site/App Name  : ";
        cin >> site;
        cout << "  Enter Username/Email : ";
        cin >> user;
        cout << "  Enter Password       : ";
        cin >> pass;

        if (vault.find(site) != vault.end()) {
            cout << "\n  [!] Entry for '" << site << "' already exists. Use update option.\n";
            return;
        }

        vault[site] = PasswordEntry(site, user, pass);
        cout << "\n  [✓] Password saved for '" << site << "'!\n";
    }

    // ----------- View a Specific Password -----------
    void viewPassword() {
        string site;
        cout << "\n  Enter Site/App Name to search: ";
        cin >> site;

        if (vault.find(site) == vault.end()) {
            cout << "\n  [!] No entry found for '" << site << "'.\n";
            return;
        }

        cout << "\n  ─────────────────────────────────────\n";
        cout << "  Site     : " << vault[site].siteName << endl;
        cout << "  Username : " << vault[site].username << endl;
        cout << "  Password : " << vault[site].password << endl;
        cout << "  ─────────────────────────────────────\n";
    }

    // ----------- View All Passwords -----------
    void viewAllPasswords() {
        if (vault.empty()) {
            cout << "\n  [!] No passwords saved yet.\n";
            return;
        }

        cout << "\n  ─────────────────────────────────────────────────────\n";
        cout << "  " << left << setw(20) << "SITE" << setw(25) << "USERNAME" << "PASSWORD\n";
        cout << "  ─────────────────────────────────────────────────────\n";

        for (auto& pair : vault) {
            cout << "  ";
            pair.second.display();
        }

        cout << "  ─────────────────────────────────────────────────────\n";
        cout << "  Total entries: " << vault.size() << endl;
    }

    // ----------- Update a Password -----------
    void updatePassword() {
        string site;
        cout << "\n  Enter Site/App Name to update: ";
        cin >> site;

        if (vault.find(site) == vault.end()) {
            cout << "\n  [!] No entry found for '" << site << "'.\n";
            return;
        }

        string newUser, newPass;
        cout << "  Enter new Username (press enter to keep current): ";
        cin.ignore();
        getline(cin, newUser);
        if (!newUser.empty()) vault[site].username = newUser;

        cout << "  Enter new Password (press enter to keep current): ";
        getline(cin, newPass);
        if (!newPass.empty()) vault[site].password = newPass;

        cout << "\n  [✓] Password updated for '" << site << "'!\n";
    }

    // ----------- Delete a Password Entry -----------
    void deletePassword() {
        string site;
        cout << "\n  Enter Site/App Name to delete: ";
        cin >> site;

        if (vault.find(site) == vault.end()) {
            cout << "\n  [!] No entry found for '" << site << "'.\n";
            return;
        }

        vault.erase(site);
        cout << "\n  [✓] Entry for '" << site << "' deleted!\n";
    }

    // ----------- Save to File (Encrypted) -----------
    void saveToFile() {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "  [!] Could not open file for saving.\n";
            return;
        }

        // Save master password (encrypted)
        file << xorEncryptDecrypt(masterPassword) << "\n";

        // Save each entry (all fields encrypted)
        for (auto& pair : vault) {
            file << xorEncryptDecrypt(pair.second.siteName) << "|"
                 << xorEncryptDecrypt(pair.second.username) << "|"
                 << xorEncryptDecrypt(pair.second.password) << "\n";
        }

        file.close();
        cout << "\n  [✓] All data saved securely to file.\n";
    }

    // ----------- Load from File (Decrypt) -----------
    bool loadFromFile() {
        ifstream file(filename);
        if (!file.is_open()) {
            return false;  // Fresh start, no file yet
        }

        string line;

        // First line = master password
        if (getline(file, line)) {
            masterPassword = xorEncryptDecrypt(line);
        }

        // Remaining lines = password entries
        while (getline(file, line)) {
            string parts[3];
            int idx = 0;
            string token = "";

            for (char c : line) {
                if (c == '|') {
                    parts[idx++] = xorEncryptDecrypt(token);
                    token = "";
                } else {
                    token += c;
                }
            }
            parts[idx] = xorEncryptDecrypt(token);

            if (idx == 2) {
                vault[parts[0]] = PasswordEntry(parts[0], parts[1], parts[2]);
            }
        }

        file.close();
        return true;
    }

    // ----------- Check if vault has master pwd -----------
    bool hasMasterPassword() {
        return !masterPassword.empty();
    }

    string getMasterPassword() {
        return masterPassword;
    }
};

// ─────────────────────────────────────────────
//  Display the main menu
// ─────────────────────────────────────────────
void showMenu() {
    cout << "\n  ╔══════════════════════════════╗\n";
    cout << "  ║      🔐 PASSWORD VAULT       ║\n";
    cout << "  ╠══════════════════════════════╣\n";
    cout << "  ║  1. Add Password             ║\n";
    cout << "  ║  2. View a Password          ║\n";
    cout << "  ║  3. View All Passwords       ║\n";
    cout << "  ║  4. Update a Password        ║\n";
    cout << "  ║  5. Delete a Password        ║\n";
    cout << "  ║  6. Save & Exit              ║\n";
    cout << "  ╚══════════════════════════════╝\n";
    cout << "  Enter your choice: ";
}

// ─────────────────────────────────────────────
//  MAIN FUNCTION
// ─────────────────────────────────────────────
int main() {
    PasswordManager pm;

    cout << "\n  =============================================\n";
    cout << "       Welcome to Password Manager (C++)\n";
    cout << "  =============================================\n";

    // Try to load existing vault
    bool fileExists = pm.loadFromFile();

    if (fileExists) {
        // Ask for master password to unlock
        cout << "\n  Vault found! Enter master password to unlock: ";
        string enteredPwd;
        cin >> enteredPwd;

        if (!pm.verifyMasterPassword(enteredPwd)) {
            cout << "\n  [✗] Wrong master password! Access denied.\n";
            return 1;
        }
        cout << "  [✓] Access granted! Welcome back.\n";

    } else {
        // First time - create master password
        cout << "\n  No vault found. Let's create one!\n";
        cout << "  Set your master password: ";
        string newPwd;
        cin >> newPwd;
        pm.setMasterPassword(newPwd);
        cout << "  [✓] Master password set! Keep it safe.\n";
    }

    // Main menu loop
    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: pm.addPassword();      break;
            case 2: pm.viewPassword();     break;
            case 3: pm.viewAllPasswords(); break;
            case 4: pm.updatePassword();   break;
            case 5: pm.deletePassword();   break;
            case 6:
                pm.saveToFile();
                cout << "\n  Goodbye! Stay secure 🔐\n\n";
                break;
            default:
                cout << "\n  [!] Invalid choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}