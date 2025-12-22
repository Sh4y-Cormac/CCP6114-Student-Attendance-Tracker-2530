#include <iostream>
#include <string>

using namespace std;

void create_sheet_structure(); // this function handles the sheet structure creation


int number_of_columns;
string column_names[10] = {}; // makes an array of all the columns




int main()
{
    create_sheet_structure(); // create sheet structure
    return 0;
}

void create_sheet_structure()
{
    cout << "Define number of columns (max 10): " << endl;
    cin >> number_of_columns;

    for (int x=0; x<number_of_columns; x++) // loops through the number of columns and receives input for the names of the column
    {
        string name;
        cout << "Enter column " << x+1 << " name: " << endl;
        cin >> name;
        column_names[x] = name;

    }

}



