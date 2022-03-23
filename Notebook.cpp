#include "Notebook.hpp"
#include "Direction.hpp"
#include <string>
#include <iostream>
using namespace ariel;
using namespace std;

void validateInput(int page, int row, int column, Direction dir, int length = 0, const string &data = "")
{
    if (page < 0 || row < 0 || column < 0 || length < 0)
    {
        throw invalid_argument("Error ,row , page , column  -> neither can be a negative value !");
    }

    if (length == 0)
    {
        if (dir == Direction::Horizontal && (column + (int)data.length() - 1 >= _COLUMN_LENGTH))
        {
            throw invalid_argument("Error ,column + data length must be less than COLUMN LENGTH");
        }
        if (data.find('~') != string::npos)
        {
            throw invalid_argument("the input string cant have '~'");
        }
    }
    else
    {
        if (dir == Direction::Horizontal && (column + length - 1 >= _COLUMN_LENGTH))
        {
            throw invalid_argument("Error ,column + data length must be less than COLUMN LENGTH");
        }
    }
}

void Notebook::updatePageIndexs(int page, int row, Direction dir, int length)
{
    if (_pages[page].first_written_row == -1)
    {
        _pages[page].first_written_row = (row > 0) ? row - 1 : row;
        _pages[page].last_written_row = (dir == Direction::Vertical) ? row + length : row;
    }
    else if (row <= _pages[page].first_written_row)
    {
        _pages[page].first_written_row = (row > 0) ? row - 1 : row;
        _pages[page].last_written_row = (dir == Direction::Vertical && row + length > _pages[page].last_written_row) ? row + length : row;
    }
}

void Notebook::write(int page, int row, int column, Direction dir, const string &data)
{
    validateInput(page, row, column, dir, 0, data);
    // check intersection
    for (int i = 0; i < data.size(); i++)
    {
        if ((dir == Direction::Horizontal && this->_pages[page].page[row][column + i].ch != '_') || (dir == Direction::Vertical && this->_pages[page].page[row + i][column].ch != '_'))
        {
            throw invalid_argument("Error , writing one of the letter intersect with another");
        }
    }

    updatePageIndexs(page, row, dir, (int)data.size());

    int i = 0;
    for (char const &ch : data)
    {
        if (dir == Direction::Horizontal)
        {
            this->_pages[page].page[row][column + i].ch = ch;
        }
        else
        {
            this->_pages[page].page[row + i][column].ch = ch;
        }
        i++;
    }
}

string Notebook::read(int page, int row, int column, Direction dir, int length)
{
    validateInput(page, row, column, dir, length);
    string str;
    for (int i = 0; i < length; i++)
    {
        if (dir == Direction::Horizontal)
        {
            str += this->_pages[page].page[row][column + i].ch;
        }
        else
        {
            str += this->_pages[page].page[row + i][column].ch;
        }
    }
    return str;
}

void Notebook::erase(int page, int row, int column, Direction dir, int length)
{
    validateInput(page, row, column, dir, length);
    updatePageIndexs(page, row, dir, length);

    for (int i = 0; i < length; i++)
    {
        if (dir == Direction::Horizontal)
        {
            this->_pages[page].page[row][column + i].ch = '~';
        }
        else
        {
            this->_pages[page].page[row + i][column].ch = '~';
        }
    }
}

int countDigits(int x)
{
    const int div = 10;
    if (x == 0)
    {
        return 1;
    }
    int cnt = 0;
    while (x != 0)
    {
        cnt++;
        x /= div;
    }
    return cnt;
}

void Notebook::printPage(int page, bool flag, int start_row, int end_row)
{
    for (int i = start_row; i <= end_row; i++)
    {
        cout << i << "-";

        int maxRowNumber = flag ? 3 : countDigits(_pages[page].last_written_row) + 1;

        for (int k = 0; k < maxRowNumber - countDigits(i); k++)
        {
            cout << " ";
        }

        for (int k = 0; k < _COLUMN_LENGTH; k++)
        {
            cout << _pages[page].page[i][k].ch << "";
        }
        cout << endl;
    }

    cout << endl;
}

void Notebook::show(int page)
{
    if ((int)page < 0)
    {
        throw invalid_argument("Error ,page cant be a negative value !");
    }

    cout
        << endl
        << "Page number " << page << endl
        << endl;

    if (_pages[page].first_written_row == -1)
    {
        printPage(page, true);
    }
    else
    {
        printPage(page, false, _pages[page].first_written_row, _pages[page].last_written_row);
    }
}
