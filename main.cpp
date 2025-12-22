#include <iostream>
#include <string>

using namespace std;

void DisplayText(string); // this function is used to display text onto the command line with endline aswell
void create_sheet_structure(); // this function handles the sheet structure creation
int number_of_columns;


int main()
{
    create_sheet_structure();
    return 0;
}


void DisplayText(string Text)
{
    cout << Text << endl;
}

void create_sheet_structure()
{
    DisplayText("Define number of columns(max 10): ");
    cin >> number_of_columns;
}

