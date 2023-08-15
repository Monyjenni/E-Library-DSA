#include <iostream>
#include <string>
using namespace std;

class Book {
public:
  int id;
  string title;
  string author;

  Book(int i, const string &t, const string &a) : id(i), title(t), author(a) {}
};

class Node {
public:
  Book *data;
  Node *next;

  Node(Book *book) : data(book), next(nullptr) {}
};

class Library {
public:
  Node *head;

  Library() : head(nullptr) {}

  void addBook(Book *book) {
    Node *newNode = new Node(book);
    if (!head) {
      head = newNode;
    } else {
      Node *temp = head;
      while (temp->next) {
        temp = temp->next;
      }
      temp->next = newNode;
    }
  }

  void viewBorrowedBook(int bookId, Library library) {
    Book *borrowedBook = library.searchBookById(bookId);

    if (borrowedBook) {
      cout << "Borrowed Book Details:" << endl;
      cout << "ID: " << borrowedBook->id << endl;
      cout << "Title: " << borrowedBook->title << endl;
      cout << "Author: " << borrowedBook->author << endl;
    } else {
      cout << "Book with ID " << bookId << " is not available." << endl;
    }
  }

  Book *searchBookById(int bookId) {
    Node *current = head;

    while (current) {
      if (current->data->id == bookId) {
        return current->data;
      }
      current = current->next;
    }

    return nullptr; // Book not found
  }
};

int main() {
  Library library;

  Book book1(1, "The Catcher in the Rye", "J.D. Salinger");
  Book book2(2, "To Kill a Mockingbird", "Harper Lee");
  Book book3(3, "1984", "George Orwell");

  library.addBook(&book1);
  library.addBook(&book2);
  library.addBook(&book3);

  int searchId;
  cout << "Enter the ID of the book you want to search: ";
  cin >> searchId;

  Book *foundBook = library.searchBookById(searchId);

  if (foundBook) {
    cout << "Book found:" << endl;
    cout << "ID: " << foundBook->id << endl;
    cout << "Title: " << foundBook->title << endl;
    cout << "Author: " << foundBook->author << endl;
  } else {
    cout << "Book with ID " << searchId << " not available." << endl;
  }

  return 0;
}
