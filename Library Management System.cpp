#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cctype>

using namespace std;

class Product {
private:
    string upc; 
    string name;
    string category;
    double costPrice;
    double retailPrice;
    int stockQuantity;
    int reorderPoint;
    bool isDeleted;

public:
    Product() : upc(""), name(""), category(""), costPrice(0.0), retailPrice(0.0), stockQuantity(0), reorderPoint(5), isDeleted(false) {}

    Product(string upc, string name, string cat, double cost, double retail, int qty, int reorder = 5)
        : upc(upc), name(name), category(cat), costPrice(cost), retailPrice(retail), stockQuantity(qty), reorderPoint(reorder), isDeleted(false) {}

    string getUPC() const { return upc; }
    string getName() const { return name; }
    string getCategory() const { return category; }
    double getCostPrice() const { return costPrice; }
    double getRetailPrice() const { return retailPrice; }
    int getStockQuantity() const { return stockQuantity; }
    int getReorderPoint() const { return reorderPoint; }
    bool getIsDeleted() const { return isDeleted; }

    void setStockQuantity(int qty) { if (qty >= 0) stockQuantity = qty; }
    void setDeleted(bool status) { isDeleted = status; }

    bool needsReorder() const { return stockQuantity <= reorderPoint && !isDeleted; }

    string toString() const {
        stringstream ss;
        ss << left << setw(14) << upc << setw(22) << name << setw(15) << category 
           << fixed << setprecision(2) << "$" << setw(9) << retailPrice << setw(10) << stockQuantity;
        return ss.str();
    }
};

class Transaction {
private:
    string transactionId;
    string upc;
    int quantitySold;
    double unitPrice;
    string timestamp;

public:
    Transaction() : transactionId(""), upc(""), quantitySold(0), unitPrice(0.0), timestamp("") {}

    Transaction(string id, string upc, int qty, double price, string time)
        : transactionId(id), upc(upc), quantitySold(qty), unitPrice(price), timestamp(time) {}

    string getTransactionId() const { return transactionId; }
    string getUPC() const { return upc; }
    int getQuantitySold() const { return quantitySold; }
    double getUnitPrice() const { return unitPrice; }
    double getTotalRevenue() const { return quantitySold * unitPrice; }
    string getTimestamp() const { return timestamp; }
};

bool isValidUPCA(const string& upc) {
    string clean;
    for (char c : upc) { if (isdigit(c)) clean += c; }
    if (clean.length() != 12) return false;

    int oddSum = 0, evenSum = 0;
    for (int i = 0; i < 11; i++) {
        int digit = clean[i] - '0';
        if (i % 2 == 0) oddSum += digit; 
        else evenSum += digit;
    }
    int total = (oddSum * 3) + evenSum;
    int checkDigit = (10 - (total % 10)) % 10;
    
    return checkDigit == (clean[11] - '0');
}

string getCurrentTimestamp() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-" 
       << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-" 
       << setw(2) << ltm->tm_mday << " " 
       << setw(2) << ltm->tm_hour << ":" 
       << setw(2) << ltm->tm_min;
    return ss.str();
}

class InventorySystem {
private:
    vector<Product> products;
    vector<Transaction> history;
    string storeName;

    // Direct pointers data accessors
    Product* findProduct(const string& upc) {
        for (auto& prod : products) {
            if (prod.getUPC() == upc) return &prod;
        }
        return nullptr;
    }

    bool getValidUPC(string& upc) {
        int attempts = 0;
        while (true) {
            cout << (attempts == 0 ? "Enter 12-Digit UPC: " : "Invalid UPC Checksum! ");
            attempts++;
            getline(cin >> ws, upc);
            if (isValidUPCA(upc)) return true;
            if (attempts == 1) cout << "Hint: Must be exactly 12 digits matching standard barcode metrics.\n";
            cout << "Please try again.\n";
        }
    }

    bool getValidPrice(double& price, const string& context) {
        int attempts = 0;
        while (true) {
            cout << "Enter " << context << " Price ($): ";
            attempts++;
            string input;
            getline(cin >> ws, input);
            try {
                price = stod(input);
                if (price >= 0.01 && price <= 10000.0) return true;
            } catch (...) {}
            cout << "Invalid monetary amount! Enter a value between 0.01 and 10000.00.\n";
        }
    }

    bool getValidInt(int& val, const string& label, int minV, int maxV) {
        while (true) {
            cout << "Enter " << label << " (" << minV << "-" << maxV << "): ";
            string input;
            getline(cin >> ws, input);
            try {
                val = stoi(input);
                if (val >= minV && val <= maxV) return true;
            } catch (...) {}
            cout << "Out of bounds numerical entry. Try again.\n";
        }
    }

    bool getNonEmptyString(string& str, const string& label) {
        while (true) {
            cout << "Enter " << label << ": ";
            getline(cin >> ws, str);
            if (!str.empty()) return true;
            cout << label << " field cannot be completely blank.\n";
        }
    }

public:
    InventorySystem(string name) : storeName(name) {}

    void addProduct() {
        cout << "\n=== REGISTER NEW PRODUCT INVENTORY ===\n";
        string upc, name, cat;
        double cost, retail;
        int qty, reorder;

        if (!getValidUPC(upc)) return;
        if (findProduct(upc) && !findProduct(upc)->getIsDeleted()) {
            cout << "Product code clash! UPC standard " << upc << " already exists.\n";
            return;
        }

        if (!getNonEmptyString(name, "Product Name")) return;
        if (!getNonEmptyString(cat, "Category Group")) return;
        if (!getValidPrice(cost, "Wholesale/Cost")) return;
        if (!getValidPrice(retail, "Target Retail")) return;
        if (!getValidInt(qty, "Initial Stock Level", 0, 5000)) return;
        if (!getValidInt(reorder, "Reorder Warning Threshold Level", 1, 100)) return;

        products.emplace_back(upc, name, cat, cost, retail, qty, reorder);
        cout << "\nSKU item '" << name << "' registered seamlessly into current system tracking.\n";
    }

    void registerSale() {
        cout << "\n=== PROCESS RETAIL CASH POINT SALE ===\n";
        string upc;
        cout << "Scan Item UPC: ";
        getline(cin >> ws, upc);

        Product* prod = findProduct(upc);
        if (!prod || prod->getIsDeleted()) {
            cout << "Item variant out of database tracking system reach.\n";
            return;
        }

        if (prod->getStockQuantity() <= 0) {
            cout << "Operation aborted: '" << prod->getName() << "' is completely out of stock!\n";
            return;
        }

        int requestedQty;
        cout << "Discovered: " << prod->getName() << " | Available units: " << prod->getStockQuantity() << "\n";
        if (!getValidInt(requestedQty, "Quantity to Purchase", 1, prod->getStockQuantity())) return;

        
        prod->setStockQuantity(prod->getStockQuantity() - requestedQty);
        
        string txnId = "TXN" + to_string(1000 + history.size());
        history.emplace_back(txnId, upc, requestedQty, prod->getRetailPrice(), getCurrentTimestamp());

        cout << "\nSale processed cleanly. Total Due: $" << fixed << setprecision(2) << (requestedQty * prod->getRetailPrice()) << "\n";
        if(prod->needsReorder()) {
            cout << "[WARNING]: Running critically low on '" << prod->getName() << "' stock items.\n";
        }
    }

    void searchInventory() {
        string search;
        cout << "\n=== INVENTORY QUERY SEARCH ===\nQuery string (Name/Category): ";
        getline(cin >> ws, search);

        cout << "\n" << left << setw(14) << "UPC" << setw(22) << "Item Name" << setw(15) << "Category" << setw(10) << "Retail" << setw(10) << "Stock" << endl;
        cout << string(71, '=') << endl;

        bool hits = false;
        for (const auto& p : products) {
            if (p.getIsDeleted()) continue;
            if (p.getName().find(search) != string::npos || p.getCategory().find(search) != string::npos) {
                cout << p.toString() << endl;
                hits = true;
            }
        }
        if (!hits) cout << "No specific retail inventory targets fit context filter details.\n";
    }

    void displayLowStockReport() const {
        cout << "\n=== CRITICAL LOW REORDER SYSTEM DATA REPORT ===\n";
        cout << left << setw(14) << "UPC" << setw(22) << "Item Name" << setw(15) << "Category" << setw(10) << "Retail" << setw(10) << "Current Stock" << endl;
        cout << string(71, '-') << endl;

        bool cleanState = true;
        for (const auto& p : products) {
            if (p.needsReorder()) {
                cout << p.toString() << " [Needs " << (p.getReorderPoint() * 3) << " replenishment units]" << endl;
                cleanState = false;
            }
        }
        if (cleanState) cout << "All clear. Wholesale tracking metrics reporting healthy unit capacity targets.\n";
    }

    void displayAllInventory() const {
        cout << "\n=== SYSTEM SHEET MASTER OVERVIEW INVENTORY ===\n";
        cout << left << setw(14) << "UPC" << setw(22) << "Item Name" << setw(15) << "Category" << setw(10) << "Retail" << setw(10) << "Stock" << endl;
        cout << string(71, '-') << endl;

        int activeItemsCount = 0;
        for (const auto& p : products) {
            if (!p.getIsDeleted()) {
                cout << p.toString() << endl;
                activeItemsCount++;
            }
        }
        if (activeItemsCount == 0) cout << "System currently registers zero core product asset records.\n";
    }

    void deleteProduct() {
        string upc;
        cout << "\nProvide target UPC data line sequence to clear tracking reference: ";
        getline(cin >> ws, upc);

        Product* prod = findProduct(upc);
        if (prod && !prod->getIsDeleted()) {
            prod->setDeleted(true);
            cout << "\nTracking data line for element item '" << prod->getName() << "' set to safe drop state.\n";
        } else {
            cout << "Target element was either already purged or was missing from index structures.\n";
        }
    }

    void saveData() const {
        ofstream prodOut("inventory_sheet.txt");
        ofstream txnOut("sales_history.txt");

        for (const auto& p : products) {
            if (!p.getIsDeleted()) {
                prodOut << p.getUPC() << "|" << p.getName() << "|" << p.getCategory() << "|"
                        << p.getCostPrice() << "|" << p.getRetailPrice() << "|" << p.getStockQuantity() << "|"
                        << p.getReorderPoint() << "\n";
            }
        }

        for (const auto& t : history) {
            txnOut << t.getTransactionId() << "|" << t.getUPC() << "|" << t.getQuantitySold() << "|"
                   << t.getUnitPrice() << "|" << t.getTimestamp() << "\n";
        }
        cout << "\nFile streaming pipelines finalized. Data safe storage state verified.\n";
    }

    void loadData() {
        ifstream prodIn("inventory_sheet.txt");
        ifstream txnIn("sales_history.txt");
        string line;

        products.clear();
        history.clear();

        if (prodIn.is_open()) {
            while (getline(prodIn, line)) {
                stringstream ss(line);
                string upc, name, cat, s_cost, s_retail, s_qty, s_reorder;
                
                getline(ss, upc, '|');
                getline(ss, name, '|');
                getline(ss, cat, '|');
                getline(ss, s_cost, '|');
                getline(ss, s_retail, '|');
                getline(ss, s_qty, '|');
                getline(ss, s_reorder, '|');

                if (!upc.empty() && isValidUPCA(upc)) {
                    products.emplace_back(upc, name, cat, stod(s_cost), stod(s_retail), stoi(s_qty), stoi(s_reorder));
                }
            }
            prodIn.close();
        }

        if (txnIn.is_open()) {
            while (getline(txnIn, line)) {
                stringstream ss(line);
                string id, upc, s_qty, s_price, time;
                
                getline(ss, id, '|');
                getline(ss, upc, '|');
                getline(ss, s_qty, '|');
                getline(ss, s_price, '|');
                getline(ss, time, '|');

                if (!id.empty()) {
                    history.emplace_back(id, upc, stoi(s_qty), stod(s_price), time);
                }
            }
            txnIn.close();
        }
        cout << "\nData persistence structures mapped to localized memory pools successfully.\n";
    }
};

void renderMenu() {
    cout << "\n=========================================";
    cout << "\n     STOCKGUARD INVENTORY SYSTEMS";
    cout << "\n=========================================";
    cout << "\n1.  Add New Retail Product Asset";
    cout << "\n2.  Scan & Log POS Sales Transaction";
    cout << "\n3.  Dynamic Stock Search Engine Query";
    cout << "\n4.  Print Master Asset Catalog Sheet";
    cout << "\n5.  Generate Low Stock Alert Metrics";
    cout << "\n6.  Purge Obsolete Core Product SKU";
    cout << "\n7.  Commit Local Cache Changes to Disk";
    cout << "\n8.  Reload System Master Log Data Files";
    cout << "\n0.  Safely Close Session Terminal Pipeline";
    cout << "\n=========================================";
    cout << "\nProcess Option Routing Request Selection: ";
}

int main() {
    InventorySystem ims("Global Retail Hub");
    int choice;

    ims.loadData();

    while (true) {
        system("clear || cls");
        renderMenu();
        
        if (!(cin >> choice)) {
            cout << "\nStream evaluation tracking error! Supply integers (0-8).\n";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Awaiting confirmation input step mechanism key signal...";
            cin.get();
            continue;
        }
        cin.ignore();

        switch (choice) {
            case 1: ims.addProduct(); break;
            case 2: ims.registerSale(); break;
            case 3: ims.searchInventory(); break;
            case 4: ims.displayAllInventory(); break;
            case 5: ims.displayLowStockReport(); break;
            case 6: ims.deleteProduct(); break;
            case 7: ims.saveData(); break;
            case 8: ims.loadData(); break;
            case 0:
                ims.saveData();
                cout << "\nSession environment context destruction sequence complete. Exiting.\n";
                return 0;
            default:
                cout << "\nRouting indexing range fault limit violation. Pick 0-8 entries.\n";
        }

        cout << "\nPress Enter to return back to option tree routing mapping panel...";
        cin.get();
    }
    return 0;
}