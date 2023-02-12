#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
#include<stdio.h>
using namespace std;


bool SearchUser(string regNos[],int size){
    string StudentRegNo;
    cout<<"Please enter the 3 digit reg-no of the user who entered the library to loan/return a book: ";
    cin>>StudentRegNo;
    while(stoi(StudentRegNo)<100 || stoi(StudentRegNo)>999){
        cout<<"\nReg-no must be of 3 digits. Enter again: ";
        cin>>StudentRegNo;
    }
    for(int i = 0; i<size;i++){
        if(StudentRegNo == regNos[i]){
            cout<<"\nThis user already exists. You may loan/return a book from this user or delete this user from the system.\n";
            return true;
        }
        
    }
    return false;

}


void AddUser(string regNos[],string names[],string NoOfBooks[],int index){
    string RegisterNewRegNo, RegisterNewName,RegisterNewNoOfBooks;
    cout<<"\nEnter the three digit reg-no of the new user to be stored into the system: ";
    cin>>RegisterNewRegNo;
    while(stoi(RegisterNewRegNo)<100 || stoi(RegisterNewRegNo)>999){
        cout<<"\nReg-no must be of 3 digits. Enter again: ";
        cin>>RegisterNewRegNo;
    }

    cout<<"\nEnter the first name of the new user to be stored into the system: ";
    cin>>RegisterNewName;
    cout<<"\nEnter the number of books(between 1 and 3 included) the new user wants to issue: ";
    cin>>RegisterNewNoOfBooks;
    while(RegisterNewNoOfBooks<"0" || RegisterNewNoOfBooks>"3"){
        cout<<"\nOne user can only loan upto 3 books at a time. Enter again: ";
        cin>>RegisterNewNoOfBooks;
    }

    fstream user_file;
    user_file.open("LibraryUsers.txt", ios::app);
    regNos[index] = RegisterNewRegNo;
    names[index] = RegisterNewName;
    NoOfBooks[index] = RegisterNewNoOfBooks;
    user_file<<endl<<regNos[index]<<","<<names[index]<<","<<NoOfBooks[index];
    user_file.close();
    cout<<"\n--------NEW USER ADDED TO THE SYSTEM SUCCESSFULLY. Please open the user file to see the updated record--------\n";
}

void DisplayExistingUsers(string regno[], string stdname[], string NoOfBooks[], int size){

    cout<<endl<<"EXISTING USERS"<<endl<<"reg-no\t"<<"names\t"<<"number of books issued\n\n";
    for(int i = 0; i<size; i++){
        cout<<regno[i]<<"\t"<<stdname[i]<<"\t"<<NoOfBooks[i]<<endl;
    }

}

void DisplayExistingBooks(string bookname[], string numofbooks[], int size){
    cout<<endl<<"EXISTING BOOKS"<<endl<<"Book Name\t\t"<<"number of books\n";
    for(int j = 0; j<size; j++){
        cout<<bookname[j]<<"----------"<<numofbooks[j]<<"\t"<<endl;
    }
}


void DisplaySortedUsers(string stdnames[], int size){
    int i;
    string temp;
    for(int i = size; i>0; i--){
        for(int j = 0; j<i; j++){
            if(stdnames[j] > stdnames[j+1]){
                temp = stdnames[j];
                stdnames[j] = stdnames[j+1];
                stdnames[j+1] = temp;

            }
        }
    }
    cout<<endl<<"--------USERS IN SORTED ORDER: --------\n";
    for(int i = 0; i <=size; i++){
        cout<<stdnames[i]<<endl;
    }
    cout<<endl;
}

void DisplayBooks(string bookname[], string availableCopies[]){
     cout<<setw(5)<<"\nName of books\tNumber of copies\n";
    for(int i = 0; i<12;i++){
        cout<<bookname[i]<<setw(8)<<availableCopies[i]<<endl;

    }

}

void OutstandingBooks(string stdRegNos[],string stdnames[], string NoOfBooksLoaned[], int size){
    string InputRegNo;
    cout<<"\nEnter a three digit reg-no of a student to check outstanding books against him/her: ";
    cin>>InputRegNo; 
    while(stoi(InputRegNo)<100 || stoi(InputRegNo)>999){
        cout<<"\nReg-no must be of 3 digits. Enter again: ";
        cin>>InputRegNo;
    }
    cout<<"\n--------SHOWING THE NUMBER OF OUTSTANDING BOOKS AGAINST A USER--------\n";
    for(int i = 0; i<size; i++){
        if(InputRegNo == stdRegNos[i]){
            cout<<"\n ********Number of outstanding books against "<<stdRegNos[i]<<" with name: "<<stdnames[i]<<" is/are: "<<NoOfBooksLoaned[i]<<endl;
            break;
        }
    }

}

string OutstandingBooks(string stdregno[], string noOfbooksloaned[], int size, string inputregno){
    string CurrentNoOfBooks;
    for(int i = 0; i <size; i++){
        if(inputregno == stdregno[i]){
            CurrentNoOfBooks = noOfbooksloaned[i];

            break;
        }
    }
    return CurrentNoOfBooks;

}



void ReturnBook(string regnos[],string stdName[] ,string booknames[],string noOfbooksloaned[],string bookcopies[],int stdsize,int booksize){
    string inputregno, currentNoOfbooks, InputNameOfBook;
    cout<<"\nEnter the 3 digit reg-no of the user who wants to return a book: ";  //function check for validity of reg-no
    cin>>inputregno;
    while(stoi(inputregno)<100 || stoi(inputregno)>999){
        cout<<"\nReg-no must be of 3 digits. Enter again: ";
        cin>>inputregno;
    }

    currentNoOfbooks = OutstandingBooks(regnos,noOfbooksloaned,stdsize,inputregno);
    if(currentNoOfbooks != "0"){
        cout<<"\nPlease enter the name of the book that you want to return. The name must exactly match the books listed above:\n----> ";
        cin.ignore();
        getline(cin, InputNameOfBook);

        bool found = false;
        while(found == false){
            for(int k = 0; k<booksize;k++){
                if(InputNameOfBook == booknames[k])
                found = true;
            }
            if(found==false){
            cout<<"\nThere exists no book of this same name. Please Re-enter the name of the book: ";
            //cin.ignore();
            getline(cin, InputNameOfBook);
            }
        }
        
        int i = 0;
        for(i = 0; i<booksize;i++){
            if(InputNameOfBook == booknames[i])
            break;
        }
        int UpdatedNoOfBooks = stoi(bookcopies[i]) + 1;
        bookcopies[i] = to_string(UpdatedNoOfBooks);
        fstream booksfile;
        booksfile.open("LibraryBooks.txt", ios::out);
        for(int k = 0; k<booksize; k++){
            booksfile<<booknames[k]<<","<<bookcopies[k];
            if(k<booksize-1)
            booksfile<<endl;
        }
        booksfile.close();

        int j;
        for(j = 0; j<stdsize; j++){
            if(inputregno == regnos[j])
            break;
            
        }
        int UpdatedNoOfLoanedBooks = stoi(noOfbooksloaned[j]) - 1;
        noOfbooksloaned[j] = to_string(UpdatedNoOfLoanedBooks); 
        fstream usersfile;
        usersfile.open("LibraryUsers.txt", ios::out);
        for(int k = 0; k<stdsize;k++){
            usersfile<<regnos[k]<<","<<stdName[k]<<","<<noOfbooksloaned[k];
            if(k<stdsize-1)
            usersfile<<endl;
        }
        usersfile.close();
        cout<<"\n--------THE BOOK HAS BEEN RETURNED SUCCESSFULLY. Please open the files to see the new results--------\n";
            
    }
}


void DeleteUser(string stdregnos[], string stdnames[], string booksloaned[], string booknames[], string NoOfcopies[], int studentsize, int booksize){
    string inputregno, currentNoOfbooks;
    cout<<"\nenter a reg-no of a user you would like to delete: ";  //check function for valid reg no
    cin>>inputregno;  

    while(stoi(inputregno)<100 || stoi(inputregno)>999){
        cout<<"\nplease enter a valid three digit reg-no between 100 and 999: ";
        cin>>inputregno;
    }                          
        int i;
        for(i = 0; i <studentsize; i++){
        if(inputregno == stdregnos[i]){
            break;
        }
        }
        int j;
        for(j = i;j<=studentsize-1;j++){
            stdregnos[j] = stdregnos[j+1];
            stdnames[j] = stdnames[j+1];
            booksloaned[j] = booksloaned[j+1];
        }
        fstream usersfile;
        usersfile.open("LibraryUsers.txt", ios::out);
        for(int i = 0; i<studentsize-1;i++){
            
            usersfile<<stdregnos[i]<<","<<stdnames[i]<<","<<booksloaned[i];
            if(i<studentsize-2)
            usersfile<<endl;
        }
        usersfile.close();
        cout<<"\n--------THE USER HAS BEEN DELETED FROM THE FILE SUCCESSFULLY--------\n";
        
}


void BooksStatus(string bookNames[],string NoOfCopies[],int size){
    string status[12] = {" "};
    for(int i = 0; i<size; i++){
        if(NoOfCopies[i]>"0"){
            status[i] = "Available";
        }
        else{
            status[i] = "Not-Available";
        }
    }
    cout<<"\n\tEXISTING BOOKS AND THEIR STATUS: \n";
    for(int j = 0; j<size;j++){
        cout<<bookNames[j]<<"--------"<<status[j]<<endl;
    }
}

void LoanBookToUser(string regnos[], string stdnames[], string BooksLoaned[], string booknames[], string NoOfCopies[], int stdsize, int booksize){
    string inputRegno, InputNameOfBook;
    int i, updatedNoOfLoanedBooks,UpdatedNoOfCopies;

    cout<<"\nEnter the 3 digit reg-no of the user who wants to loan a book: ";
    cin>>inputRegno;

    while(stoi(inputRegno)<100 || stoi(inputRegno)>999){
        cout<<"\nReg-no must be of 3 digits. Enter again: ";
        cin>>inputRegno;
    }

    for(i = 0; i<stdsize; i++){
        if(inputRegno == regnos[i])
        break;
    }
    if(BooksLoaned[i] == "3"){
        cout<<"\n--------THIS USER ALREADY HAS 3 BOOKS. MORE THAN 3 BOOKS CAN NOT BE LOANED--------";

    }


    else if(BooksLoaned[i] >="0" && BooksLoaned[i] < "3"){
        cout<<"\nPlease enter the name of the book that the user would like to loan. The name must exactly match with any one book listed above: ";
        cin.ignore();
        getline(cin,InputNameOfBook);    

        bool found = false;
        while(found == false){
            for(int k = 0; k<booksize;k++){
                if(InputNameOfBook == booknames[k])
                found = true;
            }
            if(found==false){
            cout<<"\nThere exists no book of this same name. Please Re-enter the name of the book: ";
            getline(cin, InputNameOfBook);
            }
        }

        int j;
        for(j = 0; j<booksize;j++){
            if(InputNameOfBook == booknames[j])
            break;
        }
        if(NoOfCopies[j] > "0"){
        cout<<"\n--------LOANING A BOOK TO "<<stdnames[i]<<" --------";
        UpdatedNoOfCopies = stoi(NoOfCopies[j]) - 1;
        NoOfCopies[j] = to_string(UpdatedNoOfCopies);
        updatedNoOfLoanedBooks = stoi(BooksLoaned[i]) + 1;
        BooksLoaned[i] = to_string(updatedNoOfLoanedBooks);
        fstream userfile;
        userfile.open("LibraryUsers.txt", ios::out);
            for(int k = 0; k<stdsize;k++){
                userfile<<regnos[k]<<","<<stdnames[k]<<","<<BooksLoaned[k];
                if(k<stdsize-1)
                userfile<<endl;

            }

        userfile.close();

        fstream bookfile;
        bookfile.open("LibraryBooks.txt", ios::out);
        for(int z = 0; z<booksize;z++){
            bookfile<<booknames[z]<<","<<NoOfCopies[z];
            if(z<booksize-1)
            bookfile<<endl;
        }
        bookfile.close();


        }
        else{
            cout<<"\n--------THIS BOOK IS NOT AVAILABLE SINCE IT HAS 0 COPIES IN THE SYSTEM--------";
        }

    }
}


void DisplayMenu(string stdRegNos[], string stdNames[], string NoOfBooksLoaned[], string Booknames[], string NoOfCopies[], int studentsize, int booksize){
    int option;
    cout<<"\nEnter any option(between 1 and 6) from the menu given below\n"<<"\t1.\tSearch a user and display the number of outstanding books against him/her.\n"<<"\t2.\tDisplay a list of existing users in sorted order.\n"<<"\t3.\tDelete an existing user from the system.\n"<<"\t4.\tLoan a book to the user\n"<<"\t5.\tReturn a book back from a user\n"<<"\t6.\tDisplay a list of existing books and their status\n";
    cout<<"YOUR OPTION ---->";
    cin>>option;
    while(option < 1 || option > 6){
        cout<<"\nPlease enter an option between 1 and 6\nRE-ENTER---->";
        cin>>option;
    }
    switch(option){
        case 1: OutstandingBooks(stdRegNos, stdNames,NoOfBooksLoaned,studentsize);
        break;
        case 2: DisplaySortedUsers(stdNames, studentsize);
        break;
        case 3: DeleteUser(stdRegNos,stdNames,NoOfBooksLoaned, Booknames, NoOfCopies, studentsize, booksize);
        break;
        case 4: LoanBookToUser(stdRegNos, stdNames ,NoOfBooksLoaned, Booknames,NoOfCopies, studentsize, booksize);
        break;
        case 5: ReturnBook(stdRegNos,stdNames,Booknames, NoOfBooksLoaned,NoOfCopies,studentsize,booksize);
        break;
        case 6: BooksStatus(Booknames,NoOfCopies,booksize);
        break;
    }


}

int main()
{
    string regNos[10] = {" "}, names[10] = {" "}, NoOfBooks[10] = {" "};
    string userfileline[10] = {" "};
    bool UserExists;
    fstream user_file;
    user_file.open("LibraryUsers.txt",ios::in);
    int i = 0;
    while(getline(user_file,userfileline[i])){
        regNos[i] = (userfileline[i].substr(0,3));
        names[i] = userfileline[i].substr(4,userfileline[i].length()-6);
        NoOfBooks[i] = (userfileline[i].substr(userfileline[i].length()-1,1));
        i++;
        if(i>9)
            break;
    }
    user_file.close();

    string BookName[12] = {" "}, BookCopies[9] = {" "};    //no more than 9 copies of any book are present with the library
    string bookfileline[12] = {" "};                       //12 books are available with mutiple copies
    fstream book_file;
    book_file.open("LibraryBooks.txt", ios::in);
    int j = 0;
    while(getline(book_file, bookfileline[j]))
    {
        BookName[j] = bookfileline[j].substr(0,bookfileline[j].length()-2);
        BookCopies[j] = bookfileline[j].substr(bookfileline[j].length()-1,1);
        j++;
        
    }
    
    book_file.close();

    DisplayExistingUsers(regNos,names,NoOfBooks,i);
    DisplayExistingBooks(BookName,BookCopies,j);

    UserExists = SearchUser(regNos,i);
    if(!UserExists && i<10){
        cout<<"\nThis user does not exist in the file. Please register this new student.";
        AddUser(regNos,names,NoOfBooks,i);
    }
    if(i>=10)
    cout<<"\nAlready 10 users are present in the library. More than 10 users are not alowed so please come back later\n";
    if(i<10){
    DisplayMenu(regNos, names, NoOfBooks, BookName, BookCopies, i, j);
    }
    return 0;
}