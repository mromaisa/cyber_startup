#include <iostream>
#include <string>

using namespace std;

// Base class for any cipher
class Cipher {
public:
    virtual string encrypt(const string& text, int key) = 0;
    virtual string decrypt(const string& text, int key) = 0;
    virtual ~Cipher() {} // Virtual destructor
};

// Derived class implementing Caesar Cipher
class CaesarCipher : public Cipher {
public:
    string encrypt(const string& text, int key) override {
        string encryptedText = text;
        for (char &ch : encryptedText) {
            if (isalpha(ch)) {
                char base = isupper(ch) ? 'A' : 'a';
                ch = (ch - base + key) % 26 + base;
            }
        }
        return encryptedText;
    }

    string decrypt(const string& text, int key) override {
        return encrypt(text, 26 - key); // Reverse shift
    }
};

// User interface for interacting with the program
void runApp() {
    CaesarCipher cipher;
    int choice, key;
    string text, result;

    do {
        cout << "\n===== Cryptography Program =====\n";
        cout << "1. Encrypt\n2. Decrypt\n3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1 || choice == 2) {
            cout << "Enter text: ";
            getline(cin, text);
            cout << "Enter key (1-25): ";
            cin >> key;
            cin.ignore();

            if (choice == 1)
                result = cipher.encrypt(text, key);
            else
                result = cipher.decrypt(text, key);

            cout << "Result: " << result << "\n";
        }
    } while (choice != 3);
    
    cout << "Exiting program...\n";
}

// Main function
int main() {
    runApp();
    return 0;
}
