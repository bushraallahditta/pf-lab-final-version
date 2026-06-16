#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

//====================================================
// CONSTANTS
//====================================================
const int INITIAL_SIZE = 10;
const int GROWTH_FACTOR = 2;
const int MAX_FIR_FIELDS = 5;
const int MAX_PROPERTY_FIELDS = 6;
const int MAX_MEDICAL_FIELDS = 5;

//====================================================
// GLOBAL DATA STRUCTURES - ALL DYNAMIC WITH DOUBLE POINTERS (NO TRIPLE POINTERS)
//====================================================

// 1. CITIZEN records - Dynamic 2D array using double pointer
char** citizenRecords = nullptr;
int citizenCount = 0;
int citizenCapacity = 0;

// 2. FIR records - Dynamic arrays with double pointers
int** firNumericData = nullptr;
char** firTextData = nullptr;
int firCount = 0;
int firCapacity = 0;

// 3. PROPERTY records - Double pointer (2D array, no triple pointer)
char** propertyRecords = nullptr;
int propertyCount = 0;
int propertyCapacity = 0;

// 4. MEDICAL records - Double pointer (2D array, no triple pointer)
char** medicalRecords = nullptr;
int medicalCount = 0;
int medicalCapacity = 0;

// 5. VOTING records - Dynamic 2D array
int** votingRecords = nullptr;
int votingCount = 0;
int votingCapacity = 0;

//====================================================
// FORWARD DECLARATIONS
//====================================================
void expandCitizenCapacity();
void shrinkCitizenCapacity();
void deepCopyCitizen(char** dest, char** src, int size);

//====================================================
// DEEP COPY FUNCTIONS
//====================================================

void deepCopyCitizen(char** dest, char** src, int size) {
    for (int i = 0; i < size; i++) {
        if (src[i] != nullptr) {
            dest[i] = new char[500];
            strcpy(dest[i], src[i]);
        }
        else {
            dest[i] = nullptr;
        }
    }
}

void deepCopyFIR(int** destNum, char** destText, int** srcNum, char** srcText, int size) {
    for (int i = 0; i < size; i++) {
        destNum[i] = new int[3];
        for (int j = 0; j < 3; j++) {
            destNum[i][j] = srcNum[i][j];
        }

        destText[i] = new char[500];
        strcpy(destText[i], srcText[i]);
    }
}

//====================================================
// AUTO-GROWING FUNCTIONS
//====================================================

void expandCitizenCapacity() {
    int newCapacity = (citizenCapacity == 0) ? INITIAL_SIZE : citizenCapacity * GROWTH_FACTOR;

    char** newRecords = new char* [newCapacity];

    for (int i = 0; i < newCapacity; i++) {
        newRecords[i] = nullptr;
    }

    for (int i = 0; i < citizenCount; i++) {
        newRecords[i] = new char[500];
        strcpy(newRecords[i], citizenRecords[i]);
    }

    if (citizenRecords != nullptr) {
        for (int i = 0; i < citizenCount; i++) {
            delete[] citizenRecords[i];
        }
        delete[] citizenRecords;
    }

    citizenRecords = newRecords;
    citizenCapacity = newCapacity;

    cout << "\n[System] Citizen capacity expanded to " << newCapacity << endl;
}

void shrinkCitizenCapacity() {
    if (citizenCapacity <= INITIAL_SIZE) return;
    if (citizenCount > citizenCapacity / 2) return;

    int newCapacity = citizenCapacity / GROWTH_FACTOR;
    if (newCapacity < INITIAL_SIZE) newCapacity = INITIAL_SIZE;

    char** newRecords = new char* [newCapacity];

    for (int i = 0; i < newCapacity; i++) {
        newRecords[i] = nullptr;
    }

    for (int i = 0; i < citizenCount; i++) {
        newRecords[i] = new char[500];
        strcpy(newRecords[i], citizenRecords[i]);
    }

    if (citizenRecords != nullptr) {
        for (int i = 0; i < citizenCount; i++) {
            delete[] citizenRecords[i];
        }
        delete[] citizenRecords;
    }

    citizenRecords = newRecords;
    citizenCapacity = newCapacity;

    cout << "\n[System] Citizen capacity shrunk to " << newCapacity << endl;
}

void expandFIRCapacity() {
    int newCapacity = (firCapacity == 0) ? INITIAL_SIZE : firCapacity * GROWTH_FACTOR;

    int** newNumericData = new int* [newCapacity];
    char** newTextData = new char* [newCapacity];

    for (int i = 0; i < newCapacity; i++) {
        newNumericData[i] = nullptr;
        newTextData[i] = nullptr;
    }

    for (int i = 0; i < firCount; i++) {
        newNumericData[i] = new int[3];
        for (int j = 0; j < 3; j++) {
            newNumericData[i][j] = firNumericData[i][j];
        }

        newTextData[i] = new char[500];
        strcpy(newTextData[i], firTextData[i]);
    }

    if (firNumericData != nullptr) {
        for (int i = 0; i < firCount; i++) {
            delete[] firNumericData[i];
            delete[] firTextData[i];
        }
        delete[] firNumericData;
        delete[] firTextData;
    }

    firNumericData = newNumericData;
    firTextData = newTextData;
    firCapacity = newCapacity;

    cout << "\n[System] FIR capacity expanded to " << newCapacity << endl;
}

void shrinkFIRCapacity() {
    if (firCapacity <= INITIAL_SIZE) return;
    if (firCount > firCapacity / 2) return;

    int newCapacity = firCapacity / GROWTH_FACTOR;
    if (newCapacity < INITIAL_SIZE) newCapacity = INITIAL_SIZE;

    int** newNumericData = new int* [newCapacity];
    char** newTextData = new char* [newCapacity];

    for (int i = 0; i < newCapacity; i++) {
        newNumericData[i] = nullptr;
        newTextData[i] = nullptr;
    }

    for (int i = 0; i < firCount; i++) {
        newNumericData[i] = new int[3];
        for (int j = 0; j < 3; j++) {
            newNumericData[i][j] = firNumericData[i][j];
        }

        newTextData[i] = new char[500];
        strcpy(newTextData[i], firTextData[i]);
    }

    if (firNumericData != nullptr) {
        for (int i = 0; i < firCount; i++) {
            delete[] firNumericData[i];
            delete[] firTextData[i];
        }
        delete[] firNumericData;
        delete[] firTextData;
    }

    firNumericData = newNumericData;
    firTextData = newTextData;
    firCapacity = newCapacity;

    cout << "\n[System] FIR capacity shrunk to " << newCapacity << endl;
}

void expandPropertyCapacity() {
    int newCapacity = (propertyCapacity == 0) ? INITIAL_SIZE : propertyCapacity * GROWTH_FACTOR;

    char** newRecords = new char* [newCapacity];

    for (int i = 0; i < newCapacity; i++) {
        newRecords[i] = nullptr;
    }

    for (int i = 0; i < propertyCount; i++) {
        newRecords[i] = new char[500];
        strcpy(newRecords[i], propertyRecords[i]);
    }

    if (propertyRecords != nullptr) {
        for (int i = 0; i < propertyCount; i++) {
            delete[] propertyRecords[i];
        }
        delete[] propertyRecords;
    }

    propertyRecords = newRecords;
    propertyCapacity = newCapacity;

    cout << "\n[System] Property capacity expanded to " << newCapacity << endl;
}

void shrinkPropertyCapacity() {
    if (propertyCapacity <= INITIAL_SIZE) return;
    if (propertyCount > propertyCapacity / 2) return;

    int newCapacity = propertyCapacity / GROWTH_FACTOR;
    if (newCapacity < INITIAL_SIZE) newCapacity = INITIAL_SIZE;

    char** newRecords = new char* [newCapacity];

    for (int i = 0; i < newCapacity; i++) {
        newRecords[i] = nullptr;
    }

    for (int i = 0; i < propertyCount; i++) {
        newRecords[i] = new char[500];
        strcpy(newRecords[i], propertyRecords[i]);
    }

    if (propertyRecords != nullptr) {
        for (int i = 0; i < propertyCount; i++) {
            delete[] propertyRecords[i];
        }
        delete[] propertyRecords;
    }

    propertyRecords = newRecords;
    propertyCapacity = newCapacity;

    cout << "\n[System] Property capacity shrunk to " << newCapacity << endl;
}

void expandMedicalCapacity() {
    int newCapacity = (medicalCapacity == 0) ? INITIAL_SIZE : medicalCapacity * GROWTH_FACTOR;

    char** newRecords = new char* [newCapacity];

    for (int i = 0; i < newCapacity; i++) {
        newRecords[i] = nullptr;
    }

    for (int i = 0; i < medicalCount; i++) {
        newRecords[i] = new char[500];
        strcpy(newRecords[i], medicalRecords[i]);
    }

    if (medicalRecords != nullptr) {
        for (int i = 0; i < medicalCount; i++) {
            delete[] medicalRecords[i];
        }
        delete[] medicalRecords;
    }

    medicalRecords = newRecords;
    medicalCapacity = newCapacity;

    cout << "\n[System] Medical capacity expanded to " << newCapacity << endl;
}

void shrinkMedicalCapacity() {
    if (medicalCapacity <= INITIAL_SIZE) return;
    if (medicalCount > medicalCapacity / 2) return;

    int newCapacity = medicalCapacity / GROWTH_FACTOR;
    if (newCapacity < INITIAL_SIZE) newCapacity = INITIAL_SIZE;

    char** newRecords = new char* [newCapacity];

    for (int i = 0; i < newCapacity; i++) {
        newRecords[i] = nullptr;
    }

    for (int i = 0; i < medicalCount; i++) {
        newRecords[i] = new char[500];
        strcpy(newRecords[i], medicalRecords[i]);
    }

    if (medicalRecords != nullptr) {
        for (int i = 0; i < medicalCount; i++) {
            delete[] medicalRecords[i];
        }
        delete[] medicalRecords;
    }

    medicalRecords = newRecords;
    medicalCapacity = newCapacity;

    cout << "\n[System] Medical capacity shrunk to " << newCapacity << endl;
}

void expandVotingCapacity() {
    int newCapacity = (votingCapacity == 0) ? INITIAL_SIZE : votingCapacity * GROWTH_FACTOR;
    if (newCapacity > 50) newCapacity = 50;

    int** newRecords = new int* [newCapacity];

    for (int i = 0; i < newCapacity; i++) {
        newRecords[i] = nullptr;
    }

    for (int i = 0; i < votingCount; i++) {
        newRecords[i] = new int[3];
        for (int j = 0; j < 3; j++) {
            newRecords[i][j] = votingRecords[i][j];
        }
    }

    if (votingRecords != nullptr) {
        for (int i = 0; i < votingCount; i++) {
            delete[] votingRecords[i];
        }
        delete[] votingRecords;
    }

    votingRecords = newRecords;
    votingCapacity = newCapacity;

    cout << "\n[System] Voting capacity expanded to " << newCapacity << endl;
}

//====================================================
// VALIDATION FUNCTIONS
//====================================================

bool isValidCNIC(const char* cnic) {
    int len = 0;
    while (cnic[len] != '\0') len++;

    if (len != 13) return false;

    for (int i = 0; i < len; i++) {
        if (cnic[i] < '0' || cnic[i] > '9') return false;
    }
    return true;
}

bool isDuplicateCNIC(const char* cnic, int currentIndex = -1) {
    for (int i = 0; i < citizenCount; i++) {
        if (i != currentIndex && citizenRecords[i] != nullptr) {
            if (strcmp(citizenRecords[i] + 100, cnic) == 0) return true;
        }
    }

    for (int i = 0; i < propertyCount; i++) {
        if (propertyRecords[i] != nullptr) {
            char storedCNIC[100];
            strcpy(storedCNIC, propertyRecords[i] + 100);
            if (strcmp(storedCNIC, cnic) == 0) return true;
        }
    }

    for (int i = 0; i < medicalCount; i++) {
        if (medicalRecords[i] != nullptr) {
            char storedCNIC[100];
            strcpy(storedCNIC, medicalRecords[i] + 100);
            if (strcmp(storedCNIC, cnic) == 0) return true;
        }
    }

    return false;
}

bool isDuplicateFIRID(int firID, int currentIndex = -1) {
    for (int i = 0; i < firCount; i++) {
        if (i != currentIndex && firNumericData[i] != nullptr) {
            if (firNumericData[i][0] == firID) return true;
        }
    }
    return false;
}

bool isDuplicatePropertyID(const char* propID, int currentIndex = -1) {
    for (int i = 0; i < propertyCount; i++) {
        if (i != currentIndex && propertyRecords[i] != nullptr) {
            if (strcmp(propertyRecords[i], propID) == 0) return true;
        }
    }
    return false;
}

bool isValidAge(int age) {
    return (age >= 0 && age <= 150);
}

bool isValidYear(int year) {
    return (year >= 1900 && year <= 2026);
}

bool isValidPhone(const char* phone) {
    int len = 0;
    while (phone[len] != '\0') len++;

    if (len < 10 || len > 15) return false;

    for (int i = 0; i < len; i++) {
        if ((phone[i] < '0' || phone[i] > '9') && phone[i] != '+' && phone[i] != '-') {
            return false;
        }
    }
    return true;
}

bool isValidName(const char* name) {
    int len = 0;
    while (name[len] != '\0') len++;

    if (len < 2 || len > 50) return false;

    for (int i = 0; i < len; i++) {
        if ((name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z') && name[i] != ' ' && name[i] != '.') {
            return false;
        }
    }
    return true;
}

//====================================================
// UTILITY FUNCTIONS
//====================================================

void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

void waitForUser() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

//====================================================
// CITIZEN MODULE WITH DYNAMIC MEMORY
//====================================================

void initializeCitizenRecords() {
    citizenCount = 0;
    citizenCapacity = 0;
    citizenRecords = nullptr;
}

void addCitizen() {
    if (citizenCount >= citizenCapacity) {
        expandCitizenCapacity();
    }

    cout << "\n===== ADD CITIZEN =====\n";

    char name[100], cnic[100], address[200], phone[100];

    do {
        cout << "Enter Name (2-50 characters, letters only): ";
        cin.getline(name, 100);
        if (!isValidName(name)) {
            cout << "Invalid name!\n";
        }
    } while (!isValidName(name));

    do {
        cout << "Enter CNIC (13 digits): ";
        cin.getline(cnic, 100);
        if (!isValidCNIC(cnic)) {
            cout << "Invalid CNIC! CNIC must be exactly 13 digits.\n";
        }
        else if (isDuplicateCNIC(cnic)) {
            cout << "Duplicate CNIC! This CNIC is already registered.\n";
        }
    } while (!isValidCNIC(cnic) || isDuplicateCNIC(cnic));

    cout << "Enter Address: ";
    cin.getline(address, 200);

    do {
        cout << "Enter Phone (10-15 digits): ";
        cin.getline(phone, 100);
        if (!isValidPhone(phone)) {
            cout << "Invalid phone number!\n";
        }
    } while (!isValidPhone(phone));

    citizenRecords[citizenCount] = new char[500];
    strcpy(citizenRecords[citizenCount], name);
    strcpy(citizenRecords[citizenCount] + 100, cnic);
    strcpy(citizenRecords[citizenCount] + 200, address);
    strcpy(citizenRecords[citizenCount] + 300, phone);

    ofstream file("citizens.txt", ios::app);
    if (file.is_open()) {
        file << name << "|" << cnic << "|" << address << "|" << phone << endl;
        file.close();
    }

    citizenCount++;
    cout << "\nCitizen Added Successfully!\n";
    waitForUser();
}

void displayCitizens() {
    if (citizenCount == 0) {
        cout << "\nNo Citizen Records Found!\n";
        waitForUser();
        return;
    }

    cout << "\n===== CITIZEN RECORDS =====\n";
    cout << "Current Capacity: " << citizenCapacity << " | Records: " << citizenCount << "\n";

    for (int i = 0; i < citizenCount; i++) {
        cout << "\nCitizen #" << i + 1;
        cout << "\nName    : " << citizenRecords[i];
        cout << "\nCNIC    : " << (citizenRecords[i] + 100);
        cout << "\nAddress : " << (citizenRecords[i] + 200);
        cout << "\nPhone   : " << (citizenRecords[i] + 300);
        cout << "\n-------------------------\n";
    }
    waitForUser();
}

void searchCitizen() {
    char searchCNIC[100];
    cout << "\nEnter CNIC to search: ";
    cin >> searchCNIC;
    clearInputBuffer();

    bool found = false;
    for (int i = 0; i < citizenCount; i++) {
        if (citizenRecords[i] != nullptr && strcmp(citizenRecords[i] + 100, searchCNIC) == 0) {
            cout << "\nCitizen Found!\n";
            cout << "\nName    : " << citizenRecords[i];
            cout << "\nCNIC    : " << (citizenRecords[i] + 100);
            cout << "\nAddress : " << (citizenRecords[i] + 200);
            cout << "\nPhone   : " << (citizenRecords[i] + 300);
            found = true;
            waitForUser();
            return;
        }
    }

    if (!found) {
        cout << "\nCitizen Not Found!\n";
        waitForUser();
    }
}

void updateCitizen() {
    char searchCNIC[100];
    cout << "\nEnter CNIC To Update: ";
    cin >> searchCNIC;
    clearInputBuffer();

    bool found = false;
    for (int i = 0; i < citizenCount; i++) {
        if (citizenRecords[i] != nullptr && strcmp(citizenRecords[i] + 100, searchCNIC) == 0) {
            found = true;

            char name[100], address[200], phone[100];

            do {
                cout << "New Name (2-50 characters): ";
                cin.getline(name, 100);
                if (!isValidName(name)) {
                    cout << "Invalid name!\n";
                }
            } while (!isValidName(name));

            cout << "New Address: ";
            cin.getline(address, 200);

            do {
                cout << "New Phone (10-15 digits): ";
                cin.getline(phone, 100);
                if (!isValidPhone(phone)) {
                    cout << "Invalid phone number!\n";
                }
            } while (!isValidPhone(phone));

            strcpy(citizenRecords[i], name);
            strcpy(citizenRecords[i] + 200, address);
            strcpy(citizenRecords[i] + 300, phone);

            cout << "\nRecord Updated Successfully!\n";
            waitForUser();
            return;
        }
    }

    if (!found) {
        cout << "\nCitizen Not Found!\n";
        waitForUser();
    }
}

void deleteCitizen() {
    char searchCNIC[100];
    cout << "\nEnter CNIC To Delete: ";
    cin >> searchCNIC;
    clearInputBuffer();

    bool found = false;
    for (int i = 0; i < citizenCount; i++) {
        if (citizenRecords[i] != nullptr && strcmp(citizenRecords[i] + 100, searchCNIC) == 0) {
            found = true;

            delete[] citizenRecords[i];

            for (int j = i; j < citizenCount - 1; j++) {
                citizenRecords[j] = citizenRecords[j + 1];
            }

            citizenCount--;

            shrinkCitizenCapacity();

            cout << "\nCitizen Deleted Successfully!\n";
            waitForUser();
            return;
        }
    }

    if (!found) {
        cout << "\nCitizen Not Found!\n";
        waitForUser();
    }
}

void citizenMenu() {
    int choice;

    do {
        cout << "\n\n===== CITIZEN MODULE =====";
        cout << "\n1. Add Citizen";
        cout << "\n2. Search Citizen";
        cout << "\n3. Display Citizens";
        cout << "\n4. Update Citizen";
        cout << "\n5. Delete Citizen";
        cout << "\n6. Back";
        cout << "\nEnter Choice: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: addCitizen(); break;
        case 2: searchCitizen(); break;
        case 3: displayCitizens(); break;
        case 4: updateCitizen(); break;
        case 5: deleteCitizen(); break;
        case 6: cout << "\nReturning to Main Menu...\n"; break;
        default: cout << "\nInvalid Choice!\n"; waitForUser();
        }
    } while (choice != 6);
}

//====================================================
// FIR MODULE WITH DYNAMIC MEMORY (NO SPRINTF, NO STRTOK)
//====================================================

void initializeFIRArrays() {
    firCount = 0;
    firCapacity = 0;
    firNumericData = nullptr;
    firTextData = nullptr;
}

void addFIR() {
    if (firCount >= firCapacity) {
        expandFIRCapacity();
    }

    cout << "\n===== ADD FIR =====\n";

    int firID, year, status;

    do {
        cout << "Enter FIR ID: ";
        cin >> firID;
        if (isDuplicateFIRID(firID)) {
            cout << "Duplicate FIR ID! This ID already exists.\n";
        }
    } while (isDuplicateFIRID(firID));

    do {
        cout << "Enter Year: ";
        cin >> year;
        if (!isValidYear(year)) {
            cout << "Invalid year! Year should be between 1900 and 2026.\n";
        }
    } while (!isValidYear(year));

    clearInputBuffer();

    char name[100], cnic[100], crimeType[100], location[100], date[100];

    do {
        cout << "Complainant Name: ";
        cin.getline(name, 100);
        if (!isValidName(name)) {
            cout << "Invalid name!\n";
        }
    } while (!isValidName(name));

    do {
        cout << "CNIC (13 digits): ";
        cin.getline(cnic, 100);
        if (!isValidCNIC(cnic)) {
            cout << "Invalid CNIC! CNIC must be exactly 13 digits.\n";
        }
    } while (!isValidCNIC(cnic));

    cout << "Crime Type: ";
    cin.getline(crimeType, 100);

    cout << "Crime Location: ";
    cin.getline(location, 100);

    cout << "Date (DD/MM/YYYY): ";
    cin.getline(date, 100);

    do {
        cout << "Status (1-Solved/0-Pending): ";
        cin >> status;
        if (status != 0 && status != 1) {
            cout << "Invalid status! Please enter 0 or 1.\n";
        }
    } while (status != 0 && status != 1);
    clearInputBuffer();

    firNumericData[firCount] = new int[3];
    firNumericData[firCount][0] = firID;
    firNumericData[firCount][1] = year;
    firNumericData[firCount][2] = status;

    firTextData[firCount] = new char[500];

    strcpy(firTextData[firCount], name);
    strcpy(firTextData[firCount] + 100, cnic);
    strcpy(firTextData[firCount] + 200, crimeType);
    strcpy(firTextData[firCount] + 300, location);
    strcpy(firTextData[firCount] + 400, date);

    firCount++;
    cout << "\nFIR Added Successfully!\n";
    waitForUser();
}

void displayFIRs() {
    if (firCount == 0) {
        cout << "\nNo FIR Records Available!\n";
        waitForUser();
        return;
    }

    cout << "\n===== FIR RECORDS =====\n";
    cout << "Current Capacity: " << firCapacity << " | Records: " << firCount << "\n";

    for (int i = 0; i < firCount; i++) {
        cout << "\n================================";
        cout << "\nFIR ID      : " << firNumericData[i][0];
        cout << "\nYear        : " << firNumericData[i][1];
        cout << "\nName        : " << firTextData[i];
        cout << "\nCNIC        : " << (firTextData[i] + 100);
        cout << "\nCrime Type  : " << (firTextData[i] + 200);
        cout << "\nLocation    : " << (firTextData[i] + 300);
        cout << "\nDate        : " << (firTextData[i] + 400);
        cout << "\nStatus      : " << (firNumericData[i][2] == 1 ? "Solved" : "Pending");
        cout << "\n================================\n";
    }
    waitForUser();
}

void searchFIR() {
    int searchID;
    cout << "\nEnter FIR ID: ";
    cin >> searchID;
    clearInputBuffer();

    bool found = false;
    for (int i = 0; i < firCount; i++) {
        if (firNumericData[i] != nullptr && firNumericData[i][0] == searchID) {
            found = true;

            cout << "\nRecord Found!\n";
            cout << "\nFIR ID      : " << firNumericData[i][0];
            cout << "\nYear        : " << firNumericData[i][1];
            cout << "\nName        : " << firTextData[i];
            cout << "\nCNIC        : " << (firTextData[i] + 100);
            cout << "\nCrime Type  : " << (firTextData[i] + 200);
            cout << "\nLocation    : " << (firTextData[i] + 300);
            cout << "\nDate        : " << (firTextData[i] + 400);
            cout << "\nStatus      : " << (firNumericData[i][2] == 1 ? "Solved" : "Pending");
            waitForUser();
            return;
        }
    }

    if (!found) {
        cout << "\nFIR Not Found!\n";
        waitForUser();
    }
}

void updateFIRStatus() {
    int searchID;
    cout << "\nEnter FIR ID: ";
    cin >> searchID;
    clearInputBuffer();

    bool found = false;
    for (int i = 0; i < firCount; i++) {
        if (firNumericData[i] != nullptr && firNumericData[i][0] == searchID) {
            found = true;
            int status;
            do {
                cout << "Enter New Status (1-Solved/0-Pending): ";
                cin >> status;
                if (status != 0 && status != 1) {
                    cout << "Invalid status!\n";
                }
            } while (status != 0 && status != 1);
            firNumericData[i][2] = status;
            clearInputBuffer();
            cout << "\nStatus Updated Successfully!\n";
            waitForUser();
            return;
        }
    }

    if (!found) {
        cout << "\nFIR Not Found!\n";
        waitForUser();
    }
}

void deleteFIR() {
    int searchID;
    cout << "\nEnter FIR ID: ";
    cin >> searchID;
    clearInputBuffer();

    bool found = false;
    for (int i = 0; i < firCount; i++) {
        if (firNumericData[i] != nullptr && firNumericData[i][0] == searchID) {
            found = true;

            delete[] firNumericData[i];
            delete[] firTextData[i];

            for (int j = i; j < firCount - 1; j++) {
                firNumericData[j] = firNumericData[j + 1];
                firTextData[j] = firTextData[j + 1];
            }

            firCount--;

            shrinkFIRCapacity();

            cout << "\nFIR Deleted Successfully!\n";
            waitForUser();
            return;
        }
    }

    if (!found) {
        cout << "\nFIR Not Found!\n";
        waitForUser();
    }
}

void showFIRStatistics() {
    if (firCount == 0) {
        cout << "\nNo FIR Records Available!\n";
        waitForUser();
        return;
    }

    int solved = 0;
    int pending = 0;

    for (int i = 0; i < firCount; i++) {
        if (firNumericData[i][2] == 1) solved++;
        else pending++;
    }

    cout << "\n===== FIR STATISTICS =====";
    cout << "\nTotal FIRs   : " << firCount;
    cout << "\nSolved FIRs  : " << solved;
    cout << "\nPending FIRs : " << pending;
    cout << endl;
    waitForUser();
}

void firModule() {
    int choice;

    do {
        cout << "\n\n===== FIR RECORD MODULE =====";
        cout << "\n1. Add FIR";
        cout << "\n2. Display FIRs";
        cout << "\n3. Search FIR";
        cout << "\n4. Update FIR Status";
        cout << "\n5. Delete FIR";
        cout << "\n6. FIR Statistics";
        cout << "\n0. Back";
        cout << "\nEnter Choice: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: addFIR(); break;
        case 2: displayFIRs(); break;
        case 3: searchFIR(); break;
        case 4: updateFIRStatus(); break;
        case 5: deleteFIR(); break;
        case 6: showFIRStatistics(); break;
        case 0: cout << "\nReturning to Main Menu...\n"; break;
        default: cout << "\nInvalid Choice!\n"; waitForUser();
        }
    } while (choice != 0);
}

//====================================================
// PROPERTY MODULE WITH DYNAMIC MEMORY (NO TRIPLE POINTER)
//====================================================

void initializePropertyRecords() {
    propertyCount = 0;
    propertyCapacity = 0;
    propertyRecords = nullptr;
}

void addProperty() {
    if (propertyCount >= propertyCapacity) {
        expandPropertyCapacity();
    }

    cout << "\n===== ADD PROPERTY =====\n";

    char propID[100], owner[100], cnic[100], type[100], address[200], status[100];

    do {
        cout << "Property ID: ";
        cin.getline(propID, 100);
        if (isDuplicatePropertyID(propID)) {
            cout << "Duplicate Property ID! This ID already exists.\n";
        }
    } while (isDuplicatePropertyID(propID));

    do {
        cout << "Owner Name: ";
        cin.getline(owner, 100);
        if (!isValidName(owner)) {
            cout << "Invalid owner name!\n";
        }
    } while (!isValidName(owner));

    do {
        cout << "Owner CNIC (13 digits): ";
        cin.getline(cnic, 100);
        if (!isValidCNIC(cnic)) {
            cout << "Invalid CNIC! CNIC must be exactly 13 digits.\n";
        }
    } while (!isValidCNIC(cnic));

    cout << "Property Type (House/Plot/Shop): ";
    cin.getline(type, 100);

    cout << "Property Address: ";
    cin.getline(address, 200);

    cout << "Registration Status (pending/done): ";
    cin.getline(status, 100);

    propertyRecords[propertyCount] = new char[500];

    strcpy(propertyRecords[propertyCount], propID);
    strcpy(propertyRecords[propertyCount] + 100, owner);
    strcpy(propertyRecords[propertyCount] + 200, cnic);
    strcpy(propertyRecords[propertyCount] + 300, type);
    strcpy(propertyRecords[propertyCount] + 400, address);
    strcpy(propertyRecords[propertyCount] + 450, status);

    propertyCount++;
    cout << "\nProperty Added Successfully!\n";
    waitForUser();
}

void displayProperties() {
    if (propertyCount == 0) {
        cout << "\nNo Property Records Found!\n";
        waitForUser();
        return;
    }

    cout << "\n===== PROPERTY RECORDS =====\n";
    cout << "Current Capacity: " << propertyCapacity << " | Records: " << propertyCount << "\n";

    for (int i = 0; i < propertyCount; i++) {
        cout << "\n============================";
        cout << "\nProperty ID     : " << propertyRecords[i];
        cout << "\nOwner Name      : " << (propertyRecords[i] + 100);
        cout << "\nOwner CNIC      : " << (propertyRecords[i] + 200);
        cout << "\nType            : " << (propertyRecords[i] + 300);
        cout << "\nAddress         : " << (propertyRecords[i] + 400);
        cout << "\nStatus          : " << (propertyRecords[i] + 450);
        cout << "\n============================\n";
    }
    waitForUser();
}

void searchProperty() {
    char id[100];
    cout << "\nEnter Property ID: ";
    cin >> id;
    clearInputBuffer();

    bool found = false;
    for (int i = 0; i < propertyCount; i++) {
        if (propertyRecords[i] != nullptr && strcmp(propertyRecords[i], id) == 0) {
            found = true;
            cout << "\nProperty Found!\n";
            cout << "\nOwner Name : " << (propertyRecords[i] + 100);
            cout << "\nCNIC       : " << (propertyRecords[i] + 200);
            cout << "\nType       : " << (propertyRecords[i] + 300);
            cout << "\nAddress    : " << (propertyRecords[i] + 400);
            cout << "\nStatus     : " << (propertyRecords[i] + 450);
            waitForUser();
            return;
        }
    }

    if (!found) {
        cout << "\nProperty Not Found!\n";
        waitForUser();
    }
}

void deleteProperty() {
    char id[100];
    cout << "\nEnter Property ID: ";
    cin >> id;
    clearInputBuffer();

    bool found = false;
    for (int i = 0; i < propertyCount; i++) {
        if (propertyRecords[i] != nullptr && strcmp(propertyRecords[i], id) == 0) {
            found = true;

            delete[] propertyRecords[i];

            for (int j = i; j < propertyCount - 1; j++) {
                propertyRecords[j] = propertyRecords[j + 1];
            }

            propertyCount--;

            shrinkPropertyCapacity();

            cout << "\nProperty Deleted Successfully!\n";
            waitForUser();
            return;
        }
    }

    if (!found) {
        cout << "\nProperty Not Found!\n";
        waitForUser();
    }
}

void propertyMenu() {
    int choice;

    do {
        cout << "\n\n===== PROPERTY RECORDS =====";
        cout << "\n1. Add Property";
        cout << "\n2. Display Properties";
        cout << "\n3. Search Property";
        cout << "\n4. Delete Property";
        cout << "\n5. Back";
        cout << "\nEnter Choice: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: addProperty(); break;
        case 2: displayProperties(); break;
        case 3: searchProperty(); break;
        case 4: deleteProperty(); break;
        case 5: cout << "\nReturning to Main Menu...\n"; break;
        default: cout << "\nInvalid Choice!\n"; waitForUser();
        }
    } while (choice != 5);
}

//====================================================
// VOTING MODULE WITH DYNAMIC MEMORY
//====================================================

void initializeVotingRecords() {
    votingCount = 0;
    votingCapacity = 0;
    votingRecords = nullptr;
}

void addSingleVoter() {
    if (votingCount >= votingCapacity) {
        expandVotingCapacity();
    }

    char name[100];
    int age, year;

    cout << "\n===== VOTER REGISTRATION =====\n";

    do {
        cout << "Enter Voter Name: ";
        cin.getline(name, 100);
        if (!isValidName(name)) {
            cout << "Invalid name!\n";
        }
    } while (!isValidName(name));

    do {
        cout << "Enter Age (0-150): ";
        cin >> age;
        if (!isValidAge(age)) {
            cout << "Invalid age! Age must be between 0 and 150.\n";
        }
    } while (!isValidAge(age));

    do {
        cout << "Enter Year (1900-2026): ";
        cin >> year;
        if (!isValidYear(year)) {
            cout << "Invalid year!\n";
        }
    } while (!isValidYear(year));
    clearInputBuffer();

    votingRecords[votingCount] = new int[3];
    votingRecords[votingCount][0] = age;
    votingRecords[votingCount][1] = (age >= 18) ? 1 : 0;
    votingRecords[votingCount][2] = year;

    cout << "\n========== RESULT ==========\n";
    cout << "Voter Name : " << name << endl;
    cout << "Age        : " << age << endl;

    if (age >= 18) {
        cout << "\nSTATUS: ELIGIBLE For Voting\n";
    }
    else {
        cout << "\nSTATUS: NOT ELIGIBLE For Voting\n";
        cout << "Minimum Age Required = 18 Years\n";
    }

    votingCount++;
    cout << "\nVoter #" << votingCount << " Registered Successfully!\n";
    waitForUser();
}

void addMultipleVoters() {
    int numVoters;

    cout << "\n===== REGISTER MULTIPLE VOTERS =====\n";
    cout << "How many voters do you want to enter? ";
    cin >> numVoters;
    clearInputBuffer();

    if (numVoters <= 0) {
        cout << "\nInvalid number! Please enter at least 1 voter.\n";
        waitForUser();
        return;
    }

    cout << "\n========================================\n";
    cout << "Enter details for " << numVoters << " voters:\n";
    cout << "========================================\n";

    int eligibleCount = 0;
    int nonEligibleCount = 0;

    for (int i = 0; i < numVoters; i++) {
        if (votingCount >= votingCapacity) {
            expandVotingCapacity();
        }

        char name[100];
        int age, year;

        cout << "\n--- VOTER #" << (votingCount + 1) << " ---\n";

        do {
            cout << "Name: ";
            cin.getline(name, 100);
            if (!isValidName(name)) {
                cout << "Invalid name!\n";
            }
        } while (!isValidName(name));

        do {
            cout << "Age (0-150): ";
            cin >> age;
            if (!isValidAge(age)) {
                cout << "Invalid age!\n";
            }
        } while (!isValidAge(age));

        do {
            cout << "Year (1900-2026): ";
            cin >> year;
            if (!isValidYear(year)) {
                cout << "Invalid year!\n";
            }
        } while (!isValidYear(year));
        clearInputBuffer();

        votingRecords[votingCount] = new int[3];
        votingRecords[votingCount][0] = age;
        votingRecords[votingCount][1] = (age >= 18) ? 1 : 0;
        votingRecords[votingCount][2] = year;

        cout << "\nResult for " << name << ": ";
        if (age >= 18) {
            cout << "ELIGIBLE\n";
            eligibleCount++;
        }
        else {
            cout << "NOT ELIGIBLE (Need 18+ years)\n";
            nonEligibleCount++;
        }

        votingCount++;
    }

    cout << "\n========================================\n";
    cout << "SUMMARY FOR " << numVoters << " VOTERS:\n";
    cout << "========================================\n";
    cout << "Total Voters Entered : " << numVoters << endl;
    cout << "Eligible Voters      : " << eligibleCount << endl;
    cout << "Non-Eligible Voters  : " << nonEligibleCount << endl;
    cout << "========================================\n";

    waitForUser();
}

void displayVotingStatistics() {
    if (votingCount == 0) {
        cout << "\nNo Voters Registered Yet!\n";
        waitForUser();
        return;
    }

    cout << "\n===== VOTING STATISTICS =====\n";
    cout << "Current Capacity: " << votingCapacity << " | Records: " << votingCount << "\n";
    cout << "Total Voters Registered: " << votingCount << endl;

    int eligible = 0;

    for (int i = 0; i < votingCount; i++) {
        if (votingRecords[i][1] == 1) eligible++;
    }

    int nonEligible = votingCount - eligible;

    if (votingCount > 0) {
        cout << "\n--- VOTING SUMMARY ---\n";
        cout << "Eligible Voters  : " << eligible << " ("
            << (eligible * 100 / votingCount) << "%)\n";
        cout << "Non-Eligible     : " << nonEligible << " ("
            << (nonEligible * 100 / votingCount) << "%)\n";
    }

    cout << "\n--- DETAILED VOTER LIST ---\n";
    for (int i = 0; i < votingCount; i++) {
        cout << "Voter #" << (i + 1) << ": Age=" << votingRecords[i][0]
            << ", Status=" << (votingRecords[i][1] ? "ELIGIBLE" : "NOT ELIGIBLE")
            << ", Year=" << votingRecords[i][2] << endl;
    }

    waitForUser();
}

void searchVoter() {
    if (votingCount == 0) {
        cout << "\nNo Voters Registered Yet!\n";
        waitForUser();
        return;
    }

    int searchAge;
    int searchYear;
    int choice;

    cout << "\n===== SEARCH VOTER =====\n";
    cout << "1. Search by Age\n";
    cout << "2. Search by Year\n";
    cout << "3. Search by Eligibility Status\n";
    cout << "Enter choice: ";
    cin >> choice;
    clearInputBuffer();

    switch (choice) {
    case 1: {
        cout << "Enter Age to search: ";
        cin >> searchAge;
        clearInputBuffer();

        bool found = false;
        cout << "\n--- Voters with Age " << searchAge << " ---\n";
        for (int i = 0; i < votingCount; i++) {
            if (votingRecords[i][0] == searchAge) {
                cout << "Voter #" << (i + 1) << ": Age=" << votingRecords[i][0]
                    << ", Status=" << (votingRecords[i][1] ? "ELIGIBLE" : "NOT ELIGIBLE")
                    << ", Year=" << votingRecords[i][2] << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No voters found with age " << searchAge << endl;
        }
        break;
    }

    case 2: {
        cout << "Enter Year to search: ";
        cin >> searchYear;
        clearInputBuffer();

        bool found = false;
        cout << "\n--- Voters from Year " << searchYear << " ---\n";
        for (int i = 0; i < votingCount; i++) {
            if (votingRecords[i][2] == searchYear) {
                cout << "Voter #" << (i + 1) << ": Age=" << votingRecords[i][0]
                    << ", Status=" << (votingRecords[i][1] ? "ELIGIBLE" : "NOT ELIGIBLE")
                    << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No voters found from year " << searchYear << endl;
        }
        break;
    }

    case 3: {
        int statusChoice;
        cout << "1. Eligible Voters\n";
        cout << "2. Non-Eligible Voters\n";
        cout << "Enter choice: ";
        cin >> statusChoice;
        clearInputBuffer();

        bool searchEligible = (statusChoice == 1);
        bool found = false;

        cout << "\n--- " << (searchEligible ? "ELIGIBLE" : "NON-ELIGIBLE") << " VOTERS ---\n";
        for (int i = 0; i < votingCount; i++) {
            if ((votingRecords[i][1] == 1) == searchEligible) {
                cout << "Voter #" << (i + 1) << ": Age=" << votingRecords[i][0]
                    << ", Year=" << votingRecords[i][2] << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No " << (searchEligible ? "eligible" : "non-eligible") << " voters found!\n";
        }
        break;
    }

    default:
        cout << "\nInvalid choice!\n";
    }

    waitForUser();
}

void deleteVoter() {
    if (votingCount == 0) {
        cout << "\nNo Voters Registered Yet!\n";
        waitForUser();
        return;
    }

    int voterNum;

    cout << "\n--- CURRENT VOTER LIST ---\n";
    for (int i = 0; i < votingCount; i++) {
        cout << "Voter #" << (i + 1) << ": Age=" << votingRecords[i][0]
            << ", Status=" << (votingRecords[i][1] ? "ELIGIBLE" : "NOT ELIGIBLE")
            << ", Year=" << votingRecords[i][2] << endl;
    }

    cout << "\n===== DELETE VOTER =====\n";
    cout << "Enter Voter Number to delete (1-" << votingCount << "): ";
    cin >> voterNum;
    clearInputBuffer();

    if (voterNum < 1 || voterNum > votingCount) {
        cout << "\nInvalid Voter Number!\n";
        waitForUser();
        return;
    }

    delete[] votingRecords[voterNum - 1];

    for (int i = voterNum - 1; i < votingCount - 1; i++) {
        votingRecords[i] = votingRecords[i + 1];
    }

    votingCount--;

    cout << "\nVoter #" << voterNum << " Deleted Successfully!\n";
    waitForUser();
}

void votingMenu() {
    int choice;

    do {
        cout << "\n\n===== VOTING MANAGEMENT MODULE =====";
        cout << "\n1. Register Single Voter";
        cout << "\n2. Register Multiple Voters (Bulk Entry)";
        cout << "\n3. Display Voting Statistics";
        cout << "\n4. Search Voters";
        cout << "\n5. Delete Voter";
        cout << "\n6. Back to Main Menu";
        cout << "\n\nEnter Choice: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: addSingleVoter(); break;
        case 2: addMultipleVoters(); break;
        case 3: displayVotingStatistics(); break;
        case 4: searchVoter(); break;
        case 5: deleteVoter(); break;
        case 6: cout << "\nReturning to Main Menu...\n"; break;
        default: cout << "\nInvalid Choice!\n"; waitForUser();
        }
    } while (choice != 6);
}

//====================================================
// MEDICAL MODULE WITH DYNAMIC MEMORY (NO TRIPLE POINTER)
//====================================================

void initializeMedicalRecords() {
    medicalCount = 0;
    medicalCapacity = 0;
    medicalRecords = nullptr;
}

void addMedicalRecord() {
    if (medicalCount >= medicalCapacity) {
        expandMedicalCapacity();
    }

    cout << "\n===== ADD MEDICAL RECORD =====\n";

    char name[100], cnic[100], disease[100], doctor[100], date[100];

    do {
        cout << "Patient Name: ";
        cin.getline(name, 100);
        if (!isValidName(name)) {
            cout << "Invalid name!\n";
        }
    } while (!isValidName(name));

    do {
        cout << "CNIC (13 digits): ";
        cin.getline(cnic, 100);
        if (!isValidCNIC(cnic)) {
            cout << "Invalid CNIC! CNIC must be exactly 13 digits.\n";
        }
    } while (!isValidCNIC(cnic));

    cout << "Disease: ";
    cin.getline(disease, 100);

    do {
        cout << "Doctor Name: ";
        cin.getline(doctor, 100);
        if (!isValidName(doctor)) {
            cout << "Invalid doctor name!\n";
        }
    } while (!isValidName(doctor));

    cout << "Report Date (DD/MM/YYYY): ";
    cin.getline(date, 100);

    medicalRecords[medicalCount] = new char[500];

    strcpy(medicalRecords[medicalCount], name);
    strcpy(medicalRecords[medicalCount] + 100, cnic);
    strcpy(medicalRecords[medicalCount] + 200, disease);
    strcpy(medicalRecords[medicalCount] + 300, doctor);
    strcpy(medicalRecords[medicalCount] + 400, date);

    medicalCount++;
    cout << "\nMedical Record Added Successfully!\n";
    waitForUser();
}

void displayMedicalRecords() {
    if (medicalCount == 0) {
        cout << "\nNo Medical Records Found!\n";
        waitForUser();
        return;
    }

    cout << "\n===== MEDICAL RECORDS =====\n";
    cout << "Current Capacity: " << medicalCapacity << " | Records: " << medicalCount << "\n";

    for (int i = 0; i < medicalCount; i++) {
        cout << "\n================================";
        cout << "\nPatient Name : " << medicalRecords[i];
        cout << "\nCNIC         : " << (medicalRecords[i] + 100);
        cout << "\nDisease      : " << (medicalRecords[i] + 200);
        cout << "\nDoctor Name  : " << (medicalRecords[i] + 300);
        cout << "\nReport Date  : " << (medicalRecords[i] + 400);
        cout << "\n================================\n";
    }
    waitForUser();
}

void searchMedicalRecord() {
    char searchCNIC[100];
    cout << "\nEnter CNIC: ";
    cin >> searchCNIC;
    clearInputBuffer();

    bool found = false;
    for (int i = 0; i < medicalCount; i++) {
        if (medicalRecords[i] != nullptr && strcmp(medicalRecords[i] + 100, searchCNIC) == 0) {
            found = true;
            cout << "\nRecord Found!\n";
            cout << "\nPatient Name : " << medicalRecords[i];
            cout << "\nDisease      : " << (medicalRecords[i] + 200);
            cout << "\nDoctor Name  : " << (medicalRecords[i] + 300);
            cout << "\nReport Date  : " << (medicalRecords[i] + 400);
            waitForUser();
            return;
        }
    }

    if (!found) {
        cout << "\nRecord Not Found!\n";
        waitForUser();
    }
}

void deleteMedicalRecord() {
    char searchCNIC[100];
    cout << "\nEnter CNIC: ";
    cin >> searchCNIC;
    clearInputBuffer();

    bool found = false;
    for (int i = 0; i < medicalCount; i++) {
        if (medicalRecords[i] != nullptr && strcmp(medicalRecords[i] + 100, searchCNIC) == 0) {
            found = true;

            delete[] medicalRecords[i];

            for (int j = i; j < medicalCount - 1; j++) {
                medicalRecords[j] = medicalRecords[j + 1];
            }

            medicalCount--;

            shrinkMedicalCapacity();

            cout << "\nMedical Record Deleted Successfully!\n";
            waitForUser();
            return;
        }
    }

    if (!found) {
        cout << "\nRecord Not Found!\n";
        waitForUser();
    }
}

void medicalMenu() {
    int choice;

    do {
        cout << "\n\n===== MEDICAL RECORDS =====";
        cout << "\n1. Add Medical Record";
        cout << "\n2. Display Medical Records";
        cout << "\n3. Search Medical Record";
        cout << "\n4. Delete Medical Record";
        cout << "\n5. Back";
        cout << "\nEnter Choice: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: addMedicalRecord(); break;
        case 2: displayMedicalRecords(); break;
        case 3: searchMedicalRecord(); break;
        case 4: deleteMedicalRecord(); break;
        case 5: cout << "\nReturning to Main Menu...\n"; break;
        default: cout << "\nInvalid Choice!\n"; waitForUser();
        }
    } while (choice != 5);
}

//====================================================
// CLEANUP FUNCTION - PREVENT MEMORY LEAKS
//====================================================

void cleanupMemory() {
    if (citizenRecords != nullptr) {
        for (int i = 0; i < citizenCount; i++) {
            delete[] citizenRecords[i];
        }
        delete[] citizenRecords;
        citizenRecords = nullptr;
    }

    if (firNumericData != nullptr) {
        for (int i = 0; i < firCount; i++) {
            delete[] firNumericData[i];
            delete[] firTextData[i];
        }
        delete[] firNumericData;
        delete[] firTextData;
        firNumericData = nullptr;
        firTextData = nullptr;
    }

    if (propertyRecords != nullptr) {
        for (int i = 0; i < propertyCount; i++) {
            delete[] propertyRecords[i];
        }
        delete[] propertyRecords;
        propertyRecords = nullptr;
    }

    if (medicalRecords != nullptr) {
        for (int i = 0; i < medicalCount; i++) {
            delete[] medicalRecords[i];
        }
        delete[] medicalRecords;
        medicalRecords = nullptr;
    }

    if (votingRecords != nullptr) {
        for (int i = 0; i < votingCount; i++) {
            delete[] votingRecords[i];
        }
        delete[] votingRecords;
        votingRecords = nullptr;
    }

    cout << "\n[System] All memory cleaned up successfully!\n";
}

//====================================================
// MAIN FUNCTION
//====================================================

int main() {
    initializeCitizenRecords();
    initializeFIRArrays();
    initializePropertyRecords();
    initializeMedicalRecords();
    initializeVotingRecords();

    int choice;

    do {
        cout << "\n\n====================================";
        cout << "\n SMART CITY MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Citizen Records (Dynamic Memory)";
        cout << "\n2. FIR Records (Dynamic Memory)";
        cout << "\n3. Property Records (Dynamic Memory)";
        cout << "\n4. Voting Management (Dynamic Memory)";
        cout << "\n5. Medical Records (Dynamic Memory)";
        cout << "\n6. Exit";
        cout << "\n\nEnter Choice: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: citizenMenu(); break;
        case 2: firModule(); break;
        case 3: propertyMenu(); break;
        case 4: votingMenu(); break;
        case 5: medicalMenu(); break;
        case 6:
            cout << "\nExiting System...\n";
            cleanupMemory();
            break;
        default: cout << "\nInvalid Choice!\n"; waitForUser();
        }
    } while (choice != 6);

    return 0;
}       