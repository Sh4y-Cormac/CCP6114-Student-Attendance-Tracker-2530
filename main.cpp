#include <iostream>
#include <string>

#include <vector>
#include <sstream>
#include <fstream>
#include "functions.h"
using namespace std;

void create_sheet_structure(); // this function handles the sheet structure creation

int number_of_columns;
pair<int, string> column_names[10] = {};                                // makes an array of all the columns
current_table *const current_table_ptr = new current_table("", {}, {}); // makes empty current table that can be accessed

int main()
{
    create_sheet_structure(); // create sheet structure
    cout << "enter sheet name" << endl;
    cin >> current_table_ptr->file_path; // writing the file path of current file
    // new_file_create(current_table_ptr->get_field_type_list(), current_table_ptr->file_path + ".csv"); // creating the file
    // saving_file_data({{"Ye", "Ne"}}, current_table_ptr->file_path + ".csv", true); // writing new file data // {{"Ye","Ne"}} is a 2D vector so it enables to add many rows at once
    *current_table_ptr = current_table(current_table_ptr->file_path + ".csv"); // getting table from existing file
    current_table_ptr->display();                                              // display table content

    return 0;
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

void create_sheet_structure()
{
    cout << "Define number of columns (max 10): " << endl;
    cin >> number_of_columns;

    for (int x = 0; x < number_of_columns; x++) // loops through the number of columns and receives input for the names of the column
    {
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
}
