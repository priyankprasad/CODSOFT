#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

// Function to generate a random ISBN number
std::string generateRandomISBN() {
    std::string isbn = "ISBN";
    for (int i = 0; i < 9; i++) {
        isbn += static_cast<char>('0' + (rand() % 10));
    }
    return isbn;
}

// Function to generate random book title
std::string generateRandomTitle() {
    std::string titles[] = {"The Catcher in the Rye", "To Kill a Mockingbird", "1984", "The Great Gatsby", "Moby-Dick"};
    return titles[rand() % 5];
}

// Function to generate random author name
std::string generateRandomAuthor() {
    std::string authors[] = {"J.D. Salinger", "Harper Lee", "George Orwell", "F. Scott Fitzgerald", "Herman Melville"};
    return authors[rand() % 5];
}

class Book {
public:
    Book(const std::string& title, const std::string& author, const std::string& isbn)
        : title(title), author(author), isbn(isbn), available(true) {}

    void display() const {
        std::cout << "Title: " << title << ", Author: " << author << ", ISBN: " << isbn;
        if (!available) {
            std::cout << " (Checked Out)";
        }
        std::cout << std::endl;
    }

    bool isAvailable() const {
        return available;
    }

    void checkOut() {
        available = false;
    }

    void checkIn() {
        available = true;
    }

    const std::string& getISBN() const {
        return isbn;
    }

private:
    std::string title;
    std::string author;
    std::string isbn;
    bool available;
};

class Borrower {
public:
    Borrower(const std::string& name) : name(name) {}

    const std::string& getName() const {
        return name;
    }

private:
    std::string name;
};

class Transaction {
public:
    Transaction(const Book& book, const Borrower& borrower)
        : book(book), borrower(borrower), dueDate(time(nullptr) + 14 * 24 * 60 * 60) {}  // Due date is set to 2 weeks from now

    const Book& getBook() const {
        return book;
    }

    const Borrower& getBorrower() const {
        return borrower;
    }

    bool isOverdue() const {
        return time(nullptr) > dueDate;
    }

private:
    const Book& book;
    const Borrower& borrower;
    const time_t dueDate;
};

class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addBorrower(const Borrower& borrower) {
        borrowers.push_back(borrower);
    }

    void checkOutBook(const std::string& isbn, const std::string& borrowerName) {
        for (Book& book : books) {
            if (book.getISBN() == isbn) {
                if (book.isAvailable()) {
                    book.checkOut();
                    transactions.push_back(Transaction(book, findBorrower(borrowerName)));
                    std::cout << "Book checked out successfully." << std::endl;
                } else {
                    std::cout << "Book is already checked out." << std::endl;
                }
                return;
            }
        }
        std::cout << "Book not found." << std::endl;
    }

    void checkInBook(const std::string& isbn) {
        for (Book& book : books) {
            if (book.getISBN() == isbn) {
                book.checkIn();
                std::cout << "Book checked in successfully." << std::endl;
                return;
            }
        }
        std::cout << "Book not found." << std::endl;
    }

    void displayBooks() {
        std::cout << "\nLibrary Books:\n";
        for (const Book& book : books) {
            book.display();
        }
    }

    void displayTransactions() {
        std::cout << "\nTransaction History:\n";
        for (const Transaction& transaction : transactions) {
            const Book& book = transaction.getBook();
            const Borrower& borrower = transaction.getBorrower();
            std::cout << "Borrower: " << borrower.getName() << ", Book: " << book.getISBN();
            if (transaction.isOverdue()) {
                std::cout << " (Overdue)";
            }
            std::cout << std::endl;
        }
    }

private:
    std::vector<Book> books;
    std::vector<Borrower> borrowers;
    std::vector<Transaction> transactions;

    Borrower findBorrower(const std::string& name) {
        for (const Borrower& borrower : borrowers) {
            if (borrower.getName() == name) {
                return borrower;
            }
        }
    }
};

int main() {
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Library library;

    // Generate and add random books to the library
    for (int i = 0; i < 5; i++) {
        Book book(generateRandomTitle(), generateRandomAuthor(), generateRandomISBN());
        library.addBook(book);
    }

    // Add random borrowers to the library
    Borrower borrower1("Borrower X");
    Borrower borrower2("Borrower Y");
    library.addBorrower(borrower1);
    library.addBorrower(borrower2);

    while (true) {
        std::cout << "\nLibrary Management System Menu:\n";
        std::cout << "1. Display Books\n";
        std::cout << "2. Check Out a Book\n";
        std::cout << "3. Check In a Book\n";
        std::cout << "4. Display Transactions\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice (1/2/3/4/5): ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            library.displayBooks();
        } else if (choice == 2) {
            std::string isbn, borrowerName;
            std::cout << "Enter ISBN of the book to check out: ";
            std::cin >> isbn;
            std::cout << "Enter borrower's name: ";
            std::cin.ignore(); // Consume the newline character
            std::getline(std::cin, borrowerName);
            library.checkOutBook(isbn, borrowerName);
        } else if (choice == 3) {
            std::string isbn;
            std::cout << "Enter ISBN of the book to check in: ";
            std::cin >> isbn;
            library.checkInBook(isbn);
        } else if (choice == 4) {
            library.displayTransactions();
        } else if (choice == 5) {
            std::cout << "Goodbye!" << std::endl;
            break;
        } else {
            std::cout << "Invalid choice. Please select a valid option." << std::endl;
        }
    }

    return 0;
}
