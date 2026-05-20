# Library Management System 

---

# 1. Introduction

The **Library Management Interface** is a console-based application developed using **C++ programming language**.
The system is designed to automate and simplify the management of books, library members, and borrowing transactions.

This software enables librarians to:

* Register books
* Enroll members
* Issue books
* Return books
* Search library catalog
* Display inventory records
* Save and load records from files

The project demonstrates practical implementation of:

* Object-Oriented Programming (OOP)
* File Handling
* Data Persistence
* Dynamic Arrays using STL Vector
* Input Validation
* Time and Date Management

---

# 2. Objectives of the Project

The major objectives are:

* To automate traditional library management operations
* To maintain accurate records of books and members
* To track borrowed and returned books
* To implement secure file storage
* To learn practical OOP implementation in C++
* To create a modular and reusable software system

---

# 3. Technologies Used

| Technology    | Purpose                   |
| ------------- | ------------------------- |
| C++           | Main Programming Language |
| STL Vector    | Dynamic data storage      |
| File Handling | Permanent record storage  |
| StringStream  | Parsing text data         |
| Time Library  | Due date calculations     |
| OOP           | Modular design structure  |

---

# 4. Key Features

---

# 4.1 Book Registration

The system allows librarians to:

* Add books
* Store ISBN
* Store author details
* Generate unique IDs automatically

---

# 4.2 Member Enrollment

Allows:

* New member registration
* Member ID generation
* Email storage

---

# 4.3 Book Issue System

The software:

* Issues books to members
* Prevents duplicate borrowing
* Generates due dates automatically

---

# 4.4 Return Management

Handles:

* Book returns
* Late return detection
* Status synchronization

---

# 4.5 Search Engine

Users can search books by:

* Book title
* Author name

---

# 4.6 Inventory Reports

Displays:

* Complete book inventory
* Membership roster

---

# 4.7 File Persistence

System stores records permanently using:

* books_db.txt
* members_db.txt
* ledgers_db.txt

---

# 5. System Architecture

```text
+------------------------------------------------+
|             USER CONSOLE INTERFACE             |
+------------------------------------------------+
                     |
                     v
+------------------------------------------------+
|              LIBRARY MANAGER CLASS             |
+------------------------------------------------+
      |              |               |
      v              v               v
   BOOKS          MEMBERS        BORROW RECORDS
      |              |               |
      +--------------+---------------+
                     |
                     v
+------------------------------------------------+
|                FILE STORAGE LAYER              |
+------------------------------------------------+
```

---

# 6. OOP Concepts Used

| OOP Concept   | Usage                           |
| ------------- | ------------------------------- |
| Class         | Book, Member, BorrowRecord      |
| Encapsulation | Private data members            |
| Constructors  | Object initialization           |
| Abstraction   | Hidden internal logic           |
| Modularity    | Separate methods for operations |

---

# 7. Class Explanation

---

# 7.1 Book Class

Represents books in library inventory.

---

## Data Members

```cpp
int bookId;
string title;
string author;
string isbn;
bool isIssued;
```

---

## Member Functions

| Function          | Purpose              |
| ----------------- | -------------------- |
| getId()           | Returns book ID      |
| getTitle()        | Returns title        |
| getAuthor()       | Returns author       |
| getIsbn()         | Returns ISBN         |
| getIssuedStatus() | Returns issue state  |
| setIssuedStatus() | Updates issue status |
| displayRow()      | Prints formatted row |

---

# 7.2 Member Class

Represents registered library members.

---

## Data Members

```cpp
int memberId;
string name;
string email;
```

---

# 7.3 BorrowRecord Class

Stores borrowing transaction information.

---

## Data Members

```cpp
int bookId;
int memberId;
time_t issueDate;
time_t dueDate;
bool isReturned;
```

---

# 7.4 LibraryManager Class

Controls the entire application.

Handles:

* Book operations
* Member operations
* Borrow transactions
* Searching
* File operations

---

# 8. File Handling

The project uses text files for permanent storage.

---

## Files Used

| File Name      | Purpose             |
| -------------- | ------------------- |
| books_db.txt   | Stores books        |
| members_db.txt | Stores members      |
| ledgers_db.txt | Stores transactions |

---

# Example Book Database

```text
1001|Harry Potter|J.K Rowling|9780747532743|0
1002|C++ Programming|Bjarne Stroustrup|9780321563842|1
```

---

# Example Member Database

```text
5001|Rahul Sharma|rahul@gmail.com
5002|Priya K|priya@gmail.com
```

---

# Example Ledger Database

```text
1001|5001|1716200000|1717409600|0
```

---

# 9. Input Validation

The program validates:

| Validation                 | Purpose                          |
| -------------------------- | -------------------------------- |
| Empty Input Check          | Prevents blank fields            |
| Integer Validation         | Prevents invalid numeric input   |
| Duplicate Issue Check      | Prevents issuing same book twice |
| Invalid Member Check       | Ensures valid membership         |
| Pipe Character Restriction | Prevents file corruption         |

---

# 10. Program Workflow

---

## Step 1

System loads saved files.

---

## Step 2

Main menu appears.

---

## Step 3

User selects operation.

---

## Step 4

Requested process executes.

---

## Step 5

System updates records dynamically.

---

## Step 6

Data saved before exit.

---

# 11. COMPLETE DETAILED INPUT AND OUTPUT

---

# 11.1 Main Menu

## Output

```text
=========================================
      LIBRARY MANAGEMENT INTERFACE
=========================================

1. Register New Book Asset
2. Enroll New Active Member
3. Issue Book Asset (Loan Transaction)
4. Return Book Asset (Inbound Check-in)
5. Search Catalog (Title / Author)
6. Show Entire Inventory Catalog
7. Show Enrolled Membership Roster
0. Save Configuration & Exit Session

=========================================

Select routing index parameter option:
```

---

# 11.2 Add New Book

## User Input

```text
1
Harry Potter and the Goblet of Fire
J.K Rowling
9780439139601
```

---

## System Output

```text
=== REGISTER NEW BOOK ASSET ===

Enter Book Title :
Harry Potter and the Goblet of Fire

Enter Author Name:
J.K Rowling

Enter ISBN Code:
9780439139601

>> Success:
Book added with tracking System ID: 1001
```

---

# 11.3 Add Another Book

## User Input

```text
1
C++ Data Structures
Bjarne Stroustrup
9780321563842
```

---

## System Output

```text
>> Success:
Book added with tracking System ID: 1002
```

---

# 11.4 Enroll New Member

## User Input

```text
2
Rahul Sharma
rahul@gmail.com
```

---

## System Output

```text
=== REGISTER NEW LIBRARY MEMBER ===

Enter Full Name :
Rahul Sharma

Enter Email Addr:
rahul@gmail.com

>> Success:
Membership account issued card ID: 5001
```

---

# 11.5 Enroll Another Member

## User Input

```text
2
Priya K
priya@gmail.com
```

---

## System Output

```text
>> Success:
Membership account issued card ID: 5002
```

---

# 11.6 Display Book Catalog

## User Input

```text
6
```

---

## System Output

```text
=== INTERNAL REGISTER FILE INVENTORY ===

ID      Title                         Author                   ISBN           Status
-------------------------------------------------------------------------------------

1001    Harry Potter and the Gob...  J.K Rowling              9780439139601 Available
1002    C++ Data Structures          Bjarne Stroustrup        9780321563842 Available
```

---

# 11.7 Display Member Roster

## User Input

```text
7
```

---

## System Output

```text
=== REGISTERED USERS ACTIVE ROSTER ===

Card ID  Full Name                Primary Email Interface Address
-------------------------------------------------------------------

5001     Rahul Sharma             rahul@gmail.com
5002     Priya K                  priya@gmail.com
```

---

# 11.8 Issue Book Successfully

## User Input

```text
3
1001
5001
```

---

## System Output

```text
=== PROCESS BOOK CHECKOUT ===

Enter Target Book ID:
1001

Enter Checking Member ID:
5001

>> Success:
Checkout complete!

Asset Allocated:
"Harry Potter and the Goblet of Fire"

Issued To:
Rahul Sharma

Return Deadline:
2026-06-03
```

---

# 11.9 Attempt to Issue Borrowed Book

## User Input

```text
3
1001
5002
```

---

## System Output

```text
=== PROCESS BOOK CHECKOUT ===

Enter Target Book ID:
1001

>> Error:
Target book is already loaned out.
```

---

# 11.10 Invalid Member ID

## User Input

```text
3
1002
9999
```

---

## System Output

```text
>> Error:
Missing active membership record matching ID 9999
```

---

# 11.11 Search Books by Title

## User Input

```text
5
Harry
```

---

## System Output

```text
=== QUERY CATALOG INDEXES ===

ID      Title                         Author                   ISBN           Status
=====================================================================================

1001    Harry Potter and the Gob...  J.K Rowling              9780439139601 Checked Out
```

---

# 11.12 Search Books by Author

## User Input

```text
5
Bjarne
```

---

## System Output

```text
1002    C++ Data Structures          Bjarne Stroustrup        9780321563842 Available
```

---

# 11.13 Book Not Found Search

## User Input

```text
5
Python
```

---

## System Output

```text
No records match search criterion input.
```

---

# 11.14 Return Book Successfully

## User Input

```text
4
1001
```

---

## System Output

```text
=== PROCESS BOOK RETURN ===

Enter Returned Book ID:
1001

>> Success:
File check-in verified.

Check-in received within the allocated timeline window.
```

---

# 11.15 Late Return Case

## User Input

```text
4
1002
```

---

## System Output

```text
>> Success:
File check-in verified.

[ALERT]:
This transaction is flag-marked LATE.
```

---

# 11.16 Return Already Available Book

## User Input

```text
4
1001
```

---

## System Output

```text
>> Notification:
This item is already marked safe inside internal inventory vaults.
```

---

# 11.17 Exit Application

## User Input

```text
0
```

---

## System Output

```text
>> Storage notification:
Snapshot synchronization tables safely secured onto system disks.

Closing engine tasks context safely.

Core environments dropped.

Goodbye.
```

---

# 12. Advantages of the System

* Simple and easy to use
* Efficient digital record management
* Permanent file storage
* Automatic due-date tracking
* Case-insensitive searching
* Prevents duplicate borrowing
* Structured modular design

---

# 13. Limitations

* Console-based interface only
* No database integration
* No barcode scanning
* No admin authentication
* Single-user environment
* No online access

---

# 14. Future Enhancements

---

# 14.1 Database Integration

Upgrade file handling into:

* MySQL
* PostgreSQL
* MongoDB

---

# 14.2 GUI Development

Create graphical interface using:

* Qt Framework
* JavaFX
* Web dashboard

---

# 14.3 Fine Management System

Automatically:

* Calculate penalties
* Generate payment reports

---

# 14.4 Barcode/RFID Support

Enable:

* Barcode scanners
* RFID book tracking

---

# 14.5 Authentication System

Add:

* Librarian login
* Admin access
* Password encryption

---

# 14.6 Online Reservation

Allow users to:

* Reserve books remotely
* Renew books online

---

# 14.7 Email Notification System

Send:

* Due reminders
* Late return alerts
* Membership notifications

---

# 15. Compilation and Execution

---

# Compile Program

```bash
g++ main.cpp -o library
```

---

# Run Program

## Windows

```bash
library.exe
```

## Linux / Mac

```bash
./library
```

---

# 16. GitHub Commands

---

# Clone Repository

```bash
git clone https://github.com/Jayavardhani05/Library-Management-System.git
```

---

# Move Into Project Directory

```bash
cd Library Management System

```

---

# Initialize Git

```bash
git init
```

---

# Add Files

```bash
git add .
```

---

# Commit Files

```bash
git commit -m "Initial project commit"
```

---

# Connect GitHub Repository

```bash
git remote add origin https://github.com/Jayavardhani05/Library-Management-System.git
```

---

# Push Project

```bash
git branch -M main
git push -u origin main
```

---

# 17. Project Folder Structure

```text
Library-Management-System/
│
├── Library Management System.cpp
└── README.md
```

---

# 18. README.md Description

```md
Library Management System developed using C++ and File Handling.

Features:
- Book registration
- Member enrollment
- Book issue and return
- Catalog searching
- Due date management
- Persistent storage using files
```

---

# 19. Conclusion

The **Library Management Interface** successfully demonstrates how real-world library operations can be implemented using C++ and Object-Oriented Programming concepts.

The project provides:

* Book inventory tracking
* Membership management
* Borrow transaction processing
* File-based persistence
* Search and reporting functionality

This application serves as an excellent beginner-to-intermediate level project for understanding software system design, file handling, and transaction management in C++.
