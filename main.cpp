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
        encryptedRecord() {
            strcpy(computerName, returnComputerName());
            strcpy(createdAt, returnCurrentTime());
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
                default:
                    cout << "Category: Other" << endl;
                    cout << "Content: " << recordName << endl;
                    cout << "Code: " << recordContent << endl;
                    break;
            }
        }
};

class user {
    int sudo;
    char username[255];
    char userName[255];
    public:
        char* returnName() {
            return userName;
        }
        user() {
            sudo = 0;
        }
        void login() {
            cout << "Username: ";
            cin >> username;
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
        void readContent() {
            ifstream f1;
            char fileName[259];
            strcpy(fileName, username);
            strcat(fileName, ".dat");
            f1.open(fileName, ios::binary|ios::app);
            encryptedRecord A;
            int records = 0;
            while (1) {
                if (f1.eof())
                    break;
                f1.read((char*)&A, sizeof(A));
                cout << ++records << ". " << A.returnName() << " *************\n";
            }
        }
};

int main(void) {

    cout << "Hello world" << endl << endl;

    user A;
    A.login();

    potato: cout << "\n1 for add, 2 for display";
    int n; cin >> n; cout << "\n\n";
    n == 1 ? A.addContent() : A.readContent();

    goto potato;

    return 0;

}
