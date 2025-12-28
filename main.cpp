#include <iostream>
#include <string>
#include <vector> // resizeable array or inf amount array

using namespace std;

int create_sheet_structure(); // this function handles the sheet structure creation
void create_attendance_row(int); // this function creates the attendance row process


int number_of_columns; // number of columns that the user specified to add
int attendance_row_value; // input from user whether to continue the program or not
int current_attendance_row = 1; // measures the current attendance row being used
string column_names[10] = {}; // declares the maximum amount of columns possible
vector<string> student_data{}; // ALL STUDENT DATA IS STORED IN THIS VECTOR!



int main()
{
    create_sheet_structure();
    cout << "sheet structure process has completed" << endl;
    return 0;
}



// Asks user for number of columns they want, asks them to name those columns, and asks them
// to data enter any amount of attendance rows they want
int create_sheet_structure()
{
    cout << "Define number of columns (max 10): " << endl;
    cin >> number_of_columns;

    if (number_of_columns <= 10 && number_of_columns > 0)
    {
        for (int x=0; x<number_of_columns; x++) // iterates through the specified number of columns, asks for column name for each one and
        {                                       // assigs it to an index inside an array according to order
            string name;
            cout << "Enter column " << x+1 << " name: " << endl;
            cin >> name;
            column_names[x] = name;
        }

        cout << "Sheet structure created successfully" << endl;

        do
        {
             cout << "Press 1 for a new attendance row, Press 2 to exit attendance rows" << endl;
             cin >> attendance_row_value;

             if (attendance_row_value == 1)
             {
                 create_attendance_row(current_attendance_row);
                 current_attendance_row++;
             }
             else
             {
                 return 0;
             }

        } while(attendance_row_value != 2);


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
    cout << "Insert new attendance row #"<< current_attendance_row << endl;
    cout << "------------------------" << endl;


    for (int x=0; x<number_of_columns; x++)
    {
        string inputs;
        cout << "Enter " << column_names[x] << ":";
        cin >> inputs;
        student_data.push_back(inputs); // using vector array, I am adding a datapoint into the array

    }

}



