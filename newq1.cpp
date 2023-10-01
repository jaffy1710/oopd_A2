#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "library.h"
#include <ctime>
using namespace std;
const int MAX_ITEMS = 100;
Book *books[MAX_ITEMS];
Journal *journals[MAX_ITEMS];
Magazine *magazines[MAX_ITEMS];

int CSVReader::readbooks(string &filename, Book *books[], int &bookcount)
{
    ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Could not open the CSV file." << std::endl;
        return 1; // Exit with an error code
    }

    string header;
    if (getline(inputFile, header))
    {
        // Assuming the CSV file has a header row, you can ignore it
    }

    string line;
    while (getline(inputFile, line) && bookcount < MAX_ITEMS)
    {
        stringstream ss(line);
        string token;
        int id=0;

        if (getline(ss, token, ','))
        {
            id = stoi(token);
        }
        if (std::getline(ss, token, ','))
        {
            // You can choose to use token or simply ignore it
        }
        if (std::getline(ss, token, ','))
        {
            // You can choose to use token or simply ignore it
        }
        if (std::getline(ss, token, ','))
        {
            // You can choose to use token or simply ignore it
        }
        double count=0.0, isbn=0.0;
        if (getline(ss, token, ','))
        {
            count = stod(token);
        }
        if (getline(ss, token, ','))
        {
            isbn = stod(token);
        }

        if (std::getline(ss, token, ','))
        {
            // You can choose to use token or simply ignore it
        }
        string author;
        if (getline(ss, author, ','))
        {
        }

        if (std::getline(ss, token, ','))
        {
            // You can choose to use token or simply ignore it
        }
        if (std::getline(ss, token, ','))
        {
            // You can choose to use token or simply ignore it
        }

        string title;
        if (getline(ss, title, ','))
        {
            // Create a new Book object and store it in the array
            books[bookcount] = new Book(id, count, isbn, author, title);
            bookcount++;
        }
    }

    inputFile.close();
    return 0;
}
int CSVReader::readjournal(string &filename, Journal *journals[], int &journalcount)
{
    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open the CSV file." << endl;
        return 1; // Exit with an error code
    }

    string line;
    while (std::getline(inputFile, line) && journalcount < MAX_ITEMS)
    {
        size_t pos = line.find(",,");
        while (pos != string::npos)
        {
            line.replace(pos, 2, ",");
            pos = line.find(",,", pos + 1);
        }
        stringstream ss(line);
        string token;
        string publisher_name;
        if (getline(ss, publisher_name, ','))
        {
            journals[journalcount] = new Journal(publisher_name);
            journalcount++;
        }
    }

    // Close the CSV file
    inputFile.close();

    return 0; // Success
}
int CSVReader::readmagazine(string &filename, Magazine *magazines[], int &magazinecount)
{
    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open the CSV file." << endl;
        return 1; // Exit with an error code
    }
    string header;
    if (getline(inputFile, header))
    {
        // Assuming the CSV file has a header row, you can ignore it
    }

    string line;
    while (getline(inputFile, line) && magazinecount < MAX_ITEMS)
    {
        stringstream ss(line);
        string token;
        string name;
        if (getline(ss, name, ','))
        {
            magazines[magazinecount] = new Magazine(name);
            magazinecount++;
        }
    }
    inputFile.close();

    return 0;
}

string getCurrentDate()
{
    time_t now = time(0);
    string dt = ctime(&now);

    cout << "The local date and time is: " << dt << endl;
    tm *gmtm = gmtime(&now);
    dt = asctime(gmtm);
    cout << "The UTC date and time is:" << dt << endl;
    return dt;
}

int main()
{
    int magazinecount = 0;
    int bookcount = 0;
    int journalcount = 0;
    int mid = 1;
    int jid = 1;
    int choice;
    string filename1 = "books.csv";
    string filename2 = "journals.csv";
    string filename3 = "magazines.csv"; 

    CSVReader csvReader;  
           
    csvReader.readbooks(filename1, books, bookcount);
    csvReader.readjournal(filename2, journals, journalcount);
    csvReader.readmagazine(filename3, magazines, magazinecount);
    User user2;

    cout << "IIITD Library " << endl;
    cout << "1. Read Books" << endl;
    cout << "2. Read Journals" << endl;
    cout << "3. Read Magazines" << endl;
    cout << "4. Borrow an item" << endl;
    cout << "5.Register new user" << endl;
    cout<<"6. Purchase of new book"<<endl;
    cout<<"7.Journals to be subscribed"<<endl;
    cout << "Enter your choice" << endl;
    cin >> choice;
    User user;
    string borrow_itemtype;
    bool foundInCurrentLibrary=false;
    string searchoption;
    int journal_counters[MAX_ITEMS] = {0};
    switch (choice)
    {
    case 1:
        if (csvReader.readbooks(filename1, books, bookcount) != 0)
        {
            return 1; // Exit with an error code
        }
        cout << "Books:" << endl;
        for (int i = 0; i < bookcount; i++)
        {
            Book *book = books[i];
            cout << "ID: " << book->id << ", BOOK COUNT:  " << book->count << ",ISBN:  " << book->isbn << ", AUTHOR:  " << book->author << ", TITLE:  " << book->title << endl;
        }
        break;
    case 2:
        if (csvReader.readjournal(filename2, journals, journalcount) != 0)
        {
            return 1; // Exit with an error code
        }

        cout << "Journals" << endl;
        for (int i = 0; i < journalcount; i++)
        {
            Journal *journal = journals[i];

            cout << "ID: " << jid << "  PUBLISHER NAME: " << journal->publisher_name << endl;
            journal_counters[i]++;
            jid++;
        }
        break;

    case 3:

        if (csvReader.readmagazine(filename3, magazines, magazinecount) != 0)
        {
            return 1;
        }

        cout << "Magazines" << endl;
        for (int i = 0; i < magazinecount; i++)
        {
            Magazine *magazine = magazines[i];
            cout << "ID: " << mid << "  Magazine name: " << magazine->name << endl;
            mid++;
        }
        break;

    case 4:
        cout << "Enter user type (student or faculty): " << endl;
        cin >> user.type;

        cout << "Enter item type to borrow (Book, Journal, Magazine): " << endl;
        cin >> borrow_itemtype;
        
        
        if (user.type == "student")
        {
            if (borrow_itemtype == "book")
            {
                
                cout << "You want to search on what basis(title,author,isbn)" << endl;
                cin >> searchoption;
                
                if (searchoption == "title")
                {
                    string title_search;
                    cout << "Enter the exact title to search for " << endl;
                    cin.ignore();
                    getline(cin, title_search);
                    
                    
                    for (int i = 0; i < bookcount; i++)
                    {
                        // cout<<books[i]->title;
                        if ((books[i]->title == title_search) && (books[i]->getAvailability()==true))
                        {
                            foundInCurrentLibrary = true;
                            cout << "Book found" << endl;
                            cout << "ID: " << books[i]->id << ", BOOK COUNT: " << books[i]->count << ", ISBN: " << books[i]->isbn << ", AUTHOR: " << books[i]->author << ", TITLE: " << books[i]->title << endl;
                            cout << "It is at location Ground Floor ,Reading section shelf 1" << endl;
                            cout << "Book has been borrowed" << endl;
                            user.setBorrowedDate(getCurrentDate());
                        }
                    }

                    if (!foundInCurrentLibrary) {
                cout << "Book not found in your library. Searching in other libraries..." << endl;

                // Simulate the 7-day delay for borrowing from other libraries
                cout << "You can borrow this book from Central library,New delhi after 7 days." << endl;
                const int secondsInADay = 24 * 60 * 60;
                const int delayDays = 7;
                time_t startTime = time(nullptr);
                time_t endTime = startTime + (secondsInADay * delayDays);

                while (time(nullptr) < endTime) {
                    // Wait until the specified delay has passed
                }
                
                user.setBorrowedDate(getCurrentDate());
                cout << "You can now borrow the book." << endl;
            }
                }

                if (searchoption == "author")
                {
                    string author_search;
                    cout << "Enter the exact author name to search for " << endl;
                    cin.ignore();
                    getline(cin, author_search);

                    for (int i = 0; i < bookcount; i++)
                    {

                        if ((books[i]->author == author_search) &&(books[i]->getAvailability()==true))
                        {
                            foundInCurrentLibrary = true;
                            cout << "Book found" << endl;
                            cout << "ID: " << books[i]->id << ", BOOK COUNT: " << books[i]->count << ", ISBN: " << books[i]->isbn << ", AUTHOR: " << books[i]->author << ", TITLE: " << books[i]->title << endl;
                            cout << "It is at location Ground Floor ,Reading section shelf 1" << endl;
                            cout << "Book has been borrowed" << endl;
                            user.setBorrowedDate(getCurrentDate());
                        }
                    }
                    if (!foundInCurrentLibrary) {
                cout << "Book not found in your library. Searching in other libraries..." << endl;

                // Simulate the 7-day delay for borrowing from other libraries
                cout << "You can borrow this book from Central library,New delhi after 7 days." << endl;
                const int secondsInADay = 24 * 60 * 60;
                const int delayDays = 7;
                time_t startTime = time(nullptr);
                time_t endTime = startTime + (secondsInADay * delayDays);

                while (time(nullptr) < endTime) {
                    // Wait until the specified delay has passed
                }
                
                user.setBorrowedDate(getCurrentDate());
                cout << "You can now borrow the book." << endl;
            }
                }

                if (searchoption == "isbn")
                {
                    double isbn;
                    cout << "Enter the isbn number" << endl;
                    cin >> isbn;

                    for (int i = 0; i < bookcount; i++)
                    {

                        if ((books[i]->isbn == isbn) && (books[i]->getAvailability()==true))
                        {

                            cout << "Book found" << endl;
                            cout << "ID: " << books[i]->id << ", BOOK COUNT: " << books[i]->count << ", ISBN: " << books[i]->isbn << ", AUTHOR: " << books[i]->author << ", TITLE: " << books[i]->title << endl;
                            cout << "It is at location Ground Floor ,Reading section shelf 1" << endl;
                            cout << "Book has been borrowed" << endl;
                            user.setBorrowedDate(getCurrentDate());
                        }
                    }
                }
            }
            if (borrow_itemtype == "journal")
            {
                string j_name;
                cout << "Enter the title" << endl;
                cin.ignore();
                getline(cin, j_name);

                for (int i = 0; i < journalcount; i++)
                {
                    // cout<<journals[i]->publisher_name<<endl;
                    if ((journals[i]->publisher_name == j_name)&& (journals[i]->getAvailability()==true))
                    {

                        cout << "Journal found" << endl;
                        // cout << "ID: " << journals[i]->id <<"Title "<<journals[i]->publisher_name<< endl;

                        cout << "It is present online and have no due dates" << endl;
                        cout << "Journal has been borrowed" << endl;
                        user.setBorrowedDate(getCurrentDate());
                    }
                }
            }
            if (borrow_itemtype == "magazine")
            {
                string mag_name;
                cout << "Enter the title" << endl;
                cin.ignore();
                getline(cin, mag_name);
                bool mag=false;

                for (int i = 0; i < magazinecount; i++)
                {
                    // cout<<journals[i]->publisher_name<<endl;
                    if ((magazines[i]->name == mag_name)&& (magazines[i]->getAvailability()==true))
                    {
                        mag=true;
                        cout << "Magazine found" << endl;
                        // cout << "ID: " << journals[i]->id <<"Title "<<journals[i]->publisher_name<< endl;

                        cout << "It is present at first floor in the room 20 at shelf 5" << endl;
                        cout << "Magazine has been borrowed" << endl;
                        user.setBorrowedDate(getCurrentDate());
                    }
                }
                if (!mag) {
                cout << "Magazine not found in your library. Searching in other libraries..." << endl;

                // Simulate the 7-day delay for borrowing from other libraries
                cout << "You can borrow this book from Indian library,New delhi after 7 days." << endl;
                const int secondsInADay = 24 * 60 * 60;
                const int delayDays = 7;
                time_t startTime = time(nullptr);
                time_t endTime = startTime + (secondsInADay * delayDays);

                while (time(nullptr) < endTime) {
                    // Wait until the specified delay has passed
                }
                
                user.setBorrowedDate(getCurrentDate());
                cout << "You can now borrow the Magazine." << endl;
            }
            }
        }
        if (user.type == "faculty")
        {
            if (borrow_itemtype == "book")
            {
                
                cout << "You want to search on what basis(title,author,isbn)" << endl;
                cin >> searchoption;
                if (searchoption == "title")
                {
                    string title_search;
                    cout << "Enter the exact title to search for " << endl;
                    cin.ignore();
                    getline(cin, title_search);

                    for (int i = 0; i < bookcount; i++)
                    {
                        // cout<<books[i]->title;
                        if ((books[i]->title == title_search) && (books[i]->getAvailability()==true))
                        {
                            foundInCurrentLibrary = true;
                            cout << "Book found" << endl;
                            cout << "ID: " << books[i]->id << ", BOOK COUNT: " << books[i]->count << ", ISBN: " << books[i]->isbn << ", AUTHOR: " << books[i]->author << ", TITLE: " << books[i]->title << endl;
                            cout << "It is at location Ground Floor ,Reading section shelf 1" << endl;
                            cout << "Book has been borrowed" << endl;
                            user.setBorrowedDate(getCurrentDate());
                        }
                    }
                    if (!foundInCurrentLibrary) {
                cout << "Book not found in your library. Searching in other libraries..." << endl;

                // Simulate the 7-day delay for borrowing from other libraries
                cout << "You can borrow this book from Central library,New delhi after 7 days." << endl;
                const int secondsInADay = 24 * 60 * 60;
                const int delayDays = 7;
                time_t startTime = time(nullptr);
                time_t endTime = startTime + (secondsInADay * delayDays);

                while (time(nullptr) < endTime) {
                    // Wait until the specified delay has passed
                }
                
                user.setBorrowedDate(getCurrentDate());
                cout << "You can now borrow the book." << endl;
                }
                if (searchoption== "author")
                {
                    string author_search;
                    cout << "Enter the exact author name to search for " << endl;
                    cin.ignore();
                    getline(cin, author_search);

                    for (int i = 0; i < bookcount; i++)
                    {

                        if ((books[i]->author == author_search) && (books[i]->getAvailability()==true))
                        {
                            foundInCurrentLibrary = true;
                            cout << "Book found" << endl;
                            cout << "ID: " << books[i]->id << ", BOOK COUNT: " << books[i]->count << ", ISBN: " << books[i]->isbn << ", AUTHOR: " << books[i]->author << ", TITLE: " << books[i]->title << endl;
                            cout << "It is at location Ground Floor ,Reading section shelf 1" << endl;
                            cout << "Book has been borrowed" << endl;
                            user.setBorrowedDate(getCurrentDate());
                        }
                    }
                    if (!foundInCurrentLibrary) {
                cout << "Book not found in your library. Searching in other libraries..." << endl;

                // Simulate the 7-day delay for borrowing from other libraries
                cout << "You can borrow this book from Central library,New delhi after 7 days." << endl;
                const int secondsInADay = 24 * 60 * 60;
                const int delayDays = 7;
                time_t startTime = time(nullptr);
                time_t endTime = startTime + (secondsInADay * delayDays);

                while (time(nullptr) < endTime) {
                    // Wait until the specified delay has passed
                }
                
                user.setBorrowedDate(getCurrentDate());
                cout << "You can now borrow the book." << endl;
                }
                if (searchoption == "isbn")
                {
                    double isbn;
                    cout << "Enter the isbn number" << endl;
                    cin >> isbn;

                    for (int i = 0; i < bookcount; i++)
                    {

                        if ((books[i]->isbn == isbn)&& (books[i]->getAvailability()==true))
                        {

                            cout << "Book found" << endl;
                            cout << "ID: " << books[i]->id << ", BOOK COUNT: " << books[i]->count << ", ISBN: " << books[i]->isbn << ", AUTHOR: " << books[i]->author << ", TITLE: " << books[i]->title << endl;
                            cout << "It is at location Ground Floor ,Reading section shelf 1" << endl;
                            cout << "Book has been borrowed" << endl;
                            user.setBorrowedDate(getCurrentDate());
                        }
                    }
                }
            }
            if (borrow_itemtype == "journal")
            {
                string j_name;
                cout << "Enter the title" << endl;
                cin.ignore();
                getline(cin, j_name);

                for (int i = 0; i < journalcount; i++)
                {
                    // cout<<journals[i]->publisher_name<<endl;
                    if ((journals[i]->publisher_name == j_name)&& journals[i]->getAvailability()==true)
                    {

                        cout << "Journal found" << endl;
                        // cout << "ID: " << journals[i]->id <<"Title "<<journals[i]->publisher_name<< endl;

                        cout << "It is present online and have no due dates" << endl;
                        cout << "Journal has been borrowed" << endl;
                        user.setBorrowedDate(getCurrentDate());
                    }
                }
            }
            if (borrow_itemtype == "magazine")
            {
                string mag_name;
                cout << "Enter the title" << endl;
                cin.ignore();
                getline(cin, mag_name);
                bool mag=false;

                for (int i = 0; i < magazinecount; i++)
                {
                    // cout<<journals[i]->publisher_name<<endl;
                    if ((magazines[i]->name == mag_name) && (magazines[i]->getAvailability()==true))
                    {
                        mag=true;
                        cout << "Magazine found" << endl;
                        // cout << "ID: " << journals[i]->id <<"Title "<<journals[i]->publisher_name<< endl;

                        cout << "It is present at first floor in the room 20 at shelf 5" << endl;
                        cout << "Magazine has been borrowed" << endl;
                        user.setBorrowedDate(getCurrentDate());
                    }
                }
                if (!mag) 
                {
                cout << "Magazine not found in your library. Searching in other libraries..." << endl;

                // Simulate the 7-day delay for borrowing from other libraries
                cout << "You can borrow this book from Indian library,New delhi after 7 days." << endl;
                const int secondsInADay = 24 * 60 * 60;
                const int delayDays = 7;
                time_t startTime = time(nullptr);
                time_t endTime = startTime + (secondsInADay * delayDays);

                while (time(nullptr) < endTime) {
                    // Wait until the specified delay has passed
                }
                
                user.setBorrowedDate(getCurrentDate());
                cout << "You can now borrow the Magazine." << endl;
            }
            }
        }

            break;
        case 5:
            user2 = registerUser();
            break;
        case 6:
            book_purchase(); 
        case 7:
            cout << "Journals borrowed more than 2 times can be subscribed and their names are:" << endl;
            for (int i = 0; i < journalcount; i++)
            {
                 if (journal_counters[i] > 2)
                    {
                         cout << "Journal ID " << i << ": " << journals[i]->publisher_name << endl;
                    }
            }
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        return 0;
    }
    }     
}

