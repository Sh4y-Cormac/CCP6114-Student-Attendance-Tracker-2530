#include <iostream>
#include <string>

#include <vector>
#include <sstream>
#include <fstream>
#include "functions.h"
using namespace std;

int create_sheet_structure(); // this function handles the sheet structure creation
void create_attendance_row();

template <typename T>
vector<T> array_to_vector(T some_array[], int array_size); // changes arrays to vectors bcs i fucking love vectors

int number_of_columns;
// makes an array of all the columns
current_table *const current_table_ptr = new current_table("", {}, {}); // makes empty current table that can be accessed

int attendance_row_value;
pair<int, string> column_names[10] = {{1, "John"}, {1, "Jeffrey"}, {1, "Jack"}};
string column1_data[10] = {}; // TEMP
string column2_data[10] = {}; // TEMP
string column3_data[10] = {}; // TEMP

string row1_data[10] = {}; // TEMP
string row2_data[10] = {}; // TEMP
string row3_data[10] = {}; // TEMP

int main()
{
    create_sheet_structure();
    cout << "Works" << endl;
    cout << column1_data[0] << endl;
    cout << column2_data[0] << endl;
    cout << column3_data[0] << endl;
    cout << "enter sheet name" << endl;
    cin >> current_table_ptr->file_path; // writing the file path of current file
    // new_file_create(current_table_ptr->get_field_type_list(), current_table_ptr->file_path + ".csv");  // creating the file
    // saving_file_data({{"Ye", "Ne"}}, current_table_ptr->file_path + ".csv", true);  // writing new file data // {{"Ye","Ne"}} is a 2D vector so it enables to add many rows at once // will skip if somethings wrong
    //*current_table_ptr = current_table(current_table_ptr->file_path + ".csv");  // getting table from existing file
    current_table_ptr->display(); // display table content

    return 0;
}

int create_sheet_structure()
{
    cout << "Define number of columns (max 10): " << endl;
    cin >> number_of_columns;

    for (int x = 0; x < number_of_columns; x++) // iterates through the specified number of columns, asks for column name for each one and
    {                                           // assigs it to an index inside an array according to order
        string name;
        int type = 0;
        cout << "Enter column " << x + 1 << " name: " << endl;
        cin >> name;

        cout << "Enter column " << x + 1 << " data type (0 for bool, 1 for string, 2 for float, 3 for int): " << endl;
        cin >> type;

        column_names[x].first = type;
        column_names[x].second = name;
    }
    *current_table_ptr = current_table("", array_to_vector(column_names, 0 + number_of_columns), {});
    // array_to_vector(column_names, 0 + number_of_columns);

    cout << "Sheet structure created successfully" << endl;

    do
    {
        cout << "Press 1 for a new attendance row, Press 2 to exit attendance rows" << endl;
        cin >> attendance_row_value;

        if (attendance_row_value == 1)
        {
            create_attendance_row();
        }
        else
        {
            return 0;
        }

    } while (attendance_row_value != 2);

    return 0;
}

void create_attendance_row()
{

    cout << "------------------------" << endl;
    cout << "Insert new attendance row" << endl;
    cout << "------------------------" << endl;
    string temp_array[10];
    for (int x = 0; x < number_of_columns; x++)
    {
        string data;
        cout << "Enter " << column_names[x].second << ":";
        cin >> data;
        temp_array[x] = data;
        // STOPPED RIGHT HERE -UMAR
    }
    current_table_ptr->insert_row(0 + current_table_ptr->get_table().size(), array_to_vector(temp_array, number_of_columns));
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
