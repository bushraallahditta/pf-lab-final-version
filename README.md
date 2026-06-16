# pf-lab-final-version
# Integrated Civic Records Management System

## Overview

The Integrated Civic Records Management System is a C++ application designed to manage multiple categories of government and civic records through a unified platform. The system supports citizen records, FIR records, property records, medical records, and voting records while demonstrating advanced concepts of dynamic memory management and file handling.

The project implements dynamic arrays using double pointers, automatic capacity expansion and shrinking, deep copy operations, and persistent storage through text files.

## Features

### Citizen Record Management

* Add citizen records
* View citizen information
* Update existing records
* Delete records
* Search citizen data

### FIR Record Management

* Register FIR records
* Store numeric and textual FIR information separately
* Search FIR records
* Update FIR information
* Delete FIR records

### Property Management

* Property registration
* Ownership tracking
* Property updates
* Property searching

### Medical Record Management

* Store medical information
* Update health records
* Search medical records

### Voting Record Management

* Maintain voting information
* Track participation records
* Update voting details

## Technical Concepts

The project demonstrates the following concepts:

* Dynamic Memory Allocation
* Double Pointer Data Structures
* Deep Copy Mechanisms
* Auto-Growing Arrays
* Auto-Shrinking Arrays
* File Handling
* Data Validation
* Record Management Systems

## Memory Management Strategy

Initial Capacity: 10 Records

Growth Factor: 2

Expansion occurs when:

```cpp
recordCount == capacity
```

Shrinkage occurs when:

```cpp
recordCount < capacity / 2
```

and

```cpp
capacity > INITIAL_SIZE
```

## Data Structures

### Citizen Records

```cpp
char** citizenRecords;
```

### FIR Records

```cpp
int** firNumericData;
char** firTextData;
```

### Property Records

```cpp
char** propertyRecords;
```

### Medical Records

```cpp
char** medicalRecords;
```

### Voting Records

```cpp
char** votingRecords;
```

## Project Structure

```text
Project/
│
├── pf_lab_final_version.cpp
├── citizens.txt
├── fir.txt
├── property.txt
├── medical.txt
├── voting.txt
└── README.md
```

## Compilation

### GCC

```bash
g++ -std=c++11 pf_lab_final_version.cpp -o civic_records
```

### Clang

```bash
clang++ -std=c++11 pf_lab_final_version.cpp -o civic_records
```

### MSVC

```bash
cl /std:c++latest pf_lab_final_version.cpp
```

## Running the Application

Linux and macOS:

```bash
./civic_records
```

Windows:

```bash
civic_records.exe
```

## Data Persistence

The system stores records in plain text files:

| File Name    | Purpose          |
| ------------ | ---------------- |
| citizens.txt | Citizen Records  |
| fir.txt      | FIR Records      |
| property.txt | Property Records |
| medical.txt  | Medical Records  |
| voting.txt   | Voting Records   |

## Complexity Analysis

| Operation       | Time Complexity |
| --------------- | --------------- |
| Add Record      | O(1) Amortized  |
| Search Record   | O(n)            |
| Update Record   | O(n)            |
| Delete Record   | O(n)            |
| Save Records    | O(n)            |
| Load Records    | O(n)            |
| Expand Capacity | O(n)            |
| Shrink Capacity | O(n)            |

## Limitations

* Single-user application
* Plain text file storage
* Linear search implementation
* Fixed field size limitations
* No database integration
* No authentication mechanism

## Future Improvements

* SQLite or MySQL integration
* Authentication and authorization
* Data encryption
* Search indexing
* Audit logging
* Web-based interface
* Advanced reporting
* Backup and recovery system

## Educational Objectives

This project demonstrates practical implementation of:

* Dynamic memory management
* Advanced pointer manipulation
* Two-dimensional dynamic arrays
* File input and output operations
* Record management systems
* Scalable data structure design

## License

This project is provided for educational and learning purposes.
