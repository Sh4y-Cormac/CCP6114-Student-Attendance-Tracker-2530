#include <iostream>
#include <string>

#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

class current_table
{
public:
    string file_path;

private:
    vector<pair<int, string>> field_type_list;
    vector<vector<string>> table;
    bool check_if_file_exist(string file_path)
    {
        fstream dir_file;
        string line;
        dir_file.open("dir_file.txt", ios::in);
        while (getline(dir_file, line, '\n'))
        {
            if (line == file_path)
            {

                return true;
            }
        }
        dir_file.close();
        return false;
    }

public:
    current_table(string file_path = "", vector<pair<int, string>> field_type_list = {}, vector<vector<string>> table = {})
    {
        this->file_path = file_path;
        this->field_type_list = field_type_list;
        this->table = table;
    }
    current_table(string file_path)
    {
        string field_line;
        string field;
        vector<string> temp_row;

        ifstream read_file;

        if (!check_if_file_exist(file_path))
        {
            cout << " this file doesn't exist";
            return;
        }
        this->file_path = file_path;
        read_file.open(file_path);
        getline(read_file, field_line, '\n');

        while (getline(stringstream(field_line), field, ','))
        {
            field_type_list.push_back(pair<int, string>{stoi(field.substr(1, field.find('}'))), field.substr(field.find('}') + 1)});
            if (!field_line.find(","))
            {
                break;
            }
            field_line = field_line.substr(field_line.find(',') + 1);
        }

        while (getline(read_file, field_line, '\n'))
        {
            temp_row.clear();
            while (getline(stringstream(field_line), field, ','))
            {
                temp_row.push_back(field);
                if (!field_line.find(","))
                {
                    break;
                }
                field_line = field_line.substr(field_line.find(',') + 1);
            }
            table.push_back(temp_row);
        }
    }
    void display()
    {
        cout << "|";
        for (auto field : field_type_list)
        {
            cout << field.second << "|";
        }
        cout << endl;
        for (vector<string> row : table)
        {
            cout << "|";
            for (string data : row)
            {
                cout << data << "|";
            }
            cout << endl;
        }
    }
    vector<vector<string>> get_table()
    {
        return table;
    }
    vector<pair<int, string>> get_field_type_list()
    {
        return field_type_list;
    }
    void insert_row(int index, vector<string> row)
    {
        table.insert(table.begin() + index, row);
    }
    void delete_row(int index)
    {
        if (index < table.size())
        {
            table.erase(table.begin() + index);
        }
    }
}; // current table class to make object for easier file editing/selection

string removeSpaces(string str); // remove space from inputed data

string lowercase(string line); // change inputed data to lower case

bool num_check(string line, bool is_float); // check if inputed data is Num

bool check_if_file_exist(string file_path); // check if the file already exist

void new_file_create(vector<pair<int, string>> type_list, string file_path); // creates file with inputed fields

bool type_checker(vector<string> &data, string file_path); // checks the data types if it aligns with fields

void saving_file_data(vector<vector<string>> row, string file_path, bool is_append); // save data to file, can append or rewrite file

template <typename T>
vector<T> array_to_vector(T some_array[], int array_size); // convert array to vector

void create_sheet_structure(); // this function handles the sheet structure creation

enum types
{
    Bool,
    String,
    Float,
    Int

};

int number_of_columns;
pair<int, string> column_names[10] = {}; // makes an array of all the columns
current_table *const current_table_ptr = new current_table();

int main()
{
    create_sheet_structure(); // create sheet structure
    cout << "enter sheet name" << endl;
    cin >> current_table_ptr->file_path;
    new_file_create(current_table_ptr->get_field_type_list(), current_table_ptr->file_path);
    current_table_ptr->display();
    return 0;
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

string removeSpaces(string str)
{

    int count = 0;

    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i];

    str = str.substr(0, count);
    // cout << str << " ";
    return str;
}

string lowercase(string line)
{
    for (auto &i : line)
    {
        i = tolower(i);
    }
    return line;
}

bool num_check(string line, bool is_float)
{
    int decimal_point = 0;
    const string alphabet = "abcdefghijklmnopqrstuvwxyz!@#$%^&*()_+`~";
    const string numbers = "0123456789";

    for (char i : line)
    {
        if (i == '.')
        {
            decimal_point++;
            if ((decimal_point > 0 && !is_float) || (decimal_point > 1 && is_float))
            {
                return false;
            }
        }
        if (alphabet.find(i) != string::npos)
        {
            return false;
        }
        if (numbers.find(i) == string::npos)
        {
            return false;
        }
    }
    return true;
}

bool check_if_file_exist(string file_path)
{
    fstream dir_file;
    string line;
    dir_file.open("dir_file.txt", ios::in);
    while (getline(dir_file, line, '\n'))
    {
        if (line == file_path)
        {

            return true;
        }
    }
    dir_file.close();
    return false;
}

void new_file_create(vector<pair<int, string>> type_list, string file_path)
{

    fstream dir_file;
    if (check_if_file_exist(file_path))
    {
        cout << "this file already exist";
        return;
    }

    dir_file.open("dir_file.txt", ios::app);
    dir_file << file_path << endl;
    dir_file.close();

    ofstream o_current_file;
    o_current_file.open(file_path);
    for (pair i : type_list)
    {
        o_current_file << "{" << i.first << "} " << i.second << ",";
    }
    o_current_file.close();
}

bool type_checker(vector<string> &data, string file_path)
{
    ifstream file;
    string fields_line;
    file.open(file_path);

    getline(file, fields_line, '\n');

    string field;
    vector<int> field_list;

    while (getline(stringstream(fields_line), field, '}'))
    {
        field = field.substr(fields_line.find("{") + 1);
        field_list.push_back(stoi(field));
        if (!fields_line.find(","))
        {
            break;
        }
        fields_line = fields_line.substr(fields_line.find(",") + 1);
    }

    for (int i = 0; i < field_list.size(); i++)
    {
        string temp = lowercase(removeSpaces(data[i]));

        switch (field_list[i])
        {
        case Bool:

            if (!(temp == "true" || temp == "false"))
            {

                return false;
            }
            else
            {
                data[i] = removeSpaces(data[i]);
            }
            break;
        case String:
            if (!(!temp.empty() && temp.size() > 1))
            {
                return false;
            }

            break;
        case Float:
            if (!(!temp.empty() && num_check(temp, true)))
            {
                return false;
            }
            else
            {
                data[i] = to_string(stof(removeSpaces(data[i])));
            }
            break;
        case Int:
            if (!(!temp.empty() && num_check(temp, false)))
            {

                return false;
            }
            else
            {

                data[i] = to_string(stoi(removeSpaces(data[i])));
            }
            break;
        default:
            break;
        }
    }
    file.close();
    return true;
}

void saving_file_data(vector<vector<string>> row, string file_path, bool is_append)
{
    if (!check_if_file_exist(file_path))
    {
        cout << " this file doesn't exist!" << endl;
        return;
    }
    fstream o_current_file;

    vector<vector<string>> ok_rows;
    for (vector<string> data : row)
    {
        if (type_checker(data, file_path))
        {
            ok_rows.push_back(data);
        }
        else
        {
            cout << "something went wrong at this row so we're skipping it:" << endl;
            cout << "|";
            for (string i : data)
            {
                cout << " " << i << " |";
            }
            cout << endl;
        }
    }

    if (is_append)
    {

        o_current_file.open(file_path, ios::app);
    }
    else
    {
        string first_line;
        o_current_file.open(file_path, ios::in);
        getline(o_current_file, first_line);
        o_current_file.close();

        o_current_file.open(file_path, ios::out);
        o_current_file << first_line;
    }

    for (vector<string> ok_row : ok_rows)
    {
        o_current_file << endl;
        for (string i : ok_row)
        {
            o_current_file << i << ",";
        }
    }
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