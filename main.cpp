#include "Notebook.hpp"
#include "Direction.hpp"
using ariel::Direction;

#include <iostream>
#include <stdexcept>
using namespace std;

const int exitNubmer = 5;

void printChoices()
{
    cout << endl
         << endl
         << "@@@@@@@@@@@@@@@@@@"<< endl
         << "Enter your choice" << endl
         << "1- wirte" << endl
         << "2- read" << endl
         << "3- erase" << endl
         << "4- show" << endl
         << "5- exit" << endl
         << "@@@@@@@@@@@@@@@@@@" << endl << endl;
}

void handleRequest(ariel::Notebook &notebook, const int &choice)
{
    int page, row, column, dir, length;
    Direction dr;
    string data;

    if (choice == exitNubmer - 1)
    {
        cout << "Enter page number" << endl;
        cin >> page;
        notebook.show(page);
    }

    else if (choice <= exitNubmer - 2)
    {

        cout
            << "Enter page number" << endl;
        cin >> page;

        cout << "Enter row number" << endl;
        cin >> row;

        cout << "Enter column number" << endl;
        cin >> column;

        cout << "Enter dircetion" << endl;
        cin >> dir;

        dr = (dir == 0) ? Direction::Horizontal : Direction::Vertical;

        switch (choice)
        {
        case 1:
            cout << "Enter text" << endl;
            cin >> data;
            notebook.write(page, row, column, dr, data);
            break;

        case 2:
            cout << "Enter length" << endl;
            cin >> length;
            cout << notebook.read(page, row, column, dr, length) << endl;
            break;

        case 3:
            cout << "Enter length" << endl;
            cin >> length;
            notebook.erase(page, row, column, dr, length);
            break;

        default:
            break;
        }
    }
}

int main()
{
    ariel::Notebook notebook;

    notebook.show(100);

    int choice = 0;

    while (choice != exitNubmer)
    {
        printChoices();
        cin >> choice;
        handleRequest(notebook, choice);
    }
}
