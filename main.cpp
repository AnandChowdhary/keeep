#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main (void) {

    char username[50];
    char password[50];
    int choice;

    home:   cout << "Welcome to Keeep\n\n";
            cout << "1.   Log in to your Keeep\n";
            cout << "2.   Sign up for a new Keeep\n";
            cout << "3.   String encryptor (experimental)\n";
            cout << "99.  Exit saving changes\n\n";
            cout << "Enter your choice: ";
            cin >> choice;

    switch (choice) {
        case 1:
            break;
        case 99:
            cout << "Thanks for Keeeping! Press any key to exit: ";
            getch();
            return 0;
        default:
            cout << "Invalid choice. Press any key to try again: ";
            getch();
            system("cls");
            goto home;
    }

    //////////////////////////////////////

    signup: cout << "\n\nUsername: ";
    gets (username);

    std::string testLocation (username);
    testLocation.append(".dat");

    fstream f1;
    f1.open(testLocation.c_str(), ios::in);

    if (f1.fail()) {
        cout << "\nUsername not found. Press any key to continue. ";
        getch();
        goto signup;
    } else {
        cout << "Password: ";
        gets (username);
    }

    //////////////////////////////////////

    login: cout << "\n\nUsername: ";
    gets (username);

    std::string fileLocation (username);
    fileLocation.append(".dat");

    fstream f2;
    f2.open(fileLocation.c_str(), ios::in);

    if (f2.fail()) {
        cout << "\nUsername not found. Press any key to continue. ";
        getch();
        goto login;
    } else {
        cout << "Password: ";
        gets (username);
    }

    //////////////////////////////////////

    cout << "\n\n";
    return 0;

}
