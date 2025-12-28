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
int create_sheet_structure();    // this function handles the sheet structure creation
void create_attendance_row(int); // this function creates the attendance row process

template <typename T>
vector<T> array_to_vector(T some_array[], int array_size); // changes arrays to vectors bcs i fucking love vectors

int number_of_columns;                                                  // number of columns that the user specified to add
int attendance_row_value;                                               // input from user whether to continue the program or not
int current_attendance_row = 1;                                         // measures the current attendance row being used
pair<int, string> column_names[10] = {};                                // declares the maximum amount of columns possible
vector<string> student_data{};                                          // ALL STUDENT DATA IS STORED IN THIS VECTOR!
current_table *const current_table_ptr = new current_table("", {}, {}); // makes empty current table that can be accessed

int main()
{
    create_sheet_structure();
    cout << "sheet structure process has completed" << endl;
    cout << "enter sheet name: ";
    cin >> current_table_ptr->file_path;
    cin.clear();
    cin.ignore(9999, '\n');                                                                           // writing the file path of current file
    new_file_create(current_table_ptr->get_field_type_list(), current_table_ptr->file_path + ".csv"); // creating the file
    saving_file_data(current_table_ptr->get_table(), current_table_ptr->file_path + ".csv", false);   // writing new file data // uses a 2D vector so it enables to add many rows at once // will skip certain rows if somethings wrong with said rows // if true will append
    *current_table_ptr = current_table(current_table_ptr->file_path + ".csv");                        // getting table from existing file
    current_table_ptr->display();                                                                     // display table content
    return 0;
}

// Asks user for number of columns they want, asks them to name those columns, and asks them
// to data enter any amount of attendance rows they want
int create_sheet_structure()
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
        for (int x = 0; x < number_of_columns; x++) // iterates through the specified number of columns, asks for column name for each one and
        {                                           // assigs it to an index inside an array according to order
            string name;
            int type = 0;
            cout << "Enter column " << x + 1 << " name: " << endl;
            cin >> name;

            cout << "Enter column " << x + 1 << " data type (type 0 for bool, 1 for string, 2 for float, 3 for int): " << endl;
            cin >> type;

            while (cin.fail())
            {
                cin.clear();
                cin.ignore(9999, '\n');
                cout << "Enter column " << x + 1 << " data type (type 0 for bool, 1 for string, 2 for float, 3 for int): " << endl;
                cin >> type;
            }

            column_names[x].first = type;
            column_names[x].second = name;
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
            if (attendance_row_value == 1)
            {
                create_attendance_row(current_attendance_row);
                current_attendance_row++;
            }
            else
            {

                return 0;
            }

        } while (attendance_row_value != 2);

        return 0;
    }

    else
    {
        cout << "Number of columns has to be a maximum of 10 and bigger than 0" << endl;
        create_sheet_structure();
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
        cout << "Enter " << column_names[x].second << ":";
        cin >> inputs;
        student_data.push_back(inputs); // using vector array, I am adding a datapoint into the array
    }
    current_table_ptr->insert_row(0 + current_table_ptr->get_table().size(), student_data);
    student_data.clear();
}

template <typename T>
vector<T> array_to_vector(T some_array[], int array_size)
{
    vector<T> temp_vector;
    for (int i; i < array_size; i++)
    {
        temp_vector.push_back(some_array[i]);
        // cout << some_array[i].first << some_array[i].second;
    }
    return temp_vector;
}
