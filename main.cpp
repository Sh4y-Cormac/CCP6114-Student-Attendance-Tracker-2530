#include <iostream>
#include <string>

using namespace std;

void create_sheet_structure(); // this function handles the sheet structure creation


int number_of_columns;
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

    for (int x=0; x<number_of_columns; x++)
    {
        string name;
        cout << "Enter column " << x+1 << " name: " << endl;
        cin >> name;
        column_names[x] = name;

    }

}



