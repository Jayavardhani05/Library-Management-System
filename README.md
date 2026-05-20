# Inventory Management System

---

# 1. Introduction

The **StockGuard Inventory Management System** is a console-based retail inventory tracking application developed using **C++** programming language.

The project is designed to manage retail product inventories efficiently by providing functionalities such as:

* Product registration
* Point-of-sale transaction handling
* Inventory searching
* Low stock alerts
* Product deletion
* File-based permanent storage

The system simulates a real-world inventory management environment used in:

* Retail stores
* Warehouses
* Supermarkets
* Department stores
* Distribution centers

This project demonstrates practical implementation of:

* Object-Oriented Programming (OOP)
* File Handling
* Inventory Tracking Logic
* Barcode Validation (UPC-A)
* Transaction Logging
* Dynamic Data Structures

---

# 2. Objectives of the Project

The main objectives of this project are:

* To build a complete inventory management system
* To implement retail product tracking logic
* To understand file handling in C++
* To simulate barcode-based product systems
* To perform stock monitoring operations
* To develop real-world business management logic

---

# 3. Technologies Used

| Technology    | Purpose                         |
| ------------- | ------------------------------- |
| C++           | Core Programming Language       |
| STL Vector    | Dynamic storage                 |
| File Handling | Persistent data storage         |
| OOP Concepts  | Class-based modular programming |
| StringStream  | Data parsing                    |
| Time Library  | Timestamp generation            |

---

# 4. Core Features of the System

---

# 4.1 Add New Product

The system allows:

* Product registration
* UPC validation
* Retail price setup
* Stock quantity assignment

### Product Details Stored

* UPC
* Product Name
* Category
* Cost Price
* Retail Price
* Stock Quantity
* Reorder Threshold

---

# 4.2 POS Sales Transaction

The Point-of-Sale system allows:

* Product barcode scanning
* Sales processing
* Automatic stock deduction
* Sales history recording

---

# 4.3 Inventory Search

Users can:

* Search by product name
* Search by category

---

# 4.4 Low Stock Alert System

The system identifies:

* Products below reorder threshold
* Items needing replenishment

---

# 4.5 Product Deletion

Allows:

* Safe removal of obsolete products
* Soft deletion mechanism

---

# 4.6 File Saving and Loading

Stores:

* Inventory records
* Transaction history

---

# 5. System Architecture

```text
+------------------------------------------------+
|              USER INTERFACE MENU               |
+------------------------------------------------+
                     |
                     v
+------------------------------------------------+
|             INVENTORY SYSTEM CLASS             |
+------------------------------------------------+
   |        |          |         |         |
   v        v          v         v         v
 Add      Search     Sales    Reports   Delete
 Product  Product   System    Alerts    Product
                     |
                     v
+------------------------------------------------+
| inventory_sheet.txt / sales_history.txt        |
+------------------------------------------------+
```

---

# 6. Object-Oriented Programming Concepts Used

| OOP Concept   | Usage                                  |
| ------------- | -------------------------------------- |
| Class         | Product, Transaction, InventorySystem  |
| Encapsulation | Private data members                   |
| Constructors  | Product and transaction initialization |
| Abstraction   | Business logic hidden inside methods   |
| Modularity    | Separate functions for operations      |

---

# 7. Class Explanation

---

# 7.1 Product Class

Represents individual retail products.

---

## Data Members

```cpp
string upc;
string name;
string category;
double costPrice;
double retailPrice;
int stockQuantity;
int reorderPoint;
bool isDeleted;
```

---

## Member Functions

| Function           | Purpose                |
| ------------------ | ---------------------- |
| getUPC()           | Returns UPC            |
| getName()          | Returns product name   |
| getCategory()      | Returns category       |
| getRetailPrice()   | Returns selling price  |
| setStockQuantity() | Updates stock          |
| needsReorder()     | Checks low stock       |
| toString()         | Formats display output |

---

# 7.2 Transaction Class

Represents sales transactions.

---

## Data Members

```cpp
string transactionId;
string upc;
int quantitySold;
double unitPrice;
string timestamp;
```

---

# 7.3 InventorySystem Class

Handles:

* Product management
* Sales management
* File handling
* Search operations
* Reports

---

# 8. UPC-A Barcode Validation

The project validates:

* 12-digit UPC-A codes
* Barcode checksum correctness

---

# Example Valid UPC

```text
036000291452
```

---

# Validation Logic

The system:

* Calculates odd/even digit sums
* Computes check digit
* Verifies barcode authenticity

---

# 9. File Handling

The system uses:

| File                | Purpose                   |
| ------------------- | ------------------------- |
| inventory_sheet.txt | Stores products           |
| sales_history.txt   | Stores sales transactions |

---

# Example Inventory File

```text
036000291452|Laptop|Electronics|45000|55000|20|5
123456789012|Keyboard|Accessories|500|900|50|10
```

---

# Example Transaction File

```text
TXN1000|036000291452|2|55000|2026-05-20 10:45
```

---

# 10. Input Validation

The system validates:

| Validation       | Description                 |
| ---------------- | --------------------------- |
| UPC Validation   | Checks barcode authenticity |
| Empty Inputs     | Prevents blank names        |
| Price Validation | Rejects invalid prices      |
| Stock Validation | Prevents negative stock     |
| Menu Validation  | Handles wrong menu choices  |

---

# 11. Program Workflow

---

## Step 1

System loads saved inventory.

---

## Step 2

Main menu is displayed.

---

## Step 3

User selects operation.

---

## Step 4

Requested operation executes.

---

## Step 5

Inventory updates dynamically.

---

## Step 6

Data saved into files.

---

# 12. COMPLETE DETAILED INPUT AND OUTPUT

---

# 12.1 Main Menu

## Output

```text
=========================================
     STOCKGUARD INVENTORY SYSTEMS
=========================================
1.  Add New Retail Product Asset
2.  Scan & Log POS Sales Transaction
3.  Dynamic Stock Search Engine Query
4.  Print Master Asset Catalog Sheet
5.  Generate Low Stock Alert Metrics
6.  Purge Obsolete Core Product SKU
7.  Commit Local Cache Changes to Disk
8.  Reload System Master Log Data Files
0.  Safely Close Session Terminal Pipeline
=========================================

Process Option Routing Request Selection:
```

---

# 12.2 Add New Product

## User Input

```text
1
036000291452
Gaming Laptop
Electronics
45000
55000
20
5
```

---

## System Output

```text
=== REGISTER NEW PRODUCT INVENTORY ===

Enter 12-Digit UPC:
036000291452

Enter Product Name:
Gaming Laptop

Enter Category Group:
Electronics

Enter Wholesale/Cost Price ($):
45000

Enter Target Retail Price ($):
55000

Enter Initial Stock Level (0-5000):
20

Enter Reorder Warning Threshold Level (1-100):
5

SKU item 'Gaming Laptop' registered seamlessly into current system tracking.
```

---

# 12.3 Invalid UPC Entry

## User Input

```text
1
123456789000
```

---

## System Output

```text
=== REGISTER NEW PRODUCT INVENTORY ===

Enter 12-Digit UPC:
123456789000

Invalid UPC Checksum!

Hint: Must be exactly 12 digits matching standard barcode metrics.

Please try again.
```

---

# 12.4 Add Another Product

## User Input

```text
1
042100005264
Mechanical Keyboard
Accessories
1500
2500
50
10
```

---

## System Output

```text
SKU item 'Mechanical Keyboard'
registered seamlessly into current system tracking.
```

---

# 12.5 Display All Inventory

## User Input

```text
4
```

---

## System Output

```text
=== SYSTEM SHEET MASTER OVERVIEW INVENTORY ===

UPC           Item Name            Category       Retail    Stock
-----------------------------------------------------------------------

036000291452  Gaming Laptop        Electronics    $55000    20
042100005264  Mechanical Keyboard  Accessories    $2500     50
```

---

# 12.6 Search Inventory

## User Input

```text
3
Electronics
```

---

## System Output

```text
=== INVENTORY QUERY SEARCH ===

Query string (Name/Category):
Electronics

UPC           Item Name            Category       Retail    Stock
=======================================================================

036000291452  Gaming Laptop        Electronics    $55000    20
```

---

# 12.7 Search Product by Name

## User Input

```text
3
Keyboard
```

---

## System Output

```text
UPC           Item Name            Category       Retail    Stock
=======================================================================

042100005264  Mechanical Keyboard  Accessories    $2500     50
```

---

# 12.8 Product Not Found Search

## User Input

```text
3
Mobile
```

---

## System Output

```text
No specific retail inventory targets fit context filter details.
```

---

# 12.9 Process Sales Transaction

## User Input

```text
2
036000291452
2
```

---

## System Output

```text
=== PROCESS RETAIL CASH POINT SALE ===

Scan Item UPC:
036000291452

Discovered: Gaming Laptop | Available units: 20

Enter Quantity to Purchase (1-20):
2

Sale processed cleanly.

Total Due: $110000.00
```

---

# 12.10 Low Stock Warning Sale

## User Input

```text
2
036000291452
18
```

---

## System Output

```text
Sale processed cleanly.

Total Due: $990000.00

[WARNING]:
Running critically low on 'Gaming Laptop' stock items.
```

---

# 12.11 Out of Stock Scenario

## User Input

```text
2
036000291452
1
```

---

## System Output

```text
Operation aborted:
'Gaming Laptop' is completely out of stock!
```

---

# 12.12 Generate Low Stock Report

## User Input

```text
5
```

---

## System Output

```text
=== CRITICAL LOW REORDER SYSTEM DATA REPORT ===

UPC           Item Name            Category       Retail    Current Stock
-----------------------------------------------------------------------

036000291452  Gaming Laptop        Electronics    $55000    0
[Needs 15 replenishment units]
```

---

# 12.13 Delete Product

## User Input

```text
6
042100005264
```

---

## System Output

```text
Provide target UPC data line sequence to clear tracking reference:

042100005264

Tracking data line for element item
'Mechanical Keyboard'
set to safe drop state.
```

---

# 12.14 Save Data to Disk

## User Input

```text
7
```

---

## System Output

```text
File streaming pipelines finalized.

Data safe storage state verified.
```

---

# 12.15 Reload Data Files

## User Input

```text
8
```

---

## System Output

```text
Data persistence structures mapped to localized memory pools successfully.
```

---

# 12.16 Exit Application

## User Input

```text
0
```

---

## System Output

```text
Session environment context destruction sequence complete.

Exiting.
```

---

# 13. Advantages of the System

* Fast inventory tracking
* Barcode validation support
* Dynamic stock monitoring
* Sales history tracking
* Automatic low stock alerts
* Persistent file storage
* Beginner-friendly implementation

---

# 14. Limitations of the System

* No graphical interface
* No database integration
* Single-user operation
* No cloud synchronization
* No employee authentication
* No invoice printing

---

# 15. Future Enhancements

---

# 15.1 Database Integration

Replace text files with:

* MySQL
* MongoDB
* PostgreSQL

---

# 15.2 Barcode Scanner Integration

Add:

* Real barcode scanner support
* QR code inventory tracking

---

# 15.3 Billing System

Generate:

* Customer invoices
* GST bills
* Receipt printing

---

# 15.4 Authentication System

Add:

* Admin login
* Employee accounts
* Password protection

---

# 15.5 GUI Dashboard

Develop graphical software using:

* Qt Framework
* Electron
* Web Dashboard

---

# 15.6 Sales Analytics

Implement:

* Revenue reports
* Best-selling products
* Profit calculations

---

# 15.7 Cloud Storage

Enable:

* Online inventory sync
* Multi-branch inventory access

---

# 16. GitHub Commands

---

# Clone Repository

```bash
git clone https://github.com/Jayavardhani05/Library-Management-System.git
```
---

# Navigate to Folder

```bash
cd Library-Management-System

```

---

# Compile Program

```bash
g++ main.cpp -o inventory
```

---

# Run Program

## Windows

```bash
inventory.exe
```

## Linux / Mac

```bash
./inventory
```

---

# 17. Git Commands for Uploading

---

## Initialize Git

```bash
git init
```

---

## Add Files

```bash
git add .
```

---

## Commit Changes

```bash
git commit -m "Initial commit"
```

---

## Add Remote Repository

```bash
git remote add origin https://github.com/Jayavardhani05/Library-Management-System.git
```

---

## Push Repository

```bash
git branch -M main
git push -u origin main
```

---

# 18. Folder Structure

```text
Inventory-Management-System/
│
├── main.cpp
├── inventory_sheet.txt
├── sales_history.txt
├── README.md
└── .gitignore
```

---

# 19. README.md Short Description

```md
A console-based Inventory Management System built using C++ and File Handling.

The system supports:
- Product registration
- UPC barcode validation
- POS sales transactions
- Inventory search
- Low stock alerts
- Persistent file storage
```

---

# 20. Conclusion

The **StockGuard Inventory Management System** successfully demonstrates how modern inventory and retail tracking systems can be implemented using C++ and file handling concepts.

The project effectively combines:

* Object-Oriented Programming
* Barcode validation
* Inventory control logic
* Sales transaction management
* File persistence mechanisms

This system serves as a strong foundation for developing advanced retail management software and provides practical exposure to real-world inventory tracking operations.
