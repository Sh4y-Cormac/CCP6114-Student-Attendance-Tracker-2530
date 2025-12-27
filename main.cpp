#include <iostream>
#include <string>

using namespace std;

int create_sheet_structure(); // this function handles the sheet structure creation
void create_attendance_row();


int number_of_columns;
int attendance_row_value;
string column_names[10] = {"John","Jeffrey","Jack"};
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
    return 0;
}

int create_sheet_structure()
{
    cout << "Define number of columns (max 10): " << endl;
    cin >> number_of_columns;

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
             create_attendance_row();
         }
         else
         {
             return 0;
         }

    } while(attendance_row_value != 2);


    return 0;


}

void create_attendance_row()
{
    cout << "------------------------" << endl;
    cout << "Insert new attendance row" << endl;
    cout << "------------------------" << endl;

    for (int x=0; x<number_of_columns; x++)
    {
        string data;
        cout << "Enter " << column_names[x] << ":";
        cin >> data;
        // STOPPED RIGHT HERE -UMAR


    }

}



