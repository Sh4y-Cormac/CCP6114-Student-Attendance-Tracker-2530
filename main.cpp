#include <iostream>
#include <string>

using namespace std;

void create_sheet_structure(); // this function handles the sheet structure creation
void create_attendance_row();


int number_of_columns;
int attendance_row_value;
string column_names[10] = {"John","Jeffrey","Jack"};



int main()
{
    create_sheet_structure();
    return 0;
}

void create_sheet_structure()
{
    cout << "Define number of columns (max 10): " << endl;
    cin >> number_of_columns;

    for (int x=0; x<number_of_columns; x++) // iterates through the specified number of columns, asks for column name for each one and
    {                                       // assigning it to an index inside an array according to order
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


    } while (attendance_row_value == 1);

}



