// Tuan Lai
// Section #2
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

void printMenu() {
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}


void readBooks(vector<Book *> & myBooks) {
  Book * bookPtr;
  int bookID;
  string title,author, category;

  ifstream inData ("books.txt");
  while(inData)
  {
    inData>>bookID;
    getline(inData,title);
    getline(inData,author);
    inData>>category;
    bookPtr = new Book(bookID,title,author,category);
    myBooks.push_back(bookPtr);
  }
  inData.close();
}

int readPersons(vector<Person *> & myCardholders) {
  Person * personPtr;
  int cardID,i = 0;
  bool active;
  string firstName, lastName;

  ifstream inData ("persons.txt");
  while(inData)
  {
    inData>>cardID;
    inData>>active;
    inData>>firstName;
    inData>>lastName;
    personPtr = new Person(cardID,active,firstName,lastName);
    myCardholders.push_back(personPtr);
    ++i;
  }
  inData.close();
    return i;
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {

  int bookID, cardID;
  int b = myBooks.size();
  int p = myCardholders.size();
  ifstream inData ("rentals.txt");
  while(inData)
  {
    inData>>bookID;
    inData>>cardID;
    for(int i = 0; i<b;++i)
    {
      if(bookID == myBooks[i]->getId())
      {
        for(int j=0; j<p;++j)
        {
          if(cardID == myCardholders[j]->getId())
          {
            myBooks[i]->setPersonPtr(myCardholders[j]);
          }
        }
      }
    }

  }
  inData.close();

}



/*
void openCard(vector<Person *> & myCardholders, int nextID) {

    return;
}



Book * searchBook(vector<Book *> myBooks, int id) {
    return nullptr;
}
*/

void checkOut(vector<Book*>&myBooks, vector<Person*>&myCardholders)
{
  int cardID,bookID;
  int j=0;
  int b = myBooks.size();
  int p = myCardholders.size();
  cout<<"Please enter the card ID: ";
  cin>>cardID;
  cout<<endl;
  for(int i = 0;i<p;++i)
  {
    if(cardID == myCardholders[i]->getId())
    {
      j=i;
      cout<<"Card holder: "<<(*myCardholders.at(i)).fullName()<<endl;

    }else{
      cout<<"Card ID not found"<<endl;
    }
  }
  cout<<"Please enter the book ID: ";
  cin>>bookID;
  for(int i =0; i<b;++i)
  {
    if(bookID == myBooks[i]->getId())
    {
      cout<<"Title: ";
      cout<<(*myBooks.at(i)).getTitle()<<endl;
      cout<<"Rental Completed"<<endl;
      myBooks[i]->setPersonPtr(myCardholders[j]);
    }else{
      cout<<"Book ID not found"<<endl;
    }
  }
}



int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;

    int choice;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that
        // the user pressed when entering a menu option. This is still in the input stream.
        printMenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                checkOut(books,cardholders);// Book checkout
                break;

            case 2:
                // Book return
                break;

            case 3:
                // View all available books
                break;

            case 4:
                // View all outstanding rentals
                break;

            case 5:
                // View outstanding rentals for a cardholder
                break;

            case 6:
                // Open new library card
                break;

            case 7:
                // Close library card
                break;

            case 8:
                // Must update records in files here before exiting the program
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}
