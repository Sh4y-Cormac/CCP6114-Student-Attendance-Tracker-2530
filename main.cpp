#include <iostream>
#include <string>
#include <vector> // resizeable array or inf amount array

#include <vector>
#include <sstream>
#include <fstream>
#include "functions.h"
using namespace std;

// enum types // types of data in table
//{
//   Bool, = 0
//    String, = 1
//    Float, =2
//   Int = 3

//};
int Userpage();
int main_menu();                 // main menu function that handles user input for main menu
int create_sheet_structure();    // this function handles the sheet structure creation
void create_attendance_row(int); // this function creates the attendance row process

template <typename T>
vector<T> array_to_vector(T some_array[], int array_size); // changes arrays to vectors bcs i fucking love vectors

int choice;
int number_of_columns;          // number of columns that the user specified to add
int attendance_row_value;       // input from user whether to continue the program or not
int current_attendance_row = 1; // measures the current attendance row being used
string new_file_path;
pair<int, string> column_names[10] = {};                                // declares the maximum amount of columns possible
vector<string> student_data{};                                          // ALL STUDENT DATA IS STORED IN THIS VECTOR!
current_table *const current_table_ptr = new current_table("", {}, {}); // makes empty current table that can be accessed

int option;
string sign_user, sign_pass, login_user, login_pass, saved_user, saved_pass;

int main()
{

    if (Userpage() == 1)
    {
        string filename = login_user + ".csv";
        *current_table_ptr = current_table(filename);
        current_table_ptr->display();
        main_menu(); // main menu function call

        cout << "Enter sheet name: " << endl;
        getline(cin, new_file_path);

        // Check if user already added .csv, if not add it
        if (new_file_path.length() < 4 || new_file_path.substr(new_file_path.length() - 4) != ".csv")
        {
            new_file_path += ".csv";
        }

        while (check_if_file_exist(new_file_path)) // checks if file exist, if true, then ask for another sheet name
        {
            cout << "The sheet already exist enter another sheet name: ";
            getline(cin, new_file_path);
            if (new_file_path.length() < 4 || new_file_path.substr(new_file_path.length() - 4) != ".csv")
            {
                new_file_path += ".csv";
            }
        }

        current_table_ptr->file_path = new_file_path;
        new_file_create(current_table_ptr->get_field_type_list(), current_table_ptr->file_path); // creating the file
        saving_file_data(current_table_ptr->get_table(), current_table_ptr->file_path, false);   // writing new file data // uses a 2D vector so it enables to add many rows at once // will skip certain rows if somethings wrong with said rows // if true will append
        *current_table_ptr = current_table(current_table_ptr->file_path);                        // getting table from existing file and writing it to curent file
        current_table_ptr->display();                                                            // display current table content

        delete current_table_ptr; // Free allocated memory
        return 0;
    }
}

int Userpage()
{
    do
    {
        system("cls"); // to clear screen everytime the user input something
        int exist = 0;
        cout << "=========================" << endl;
        cout << "        MMU Portal       " << endl;
        cout << "=========================" << endl;
        cout << "1. Sign up" << endl;
        cout << "2. Login " << endl;
        cout << "3.Exit" << endl;
        cout << " Type 1 to sign up, 2 to login or 3 to exit. " << endl;
        cin >> option;

        if (option == 1)
        {
            system("cls");
            cout << "=========================" << endl;
            cout << "       Signup Page       " << endl;
            cout << "=========================" << endl;
            cout << "No spaces can be added in your username and password" << endl;
            cout << "Enter your username: ";
            cin >> sign_user;
            if (cin.peek() != '\n')
            {
                cout << "No spaces allowed in username!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                system("pause");
            }
            else
            {
                cout << "Enter your password: ";
                cin >> sign_pass;
                if (cin.peek() != '\n')
                {
                    cout << "No spaces allowed in password!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    system("pause");
                }
                else
                {
                    ofstream outFile("Database.txt", ios::app);
                    outFile << sign_user << " " << sign_pass << endl;
                    outFile.close();

                    cout << "Registration complete!" << endl;
                }
            }
            system("pause");
        }

        else if (option == 2)
        {
            system("cls");
            cout << "=========================" << endl;
            cout << "        Login page       " << endl;
            cout << "=========================" << endl;
            cout << "No spaces can be added in your username and password" << endl;
            cout << "Username:";
            cin >> login_user;
            if (cin.peek() != '\n')
            {
                cout << "No spaces allowed in username!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                system("pause");
            }
            else
            {
                cout << "Password:";
                cin >> login_pass;
                if (cin.peek() != '\n')
                {
                    cout << "No spaces allowed in Password!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    system("pause");
                }
                else
                {
                    ifstream inFile("database.txt");

                    if (!inFile)
                    {
                        cout << "No username exist. Please sign up first." << endl;
                    }
                    else
                    {
                        while (inFile >> saved_user >> saved_pass)
                        { // This is to see if the login user and pass matches the saved user and pass
                            if (login_user == saved_user && login_pass == saved_pass)
                            {
                                exist = 1;
                            } // when it is 1 a match is found
                        }
                        inFile.close();

                        if (exist == 1)
                        {
                            system("cls");
                            cout << "Welcome, " << login_user << "." << endl;

                            return 1;
                        }
                        else
                        {
                            cout << "Incorrect username or password." << endl;
                        }
                    }
                }
            }
            system("pause");
        }
        else if (option == 3)
        {
            cout << "Exiting portal...." << endl;
        }
        else
        {
            cout << "Please choose 1,2 or 3 only." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            system("pause");
        }
    } while (option != 3);
    return 0;
}
//*******************************************************************************************

int main_menu()
{
    cout << "================================" << endl;
    cout << "   STUDENT ATTENDANCE TRACKER  " << endl;
    cout << "================================" << endl;
    cout << "\n1. Create new attendance sheet" << endl;
    cout << "2. Load existing attendance sheet" << endl;
    cout << "3. Logout\n"
         << endl;

    cout << "Type 1 to create new attendance sheet, 2 to load existing attendance sheet or 3 to logout: " << endl;

    while (true)
    {
        if (!(cin >> option))
        {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Invalid input. Please enter a number between 1 and 3." << endl;
            continue;
        }

        if (option >= 1 && option <= 3)
        {
            if (option == 1)
            {
                create_sheet_structure();
                cout << "\nSheet structure process has completed！" << endl;
                return 0;
            }

            else if (option == 2)
            {
                string load_file_path;
                cout << "\nEnter existing attendance sheet file path: " << endl;
                cin >> load_file_path;
                if (!check_if_file_exist(load_file_path))
                {
                    cout << "This file doesn't exist" << endl;
                    return main_menu();
                }
                *current_table_ptr = current_table(load_file_path);
                current_table_ptr->display();

                while (true)
                {
                    cout << "\nType 1 to load another file, or 0 to return main menu: " << endl;
                    cin >> choice;

                    if (choice == 0)
                    {
                        return main_menu();
                    }
                    else if (choice == 1)
                    {
                        cout << "Enter existing attendance sheet file path: " << endl;
                        cin >> load_file_path;
                        if (!check_if_file_exist(load_file_path))
                        {
                            cout << "This file doesn't exist" << endl;
                            continue;
                        }
                        *current_table_ptr = current_table(load_file_path);
                        current_table_ptr->display();
                    }
                    else
                    {
                        cout << "Invalid option. Please enter 1 or 0." << endl;
                    }
                }
            }

            else if (option == 3)
            {
                cout << "Logging out..." << endl;
                break;
            }
        }
        else
        {
            cout << "Invalid input. Please enter a number between 1 and 3." << endl;
        }
    }

    return 0;
}

// Asks user for number of columns they want, asks them to name those columns, and asks them
// to data enter any amount of attendance rows they want
int create_sheet_structure()
{
    while (true)
    {
        cout << "Define number of columns (max 10): " << endl;
        cin >> number_of_columns;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(9999, '\n');

            cout << "Define number of columns (max 10): " << endl;
            cin >> number_of_columns;
        }

        if (number_of_columns <= 10 && number_of_columns > 0)
        {
            cin.ignore(9999, '\n'); // Clear the input buffer

            for (int x = 0; x < number_of_columns; x++) // iterates through the specified number of columns, asks for column name for each one and
            {                                           // assigs it to an index inside an array according to order
                string name;
                int type = 0;
                cout << "Enter column " << x + 1 << " name: " << endl;
                getline(cin, name);                     // Use getline to read entire column name with spaces
                while (name != removeSpaces(name, ',')) // get input that doesnt have commas
                {
                    cin.clear();
                    cin.ignore(9999, '\n');
                    cout << "Enter column " << x + 1 << " name (no commas): " << endl;
                    getline(cin, name);
                }
                cout << "Enter column " << x + 1 << " data type (type 0 for bool, 1 for string, 2 for float, 3 for int): " << endl;
                cin >> type;

                while (cin.fail())
                {
                    cin.clear();
                    cin.ignore(9999, '\n');
                    cout << "Enter column " << x + 1 << " data type (type 0 for bool, 1 for string, 2 for float, 3 for int): " << endl;
                    cin >> type;
                }

                cin.ignore(9999, '\n'); // Clear the input buffer after reading type

                column_names[x].first = type;
                column_names[x].second = name, ',';
            }
            *current_table_ptr = current_table("", array_to_vector(column_names, 0 + number_of_columns), {});

            do
            {
                cout << "Press 1 for a new attendance row, Press 2 to exit attendance rows" << endl;
                cin >> attendance_row_value;
                while (cin.fail())
                {
                    cin.clear();
                    cin.ignore(9999, '\n');
                    cout << "Press 1 for a new attendance row, Press 2 to exit attendance rows" << endl;
                    cin >> attendance_row_value;
                }

                cin.ignore(9999, '\n'); // Clear input buffer

                if (attendance_row_value == 1)
                {
                    create_attendance_row(current_attendance_row);
                    current_attendance_row++;
                }
                else if (attendance_row_value == 2)
                {
                    return 0;
                }
                else
                {
                    cout << "Invalid option. Please enter 1 or 2." << endl;
                }

            } while (attendance_row_value != 2);

            return 0;
        }
        else
        {
            cout << "Number of columns has to be a maximum of 10 and bigger than 0" << endl;
        }
    }

    return 0;
}

// the actual attendance row process where data inputted from user gets transferred into the array.
void create_attendance_row(int current_attendance_row)
{
    cout << "------------------------" << endl;
    cout << "Insert new attendance row #" << current_attendance_row << endl;
    cout << "------------------------" << endl;

    for (int x = 0; x < number_of_columns; x++)
    {
        string inputs;
        cout << "Enter " << column_names[x].second << ": ";
        getline(cin, inputs); // Use getline to read entire input including spaces
        // Use getline to read entire column name with spaces
        while (inputs != removeSpaces(inputs, ',')) // get input that doesnt have commas
        {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Enter " << column_names[x].second << " (no commas): ";
            getline(cin, inputs);
        }
        student_data.push_back(inputs); // using vector array, I am adding a datapoint into the array
    }
    current_table_ptr->insert_row(0 + current_table_ptr->get_table().size(), student_data);
    student_data.clear();
}

template <typename T>
vector<T> array_to_vector(T some_array[], int array_size)
{
    vector<T> temp_vector;
    for (int i = 0; i < array_size; i++)
    {
        temp_vector.push_back(some_array[i]);
        // cout << some_array[i].first << some_array[i].second;
    }
    return temp_vector;
}
