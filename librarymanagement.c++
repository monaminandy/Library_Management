//Header Files
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// Creating class Book
class Book {
public:
    int id;
    string title;
    string author;
    string genre;
    int publicationYear;
    bool isAvailable;
    time_t dueDate;

    Book(int id, string title, string author, string genre, int year) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->genre = genre;
        this->publicationYear = year;
        this->isAvailable = true;
        dueDate = 0;
    }
};

//Creating Class Member
class Member {
public:
    int id;
    string name;
    string address;
    string contact;
    vector<Book*> borrowedBooks;

    Member(int id, string name, string address, string contact) {
        this->id = id;
        this->name = name;
        this->address = address;
        this->contact = contact;
    }
// Borrow Book Method
    void borrowBook(Book& book) {
        if (book.isAvailable) {
            borrowedBooks.push_back(&book);
            book.isAvailable = false;
            book.dueDate = time(nullptr) + 14 * 24 * 60 * 60; // 14 days in seconds
            cout << "Book borrowed successfully! Due date: " << ctime(&book.dueDate) << endl;
        } else {
            cout << "Book is not available." << endl;
        }
    }
 //Display Book Method   
    void displayBorrowedBooks() {
        if (borrowedBooks.empty()) {
            cout << "No books borrowed." << endl;
        } else {
            cout << "Borrowed Books:\n";
            for (Book* book : borrowedBooks) {
                cout << "- " << book->title << " (Due: " << ctime(&book->dueDate) << ")" << endl;
            }
        }
    }
//Return Book Method
    void returnBook(Book& book) {
        for (int i = 0; i < borrowedBooks.size(); i++) {
            if (borrowedBooks[i] == &book) {
                borrowedBooks.erase(borrowedBooks.begin() + i);
                book.isAvailable = true;
                book.dueDate = 0;

               time_t currentTime = time(nullptr);
               book.dueDate = currentTime + (14 * 24 * 60 * 60);
            double secondsOverdue = difftime(currentTime, book.dueDate);
            int daysOverdue = secondsOverdue / (24 * 60 * 60);

                if (daysOverdue > 0) {
                    int fine = daysOverdue * 5;
                    cout << "Book returned! Overdue fine: Rs " << fine << endl;
                } else {
                    cout << "Book returned successfully!" << endl;
                }

                return;
            }
        }
        cout << "Book not found in your borrowed books." << endl;
    }
};

vector<Member> members;
int nextMemberId = 1;

vector<Book> books;
int nextBookId = 1;
//Register Member Function
void registerMember() {
    string name, address, contact;
    cout << "Enter member";
    getline(cin, name);
    cout << " name: ";
    getline(cin, name);
    cout << "Enter member contact: ";
    getline(cin, contact);
    cout << "Enter member address: ";
    getline(cin, address);

    Member member(nextMemberId++, name, address, contact);
    members.push_back(member);
    cout << "Member registered successfully!" << endl;
}
//Remove Member Function
void removeMember() {
    int id;
    cout << "Enter member ID to remove: ";
    cin >> id;

    for (auto it = members.begin(); it != members.end(); ++it) {
        if (it->id == id) {
            members.erase(it);
            cout << "Member removed successfully!" << endl;
            return;
        }
    }

    cout << "Member not found!" << endl;
}
//Display Members Function
void displayMembers() {
    if (members.empty()) {
        cout << "No members found." << endl;
        return;
    }

    cout << "Member List:\n";
    for (const Member& member : members) {
        cout << "ID: " << member.id << endl;
        cout << "Name: " << member.name << endl;
        cout << "Address: " << member.address << endl;
        cout << "Contact: " << member.contact << endl;
        cout << endl;
    }
}
//Adding Book Function
void addBook() {
    string title, author, genre;
    int year;

    cout << "Enter book";
    getline(cin, title);
    cout << " title: ";
    getline(cin, title);
    cout << "Enter author name: ";
    getline(cin, author);
    cout << "Enter genre: ";
    getline(cin, genre);
    cout << "Enter publication year: ";
    cin >> year;

    books.push_back(Book(nextBookId++, title, author, genre, year));
    cout << "Book added successfully!\n";
}
//Removing Book Function
void removeBook() {
    int id;
    cout << "Enter book ID to remove: ";
    cin >> id;

    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->id == id) {
            books.erase(it);
            cout << "Book removed successfully!\n";
            return;
        }
    }

    cout << "Book not found!\n";
}
//Display Book Function
void displayBooks() {
    if (books.empty()) {
        cout << "No books found." << endl;
        return;
    }

    cout << "Books in the library:\n";
    for (const Book& book : books) {
        cout << "ID: " << book.id << endl;
        cout << "Title: " << book.title << endl;
        cout << "Author: " << book.author << endl;
        cout << "Genre: " << book.genre << endl;
        cout << "Publication Year: " << book.publicationYear << endl;
        cout << "Availability: " << (book.isAvailable ? "Available" : "Borrowed") << endl;
        cout << endl;
    }
}
//Creating class Library
class Library {
public:
//Borrow Book Function
    void borrowBook(int memberId, int bookId) {
        for (Member& member : members) {
            if (member.id == memberId) {
                for (Book& book : books) {
                    if (book.id == bookId) {
                        member.borrowBook(book);
                        return;
                    }
                }
            }
        }
        cout << "Member or book not found." << endl;
    }
//Return Book function
    void returnBook(int bookId) {
        for (Book& book : books) {
            if (book.id == bookId) {
                for (Member& member : members) {
                    member.returnBook(book);
                }
                return;
            }
        }
        cout << "Book not found." << endl;
    }
//Generating Borrowed Books Reports
    void generateBorrowedBooksReport() {
        cout << "Currently Borrowed Books:\n";
        for (Member& member : members) {
            cout << "Member: " << member.name << endl;
            member.displayBorrowedBooks();
            cout << endl;
        }
    }
//Generating Overdue Books Report
    void generateOverdueReport() {
        cout << "Overdue Books:\n";
        bool foundOverdue = false;
        for (Member& member : members) {
            for (Book* book : member.borrowedBooks) {
                time_t currentTime = time(nullptr);
                int daysOverdue = difftime(currentTime, book->dueDate) / (24 * 60 * 60);
                if (daysOverdue > 0) {
                    foundOverdue = true;
                    cout << "Member: " << member.name << endl;
                    cout << "- " << book->title << " (Overdue by " << daysOverdue << " days, Fine: Rs " << daysOverdue * 5 << ")" << endl;
                }
            }
        }
        if (!foundOverdue) {
            cout << "No overdue books found." << endl;
        }
    }
};

int main() {
    Library library;
    int choice;
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Display Books\n";
        cout << "4. Register Member\n";
        cout << "5. Remove Member\n";
        cout << "6. Display Members\n";
        cout << "7. Borrow Book\n";
        cout << "8. Return Book\n";
        cout << "9. Borrow Book Report\n";
        cout << "10. Overdue Report\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                removeBook();
                break;
            case 3:
                displayBooks();
                break;
            case 4:
                registerMember();
                break;
            case 5:
                removeMember();
                break;
            case 6:
                displayMembers();
                break;
            case 7: {
                int memberId, bookId;
                cout << "Enter member ID: ";
                cin >> memberId;
                cout << "Enter book ID: ";
                cin >> bookId;
                library.borrowBook(memberId, bookId);
                break;
            }
            case 8: {
                int bookId;
                cout << "Enter book ID to return: ";
                cin >> bookId;
                library.returnBook(bookId);
                break;
            }
            case 9:{
                 library.generateBorrowedBooksReport();
                 break;
            }
               
            case 10:{
                library.generateOverdueReport();
                break;
            }
            case 11:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 11);
    return 0;
}
