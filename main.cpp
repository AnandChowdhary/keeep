#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <ctime>
#include <algorithm>

using namespace std;

char l[] = "----------------------------------------------------------------------------------------------";
char m[] = "----------------------------------------------------------------------------------------------";

char engine (int engineCommand, char replacable) {
    char replaced = replacable;
    if (engineCommand == 0) {
        for (int i = 0; i < strlen(l); i++) {
            if (replacable == l[i]) {
                replaced = m[i];
            }
        }
    } else {
        for (int i = 0; i < strlen(m); i++) {
            if (replacable == m[i]) {
                replaced = l[i];
            }
        }
    }
    return replaced;
}

char* divideString (char originalString[]) {
    char newString[strlen (originalString)];
    strcpy (newString, originalString);
    return newString;
}

void reverseString(char* str, int start, int end) { // [3]
    int front = start;
    int back = end;
    while (front < back) {
        /* This is how you can swap two variables without
        using a temporary one. */
        str[front] = str[front] ^ str[back];
        str[back]  = str[front] ^ str[back];
        str[front] = str[front] ^ str[back];
        ++front;
        --back;
    }
    return;
}

void rotateString(char* str, int k) {
    if (!str || !*str)
        return;
    int len = strlen(str);
    /* Rotating a string by it's length is string itself. */
    k %= len;
    reverseString(str, 0, len-1);
    reverseString(str, 0, k-1);
    reverseString(str, k, len-1);
    return;
}

void antirotateString(char* str, int k) {
    k = (strlen(str) - k);
    if (!str || !*str)
        return;
    int len = strlen(str);
    k %= len;
    reverseString(str, 0, len-1);
    reverseString(str, 0, k-1);
    reverseString(str, k, len-1);
    return;
}

int extractSeed (char originalString[]) {
    int seed = 0;
    for (int i = 0; i < strlen (originalString); i++)
        seed += originalString[i];
    return (seed % strlen (l));
}

void shuffleRandom (int type, char original[]) {
    int index = extractSeed(original);
    char t1[] = "!@#$%^&*()_+=ab1cd2ef3-[]{}\|';:<>,.?/~` gh4ij5kl6mn7op8qr9st0uvwxyzQWERTYUIOPLKJHGFDSAZXCVBNM";
    char t2[] = "bcdefghijklmnopqrstuvwxyza1234567890 !@#$%^&*()_+=-[]{}\|';ABCDEFGHIJKLMNOPQRSTUVWXYZ:<>,.?/~`";
    if (type == 0) {
        rotateString(t1, index);
    } else if (type == 1) {
        antirotateString(t1, index);
    }
    strcpy(l, t1);
    strcpy(m, t2);
}

char* encode (char original[]) {
    shuffleRandom(0, original);
    strcpy (original, divideString (original));
    for (int i = 0; i < strlen(original); i++)
        original[i] = engine (0, original[i]);
    return original;
}

char* decode (char original[]) {
    shuffleRandom(1, original);
    strcpy (original, divideString (original));
    for (int i = 0; i < strlen(original); i++)
        original[i] = engine (1, original[i]);
    return original;
}

void designImplement() {
    //clrscr();
    system ("cls");
    cout << "\n\n     Keeep\n\n\n";
}

void writeLine (char text[]) {
    cout << "    |    " << endl << "    |    " << text << endl << "    |    >>  ";
}

void writeText (char text[]) {
    cout << "    |    " << text << endl;
}

void leaveLine() {
    cout << "    |    " << endl;
}

void message(char text[]) {
    leaveLine();
    writeText(text);
    writeLine("Press any key to continue.");
    getch();
}

void throwError (char text[]) {
    leaveLine();
    cout << "    |    ";
    for (int i = 0; i < (strlen(text) + 12); i++)
        cout << "_";
    cout << endl;
    cout << "    |    |";
    for (int i = 0; i < (strlen(text) + 11); i++)
        cout << " ";
    cout << "|" << endl;
    cout << "    |    |  ERROR: " << text << "  |" << endl;
    cout << "    |    |";
    for (int i = 0; i < (strlen(text) + 11); i++)
        cout << "_";
    cout << "|" << endl;
    leaveLine();
    writeLine("Press any key to continue.");
    getch();
}

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
            writeText("Great! Let's encrypt and add a new record to your Keeep.");
            writeText("What kind of a record are we adding?");
            leaveLine();
            writeText("1.   Password");
            writeText("2.   Credit card number");
            writeText("3.   Other information");
            writeLine("Choose a category: ");
            cin >> category; char a[2];
            designImplement();
            switch (category) {
                case 1:
                    gets (a);
                    writeText("We'll securely add your password to your Keeep now.");
                    leaveLine();
                    writeText("Enter the name of the website or app");
                    writeLine("It can be anything like Facebook or Gmail:");
                    gets (recordName);
                    leaveLine();
                    writeText("Enter the URL of the website or app");
                    writeLine("eg. www.facebook.com");
                    gets (recordContentOther);
                    writeLine("Enter your password:");
                    gets (recordContent);
                    break;
                case 2:
                    gets (a);
                    writeText("We'll securely add your credit card to your Keeep now.");
                    leaveLine();
                    writeText("Enter a name for your card");
                    writeLine("It can be anything like HDFC Mastercard or ICICI Visa:");
                    gets (recordName);
                    writeLine("Enter your card number:");
                    gets (recordContent);
                    leaveLine();
                    writeText("Enter your card CVV");
                    writeLine("It's that 3-digit code at the back:");
                    gets (recordContentOther);
                    break;
                case 3:
                    gets (a);
                    writeText("We'll securely add your information to your Keeep now.");
                    leaveLine();
                    writeText("Enter a name for your record");
                    writeLine("eg. Aadhar number or Social security code:");
                    gets (recordName);
                    writeLine("Enter the code:");
                    gets (recordContent);
                    break;
                default:
                    break;
            }
            encode(recordContent);
            encode(recordContentOther);
        }
        void displayRecord() {
            designImplement();
            cout << "    |    Created at: " << createdAt;
            cout << "    |    Computer name: " << computerName << endl;
            decode(recordContent);
            decode(recordContentOther);
            switch (category) {
                case 1:
                    cout << "    |    Category: Password" << endl;
                    cout << "    |    Website/ app: " << recordName << endl;
                    cout << "    |    URL: " << recordContentOther << endl;
                    cout << "    |    Password: " << recordContent << endl;
                    break;
                case 2:
                    cout << "    |    Category: Credit card" << endl;
                    cout << "    |    Card name: " << recordName << endl;
                    cout << "    |    Card number: " << recordContent << endl;
                    cout << "    |    CVV: " << recordContentOther << endl;
                    break;
                case 3:
                    cout << "    |    Category: Other" << endl;
                    cout << "    |    Record Name: " << recordName << endl;
                    cout << "    |    Password: " << recordContent << endl;
                    break;
                default:
                    break;
            }
        }
};

class user {
    int sudo;
    char username[255];
    public:
        void authenticate(char u[]) {
            strcpy(username, u);
        }
        char* returnName() {
            return username;
        }
        user() {
            sudo = 0;
        }
        void signup() {
            designImplement();
            char signup_username[255];
            char signup_password[255];
            writeLine("Enter your username:");
            cin >> signup_username;
            char tempName[255];
            strcpy(tempName, signup_username);
            strcat(tempName, ".dat");
            ifstream f1;
            f1.open(tempName, ios::in);
            if (!f1.fail()) {
                throwError("An account with that username already exists");
                signup();
            } else {
                writeLine("Enter a password:");
                cin >> signup_password;
                char firstAccount[255];
                strcpy(firstAccount, signup_username);
                strcat(firstAccount, ".dat");
                ofstream f2;
                f2.open(firstAccount, ios::binary|ios::out);
                encryptedRecord A;
                A.addRecord(0, "Keeep", signup_password);
                f2.write((char*)&A, sizeof(A));
                message("Account created successfully");
                authenticate(signup_username);
            }
        }
        void login() {
            designImplement();
            char login_username[255];
            char login_password[255];
            writeLine("Enter your username: ");
            cin >> login_username;
            char tempName[255];
            strcpy(tempName, login_username);
            strcat(tempName, ".dat");
            ifstream f1;
            f1.open(tempName, ios::in);
            if (f1.fail()) {
                throwError("Username not found");
                login();
            } else {
                writeLine("Password:");
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
                   throwError("Incorrect password");
                    login();
                } else {
                    authenticate(login_username);
                }
            }
        }
        void addContent() {
            designImplement();
            ofstream f1;
            char fileName[259];
            strcpy(fileName, username);
            strcat(fileName, ".dat");
            f1.open(fileName, ios::binary|ios::app);
            encryptedRecord A;
            A.insertRecord();
            f1.write((char*)&A, sizeof(A));
            message("Record added successfully");
        }
        void findParticular() {
            writeLine("Enter a record number to view details:");
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
                    leaveLine();
                    A.displayRecord();
                    found++;
                }
            }
            if (found == 0) {
                throwError("No record found");
            }
            writeLine("Press any key to continue:");
            getch();
        }
        void readContent() {
            designImplement();
            writeText("Here are your records: ");
            leaveLine();
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
                    cout << "    |    " << ++records - 1 << ". " << A.returnName() << "\n";
                }
            }
            leaveLine();
            cout << "    |    " << "A total of " << records - 1 << " record were found.\n";
            findParticular();
        }
};

void launchEncrypter() {
    designImplement();
    writeText ("Keeep will now help you encrypt a string of data.  ");
    writeText ("Please enter your string below, and we'll do the rest.");
    encryptChecker: writeLine ("Enter a string: ");
    char userEntered[255]; char a[2]; gets(a);
    gets(userEntered);
    if (strlen(userEntered) <= 3) {
        throwError ("Your string must be at least 4 characters in length");
        goto encryptChecker;
    }
    writeLine ("Encoded string: "); puts (encode (userEntered));
    writeLine ("Decoded string: "); puts (decode (userEntered));
    leaveLine();
    getch();
}

void launchDecrypter() {
    designImplement();
    writeText ("Keeep will now help you decrypt a string of data.  ");
    writeText ("Please enter your string below, and we'll do the rest.");
    encryptChecker: writeLine ("Enter a string: ");
    char userEntered[255]; char a[2]; gets(a);
    gets(userEntered);
    if (strlen(userEntered) <= 3) {
        throwError ("Your string must be at least 4 characters in length");
        goto encryptChecker;
    }
    writeLine ("Encoded string: "); puts (decode (userEntered));
    leaveLine();
    getch();
}

void launchRandomPassword() {
    designImplement();
    int charLength;
    writeText ("Keeep will now generate a random password for you.");
    writeLine ("Enter number of characters for password:");
    cin >> charLength;
    char l[] = "!@#$%^&*()_+=ab1cd2ef3-[]{}\|';:<>,.?/~` gh4ij5kl6mn7op8qr9st0uvwxyzQWERTYUIOPLKJHGFDSAZXCVBNM";
    char randomPassword[charLength];
    srand (time (NULL));
    for (int i = 0; i < charLength; i++) {
        randomPassword[i] = l[rand() % strlen(l)];
    }
    writeLine ("Generated password: "); puts (randomPassword);
    leaveLine();
    getch();
}

int main(void) {

    user A; int u;

    home:   //designImplement();
            writeText("1.   Log in to your Keeep");
            writeText("2.   Sign up for a new Keeep");
            writeText("3.   String encryptor (experimental)");
            writeText("4.   String decryptor (experimental)");
            writeText("5.   Generate a random password (experimental)");
            writeText("99.  Exit saving changes");
            leaveLine();
            writeLine("Enter your choice: ");
            cin >> u;

    switch (u) {
        case 1:
            A.login();
            goto dashboard;
            break;
        case 2:
            A.signup();
            goto dashboard;
            break;
        case 3:
            launchEncrypter();
            break;
        case 4:
            launchDecrypter();
            break;
        case 5:
            launchRandomPassword();
            break;
        case 99:
            return 0;
            break;
        default:
            cout << "Invalid choice. Press any key to try again.";
            getch();
            goto home;
    }

    goto home;

    int n;

    dashboard: designImplement();
               cout << "    |    " << endl << "    |    Hello, " << A.returnName() << "!\n";
               leaveLine();
               writeText("1.   Add a new record");
               writeText("2.   View your records");
               writeText("99.  Log out");
               leaveLine();
               writeLine("Enter your choice: ");
               cin >> n;

    switch (n) {
        case 1:
            A.addContent();
            break;
        case 2:
            A.readContent();
            break;
        case 99:
            goto home;
            break;
        default:
            cout << "Invalid choice. Press any key to try again.";
            getch();
            goto dashboard;
    }

    goto dashboard;

    return 0;

}
