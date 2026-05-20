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

const int LOAN_PERIOD_DAYS = 14;

string formatDate(time_t rawTime) {
    tm *timeInfo = localtime(&rawTime);
    stringstream ss;
    ss << 1900 + timeInfo->tm_year << "-"
       << setfill('0') << setw(2) << 1 + timeInfo->tm_mon << "-"
       << setw(2) << timeInfo->tm_mday;
    return ss.str();
}

string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return tolower(c); });
    return str;
}



class Book {
private:
    int bookId;
    string title;
    string author;
    string isbn;
    bool isIssued;

public:
    Book() : bookId(0), title(""), author(""), isbn(""), isIssued(false) {}
    Book(int id, string t, string a, string i, bool issued = false) 
        : bookId(id), title(t), author(a), isbn(i), isIssued(issued) {}

    int getId() const { return bookId; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getIsbn() const { return isbn; }
    bool getIssuedStatus() const { return isIssued; }

    void setIssuedStatus(bool status) { isIssued = status; }

    void displayRow() const {
        cout << left << setw(8) << bookId 
             << setw(30) << (title.length() > 28 ? title.substr(0, 25) + "..." : title)
             << setw(25) << (author.length() > 23 ? author.substr(0, 20) + "..." : author) 
             << setw(15) << isbn 
             << (isIssued ? "Checked Out" : "Available") << "\n";
    }
};

class Member {
private:
    int memberId;
    string name;
    string email;

public:
    Member() : memberId(0), name(""), email("") {}
    Member(int id, string n, string e) : memberId(id), name(n), email(e) {}

    int getId() const { return memberId; }
    string getName() const { return name; }
    string getEmail() const { return email; }

    void displayRow() const {
        cout << left << setw(10) << memberId 
             << setw(25) << (name.length() > 23 ? name.substr(0, 20) + "..." : name) 
             << email << "\n";
    }
};

class BorrowRecord {
private:
    int bookId;
    int memberId;
    time_t issueDate;
    time_t dueDate;
    bool isReturned;

public:
    BorrowRecord() : bookId(0), memberId(0), issueDate(0), dueDate(0), isReturned(false) {}
    BorrowRecord(int bId, int mId, time_t issue, time_t due, bool returned = false)
        : bookId(bId), memberId(mId), issueDate(issue), dueDate(due), isReturned(returned) {}

    int getBookId() const { return bookId; }
    int getMemberId() const { return memberId; }
    time_t getIssueDate() const { return issueDate; }
    time_t getDueDate() const { return dueDate; }
    bool getReturnedStatus() const { return isReturned; }

    void markAsReturned() { isReturned = true; }
};


class LibraryManager {
private:
    vector<Book> books;
    vector<Member> members;
    vector<BorrowRecord> records;
    
    int nextBookId;
    int nextMemberId;

    Book* findBookPointer(int id) {
        for (auto& b : books) { if (b.getId() == id) return &b; }
        return nullptr;
    }

    Member* findMemberPointer(int id) {
        for (auto& m : members) { if (m.getId() == id) return &m; }
        return nullptr;
    }

    void getValidatedString(string& target, const string& prompt) {
        while (true) {
            cout << prompt;
            getline(cin >> ws, target);
            if (!target.empty() && target.find('|') == string::npos) return;
            cout << "Invalid entry: Text cannot be empty or contain standard divider keys ('|').\n";
        }
    }

    int getValidatedInt(const string& prompt) {
        int inputVal;
        while (true) {
            cout << prompt;
            if (cin >> inputVal) {
                cin.ignore(10000, '\n');
                return inputVal;
            }
            cout << "Invalid entry: Please enter numeric digits only.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

public:
    LibraryManager() : nextBookId(1001), nextMemberId(5001) {}

    void addBook() {
        cout << "\n=== REGISTER NEW BOOK ASSET ===\n";
        string title, author, isbn;
        getValidatedString(title, "Enter Book Title : ");
        getValidatedString(author, "Enter Author Name: ");
        getValidatedString(isbn, "Enter ISBN Code  : ");

        books.emplace_back(nextBookId++, title, author, isbn);
        cout << ">> Success: Book added with tracking System ID: " << nextBookId - 1 << "\n";
    }

    void addMember() {
        cout << "\n=== REGISTER NEW LIBRARY MEMBER ===\n";
        string name, email;
        getValidatedString(name, "Enter Full Name : ");
        getValidatedString(email, "Enter Email Addr: ");

        members.emplace_back(nextMemberId++, name, email);
        cout << ">> Success: Membership account issued card ID: " << nextMemberId - 1 << "\n";
    }

    void issueBook() {
        cout << "\n=== PROCESS BOOK CHECKOUT ===\n";
        int bId = getValidatedInt("Enter Target Book ID: ");
        Book* book = findBookPointer(bId);

        if (!book) { cout << ">> Error: Missing asset matching ID " << bId << "\n"; return; }
        if (book->getIssuedStatus()) { cout << ">> Error: Target book is already loaned out.\n"; return; }

        int mId = getValidatedInt("Enter Checking Member ID: ");
        Member* member = findMemberPointer(mId);
        if (!member) { cout << ">> Error: Missing active membership record matching ID " << mId << "\n"; return; }

        time_t standardNow = time(0);
        time_t absoluteDue = standardNow + (LOAN_PERIOD_DAYS * 24 * 60 * 60);

        book->setIssuedStatus(true);
        records.emplace_back(bId, mId, standardNow, absoluteDue, false);

        cout << "\n>> Success: Checkout complete!\n";
        cout << "   Asset Allocated: \"" << book->getTitle() << "\"\n";
        cout << "   Issued To      : " << member->getName() << "\n";
        cout << "   Return Deadline: " << formatDate(absoluteDue) << "\n";
    }

    void returnBook() {
        cout << "\n=== PROCESS BOOK RETURN ===\n";
        int bId = getValidatedInt("Enter Returned Book ID: ");
        Book* book = findBookPointer(bId);

        if (!book) { cout << ">> Error: No structural matching record tracking matches ID " << bId << "\n"; return; }
        if (!book->getIssuedStatus()) { cout << ">> Notification: This item is already marked safe inside internal inventory vaults.\n"; return; }

        bool updated = false;
        for (auto& rec : records) {
            if (rec.getBookId() == bId && !rec.getReturnedStatus()) {
                rec.markAsReturned();
                book->setIssuedStatus(false);
                updated = true;
                
                time_t currentTime = time(0);
                cout << ">> Success: File check-in verified.\n";
                if (currentTime > rec.getDueDate()) {
                    cout << "   [ALERT]: This transaction is flag-marked LATE.\n";
                } else {
                    cout << "   Check-in received within the allocated timeline window.\n";
                }
                break;
            }
        }
        if (!updated) {
            book->setIssuedStatus(false); 
            cout << ">> System sync: Fixed internal loan discrepancy flags.\n";
        }
    }

    void searchBooks() {
        cout << "\n=== QUERY CATALOG INDEXES ===\n";
        string filterTerms;
        getValidatedString(filterTerms, "Enter search keyword (Title/Author Name): ");
        string phrase = toLower(filterTerms);

        cout << "\n" << left << setw(8) << "ID" << setw(30) << "Title" << setw(25) << "Author" << setw(15) << "ISBN" << "Status" << "\n";
        cout << string(85, '=') << "\n";

        bool matchesFound = false;
        for (const auto& b : books) {
            if (toLower(b.getTitle()).find(phrase) != string::npos || toLower(b.getAuthor()).find(phrase) != string::npos) {
                b.displayRow();
                matchesFound = true;
            }
        }
        if (!matchesFound) cout << "No records match search criterion input.\n";
    }

    void listAllBooks() const {
        cout << "\n=== INTERNAL REGISTER FILE INVENTORY ===\n";
        cout << left << setw(8) << "ID" << setw(30) << "Title" << setw(25) << "Author" << setw(15) << "ISBN" << "Status" << "\n";
        cout << string(85, '-') << "\n";

        if (books.empty()) { cout << "System dynamic records file tracking tables are currently empty.\n"; return; }
        for (const auto& b : books) b.displayRow();
    }

    void listAllMembers() const {
        cout << "\n=== REGISTERED USERS ACTIVE ROSTER ===\n";
        cout << left << setw(10) << "Card ID" << setw(25) << "Full Name" << "Primary Email Interface Address\n";
        cout << string(65, '-') << "\n";

        if (members.empty()) { cout << "No accounts exist inside database indices.\n"; return; }
        for (const auto& m : members) m.displayRow();
    }

    
    void saveSystemState() const {
        ofstream bFile("books_db.txt");
        ofstream mFile("members_db.txt");
        ofstream rFile("ledgers_db.txt");

        for (const auto& b : books) {
            bFile << b.getId() << "|" << b.getTitle() << "|" << b.getAuthor() << "|" 
                  << b.getIsbn() << "|" << b.getIssuedStatus() << "\n";
        }
        for (const auto& m : members) {
            mFile << m.getId() << "|" << m.getName() << "|" << m.getEmail() << "\n";
        }
        for (const auto& r : records) {
            rFile << r.getBookId() << "|" << r.getMemberId() << "|" << r.getIssueDate() << "|" 
                  << r.getDueDate() << "|" << r.getReturnedStatus() << "\n";
        }
        cout << ">> Storage notification: Snapshot synchronization tables safely secured onto system disks.\n";
    }

    void loadSystemState() {
        ifstream bFile("books_db.txt");
        ifstream mFile("members_db.txt");
        ifstream rFile("ledgers_db.txt");
        string textLine;

        books.clear(); members.clear(); records.clear();

        if (bFile.is_open()) {
            while (getline(bFile, textLine)) {
                stringstream ss(textLine);
                string id_s, title, author, isbn, issued_s;
                getline(ss, id_s, '|'); getline(ss, title, '|'); getline(ss, author, '|');
                getline(ss, isbn, '|'); getline(ss, issued_s, '|');
                if (!id_s.empty()) {
                    int id = stoi(id_s);
                    books.emplace_back(id, title, author, isbn, (issued_s == "1"));
                    if (id >= nextBookId) nextBookId = id + 1;
                }
            }
            bFile.close();
        }
        if (mFile.is_open()) {
            while (getline(mFile, textLine)) {
                stringstream ss(textLine);
                string id_s, name, email;
                getline(ss, id_s, '|'); getline(ss, name, '|'); getline(ss, email, '|');
                if (!id_s.empty()) {
                    int id = stoi(id_s);
                    members.emplace_back(id, name, email);
                    if (id >= nextMemberId) nextMemberId = id + 1;
                }
            }
            mFile.close();
        }
        if (rFile.is_open()) {
            while (getline(rFile, textLine)) {
                stringstream ss(textLine);
                string bId_s, mId_s, iss_s, due_s, ret_s;
                getline(ss, bId_s, '|'); getline(ss, mId_s, '|'); getline(ss, iss_s, '|');
                getline(ss, due_s, '|'); getline(ss, ret_s, '|');
                if (!bId_s.empty()) {
                    records.emplace_back(stoi(bId_s), stoi(mId_s), stol(iss_s), stol(due_s), (ret_s == "1"));
                }
            }
            rFile.close();
        }
    }
};


void displayMenu() {
    cout << "\n=========================================";
    cout << "\n      LIBRARY MANAGEMENT INTERFACE       ";
    cout << "\n=========================================";
    cout << "\n 1. Register New Book Asset";
    cout << "\n 2. Enroll New Active Member";
    cout << "\n 3. Issue Book Asset (Loan Transaction)";
    cout << "\n 4. Return Book Asset (Inbound Check-in)";
    cout << "\n 5. Search Catalog (Title / Author)";
    cout << "\n 6. Show Entire Inventory Catalog";
    cout << "\n 7. Show Enrolled Membership Roster";
    cout << "\n 0. Save Configuration & Exit Session";
    cout << "\n=========================================";
    cout << "\nSelect routing index parameter option: ";
}

int main() {
    LibraryManager coreEngine;
    int systemRouteCode;

    coreEngine.loadSystemState();

    while (true) {
        displayMenu();
        if (!(cin >> systemRouteCode)) {
            cout << "\nStream entry validation exception error: Numbers only.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n');

        switch (systemRouteCode) {
            case 1: coreEngine.addBook(); break;
            case 2: coreEngine.addMember(); break;
            case 3: coreEngine.issueBook(); break;
            case 4: coreEngine.returnBook(); break;
            case 5: coreEngine.searchBooks(); break;
            case 6: coreEngine.listAllBooks(); break;
            case 7: coreEngine.listAllMembers(); break;
            case 0:
                coreEngine.saveSystemState();
                cout << "\nClosing engine tasks context safely. Core environments dropped. Goodbye.\n";
                return 0;
            default:
                cout << "\nRoute selection bounds exception tracking error. Re-try selection code parameters.\n";
        }
        
        cout << "\nPress Enter to return to main tracking dashboard system menu...";
        cin.get();
    }
    return 0;
}
