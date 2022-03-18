#include "Notebook.hpp"
#include "Direction.hpp"
#include <string>
#include <iostream>
using namespace ariel;
using namespace std;

void Notebook::write(int page, int row, int column, Direction dir, string data)
{
    if (!this->_pages.count(page))
    {
        map<int, Word[rowLength]> mp;
        this->_pages[page] = mp;
    }

    this->_pages.at(page).at(row)[column].setWord(data);
    this->_pages.at(page).at(row)[column].setDirection(dir);
}

string Notebook::read(int page, int row, int column, Direction dir, int length)
{
    return "aaaa";
}

void Notebook::erase(int page, int row, int column, Direction dir, int length)
{
    this->_pages.at(page).at(row)[column].setWord("`");
}

void Notebook::show(int page)
{
    for (int i = 0; i < this->_pages.size(); i++)
    {
        for (int k = 0; k < this->_pages.at(i).size(); k++)
        {
            cout << _pages.at(i).at(k)->getWord() << " ";
        }

        cout << endl;
    }
}

// void Notebook::setTitle(string title)
// {
//     this->_title = title;
// }
