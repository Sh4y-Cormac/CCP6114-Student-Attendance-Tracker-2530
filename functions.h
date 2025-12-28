
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
// Function declarations (only the function names and parameters, not the logic)

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
    current_table(string file_path, vector<pair<int, string>> field_type_list, vector<vector<string>> table)
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

void delete_file(string file_path); // delete file from directory

bool num_check(string line, bool is_float); // check if inputed data is Num

bool check_if_file_exist(string file_path); // check if the file already exist

void new_file_create(vector<pair<int, string>> type_list, string file_path); // creates file with inputed fields

bool type_checker(vector<string> &data, string file_path); // checks the data types if it aligns with fields

void saving_file_data(vector<vector<string>> row, string file_path, bool is_append); // save data to file, can append or rewrite file

#endif