#include  <iostream>
#include  <fstream>
#include  <string>
#include "User.h"

using namespace std;

int option;
string sign_user, sign_pass, login_user, login_pass, saved_user, saved_pass;


int main()
{

    do {
    system("cls");// to clear screen everytime the user input something
    int exist = 0;
    cout << "=========================" <<endl;
    cout << "        MMU Portal       " <<endl;
    cout << "=========================" <<endl;
    cout << "1. Sign up" <<endl;
    cout << "2. Login " <<endl;
    cout << "3. Exit" <<endl;
    cout << " Type 1 to sign up, 2 to login or 3 to exit. " <<endl;
    cin >> option;

    if (option == 1)
    {
    system("cls");
    cout << "=========================" <<endl;
    cout << "       Signup Page       " <<endl;
    cout << "=========================" <<endl;
    cout << "Enter your username: ";
    cin >>sign_user;
    cout << "Enter your password: ";
    cin >>sign_pass;

    ofstream outFile("Database.txt", ios::app);
    outFile << sign_user << " "<< sign_pass << endl;
    outFile.close();

    cout << "Registration complete!" <<endl;
    }

    else if (option == 2)
    {
    system("cls");
    cout << "=========================" <<endl;
    cout << "        Login page       " <<endl;
    cout << "=========================" <<endl;
    cout << "Username:";
    cin >> login_user;
    cout << "Password:";
    cin >> login_pass;

    ifstream inFile("database.txt");

    if (!inFile)
    {
      cout << "No username exist. Please sign up first." <<endl;
      }
    else {
        while (inFile >> saved_user >> saved_pass) { // This is to see if the login user and pass matches the saved user and pass
            if (login_user == saved_user && login_pass == saved_pass) {
                exist = 1;
                }// when it is 1 a match is found
            }
            inFile.close();

            if (exist == 1) {
                system("cls");
                cout << "Welcome, " << login_user << "." <<endl;
                system("..\\CCP6114-Student-Attendance-Tracker-2530\\main.exe");
            }
            
            else {
                cout << "Incorrect username or password."<< endl;
            }
        } system("pause");
    }
    } while (option !=3);
    return 0;
}
