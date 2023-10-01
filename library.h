#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Library {
public:
    int id=0;
    bool available=true;
    Library() : id(0) {}
    Library(int _id) : id(_id) {}

    bool getAvailability() const {
    return available;
}
    void setAvailability(bool _available) {
    available = _available;
}

};

class Book : public Library {
public:
    double count=0.0;
    double isbn=0.0;
    string author;
    string title;
    
    
    Book() : Library(),count(0.0),isbn(0.0), author(""),title("") {}
    Book(int _id,double _count, double _isbn,string& _author,string& _title) : Library(_id),count(_count),isbn(_isbn),author(_author),title(_title) {}

};

Book book_purchase()
{
    // double bookCount, bookISBN;
    // string bookAuthor, bookTitle;
    Book newBook;

    cout << "Enter book author: ";
    cin.ignore(); // Clear the newline character from the previous input
    getline(cin, newBook.author);

    cout << "Enter book title: ";
    getline(cin, newBook.title);

    cout << "Enter book ISBN: ";
    cin >> newBook.isbn;

    cout << "Enter book count: ";
    cin >> newBook.count;

    cout << "New Book Details:" << endl;
    cout << "Author: " << newBook.author << endl;
    cout << "Title: " << newBook.title << endl;
    cout << "ISBN: " << newBook.isbn << endl;
    cout << "Count: " << newBook.count << endl;


    return newBook;
}
class Journal: public Library{
    public:
    string publisher_name;
    Journal(): publisher_name(""){}
    Journal(string& _publisher_name):publisher_name(_publisher_name){}
};

class Magazine: public Library{
    public:
    string name;
    Magazine(): name(""){}
    Magazine(string& _name):name(_name){}
};

class CSVReader {
public:
     int readbooks( string& filename, Book* books[], int& bookcount);
     int readjournal(string&filename, Journal* journals[],int& journalcount);
     int readmagazine(string&filename,Magazine* magazines[],int& magazinecount);
};
 class User{
    public:
    string type;
    string u_name;
    string borrowedDate;
    User(): type(""){}
    User(string _type,string name): type(_type), u_name(name){}
    string getBorrowedDate() const
    {
        return borrowedDate;
    }

    void setBorrowedDate(string date) 
    {
        borrowedDate=date;
    }
    string getusername() const
    {
        return u_name;
    }

    void setusername(string name) 
    {
        u_name=name;
    }
 };
 User registerUser() 
 {
    string userType,name;
    cout<<"Enter the name"<<endl;
    cin>>name;
    cout << "Enter user type (student or faculty): ";
    cin >> userType;

    // Check if the user entered a valid user type (student or faculty)
    while (userType != "student" && userType != "faculty") {
        cout << "Invalid user type. Please enter 'student' or 'faculty': ";
        cin >> userType;
    }

    // Create and return a User object with the specified type
    return User(userType,name);
}
