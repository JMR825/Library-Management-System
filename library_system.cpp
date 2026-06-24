#include<iostream>
#include<string>
#include<vector>
#include <cctype>
class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    bool is_available;

public:
    Book(std::string title, std::string author, std::string isbn);
    void print();
    std::string getIsbn() { return isbn; }
};

Book::Book(std::string title, std::string author, std::string isbn) {
    this->title = title;
    this->author = author;
    this->isbn = isbn;
    this->is_available = true;
}

void Book::print() {
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
    std::cout << "Available: " << (is_available ? "Yes" : "No") << std::endl;
}

class Member {
private:
    std::string name;
    int member_id;
    std::vector<std::string> borrowed_books;

public:
    Member(std::string name, int member_id);
    void addBook(std::string isbn);
    void removeBook(std::string isbn);
    void print();
    bool hasBook(std::string isbn);
};

Member::Member(std::string name, int member_id) {
    this->name = name;
    this->member_id = member_id;
    this->borrowed_books = std::vector<std::string>();
}

void Member::addBook(std::string isbn) {
    borrowed_books.push_back(isbn);
}

void Member::removeBook(std::string isbn) {
    for (size_t i = 0; i < borrowed_books.size(); i++) {
        if (borrowed_books[i] == isbn) {
            borrowed_books.erase(borrowed_books.begin() + i);
            return;
        }
    }
}

bool Member::hasBook(std::string isbn) {
    for (size_t i = 0; i < borrowed_books.size(); i++) {
        if (borrowed_books[i] == isbn) {
            return true;
        }
    }
    return false;
}

void Member::print() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Member ID: " << member_id << std::endl;
    std::cout << "Borrowed Books: ";
    if (borrowed_books.empty()) {
        std::cout << "None";
    } else {
        for (size_t i = 0; i < borrowed_books.size(); i++) {
            std::cout << borrowed_books[i];
            if (i < borrowed_books.size() - 1) {
                std::cout << ", ";
            }
        }
    }
    std::cout << std::endl;
}

class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;

public:
    void addBook(Book book);
    void addMember(Member member);
    void printAllBooks();
    void printAllMembers();
    bool issueBook(int member_id, std::string isbn);
bool returnBook(int member_id, std::string isbn);
std::vector<Book> searchByTitle(std::string title);
std::vector<Book> searchByAuthor(std::string author);
};

void Library::addBook(Book book) {
    books.push_back(book);
}

void Library::addMember(Member member) {
    members.push_back(member);
}

void Library::printAllBooks() {
    if (books.empty()) {
        std::cout << "No books in library." << std::endl;
        return;
    }
    for (size_t i = 0; i < books.size(); i++) {
        std::cout << "--- Book " << (i + 1) << "---" << std::endl;
        books[i].print();
        std::cout << std::endl;
    }
}

void Library::printAllMembers() {
    if (members.empty()) {
        std::cout << "No members in library." << std::endl;
        return;
    }
    for (size_t i = 0; i < members.size(); i++) {
        std::cout << "--- Member " << (i + 1) << "---" << std::endl;
        members[i].print();
        std::cout << std::endl;
    }
}

bool Library::issueBook(int member_id, std::string isbn) {
    // Find member
    Member* foundMember = nullptr;
    for (size_t i = 0; i < members.size(); i++) {
        if (members[i].member_id == member_id) {
            foundMember = &members[i];
            break;
        }
    }
    if (foundMember == nullptr) {
        return false;
    }

    // Find book
    Book* foundBook = nullptr;
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].getIsbn() == isbn) {
            foundBook = &books[i];
            break;
        }
    }
    if (foundBook == nullptr) {
        return false;
    }

    // Check if book is available
    if (!foundBook->is_available) {
        return false;
    }

    // Check if member already has this book
    if (foundMember->hasBook(isbn)) {
        return false;
    }

    // Issue the book
    foundMember->addBook(isbn);
    foundBook->is_available = false;
    return true;
}

bool Library::returnBook(int member_id, std::string isbn) {
    // Find member
    Member* foundMember = nullptr;
    for (size_t i = 0; i < members.size(); i++) {
        if (members[i].member_id == member_id) {
            foundMember = &members[i];
            break;
        }
    }
    if (foundMember == nullptr) {
        return false;
    }

    // Find book
    Book* foundBook = nullptr;
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].getIsbn() == isbn) {
            foundBook = &books[i];
            break;
        }
    }
    if (foundBook == nullptr) {
        return false;
    }

    // Check if member has this book
    if (!foundMember->hasBook(isbn)) {
        return false;
    }

    // Return the book
    foundMember->removeBook(isbn);
    foundBook->is_available = true;
    return true;
}

// Helper function to convert string to lowercase
std::string toLower(std::string str) {
    std::string result = "";
    for (size_t i = 0; i < str.length(); i++) {
        result += (char)tolower(str[i]);
    }
    return result;
}

std::vector<Book> Library::searchByTitle(std::string title) {
    std::vector<Book> result;
    std::string lowerTitle = toLower(title);
    
    for (size_t i = 0; i < books.size(); i++) {
        if (toLower(books[i].title) == lowerTitle) {
            result.push_back(books[i]);
        }
    }
    return result;
}

std::vector<Book> Library::searchByAuthor(std::string author) {
    std::vector<Book> result;
    std::string lowerAuthor = toLower(author);
    
    for (size_t i = 0; i < books.size(); i++) {
        if (toLower(books[i].author) == lowerAuthor) {
            result.push_back(books[i]);
        }
    }
    return result;
}
int main() {
    Library library;
    int choice;
    
    while (true) {
        // Display menu
        std::cout << "\n====== Library Management System ======" << std::endl;
        std::cout << "1. Add Book" << std::endl;
        std::cout << "2. Add Member" << std::endl;
        std::cout << "3. Issue Book" << std::endl;
        std::cout << "4. Return Book" << std::endl;
        std::cout << "5. Search by Title" << std::endl;
        std::cout << "6. Search by Author" << std::endl;
        std::cout << "7. Print All Books" << std::endl;
        std::cout << "8. Print All Members" << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;
        
        // Handle choice
        if (choice == 1) {
            std::string title, author, isbn;
            std::cout << "Enter title: ";
            std::cin >> title;
            std::cout << "Enter author: ";
            std::cin >> author;
            std::cout << "Enter ISBN: ";
            std::cin >> isbn;
            library.addBook(Book(title, author, isbn));
            std::cout << "Book added successfully!" << std::endl;
        }
        else if (choice == 2) {
            std::string name;
            int member_id;
            std::cout << "Enter name: ";
            std::cin >> name;
            std::cout << "Enter member ID: ";
            std::cin >> member_id;
            library.addMember(Member(name, member_id));
            std::cout << "Member added successfully!" << std::endl;
        }
        else if (choice == 3) {
            int member_id;
            std::string isbn;
            std::cout << "Enter member ID: ";
            std::cin >> member_id;
            std::cout << "Enter ISBN: ";
            std::cin >> isbn;
            if (library.issueBook(member_id, isbn)) {
                std::cout << "Book issued successfully!" << std::endl;
            } else {
                std::cout << "Failed to issue book. Check member ID, ISBN, availability, or if member already has the book." << std::endl;
            }
        }
        else if (choice == 4) {
            int member_id;
            std::string isbn;
            std::cout << "Enter member ID: ";
            std::cin >> member_id;
            std::cout << "Enter ISBN: ";
            std::cin >> isbn;
            if (library.returnBook(member_id, isbn)) {
                std::cout << "Book returned successfully!" << std::endl;
            } else {
                std::cout << "Failed to return book. Check member ID, ISBN, or if member has the book." << std::endl;
            }
        }
        else if (choice == 5) {
            std::string title;
            std::cout << "Enter title to search: ";
            std::cin >> title;
            std::vector<Book> results = library.searchByTitle(title);
            if (results.empty()) {
                std::cout << "No books found with that title." << std::endl;
            } else {
                std::cout << "Found " << results.size() << " book(s):" << std::endl;
                for (size_t i = 0; i < results.size(); i++) {
                    results[i].print();
                    std::cout << std::endl;
                }
            }
        }
        else if (choice == 6) {
            std::string author;
            std::cout << "Enter author to search: ";
            std::cin >> author;
            std::vector<Book> results = library.searchByAuthor(author);
            if (results.empty()) {
                std::cout << "No books found with that author." << std::endl;
            } else {
                std::cout << "Found " << results.size() << " book(s):" << std::endl;
                for (size_t i = 0; i < results.size(); i++) {
                    results[i].print();
                    std::cout << std::endl;
                }
            }
        }
        else if (choice == 7) {
            library.printAllBooks();
        }
        else if (choice == 8) {
            library.printAllMembers();
        }
        else if (choice == 9) {
            std::cout << "Exiting..." << std::endl;
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    
    return 0;
}