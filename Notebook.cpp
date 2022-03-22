#include "Notebook.hpp"
#include "Direction.hpp"
#include <string>
#include <iostream>
using namespace ariel;
using namespace std;

void Notebook::addLines(int page, int rows, Direction dir, int length)
{
    int lg = (dir == Direction::Horizontal) ? rows : rows + length;
    for (int i = 0; i <= lg; i++)
    {
        if (this->_pages[page].count(i) == 0)
        {
            this->_pages[page][i] = new char[_COLUMN_LENGTH];
            for (int k = 0; k < _COLUMN_LENGTH; k++)
            {
                this->_pages[page][i][k] = '_';
            }
        }
    }
}

bool isValidString(string str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == '~')
        {
            return false;
        }
    }
    return true;
}

void Notebook::write(int page, int row, int column, Direction dir, const string &data)
{
    if ((int)page < 0 || (int)row < 0 || (int)column < 0)
    {
        throw invalid_argument("Error ,row , page , column  -> neither can be a negative value !");
    }

    if (!isValidString(data))
    {
        throw invalid_argument("the input string cant have '~' or '_'");
    }

    if (dir != Direction::Vertical && (column + (int)data.length() - 1 >= _COLUMN_LENGTH))
    {
        throw invalid_argument("Error ,column + data length must be less than COLUMN LENGTH");
    }

    addLines(page, row, dir, data.length());

    for (int i = 0; i < data.size(); i++)
    {
        if ((dir == Direction::Horizontal && this->_pages[page][row][column + i] != '_') || (dir == Direction::Vertical && this->_pages[page][row + i][column] != '_'))
        {
            throw invalid_argument("Error , writing one of the letter intersect with another");
        }
    }

    int i = 0;
    for (char const &ch : data)
    {
        if (dir == Direction::Horizontal)
        {
            this->_pages[page][row][column + i] = ch;
        }
        else
        {
            this->_pages[page][row + i][column] = ch;
        }
        i++;
    }
}

string Notebook::read(int page, int row, int column, Direction dir, int length)
{
    if ((int)page < 0 || (int)row < 0 || (int)column < 0 || (int)length < 0)
    {
        throw invalid_argument("Error ,row , page , column , length -> neither can be a negative value !");
    }

    if (dir != Direction::Vertical && (column + length - 1 >= _COLUMN_LENGTH))
    {
        throw invalid_argument("Error ,column + data length must be less than COLUMN LENGTH");
    }

    addLines(page, row, dir, length);

    string str;
    for (int i = 0; i < length; i++)
    {
        if (dir == Direction::Horizontal)
        {
            str += this->_pages[page][row][column + i];
        }
        else
        {
            str += this->_pages[page][row + i][column];
        }
    }
    return str;
}

void Notebook::erase(int page, int row, int column, Direction dir, int length)
{
    if ((int)page < 0 || (int)row < 0 || (int)column < 0 || (int)length < 0)
    {
        throw invalid_argument("Error ,row , page , column , length -> neither can be a negative value !");
    }

    if (dir != Direction::Vertical && (column + length - 1 >= _COLUMN_LENGTH))
    {
        throw invalid_argument("Error ,column + data length must be less than COLUMN LENGTH");
    }

    addLines(page, row, dir, length);
    // for (int i = 0; i < length; i++)
    // {
    //     if ((dir == Direction::Horizontal && this->_pages[page][row][column + i] == '~') || (dir == Direction::Vertical && this->_pages[page][row + i][column] == '~'))
    //     {
    //         throw invalid_argument("Error , Already removed this char");
    //     }
    // }

    for (int i = 0; i < length; i++)
    {
        if (dir == Direction::Horizontal)
        {
            this->_pages[page][row][column + i] = '~';
        }
        else
        {
            this->_pages[page][row + i][column] = '~';
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

int Notebook::findFirstWirttenLine(int page)
{
    for (int i = 0; _pages[page].count(i) != 0; i++)
    {
        for (int k = 0; k < _COLUMN_LENGTH; k++)
        {
            if (_pages[page][i][k] != '_')
            {
                if (i > 0)
                {
                    return i - 1;
                }
                return i;
            }
        }
    }
    return 0;
}

void Notebook::show(int page)
{
    if ((int)page < 0)
    {
        throw invalid_argument("Error ,page cant be a negative value !");
    }

    cout << endl
         << "-----"
         << "Notebook title: " << this->_title << "-----" << endl;

    cout
        << endl
        << "Page number " << page << endl
        << endl;

    int starterLine = findFirstWirttenLine(page);

    for (int i = starterLine; (_pages[page].count(i) != 0); i++)
    {
        cout << i << "-";

        for (int k = 0; k < countDigits(_pages[page].size()) + 1 - countDigits(i); k++)
        {
            cout << " ";
        }

        for (int k = 0; k < _COLUMN_LENGTH; k++)
        {
            cout << _pages[page][i][k] << "";
        }
        cout << endl;
    }

    cout << endl;
}

/**
 * @brief  This is the Show format
 *
 */

/**
    Page number 100


    83-  ____________________________________________________________________________________________________
    84-  ____________________________________________________________________________________________________
    85-  ____________________________________________________________________________________________________
    86-  ____________________________________________________________________________________________________
    87-  ____________________________________________________________________________________________________
    88-  ____________________________________________________________________________________________________
    89-  ____________________________________________________________________________________________________
    90-  ____________________________________________________________________________________________________
    91-  ____________________________________________________________________________________________________
    92-  ____________________________________________________________________________________________________
    93-  ____________________________________________________________________________________________________
    94-  ____________________________________________________________________________________________________
    95-  ____________________________________________________________________________________________________
    96-  ____________________________________________________________________________________________________
    97-  ____________________________________________________________________________________________________
    98-  ____________________________________________________________________________________________________
    99-  ___________________________________________________~________________________________________________
    100- __________________________________________________a~cd______________________________________________
    101- ___________________________________________________~________________________________________________
    102- ____________________________________________________________________________________________________

**/

Notebook::~Notebook()
{
    for (auto &pg : _pages)
    {
        for (auto &ln : pg.second)
        {
            delete[] ln.second;
        }
    }
}