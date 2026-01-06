#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

//struture to store book data
struct Book{
    int id;
    string title;
    string author;
    string status; //"Available" or "Borrowed"
};

//function declarations
void loadFromFile(vector<Book>& books);
void saveToFile(const vector<Book>& books);
void addBook(vector<Book>& books);
void deleteBook(vector<Book>& books);
void displayBooks(const vector<Book>& books);
void searchBook(const vector<Book>& books);
void borrowBook(vector<Book>& books);
void returnBook(vector<Book>& books);

int main(){
    vector<Book> books; // Vector to store all books in memory
    loadFromFile(books); // Load existing records from file
    
    int choice;
    do{
        // Menu
        cout<<"===== Library Book Management System =====\n";
        cout<<"1. Add Book\n2. Delete Book\n3. Display All Books\n4. Search Book\n";
        cout<<"5. Borrow Book\n6. Return Book\n7. Save & Exit\n";
        cout<<"Enter Choice [1 to 7 only]:";
        cin>>choice; // User input
            
        switch (choice){
            case 1: addBook(books);break; // Add a new book
            case 2: deleteBook(books);break;//delete a book
            case 3: displayBooks(books);break; // Display all books
            case 4: searchBook(books);break; // Search for a book
            case 5: borrowBook(books);break; // Borrow a book
            case 6: returnBook(books);break; // Return a book
            case 7: saveToFile(books);cout<<"Saving records... Goodbye!\n";break; // Save before exit
            default: cin.clear();cin.ignore(1000,'\n'); // Handle invalid menu input
            cout<<"Invalid choice! Try again.\n\n";
        }
    }while(choice != 7); // Loop until Exit
    return 0;
}

//for load file
void loadFromFile(vector<Book>& books){
    ifstream file("books.txt"); // Open file for reading
    if (!file) return; //if there is no file, skip
    
    string line;
    while (getline(file, line)){ // Read each line as a book record
        stringstream ss(line); // Convert line into a stream for parsing
        Book b;
        string idStr;
        
        // Extract values separated by "|"
        getline(ss,idStr,'|');
        getline(ss,b.title,'|');
        getline(ss,b.author,'|');
        getline(ss,b.status,'|');
        b.id = stoi(idStr); // string to integer
        books.push_back(b); // Add book to vector
    }
}

//for save file
void saveToFile(const vector<Book>& books){
    ofstream file("books.txt"); // Open file (overwrites existing)
    // Write each book into file
    for (const auto& b : books){
        file<<b.id<<"|"<<b.title<<"|"<<b.author<<"|"<<b.status<<"\n";
    }
    file.close(); // Close file
}

//for add book
void addBook(vector<Book>& books){
    Book b;
    cout<<"\n[ADD BOOK]\nEnter Book ID: ";
    cin>>b.id;
    cin.ignore(); // Clear leftover newline

    // Check for duplicate ID
    for (const auto& book : books){
        if (book.id == b.id){
            cout<<"Error: This ID already exists! Book NOT added.\n\n";
            return;
        }
    }

    cout<<"Enter Title: ";
    getline(cin, b.title);

    // Check for duplicate Title
    for (const auto& book : books){
        if (book.title == b.title){
            cout<<"Error: This title already exists! Book NOT added.\n\n";
            return;
        }
    }

    cout<<"Enter Author: ";
    getline(cin, b.author);

    b.status = "Available"; // New books always available
    books.push_back(b); // Add to vector
    cout<<"Book added successfully!\n\n";
}

//for delete book
void deleteBook(vector<Book>& books){
    cout << "\n[Delete Book}\n Enter Book ID to delete: ";
    int id;
    cin >> id;
    cin.clear();
    cin.ignore(1000, '\n');
    
    bool found = false;
    
    //use iterators to traverse a vector
    for(auto it = books.begin(); it!=books.end(); ++it){
        if(it->id == id){
            if(it->status == "Borrowed"){
                cout << "ERROR: Cannot delete a borrowed book! Ask user to return it first.\n\n";
                return;
            }
            cout << "Are you sure you want to delete this book?(Y/N):";
            char confirm;
            cin >> confirm;
            
            if (confirm == 'y' || confirm == 'Y'){
                books.erase(it);
                cout << "Book deleted successfully.\n\n";
                return;
            }
            else{
                cout << "Deletion cancelled.\n\n";
            }
            if (!found);
            cout << "Book ID not found.\n\n";
            return;
        }
    }
    if (!found){
    cout << "Book ID not found.\n\n";
    return;
    }
}

//for display book
void displayBooks(const vector<Book>& books){
    cout<<"\n[Display All Books]\n";
    // Loop through vector and print each book
    for (const auto& b : books){
        cout<<"ID: "<<b.id<<" | Title: "<<b.title<<" | Author: "<<b.author<<" | Status: "<<b.status<<'\n'<<endl;
    }
}

//for search book
void searchBook(const vector<Book>& books){
    cout<<"\n[SEARCH BOOK]\nSearch by (1) ID or (2) Title: ";
    int option; cin>>option;
    cin.ignore();
    
    // Search by ID
    if(option == 1){
        int id;
        cout<<"Enter ID: ";
        cin>>id;
        for (const auto& b : books){
            if(b.id == id){
                cout<<"Found: "<<b.title<<" by "<<b.author<<" | Status: "<<b.status<<'\n'<<endl;
                return;
            }
        }
    }
    // Search by title
    else if(option == 2){
        string title;
        cout<<"Enter Title: ";
        getline(cin, title);
        for (const auto& b : books){
            if(b.title == title){
                cout<<"Found: ID "<<b.id<<" | Author: "<<b.author<<" | Status: "<<b.status<<'\n'<<endl;
                return;
            }
        }
    }
    cout<<"Book not found or invalid input.\n\n";
}

//for borrow book
void borrowBook(vector<Book>& books){
    cout<<"\n[BORROW BOOK]\nEnter Book ID: ";
    int id; cin>>id;
    cin.clear();cin.ignore(1000,'\n');
    for(auto& b : books){
        if(b.id==id){ // Match found
            if(b.status == "Available"){
                b.status = "Borrowed"; // Change status
                cout<<"Book borrowed successfully!\n\n";
            }
            else{
                cout<<"Book already Borrowed.\n\n";
            }
            return;
        }
    }
    cout<<"Book not found!\n\n";
}

//for return book
void returnBook(vector<Book>& books){
    cout<<"\n[RETURN BOOK]\nEnter book ID: ";
    int id; cin>>id;
    cin.clear();cin.ignore(1000,'\n');
    for(auto& b : books){
        if(b.id == id){
            if(b.status == "Borrowed"){
                b.status = "Available"; // Change status back
                cout<<"Book returned successfully!\n\n";
            }
            else{
                cout<<"Book was not borrowed.\n\n";
            }
            return;
        }
    }
    cout<<"Book not found!\n\n";
}