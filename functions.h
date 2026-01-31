
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
// Functions
enum types // types of data in table
{
    Bool,
    String,
    Float,
    Int

};
class current_db
{
public:
    string file_path;

private:
    vector<string> content;

public:
    bool check_if_file_exist(string file_path)
    {
        fstream dir_file;
        string line;
        dir_file.open("dir_file.txt", ios::in);
        while (getline(dir_file, line, '\n')) // iterates thru all lines in dir_file.txt to find file_path
        {
            if (line == file_path)
            {

                return true;
            }
        }
        dir_file.close();
        return false;
    }
    current_db(string file_path)
    {
        string temp_row;
        ifstream read_file;
        if (!check_if_file_exist(file_path))
        {
            cout << "This file doesn't exist!";
            return;
        }
        this->file_path = file_path;
        read_file.open(file_path);
        while (getline(read_file, temp_row))
        {
            this->content.push_back(temp_row);
        }
    }
};
class current_table // current table class to make object for easier file editing/selection
{
public:
    string file_path;

private:
    vector<pair<int, string>> field_type_list;
    vector<vector<string>> table;

    bool check_if_file_exist(string file_path, current_db curr_db)
    {
        fstream dir_file;
        string line;
<<<<<<< Updated upstream
        dir_file.open("dir_file.txt", ios::in);
        while (getline(dir_file, line, '\n'))
=======
        dir_file.open(curr_db.file_path, ios::in);
        while (getline(dir_file, line, '\n')) // iterates thru all lines in dir_file.txt to find file_path
>>>>>>> Stashed changes
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
    current_table(string file_path, vector<pair<int, string>> field_type_list, vector<vector<string>> table)
    {
        this->file_path = file_path;
        this->field_type_list = field_type_list;
        this->table = table;
    }
    current_table(string file_path, current_db curr_db)
    {
        string field_line;
        string field;
        vector<string> temp_row;

        ifstream read_file;

        if (!check_if_file_exist(file_path, curr_db))
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
};

string removeSpaces(string str) // remove space in string
{

    int count = 0;

    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i];

    str = str.substr(0, count);
    // cout << str << " ";
    return str;
}

string lowercase(string line) // turn string lowwercase
{
    for (auto &i : line)
    {
        i = tolower(i);
    }
    return line;
}

void delete_file(string file_path) // delete file in filepath
{
    fstream dir_file;
    string line;
    vector<string> rewrite;
    bool is_exist = false;
    dir_file.open("dir_file.txt", ios::in);
    while (getline(dir_file, line))
    {
        if (file_path != line)
        {
            rewrite.push_back(line);
        }
        else
        {
            is_exist = true;
        }
    }
    dir_file.close();

    if (is_exist)
    {
        filesystem::remove(file_path);
        dir_file.open("dir_file.txt", ios::out);
        for (string line : rewrite)
        {
            dir_file << line << endl;
        }
        dir_file.close();
    }
    else
    {
        cout << file_path << "does not exist!" << endl;
    }
}

bool num_check(string line, bool is_float) // check if data is a number (int or float)
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

bool check_if_file_exist(string file_path) // check if file exist in file dirctory
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

void new_file_create(vector<pair<int, string>> type_list, string file_path) // create new file from fields with specified data types
{

    fstream dir_file;
    if (check_if_file_exist(file_path))
    {
        cout << "this file already exist" << endl;
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

bool type_checker(vector<string> &data, string file_path) // check if data types align with fields
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
    if (field_list.size() < data.size())
    {
        cout << "data entry scope is out of bounds!" << endl;
        return false;
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

void saving_file_data(vector<vector<string>> row, string file_path, bool is_append) // save data entered in to file // can append at the end of the file or rewrite the file from first row after fields
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
            cout << endl
                 << endl;
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

#endif