# Library-Management-System

1. Introduction

The StockGuard Inventory Management System is a console-based application developed using C++ that manages retail inventory efficiently. The system maintains product information, sales transactions, inventory tracking, and stock monitoring.

The project is designed to automate inventory-related tasks such as:

Adding new products
Searching inventory
Processing sales transactions
Monitoring low-stock products
Removing obsolete products
Saving and loading inventory data

The application implements Object-Oriented Programming (OOP) concepts and file handling mechanisms to ensure permanent data storage and maintain data consistency.

The project simulates real-world retail inventory systems used in supermarkets, warehouses, and retail businesses.

2. Objectives of the Project

The objectives of the Inventory Management System are:

To understand Object-Oriented Programming concepts
To implement inventory tracking mechanisms
To manage retail products efficiently
To perform sales transaction management
To use file handling for permanent storage
To understand data validation techniques
3. Technologies Used
Technology	Purpose
C++	Core programming language
File Handling	Permanent data storage
Vectors	Dynamic storage of products
String Streams	Data parsing
OOP	Encapsulation and modularity
STL Algorithms	Searching and manipulation
4. Features of the System
4.1 Product Registration

The system allows users to:

Add new products
Assign UPC code
Specify category
Set pricing information
Set stock quantity
Set reorder threshold

Validation includes:

UPC validation
Empty field checking
Duplicate product detection
Quantity range checking
4.2 Point of Sale (POS) Transaction

Users can:

Scan product UPC
Enter quantity purchased
Generate sales records
Automatically reduce stock
4.3 Inventory Search

Users can search inventory using:

Product Name
Category
4.4 Inventory Catalog

Displays:

UPC
Product Name
Category
Retail Price
Stock Quantity
4.5 Low Stock Monitoring

Automatically identifies:

Products below reorder threshold
Products requiring replenishment
4.6 Product Deletion

Allows:

Safe removal of obsolete products
Soft deletion using status flag
4.7 Data Persistence

Inventory and sales history are stored in:

inventory_sheet.txt
sales_history.txt
5. System Architecture
+--------------------------------+
|         User Interface         |
+--------------------------------+
               |
               v
+--------------------------------+
|       Inventory System         |
+--------------------------------+
      |       |         |
      v       v         v
 Product  Transaction  Reports
      |
      v
+--------------------------------+
|       File Storage System      |
| inventory_sheet.txt            |
| sales_history.txt              |
+--------------------------------+
6. Classes Used in the System
6.1 Product Class

Represents product information.

Data Members
string upc;
string name;
string category;
double costPrice;
double retailPrice;
int stockQuantity;
int reorderPoint;
bool isDeleted;
Functions
Function	Purpose
getUPC()	Returns UPC
getName()	Returns product name
getCategory()	Returns category
getCostPrice()	Returns cost
getRetailPrice()	Returns selling price
getStockQuantity()	Returns stock quantity
setStockQuantity()	Updates quantity
setDeleted()	Marks deleted
needsReorder()	Checks stock status
6.2 Transaction Class

Stores sales transaction details.

Data Members
string transactionId;
string upc;
int quantitySold;
double unitPrice;
string timestamp;
Functions
Function	Purpose
getTransactionId()	Returns transaction ID
getUPC()	Returns UPC
getQuantitySold()	Returns quantity sold
getTotalRevenue()	Calculates revenue
getTimestamp()	Returns time
6.3 InventorySystem Class

Controls the complete inventory operations.

Functions include:

Function	Purpose
addProduct()	Add product
registerSale()	Process sales
searchInventory()	Search products
displayAllInventory()	Display products
displayLowStockReport()	Low stock report
deleteProduct()	Delete product
saveData()	Save files
loadData()	Load files

7. File Handling

Two files are used:

Product Storage
inventory_sheet.txt

Example:

123456789012|Milk|Dairy|35|50|120|10
987654321098|Bread|Bakery|20|30|75|5
Transaction Storage
sales_history.txt

Example:

TXN1000|123456789012|3|50|2026-05-20 12:30
TXN1001|987654321098|2|30|2026-05-20 12:45
8. Validation Mechanisms

The system validates:

Validation Type	Description
UPC Validation	Verifies 12-digit UPC
Empty Strings	Rejects blank values
Price Validation	Limits price range
Quantity Validation	Restricts stock values
Duplicate UPC	Prevents duplicates
9. Program Workflow
Step 1

Load existing inventory data

↓

Step 2

Display main menu

↓

Step 3

User selects operation

↓

Step 4

Perform requested task

↓

Step 5

Update inventory data

↓

Step 6

Save updated records

↓

Step 7

Return to menu

10. Complete Detailed Input and Output
10.1 Main Menu
Output
=========================================
     STOCKGUARD INVENTORY SYSTEMS
=========================================
1. Add New Retail Product Asset
2. Scan & Log POS Sales Transaction
3. Dynamic Stock Search Engine Query
4. Print Master Asset Catalog Sheet
5. Generate Low Stock Alert Metrics
6. Purge Obsolete Core Product SKU
7. Commit Local Cache Changes to Disk
8. Reload System Master Log Data Files
0. Safely Close Session Terminal Pipeline
=========================================

Process Option Routing Request Selection:
10.2 Add New Product
Input
1
123456789012
Milk
Dairy
35
50
100
10
Output
=== REGISTER NEW PRODUCT INVENTORY ===

Enter 12-Digit UPC: 123456789012
Enter Product Name: Milk
Enter Category Group: Dairy
Enter Wholesale/Cost Price ($):35
Enter Target Retail Price ($):50
Enter Initial Stock Level (0-5000):100
Enter Reorder Warning Threshold Level (1-100):10

SKU item 'Milk' registered seamlessly into current system tracking.
10.3 Display Inventory
Input
4
Output
=== SYSTEM SHEET MASTER OVERVIEW INVENTORY ===

UPC          Item Name            Category      Retail   Stock
-----------------------------------------------------------------
123456789012 Milk                 Dairy         $50.00   100
987654321098 Bread                Bakery        $30.00   75
10.4 Register Sale
Input
2
123456789012
5
Output
=== PROCESS RETAIL CASH POINT SALE ===

Scan Item UPC:123456789012

Discovered: Milk
Available units:100

Enter Quantity to Purchase:5

Sale processed cleanly.
Total Due: $250.00
10.5 Search Inventory
Input
3
Milk
Output
=== INVENTORY QUERY SEARCH ===

UPC          Item Name            Category      Retail   Stock
=================================================================
123456789012 Milk                 Dairy         $50.00   95
10.6 Low Stock Report
Input
5
Output
=== CRITICAL LOW REORDER SYSTEM DATA REPORT ===

UPC          Item Name          Category      Retail    Current Stock
-----------------------------------------------------------------------
987654321098 Bread              Bakery        $30.00    3

[Needs 15 replenishment units]
10.7 Delete Product
Input
6
123456789012
Output
Provide target UPC data line sequence to clear tracking reference:

123456789012

Tracking data line for element item 'Milk' set to safe drop state.
10.8 Save Data
Input
7
Output
File streaming pipelines finalized.
Data safe storage state verified.
10.9 Load Data
Input
8
Output
Data persistence structures mapped to localized memory pools successfully.
10.10 Exit Program
Input
0
Output
Session environment context destruction sequence complete.
Exiting.
11. Advantages of the Project
Fast inventory searching
Permanent data storage
Low stock monitoring
Product categorization
Sales tracking
Input validation
Easy user interface
12. Limitations
No graphical user interface
Single-user system
No database connectivity
No login authentication
No cloud storage support

13. Future Enhancements
Database Integration

Replace text files with:

MySQL
MongoDB
SQLite
Authentication System

Add:

Username login
Password encryption
Admin access control
Barcode Scanner Integration

Allow:

Real barcode scanning
Automatic product retrieval
Sales Analytics Dashboard

Generate:

Daily revenue reports
Monthly sales charts
Product performance analysis
GUI Interface

Develop using:

Qt Framework
C++ GUI libraries
Cloud Synchronization

Enable:

Online inventory updates
Multi-system synchronization
AI-based Inventory Prediction

Implement:

Demand forecasting
Stock prediction
Automated reorder suggestions
14. GitHub Commands
Clone Repository
git clone <repository-url>

Example:

git clone https://github.com/username/inventory-management-system.git
Move into Project Folder
cd inventory-management-system
Compile Program
g++ main.cpp -o inventory
Run Program
Windows
inventory.exe
Linux/Mac
./inventory
15. Git Commands for Uploading

Initialize Git:

git init

Add Files:

git add .

Commit Files:

git commit -m "Initial Commit"

Connect Repository:

git remote add origin https://github.com/username/inventory-management-system.git

Push Project:

git branch -M main
git push -u origin main

16. Folder Structure
Inventory-Management-System/
│
├── main.cpp
├── inventory_sheet.txt
├── sales_history.txt
├── README.md
└── .gitignore

17. README Description
StockGuard Inventory Management System is a console-based C++ application developed using Object-Oriented Programming and File Handling concepts. The application manages products, inventory stock, sales transactions, and low-stock monitoring with permanent data storage.
18. Conclusion

The StockGuard Inventory Management System successfully demonstrates the implementation of inventory control mechanisms using C++.

The system integrates:

Object-Oriented Programming
Dynamic data structures
File persistence
Product tracking
Sales management
Input validation

The project provides a practical understanding of how retail inventory systems function in real-world environments and creates a foundation for future enterprise-level inventory applications.
