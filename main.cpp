// **************************************
// Program: main.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TT1L
// Tutorial Class: TC1L
// Trimester: 2530
// Member 1: 252UC241ST | UMAR ZAID BIN AZZADDIN | UMAR.ZAID.AZZADDIN1@student.mmu.edu.my | 012-8228050
// Member 2: 252UC2421K | Harun bin Ghazari | harun.ghazari@student.mmu.edu.my | 011-26677221
// Member 3: 252UC2421P | Chan Kar Fung | chan.kar.fung1@student.mmu.edu.my | 01161645742
// Member 4: 252UC242FD | Ong Jun Ze | ONG.JUN.ZE1@student.mmu.edu.my | 0166080354
// **************************************
// Task Distribution
// Member 1: Implemented sheet structure inputs such as attendance_sheet_name, number_of_columns, column1_name, column2_name, column3_name.
//           Implemented actual insertations of the attendance rows as well;  Make sure to save all these inside an array for reference for the next person.
//           Create input to name a school term, the school term is our ‘database,’ and we must only be able to use the ‘attendance sheets’ from that database.
// Member 2: File saving, saves the studentID, gets input for data type for each column. saves Name and Status based on the input from the user into a file or CSV.
//           A function can be made with parameters and can be put inside the code of member 2 for saving.
//           Create code to UPDATE and DELETE attendance rows of a designated .csv file, which is to be able to ADD attendance sheets to the designated .csv file; e.g we can choose TT1L.csv that was created beforehand, and add data values to it.
// Member 3: Created a login/signin welcome screen where the lecturer has to sign into her credentials.
//           Implement basic error handling, include file saving as well for passwords and username.
//           Create code to count the number of attendance rows within the selected ‘attendance sheet
// Member 4: Implement a basic directory which main_menu after the original welcome screen, such as “ Type 1 to create a new attendance sheet, 2 to load an existing attendance sheet, or 3 to log out: ”,
//           Implement basic error handling as well, e.g “ Invalid input. Please enter a number between 1 and 3.” All these functions allow a good layout as a user-friendly interface.
//           Handle documentation, including making sure we follow the rubrics correctly. Advanced error handling and validation in the code (e.g., fault run test)

#include <iostream>
#include <string>
#include <vector> // resizeable array or inf amount array
#include <sstream>
#include <fstream>
#include <filesystem> // sole purpose of creating a folder for our database.
#include "functions.h"
using namespace std;

// enum types // types of data in table
//{
//   Bool, = 0
//    String, = 1
//    Float, =2
//   Int = 3

//};
int Userpage(); // This function is to handle user sign up and login
void displayMainMenu();
int main_menu();                      // main menu function that handles user input for main menu
int create_sheet_structure();         // this function handles the sheet structure creation
void create_attendance_row(int);      // this function creates the attendance row process
int load_existing_attendance_sheet(); // function to load existing attendance sheet
void generateSchoolTerm(string);
void deleting_row();
void inserting_row(int);
void update_row();
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
string sign_user, sign_pass, login_user, login_pass, saved_user, saved_pass, term_name;

int main()
{
    bool running = true;

    while (running)
    {
        if (Userpage() == 1)
        {
            int menuResult = main_menu();

            if (menuResult == -1)
            {
                // Logout - just continue the loop to show login page again
                cout << "Logging out..." << endl;
                system("pause");
                continue;
            }
            else if (menuResult == 0)
            {
                // Exit program
                running = false;
            }
        }
        else
        {
            // User chose to exit from login page
            running = false;
        }
    }

    cout << "Exiting program..." << endl;
    return 0;
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

        if (option == 1) // when user type "1" it will bring them to the sign up page
        {
            system("cls");
            cout << "=========================" << endl;
            cout << "       Signup Page       " << endl;
            cout << "=========================" << endl;
            cout << "No spaces can be added in your username and password" << endl;
            cout << "Enter your username: ";
            cin >> sign_user;
            if (cin.peek() != '\n') // anything after the space has any character it will display error message.
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
                    outFile.close(); // This opens up Database.txt and add in username and password into the text file.

                    cout << "Registration complete!" << endl;
                }
            }
            system("pause");
        }

        else if (option == 2) // This is the login page where the user enter the username and password
        {
            system("cls");
            cout << "=========================" << endl;
            cout << "        Login page       " << endl;
            cout << "=========================" << endl;
            cout << "No spaces can be added in your username and password" << endl;
            cout << "Username:";
            cin >> login_user;
            if (cin.peek() != '\n') // same function as when the user sign up
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
                    ifstream inFile("Database.txt");

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
                            } // when it is 1 a match of username and password is found
                        }
                        inFile.close();

                        if (exist == 1) // when the username and password exist in the txt the user can proceed
                        {
                            system("cls");
                            // cout << "Welcome, " << login_user << "." << endl;

                            return 1;
                        }
                        else // if no username is found in the text file it will display the error message below
                        {
                            cout << "Incorrect username or password." << endl;
                        }
                    }
                }
            }
            system("pause");
        }
        else if (option == 3) // this function is to allow the user to quit the program at the menu.
        {
            cout << "Exiting portal...." << endl;
        }
        else // error handling anything that is not 1,2 or 3 it will not allow the user to proceed and send the user back to the menu.
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

void displayMainMenu()
{
    system("cls");
    cout << "\n================================" << endl;
    cout << "   STUDENT ATTENDANCE TRACKER  " << endl;
    cout << "================================" << endl;
    cout << "HI " << login_user << "! Welcome to main menu." << endl;
    cout << "Current term being analysed is: " << term_name << endl;
    cout << "\n1. Create new attendance sheet" << endl;
    cout << "2. Load existing attendance sheet" << endl;
    cout << "3. Logout\n"
         << endl;
    cout << "Type 1 to create a new attendance sheet, 2 to load an existing attendance sheet, or 3 to logout: ";
}

// Creation of the 'database' / defining the selection of term for user
void generateSchoolTerm(string folderName)
{
    if (filesystem::create_directory(folderName))
    {
        cout << "Folder created successfully" << endl;
    }
    else
    {
        cout << "Folder already exists" << endl;
    }
    term_name = folderName;
    system("pause");
}

int main_menu()
{
    string termName;
    cout << "Before we proceed, please enter the school term you wish to analyse: " << endl;
    cin >> termName;
    generateSchoolTerm(termName);

    while (true)
    {
        displayMainMenu();

        while (true)
        {
            if (!(cin >> option))
            {
                cin.clear();
                cin.ignore(9999, '\n');
                cout << "Invalid input. Please enter a number between 1 and 3." << endl;
                system("pause");
                break; // Break to show menu again
            }

            if (option >= 1 && option <= 3)
            {
                if (option == 1)
                {
                    bool returnToMainMenu = false;

                    while (!returnToMainMenu)
                    {
                        create_sheet_structure();
                        cout << "\nSheet structure process has completed! " << endl;

                        // string filename = login_user + ".csv";
                        //  to save the file path so the path becomes "Term1/username.csv"
                        filesystem::path filename = filesystem::path(term_name) / (login_user + ".csv");

                        // Only load if file exists
                        if (filesystem::exists(filename.string()))
                        {
                            *current_table_ptr = current_table(filename.string());
                            current_table_ptr->display();
                        }

                        // Only continue with file creation if we're still here
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter sheet name: " << endl;
                        getline(cin, new_file_path);

                        // Check if user already added .csv, if not add it
                        if (new_file_path.length() < 4 || new_file_path.substr(new_file_path.length() - 4) != ".csv")
                        {
                            new_file_path += ".csv";
                        }

                        while (filesystem::exists(filesystem::path(term_name) / new_file_path)) // checks if file exist, if true, then ask for another sheet name
                        {
                            cout << "The sheet already exist enter another sheet name: ";
                            getline(cin, new_file_path);
                            if (new_file_path.length() < 4 || new_file_path.substr(new_file_path.length() - 4) != ".csv")
                            {
                                new_file_path += ".csv";
                            }
                        }

                        // current_table_ptr->file_path = new_file_path;

                        // concatenates the folder and the .csv file into a file path.
                        filesystem::path fullPath = filesystem::path(term_name) / new_file_path;
                        current_table_ptr->file_path = fullPath.string();

                        // Get the field definitions from column_names array (which was populated in create_sheet_structure)
                        vector<pair<int, string>> field_definitions;

                        for (int i = 0; i < number_of_columns; i++)
                        {
                            field_definitions.push_back(column_names[i]);
                        }

                        new_file_create(field_definitions, current_table_ptr->file_path); // creating the file

                        saving_file_data(current_table_ptr->get_table(), current_table_ptr->file_path, false);

                        saving_file_data(current_table_ptr->get_table(), current_table_ptr->file_path, false);

                        *current_table_ptr = current_table(current_table_ptr->file_path);
                        current_table_ptr->display();
                        // delete current_table_ptr; // Free allocated memory

                        cout << "\nType 1 to create another sheet, or 0 to return main menu: " << endl;
                        cin >> choice;
                        cin.ignore(); // Clear buffer

                        if (choice == 0)
                        {
                            returnToMainMenu = true;
                            break; // Exit create loop
                        }
                        else if (choice != 1)
                        {
                            cout << "Invalid option. Please enter 1 or 0." << endl;
                            system("pause");
                        }
                    }
                    break; // Break to outer loop to show menu again
                }

                else if (option == 2)
                {
                    bool returnToMainMenu = false;

                    while (!returnToMainMenu)
                    {
                        load_existing_attendance_sheet();

                        cout << "\nType 1 to load another file, or 0 to return main menu: " << endl;
                        cin >> choice;
                        cin.ignore(); // Clear buffer

                        if (choice == 0)
                        {
                            returnToMainMenu = true;
                            break; // Exit load loop
                        }
                        else if (choice != 1)
                        {
                            cout << "Invalid option. Please enter 1 or 0." << endl;
                            system("pause");
                        }
                    }
                    break; // Break to outer loop to show menu again
                }

                else if (option == 3)
                {
                    cout << "Logging out..." << endl;
                    system("pause");
                    Userpage(); // Go back to login
                    return -1;  // Indicate logout
                }
            }
            else
            {
                cout << "Invalid input. Please enter a number between 1 and 3." << endl;
                system("pause");
                break; // Break to show menu again
            }
        }
    }

    return 0;
}

// Asks user for number of columns they want, asks them to name those columns, and asks them
// to data enter any amount of attendance rows they want
int create_sheet_structure()
{
    cout << "\n==============================" << endl;
    cout << "   CREATE ATTENDANCE SHEET   " << endl;
    cout << "==============================\n"
         << endl;

    do
    {
        cout << "Define number of columns (max 10): " << endl;
        cin >> number_of_columns;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(9999, '\n');
            number_of_columns = -1; // force retry
        }

        if (number_of_columns <= 0 || number_of_columns > 10)
        {
            cout << "Number of columns has to be between 1 and 10." << endl;
        }

    } while (number_of_columns <= 0 || number_of_columns > 10);

    if (number_of_columns <= 10 && number_of_columns > 0)
    {
        cin.ignore(9999, '\n'); // Clear the input buffer

        for (int x = 0; x < number_of_columns; x++) // iterates through the specified number of columns, asks for column name for each one and
        {                                           // assigs it to an index inside an array according to order
            string name;
            int type = 0;
            cout << "Enter column " << x + 1 << " name: " << endl;
            getline(cin, name);                   // Use getline to read entire column name with spaces
            while (name != removeChar(name, ',')) // get input that doesnt have commas
            {
                cin.clear();
                cin.ignore(9999, '\n');
                cout << "Enter column " << x + 1 << " name (no commas): " << endl;
                getline(cin, name);
            }
            cout << "Enter column " << x + 1 << " data type (type 0 for bool, 1 for string, 2 for float, 3 for int): " << endl;
            cin >> type;

            while (cin.fail() || type < 0 || type > 3)
            {
                cin.clear();
                cin.ignore(9999, '\n');
                if (!(type < 0 || type > 3))
                {
                    cout << "You entered an invalid input. Please enter a number." << endl;
                    cout << "Enter column " << x + 1 << " data type (type 0 for bool, 1 for string, 2 for float, 3 for int) : " << endl;
                }
                else
                {
                    cout << "Please enter column " << x + 1 << " data type that is in the range of 0 until 3 " << endl
                         << "(type 0 for bool, 1 for string, 2 for float, 3 for int) : " << endl;
                }
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
        if (column_names[x].first == 0)
        {
            cout << "(enter true/false)";
        }

        getline(cin, inputs); // Use getline to read entire input including spaces
        // Use getline to read entire column name with spaces
        while (inputs != removeChar(inputs, ',') || !single_type_check(static_cast<types>(column_names[x].first), inputs)) // get input that doesnt have commas
        {
            if (inputs != removeChar(inputs, ','))
            {
                cin.clear();
                cin.ignore(9999, '\n');
                cout << "Enter " << column_names[x].second << " (no commas): ";
                getline(cin, inputs);
            }
            else
            {
                cin.clear();
                cin.ignore(9999, '\n');
                cout << "Enter " << column_names[x].second << ": ";
                getline(cin, inputs);
            }
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

int load_existing_attendance_sheet()
{
    string load_file_path;
    int edit_option;
    bool has_changed = false;
    cout << "\n===========================" << endl;
    cout << "   LOAD ATTENDANCE SHEET  " << endl;
    cout << "===========================\n"
         << endl;
    cout << "Enter existing attendance sheet file name with .csv: " << endl;
    cin >> load_file_path;
    filesystem::path fullPath = filesystem::path(term_name) / load_file_path;

    if (!filesystem::exists(fullPath.string()))
    {
        cout << "\nThis file doesn't exist" << endl;
        return -1;
    }

    *current_table_ptr = current_table(fullPath.string());
    current_table_ptr->display();

    cout << "\n--------------------------" << endl;
    cout << "COUNT ROWS" << endl;
    cout << "\n--------------------------" << endl;
    int totalRows = current_table_ptr->get_table().size(); // this grabs the list in the return the total number of rows in the lsit
    cout << "Number of rows: " << totalRows << endl;
    cout << "\n---------------------------" << endl;

    while (edit_option != 4)
    {
        cout << "Press 1 to insert a new row" << endl
             << "Press 2 to delete a row" << endl
             << "Press 3 to update a row" << endl
             << "Press 4 to exit" << endl;
        while (!(cin >> edit_option) || edit_option > 4 || edit_option < 1)
        {
            cin.clear();
            cin.ignore(9999, '\n');
            if (cin.fail())
            {

                cout << "Please enter a number!" << endl;
            }
            else
            {
                cout << "Please enter a number between 1 to 4!" << endl;
            }
        }
        if (edit_option == 1)
        {
            has_changed = true;
            inserting_row(-1);
        }
        else if (edit_option == 2)
        {
            has_changed = true;
            deleting_row();
        }
        else if (edit_option == 3)
        {
            has_changed = true;
            update_row();
        }
    }
    if (has_changed)
    {
        saving_file_data(current_table_ptr->get_table(), fullPath.string(), false);
        //*current_table_ptr = current_table(fullPath.string());
    }
    return 0;
}

void inserting_row(int insert_pos = -1)
{
    int insert_index;
    current_table_ptr->display(true);
    cin.clear();
    cin.ignore(9999, '\n');
    for (auto i : current_table_ptr->get_field_type_list())
    {
        string inputs;

        cout << "Enter " << i.second << ": ";
        if (i.first == 0)
        {
            cout << "(enter true/false)";
        }
        getline(cin, inputs);                                                                                // Use getline to read entire input including spaces
                                                                                                             // Use getline to read entire column name with spaces
        while (inputs != removeChar(inputs, ',') || !single_type_check(static_cast<types>(i.first), inputs)) // gets inputs with no commas and with correcct type
        {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "Enter " << i.second << " (no commas): ";
            getline(cin, inputs);
        }
        student_data.push_back(inputs); // using vector array, I am adding a datapoint into the array
    }
    cout << endl
         << endl;
    current_table_ptr->display(true);
    if (insert_pos == -1)
    {
        cout << "insert index : ";
        while (!(cin >> insert_index) || insert_index > current_table_ptr->get_field_type_list().size() || insert_index < 0)
        {
            if (cin.fail())
            {
                cout << "Please enter a number!" << endl;
            }
            else
            {
                cout << "Please enter a number between 0 to the number of columns in the selected sheet!" << endl;
            }
        }
    }
    else
    {
        insert_index = insert_pos;
    }
    current_table_ptr->insert_row(insert_index, student_data);
    cout << endl
         << endl;
    current_table_ptr->display();
    student_data.clear();
}
void deleting_row()
{
    string delete_id;
    int position = 0;
    current_table_ptr->display();
    cout << "Delete a row by the ID: ";
    while (!(cin >> delete_id) || delete_id.empty())
    {

        cin.clear();
        cin.ignore(9999, '\n');
        cout << "Please enter a valid ID!" << endl;
    }
    for (vector<string> row : current_table_ptr->get_table())
    {
        if (row[0] == delete_id)
        {
            current_table_ptr->delete_row(position);
            cout << endl
                 << endl;
            current_table_ptr->display();
            return;
        }
        position++;
    }
    cin.clear();
    cin.ignore(9999, '\n');
    cout << "Please enter a valid ID!" << endl;
    //
}

void update_row()
{
    string update_id;
    int position = 0;
    bool found = false;
    current_table_ptr->display();
    cout << "Update a row by the ID: ";
    while (!(cin >> update_id) || update_id.empty())
    {

        cin.clear();
        cin.ignore(9999, '\n');
        cout << "Please enter a valid ID!" << endl;
    }

    for (vector<string> row : current_table_ptr->get_table())
    {
        if (row[0] == update_id)
        {
            current_table_ptr->delete_row(position);
            inserting_row(position);
            return;
        }
        position++;
    }
    cin.clear();
    cin.ignore(9999, '\n');
    cout << "Please enter a valid ID!" << endl;
    //
}
