#include<iostream>
#include<vector>
#include<cstdlib>
#include<stdlib.h>
#include<fstream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <iomanip>

using namespace std;

class sales_management
{
public:
	string item;
	double cost;
	int id;

	void add_item();
	void menu();
    void display_items();
    void search_menu();
    void search_item();
    void search_id();
    void search_cost();
};

void sales_management::add_item()
{
	sales_management sm;

	fstream fout;
	fout.open("Items.csv", ios::out | ios::app);

	cout << "\t\t\t+--------------------------------------+";
    cout << "\n\t\t\t|--NDERITU'S STORE MANAGEMENT SYSTEM---|";
    cout << "\n\t\t\t+--------------------------------------+";

    cout << "\n\n\t\t\tEnter Item ID: ";
    cin >> sm.id;
    cout << "\n\n\t\t\tEnter Item Name: ";
    cin >> sm.item;
    cout << "\n\n\t\t\tEnter Item Cost: ";
    cin >> sm.cost;

    fout << sm.id << "," << sm.item << "," << sm.cost << endl;
    fout.close();

    cout << "\n\n\t\t\t\tItem Added Successfully..." << endl;
    cout << "\n\t\t\t+-----------------------------------------+";

    cout << "\n\n\t\t\t\tPress Enter To Continue..." << endl;

    cin.ignore();
    cin.get();
    sm.menu();
}

void sales_management::display_items()
{
    system("clear");

    sales_management sm;

    cout << "\t\t\t+--------------------------------------+";
    cout << "\n\t\t\t|--NDERITU'S STORE MANAGEMENT SYSTEM---|";
    cout << "\n\t\t\t+--------------------------------------+";

    cout << "\n\n\t\t+------+-------------+---------+";
    cout << "\n\t\t| ID   |     ITEM    |   COST  |";
    cout << "\n\t\t+------+-------------+---------+";

    const char separator = ' ';
    const int idwidth = 6;
    const int itwidth = 13;
    const int cowidth = 9;
    vector<string> row;
    string line, word;

    fstream fin;
    fin.open("Items.csv", ios::in | ios::app);

    if (fin.good())
    {
        while(!fin.eof())
        {
            row.clear();
            getline(fin, line);
            stringstream s(line);

            while(s.good())
            {
                getline(s, word, ',');
                row.push_back(word);
            }

            if (row.size() > 1)
            {
                sm.id = stoi(row[0]);
                sm.item = row[1];
                sm.cost = stod(row[2]);

                for (int i = 0; i < 1; ++i)
                {

                    cout << "\n\t\t|" << setw(idwidth) << setfill(separator) << row[0] << "|";
                    cout << setw(itwidth) << setfill(separator) << row[1] << "|";
                    cout << setw(cowidth) << setfill(separator) << row[2] << "|";

                    cout << "\n\t\t+------+-------------+---------+";
                }
            }
        }
    }
    else
        sm.add_item();

    fin.close();

    cout << "\n\n\t\t\t\tPress Enter To Continue..." << endl;

    cin.ignore();
    cin.get();
    sm.menu();
}

void sales_management::search_menu()
{
    system("clear");

    sales_management sm;
    int choice;

   cout << "\t\t\t+--------------------------------------+";
    cout << "\n\t\t\t|--NDERITU'S STORE MANAGEMENT SYSTEM---|";
    cout << "\n\t\t\t+--------------------------------------+";

    cout << "\n\n\t\t\t1. Search By Name";
    cout << "\n\n\t\t\t2. Search By ID";
    cout << "\n\n\t\t\t3. Search By Cost";
    cout << "\n\n\t\t\t4. Back";
    cout << "\n\n\t\t\tEnter Your Choice: ";
    cin >> choice;

    switch(choice)
    {
        case 1:
            sm.search_item();
            break;
        case 2:
            sm.search_id();
            break;
        case 3:
            sm.search_cost();
            break;
        case 4:
            sm.menu();
            break;
        default:
            cout << "\n\n\t\t\t\tInvalid choice..." << endl;
            cin.ignore();
            cin.get();

            sm.search_menu();
            break;
    }
}

void sales_management::search_item()
{
    system("clear");

    sales_management sm;

   cout << "\t\t\t+--------------------------------------+";
    cout << "\n\t\t\t|--NDERITU'S STORE MANAGEMENT SYSTEM---|";
    cout << "\n\t\t\t+--------------------------------------+";

    const char separator = ' ';
    const int idwidth = 6;
    const int itwidth = 13;
    const int cowidth = 9;
    vector<string> row;
    string line, word;
    string entered_name;

    fstream fin;
    fin.open("Items.csv", ios::in | ios::app);

    cout << "\n\n\t\tEnter Item Name: ";
    cin >> entered_name;

    if (fin.good())
    {
        while(!fin.eof())
        {
            row.clear();
            getline(fin, line);
            stringstream s(line);

            while(s.good())
            {
                getline(s, word, ',');
                row.push_back(word);
            }

            if (row.size() > 1)
            {
                //sm.id = stoi(row[0]);
                sm.item = row[1];
                //sm.cost = stod(row[2]);

                for (int i = 0; i < 1; ++i)
                {
                    if (entered_name == sm.item)
                    {
                        cout << "\n\n\t\t+------+-------------+---------+";
                        cout << "\n\t\t| ID   |     ITEM    |   COST  |";
                        cout << "\n\t\t+------+-------------+---------+";

                        cout << "\n\t\t|" << setw(idwidth) << setfill(separator) << row[0] << "|";
                        cout << setw(itwidth) << setfill(separator) << row[1] << "|";
                        cout << setw(cowidth) << setfill(separator) << row[2] << "|";

                        cout << "\n\t\t+------+-------------+---------+";
                    }                    
                }
            }
        }
    }
    else
        sm.add_item();

    fin.close();

    cout << "\n\n\t\t\t\tPress Enter To Continue..." << endl;

    cin.ignore();
    cin.get();
    sm.search_menu();
}

void sales_management::search_id()
{
    system("clear");

    sales_management sm;

   cout << "\t\t\t+--------------------------------------+";
    cout << "\n\t\t\t|--NDERITU'S STORE MANAGEMENT SYSTEM---|";
    cout << "\n\t\t\t+--------------------------------------+";

    const char separator = ' ';
    const int idwidth = 6;
    const int itwidth = 13;
    const int cowidth = 9;
    vector<string> row;
    string line, word;
    int entered_id;

    fstream fin;
    fin.open("Items.csv", ios::in | ios::app);

    cout << "\n\n\t\tEnter Item ID: ";
    cin >> entered_id;

    if (fin.good())
    {
        while(!fin.eof())
        {
            row.clear();
            getline(fin, line);
            stringstream s(line);

            while(s.good())
            {
                getline(s, word, ',');
                row.push_back(word);
            }

            if (row.size() > 1)
            {
                sm.id = stoi(row[0]);
                //sm.item = row[1];
                //sm.cost = stod(row[2]);

                for (int i = 0; i < 1; ++i)
                {
                    if (entered_id == sm.id)
                    {
                        cout << "\n\n\t\t+------+-------------+---------+";
                        cout << "\n\t\t| ID   |     ITEM    |   COST  |";
                        cout << "\n\t\t+------+-------------+---------+";

                        cout << "\n\t\t|" << setw(idwidth) << setfill(separator) << row[0] << "|";
                        cout << setw(itwidth) << setfill(separator) << row[1] << "|";
                        cout << setw(cowidth) << setfill(separator) << row[2] << "|";

                        cout << "\n\t\t+------+-------------+---------+";
                    }                    
                }
            }
        }
    }
    else
        sm.add_item();

    fin.close();

    cout << "\n\n\t\t\t\tPress Enter To Continue..." << endl;

    cin.ignore();
    cin.get();
    sm.search_menu();
}

void sales_management::search_cost()
{
    system("clear");

    sales_management sm;

    cout << "\t\t\t+--------------------------------------+";
    cout << "\n\t\t\t|--NDERITU'S STORE MANAGEMENT SYSTEM---|";
    cout << "\n\t\t\t+--------------------------------------+";

    const char separator = ' ';
    const int idwidth = 6;
    const int itwidth = 13;
    const int cowidth = 9;
    vector<string> row;
    string line, word;
    double entered_cost;

    fstream fin;
    fin.open("Items.csv", ios::in | ios::app);

    cout << "\n\n\t\tEnter Item Cost: ";
    cin >> entered_cost;

    if (fin.good())
    {
        while(!fin.eof())
        {
            row.clear();
            getline(fin, line);
            stringstream s(line);

            while(s.good())
            {
                getline(s, word, ',');
                row.push_back(word);
            }

            if (row.size() > 1)
            {
                //sm.id = stoi(row[0]);
                //sm.item = row[1];
                sm.cost = stod(row[2]);

                for (int i = 0; i < 1; ++i)
                {
                    if (entered_cost == sm.cost)
                    {
                        cout << "\n\n\t\t+------+-------------+---------+";
                        cout << "\n\t\t| ID   |     ITEM    |   COST  |";
                        cout << "\n\t\t+------+-------------+---------+";

                        cout << "\n\t\t|" << setw(idwidth) << setfill(separator) << row[0] << "|";
                        cout << setw(itwidth) << setfill(separator) << row[1] << "|";
                        cout << setw(cowidth) << setfill(separator) << row[2] << "|";

                        cout << "\n\t\t+------+-------------+---------+";
                    }                    
                }
            }
        }
    }
    else
        sm.add_item();

    fin.close();

    cout << "\n\n\t\t\t\tPress Enter To Continue..." << endl;

    cin.ignore();
    cin.get();
    sm.search_menu();
}

void sales_management::menu()
{
    system("clear");

    sales_management sm;
    int choice;

    cout << "\t\t\t+--------------------------------------+";
    cout << "\n\t\t\t|--NDERITU'S STORE MANAGEMENT SYSTEM---|";
    cout << "\n\t\t\t+--------------------------------------+";

    cout << "\n\n\t\t\t1. Add Item";
    cout << "\n\n\t\t\t2. Display Items";
    cout << "\n\n\t\t\t3. Search Menu";
    cout << "\n\n\t\t\t4. Exit";
    cout << "\n\n\t\t\tEnter Your Choice: ";
    cin >> choice;

    switch(choice)
    {
        case 1:
        {
            system("clear");

            sales_management sm;

            const char separator = ' ';
            const int idwidth = 6;
            const int itwidth = 13;
            const int cowidth = 9;

            vector<string> row;
            string line, word;
            int entered_id; 

            fstream fin;
            fin.open("Items.csv", ios::in | ios::app);

            if (fin.good())
            {
                while(!fin.eof())
                {
                    row.clear();
                    getline(fin, line);
                    stringstream s(line);

                    while(s.good())
                    {
                        getline(s, word, ',');
                        row.push_back(word);
                    }

                    if (row.size() > 1)
                    {
                        sm.id = stoi(row[0]);

                        cout << "\t\t\t+--------------------------------------+";
                        cout << "\n\t\t\t|--NDERITU'S STORE MANAGEMENT SYSTEM---|";
                        cout << "\n\t\t\t+--------------------------------------+";

                        cout << "\n\n\t\t\tEnter Item ID: ";
                        cin >> entered_id;
                       
                        for (int i = 0; i < 1; ++i)
                        {
                            if (entered_id == sm.id)
                            {
                                cout << "\n\n\t\t\t\tItem Entry Available...";
                                cout << "\n\t\t\t+--------------------------------------------+";

                                cout << "\n\n\t\t\t\tPress Enter To Continue..." << endl;
                                cin.ignore();
                                cin.get();

                                sm.menu();
                            }
                            else
                            {
                                if (entered_id != sm.id)
                                {    
                                    sales_management sm;
                                    
                                    fstream fout;
                                    fout.open("Items.csv", ios::out | ios::app);

                                    cout << "\n\n\t\t\tEnter Item Name: ";
                                    cin >> sm.item;
                                    cout << "\n\n\t\t\tEnter Item Cost: ";
                                    cin >> sm.cost;

                                    fout << entered_id << "," << sm.item << "," << sm.cost << endl;
                                    fout.close();

                                    cout << "\n\n\t\t\t\tItem Added Successfully..." << endl;
                                    cout << "\n\t\t\t+-----------------------------------------+";

                                    cout << "\n\n\t\t\t\tPress Enter To Continue..." << endl;

                                    cin.ignore();
                                    cin.get();
                                    sm.menu();    
                                }
                            }                                         
                        } 
                    }                                                  
                    
                }               
            }
            
            sm.add_item();

            fin.close();

            break;
        }
        case 2:
            sm.display_items();
            break;
        case 3:
            sm.search_menu();
            break;
        case 4:
            try
            {
                quick_exit(0);
            }
            catch(exception& e)
            {
                cout << e.what() << endl;
            }
        default:
            cout << "\n\n\t\t\t\tInvalid choice..." << endl;
            cin.ignore();
            cin.get();

            sm.menu();
            break;
    }
}

int main(int argc, char const *argv[])
{
	sales_management sm;

	try
    {
    	sm.menu();
    }
    catch(exception& e)
    {
    	cout << e.what() << endl;
   	}

	return 0;
}
