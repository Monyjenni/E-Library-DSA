#include <iostream>
#include <string>
using namespace std;

struct Admin {
  string username;
  string password;
};

bool isValidAdmin(const Admin &admin, const string &inputUsername,
                  const string &inputPassword) {
  return (admin.username == inputUsername && admin.password == inputPassword);
}

struct BookData {
  int bookID;
  string bookNAME;
  BookData *next;
};

struct usersData {
  int userID;
  string userNAME;
  char userGender;
  int userAge;
  string DATE;
  BookData *borrowedBooks;
  usersData *next;
};

class Library {
public:
  usersData *usersHead;
  BookData *booksHead;

  Library() : usersHead(nullptr), booksHead(nullptr) {}

  void addUser(usersData *user) {
    if (!usersHead) {
      usersHead = user;
    } else {
      usersData *temp = usersHead;
      while (temp->next) {
        temp = temp->next;
      }
      temp->next = user;
    }
  }

  void addBook(BookData *book) {
    if (!booksHead) {
      booksHead = book;
    } else {
      BookData *temp = booksHead;
      while (temp->next) {
        temp = temp->next;
      }
      temp->next = book;
    }
  }

  void viewUserBorrowedBooks(usersData *user) {
    cout << "User " << user->userNAME << "'s Borrowed Books:\n";
    cout << "------------------------------------------\n";
    cout << "Book ID\t\t\t\t BOOK NAME\t\t BORROW DATE\n";
    cout << "-----------------------------------------------\n";

    BookData *currentBook = user->borrowedBooks;
    while (currentBook != nullptr) {
      cout << currentBook->bookID << "\t\t\t\t " << currentBook->bookNAME
           << "\t\t " << user->DATE << "\n";
      currentBook = currentBook->next;
    }

    cout << "------------------------------------------\n";
  }

  void viewAllBooks() {
    cout << "All Books:\n";
    cout << "------------------------------------------\n";
    cout << "Book ID\t\t\t BOOK NAME\n";
    cout << "------------------------------------------\n";

    BookData *currentBook = booksHead;
    while (currentBook != nullptr) {
      cout << currentBook->bookID << "\t\t\t\t " << currentBook->bookNAME
           << "\n";
      currentBook = currentBook->next;
    }

    cout << "------------------------------------------\n";
  }
  void viewReturnedBooks() {
    cout << "Returned Books:\n";
    cout << "------------------------------------------\n";
    cout << "Book ID\t\t\t\t BOOK NAME\t\t RETURN DATE\n";
    cout << "------------------------------------------\n";

    BookData *currentBook = booksHead;
    while (currentBook != nullptr) {
      cout << currentBook->bookID << "\t\t\t\t " << currentBook->bookNAME
           << "\t\t "
           << "DD-MM-YYYY"
           << "\n";
      currentBook = currentBook->next;
    }

    cout << "------------------------------------------\n";
  }

  void borrowBook(int userID, int bookID, const string &borrowDate) {
    usersData *currentUser = usersHead;
    while (currentUser != nullptr) {
      if (currentUser->userID == userID) {
        BookData *currentBook = booksHead;
        BookData *prevBook = nullptr;
        while (currentBook != nullptr) {
          if (currentBook->bookID == bookID) {
            BookData *newBorrowedBook =
                new BookData{currentBook->bookID, currentBook->bookNAME};
            newBorrowedBook->next = currentUser->borrowedBooks;
            currentUser->borrowedBooks = newBorrowedBook;
            if (prevBook) {
              prevBook->next = currentBook->next;
            } else {
              booksHead = currentBook->next;
            }

            cout << "Book successfully borrowed." << endl;
            return;
          }
          prevBook = currentBook;
          currentBook = currentBook->next;
        }
        break;
      }
      currentUser = currentUser->next;
    }

    cout << "User or book not found. Borrow failed." << endl;
  }

  void returnBook(int userID, int bookID) {
    usersData *currentUser = usersHead;
    while (currentUser != nullptr) {
      if (currentUser->userID == userID) {
        BookData *currentBook = currentUser->borrowedBooks;
        BookData *prevBook = nullptr;

        while (currentBook != nullptr) {
          if (currentBook->bookID == bookID) {
            if (prevBook) {
              prevBook->next = currentBook->next;
            } else {
              currentUser->borrowedBooks = currentBook->next;
            }
            currentBook->next = booksHead;
            booksHead = currentBook;

            cout << "Book successfully returned." << endl;
            return;
          }
          prevBook = currentBook;
          currentBook = currentBook->next;
        }
        break;
      }
      currentUser = currentUser->next;
    }

    cout << "User or borrowed book not found. Return failed." << endl;
  }

  void addNewBook() {
    int bookID;
    string bookName;
    string date;

    cout << "Enter the Book ID: ";
    cin >> bookID;

    cout << "Enter the Book Name: ";
    cin.ignore();
    getline(cin, bookName);

    cout << "Enter the date of adding (DD-MM-YYYY): ";
    cin >> date;

    BookData *newBook = new BookData{bookID, bookName};
    newBook->next = booksHead;
    booksHead = newBook;

    cout << "Book added successfully." << endl;
  }
};
bool isValidChoice(char choice) {
  return choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n';
}

int main() {
  Admin admin;
  admin.username = "Admin";
  admin.password = "12345";

  Library library;

  usersData *user1 = new usersData{1, "Nettra", 'F', 25};
  user1->borrowedBooks = nullptr;
  library.addUser(user1);

  usersData *user2 = new usersData{2, "Sophavinn", 'M', 18};
  user2->borrowedBooks = nullptr;
  library.addUser(user2);

  BookData *allBooks = new BookData{101, "Book A"};
  allBooks->next = new BookData{102, "Book B", nullptr};
  allBooks->next->next = new BookData{103, "Book C"};
  allBooks->next->next->next = new BookData{104, "Book D", nullptr};

  library.addBook(allBooks);

  string inputUsername;
  string inputPassword;
  bool loggedIn = false;

  while (!loggedIn) {
    cout << "Welcome admin to the Login!" << endl;
    cout << "Username: ";
    cin >> inputUsername;
    cout << "Password: ";
    cin >> inputPassword;

    if (isValidAdmin(admin, inputUsername, inputPassword)) {
      loggedIn = true;
      cout << "Login successful. Welcome, " << admin.username << "!" << endl;
    } else {
      cout << "Invalid username or password." << endl;
      char tryAgain;
      cout << "Wanna try again? (Y/N): ";
      cin >> tryAgain;
      if (tryAgain != 'Y' && tryAgain != 'y') {
        cout << "Exiting program. Goodbye!" << endl;
        return 0;
      }
    }
  }
  int choice;
  bool end = false;
  char YN;

  while (!end) {
    cout << "Choose your option: " << endl;
    cout << "1 - View User's Borrowed Books" << endl;
    cout << "2 - View All Books" << endl;
    cout << "3 - View Returned Books" << endl;
    cout << "4 - Borrow Book" << endl;
    cout << "5 - Return Book" << endl;
    cout << "6 - Add New Book" << endl;
    cout << "7 - Exit" << endl;
    cout << "Enter your choice: ";

    cin >> choice;
    switch (choice) {
    case 1: {
      int userID;
      cout << "Enter the user ID: ";
      cin >> userID;

      usersData *currentUser = library.usersHead;
      while (currentUser != nullptr) {
        if (currentUser->userID == userID) {
          library.viewUserBorrowedBooks(currentUser);
          break;
        }
        currentUser = currentUser->next;
      }
      break;
    }
    case 2: {
      library.viewAllBooks();
      break;
    }
    case 3: {
      library.viewReturnedBooks();
      break;
    }
    case 4: {
      int userID, bookID;
      string borrowDate;
      cout << "Enter the user ID: ";
      cin >> userID;
      cout << "Enter the book ID to borrow: ";
      cin >> bookID;
      cout << "Enter the borrow date (DD/MM/YYYY): ";
      cin >> borrowDate;

      library.borrowBook(userID, bookID, borrowDate);
      break;
    }
    case 5: {
      int userID, bookID;
      cout << "Enter the user ID: ";
      cin >> userID;
      cout << "Enter the book ID to return: ";
      cin >> bookID;

      library.returnBook(userID, bookID);
      break;
    }
    case 6: {
      library.addNewBook();
      break;
    }
    case 7:
      end = true;
      break;
    default:
      cout << "Invalid choice. Please select a valid option." << endl;
      break;
    }
  }
  if (!end) {
    cout << "Would you like to go back to the menu? " << endl;
    cout << "If yes then press Y, if no press N" << endl;

    do {
      cout << "Choice: ";
      cin >> YN;
      if (!isValidChoice(YN)) {
        cout << "Invalid choice. Please enter 'Y' or 'N'." << endl;
      }
    } while (!isValidChoice(YN));

    if (YN == 'N' || YN == 'n') {
      end = true;
    }
  }
  cout << "Thank you for using our admin dashboard ,Goodbye People!" << endl;
  return 0;
}