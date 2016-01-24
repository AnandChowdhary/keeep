#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

char* returnComputerName() { // [1]
    TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof (computerName) / sizeof (computerName[0]);
    GetComputerName (computerName, &size);
    return computerName;
}

char *returnCurrentTime() { // [2]
    time_t now = time(0);
    char* dt = ctime(&now);
    tm *gmtm = gmtime(&now);
    dt = asctime(gmtm);
    return dt;
}

class encryptedRecord {
    char computerName[255];
    char createdAt[255];
    int category;
    char recordName[255];
    char recordContent[255];
    char recordContentOther[255];
    public:
        char* returnName() {
            return recordName;
        }
        char* returnContent() {
            return recordContent;
        }
        encryptedRecord() {
            strcpy(computerName, returnComputerName());
            strcpy(createdAt, returnCurrentTime());
        }
        void addRecord(int cat, char rname[], char rcont[]) {
            category = cat;
            strcpy(recordName, rname);
            strcpy(recordContent, rcont);
        }
        void insertRecord() {
            cout << "Choose a category:     1. Password" << endl;
            cout << "                       2. Credit card number" << endl;
            cout << "                       3. Other information" << endl;
            cin >> category; char a[2];
            switch (category) {
                case 1:
                    gets (a);
                    cout << "Name of website/ app: ";
                    gets (recordName);
                    cout << "Your password: ";
                    gets (recordContent);
                    break;
                case 2:
                    gets (a);
                    cout << "Name of your card (eg. HDFC MasterCard): ";
                    gets (recordName);
                    cout << "Your card number: ";
                    gets (recordContent);
                    cout << "Your card CVV: ";
                    gets (recordContentOther);
                    break;
                default:
                    gets (a);
                    cout << "Name of content (eg. Aadhar Number): ";
                    gets (recordName);
                    cout << "Your code: ";
                    gets (recordContent);
                    break;
            }
        }
        void displayRecord() {
            cout << "Created at: " << createdAt;
            cout << "Computer name: " << computerName << endl;
            switch (category) {
                case 1:
                    cout << "Category: Password" << endl;
                    cout << "Website/ app: " << recordName << endl;
                    cout << "Password: " << recordContent << endl;
                    break;
                case 2:
                    cout << "Category: Credit card" << endl;
                    cout << "Card name: " << recordName << endl;
                    cout << "Card number: " << recordContent << endl;
                    cout << "CVV: " << recordContentOther << endl;
                    break;
                case 3:
                    cout << "Category: Other" << endl;
                    cout << "Record Name: " << recordName << endl;
                    cout << "Password: " << recordContent << endl;
                    break;
                default:
                    break;
            }
        }
};

class user {
    int sudo;
    char username[255];
    char userName[255];
    public:
        void authenticate(char u[]) {
            strcpy(username, u);
        }
        char* returnName() {
            return userName;
        }
        user() {
            sudo = 0;
        }
        void signup() {
            char signup_username[255];
            char signup_password[255];
            cout << "Enter your username: ";
            cin >> signup_username;
            char tempName[255];
            strcpy(tempName, signup_username);
            strcat(tempName, ".dat");
            ifstream f1;
            f1.open(tempName, ios::in);
            if (!f1.fail()) {
                cout << "\nAn account with that username already exists.\n\n";
                signup();
            } else {
                cout << "Enter a password: ";
                cin >> signup_password;
                char firstAccount[255];
                strcpy(firstAccount, signup_username);
                strcat(firstAccount, ".dat");
                ofstream f2;
                f2.open(firstAccount, ios::binary|ios::out);
                encryptedRecord A;
                A.addRecord(0, "Keeep", signup_password);
                f2.write((char*)&A, sizeof(A));
                cout << "Account created successfully.";
                authenticate(signup_username);
            }
        }
        void login() {
            char login_username[255];
            char login_password[255];
            cout << "Username: ";
            cin >> login_username;
            char tempName[255];
            strcpy(tempName, login_username);
            strcat(tempName, ".dat");
            ifstream f1;
            f1.open(tempName, ios::in);
            if (f1.fail()) {
                cout << "Username not found.\n\n";
                login();
            } else {
                cout << "Password: ";
                cin >> login_password;
                ifstream f1;
                int authenticated = 0;
                char fileName[259];
                strcpy(fileName, login_username);
                strcat(fileName, ".dat");
                f1.open(fileName, ios::binary);
                encryptedRecord B;
                while (1) {
                    f1.read((char*)&B, sizeof(B));
                    if (f1.eof())
                        break;
                    if (strcmpi(B.returnName(), "Keeep") == 0) {
                        if (strcmpi(B.returnContent(), login_password) == 0) {
                            authenticated++;
                            break;
                        }
                    }
                }
                if (authenticated == 0) {
                    cout << "\n\nIncorrect password.\n\n";
                    login();
                } else {
                    authenticate(login_username);
                }
            }
        }
        void addContent() {
            ofstream f1;
            char fileName[259];
            strcpy(fileName, username);
            strcat(fileName, ".dat");
            f1.open(fileName, ios::binary|ios::app);
            encryptedRecord A;
            A.insertRecord();
            f1.write((char*)&A, sizeof(A));
            cout << "Record added successfully.";
        }
        void findParticular() {
            int p; cin >> p;
            ifstream f1;
            char fileName[259];
            strcpy(fileName, username);
            strcat(fileName, ".dat");
            f1.open(fileName, ios::binary|ios::app);
            encryptedRecord A;
            int records = 0;
            int found = 0;
            while (1) {
                f1.read((char*)&A, sizeof(A));
                if (f1.eof())
                    break;
                if (++records == p + 1 && p != 0) {
                    cout << endl;
                    A.displayRecord();
                    found++;
                }
            }
            if (found == 0) {
                cout << "No record found";
            }
            cout << "\nPress any key to continue.\n";
            getch();
        }
        void readContent() {
            cout << username << endl << endl << endl;
            ifstream f1;
            char fileName[259];
            strcpy(fileName, username);
            strcat(fileName, ".dat");
            f1.open(fileName, ios::binary|ios::app);
            encryptedRecord A;
            int records = 0;
            while (1) {
                f1.read((char*)&A, sizeof(A));
                if (f1.eof())
                    break;
                if (strcmpi(A.returnName(), "Keeep") == 0) {
                    ++records;
                } else {
                    cout << ++records - 1 << ". " << A.returnName() << " *************\n";
                }
            }
            cout << "\nA total of " << records - 1 << " record were found.\n\nEnter a record number to view details: ";
            findParticular();
        }
};

int main(void) {

    cout << "Hello world" << endl << endl;

    user A;

    cout << "1. Login\n2. Register\n\nChoice: ";
    int u; cin >> u; cout << "\n";
    u == 1 ? A.login() : A.signup();

    potato: cout << "\n Press 1 to add new, 2 to view: ";
    int n; cin >> n; cout << "\n";
    n == 1 ? A.addContent() : A.readContent();

    goto potato;

    return 0;

}
