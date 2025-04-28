#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

// -------------------- USER MANAGEMENT --------------------
class UserManager
{
public:
    void isRegister(string name, string password)
    {
        ofstream LoginFile("login.csv", ios::app); // append mode
        if (LoginFile.is_open())
        {
            LoginFile << name << "," << password << endl;
            LoginFile.close();
        }
        else
        {
            cout << "Error in opening the file.\n";
        }
    }

    bool Login(string name, string password)
    {
        ifstream LoginFile("login.csv");
        if (LoginFile.is_open())
        {
            string line;
            while (getline(LoginFile, line))
            {
                stringstream piece(line);
                string input_name, input_password;
                getline(piece, input_name, ',');
                getline(piece, input_password, '\n');
                if (input_name == name && input_password == password)
                {
                    cout << "You are logged in.\n";
                    return true;
                }
            }
            cout << "Username or password is invalid.\n";
        }
        else
        {
            cout << "Error opening the file.\n";
        }
        return false;
    }
};

// -------------------- ENCRYPTION --------------------
class Encrypt
{
public:
    string Vigenere_cipher(string message, string key)
    {
        string encrypted_message = message;
        for (int i = 0; i < encrypted_message.length(); i++)
        {
            if (isalpha(encrypted_message[i]))
            {
                char msg_offset = isupper(encrypted_message[i]) ? 'A' : 'a';
                char key_offset = isupper(key[i % key.length()]) ? 'A' : 'a';
                encrypted_message[i] =
                    ((encrypted_message[i] - msg_offset) + (key[i % key.length()] - key_offset)) % 26 + msg_offset;
            }
        }
        return encrypted_message;
    }

    string Caeser_cipher(string message, int shift)
    {
        string encrypted_message = message;
        for (int i = 0; i < encrypted_message.length(); i++)
        {
            if (isalpha(encrypted_message[i]))
            {
                char base = isupper(encrypted_message[i]) ? 'A' : 'a';
                encrypted_message[i] = (encrypted_message[i] - base + shift) % 26 + base;
            }
        }
        return encrypted_message;
    }
};

// -------------------- DECRYPTION --------------------
class Decrypt
{
public:
    string decrypt_vigenere(string message, string key)
    {
        string decrypted_message = message;
        for (int i = 0; i < decrypted_message.length(); i++)
        {
            if (isalpha(decrypted_message[i]))
            {
                char msg_offset = isupper(decrypted_message[i]) ? 'A' : 'a';
                char key_offset = isupper(key[i % key.length()]) ? 'A' : 'a';
                decrypted_message[i] =
                    ((decrypted_message[i] - msg_offset) - (key[i % key.length()] - key_offset) + 26) % 26 + msg_offset;
            }
        }
        return decrypted_message;
    }

    string decrypt_caeser(string message, int shift)
    {
        string decrypted_message = message;
        for (int i = 0; i < decrypted_message.length(); i++)
        {
            if (isalpha(decrypted_message[i]))
            {
                char base = isupper(decrypted_message[i]) ? 'A' : 'a';
                decrypted_message[i] = (decrypted_message[i] - base - shift + 26) % 26 + base;
            }
        }
        return decrypted_message;
    }
};

// -------------------- SYSTEM MANAGER --------------------
class SystemManager : public UserManager, public Encrypt, public Decrypt
{
    bool isLoggedIn = false;
    string current_user;

public:
    bool showLogin(string name, string password)
    {
        if (Login(name, password))
        {
            current_user = name;
            isLoggedIn = true;
            return true;
        }
        cout << "Login failed.\n";
        return false;
    }

    bool showRegister(string name, string password)
    {
        isRegister(name, password);
        if (Login(name, password))
        {
            current_user = name;
            isLoggedIn = true;
            return true;
        }
        cout << "Registration failed.\n";
        return false;
    }

    void encryp_msg(string msg, string key)
    {
        cout << "Encrypted Message: " << Vigenere_cipher(msg, key) << endl;
    }

    void encryp_msg(string msg, int key)
    {
        cout << "Encrypted Message: " << Caeser_cipher(msg, key) << endl;
    }

    void decrypt_msg(string msg, string key)
    {
        cout << "Decrypted Message: " << decrypt_vigenere(msg, key) << endl;
    }

    void decrypt_msg(string msg, int key)
    {
        cout << "Decrypted Message: " << decrypt_caeser(msg, key) << endl;
    }
};

// -------------------- MAIN --------------------
int main()
{
    cout << "Welcome to the Cryptographic System\n";
    cout << "Select\n1. Login \n2. Register\n";
    int choice;
    cin >> choice;
    cin.ignore(); // Clear newline

    SystemManager sm1;
    string name, password;

    if (choice == 1 || choice == 2)
    {
        cout << "\nEnter your username: ";
        getline(cin, name);
        cout << "Enter your password: ";
        getline(cin, password);
    }

    if (choice == 1)
    {
        if (sm1.showLogin(name, password))
        {
            cout << "\nDo you want to:\n1. Encrypt\n2. Decrypt\n";
            int option;
            cin >> option;
            cin.ignore();

            cout << "\nEnter your message:\n";
            string message;
            getline(cin, message);

            cout << "\nChoose key type:\n1. String key\n2. Integer shift\n";
            int keyType;
            cin >> keyType;
            cin.ignore();

            if (keyType == 1)
            {
                string key;
                cout << "Enter your string key: ";
                cin >> key;
                if (option == 1)
                    sm1.encryp_msg(message, key);
                else
                    sm1.decrypt_msg(message, key);
            }
            else if (keyType == 2)
            {
                int shift;
                cout << "Enter your integer shift: ";
                cin >> shift;
                if (option == 1)
                    sm1.encryp_msg(message, shift);
                else
                    sm1.decrypt_msg(message, shift);
            }
            else
            {
                cout << "Invalid input.\n";
            }
        }
    }
    else if (choice == 2)
    {
        if (sm1.showRegister(name, password))
        {
            cout << "Registration successful.\n";
            if (sm1.Login(name, password))
            {
                cout << "\nDo you want to:\n1. Encrypt\n2. Decrypt\n";
                int option;
                cin >> option;
                cin.ignore();

                cout << "\nEnter your message:\n";
                string message;
                getline(cin, message);

                cout << "\nChoose key type:\n1. String key\n2. Integer shift\n";
                int keyType;
                cin >> keyType;
                cin.ignore();

                if (keyType == 1)
                {
                    string key;
                    cout << "Enter your string key: ";
                    cin >> key;
                    if (option == 1)
                        sm1.encryp_msg(message, key);
                    else
                        sm1.decrypt_msg(message, key);
                }
                else if (keyType == 2)
                {
                    int shift;
                    cout << "Enter your integer shift: ";
                    cin >> shift;
                    if (option == 1)
                        sm1.encryp_msg(message, shift);
                    else
                        sm1.decrypt_msg(message, shift);
                }
                else
                {
                    cout << "Login failed.\n";
                }
            }
            else
            {
                cout << "Invalid input\n";
            }
        }
        else
        {
            cout << "Registration failed.\n";
        }

        return 0;
    }
}
