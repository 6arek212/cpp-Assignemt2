#include "Direction.hpp"
#include <string>
#include <map>
using namespace std;

namespace ariel
{
    const int rowLength = 20;

    class Word
    {
    private:
        string word;
        Direction direction;

    public:
        void setWord(string word)
        {
            this->word = word;
        }

        void setDirection(Direction dr)
        {
            this->direction = dr;
        }

        string getWord(){
            return word;
        }
    };

    class Notebook
    {

    private:
        int _pagesNumber;
        string _title;
        string _description;
        map<int, map<int, Word[rowLength]>> _pages;

    public:
        void write(int page, int row, int column, Direction dir, string data);
        string read(int page, int row, int column, Direction dir, int length);
        void erase(int page, int row, int column, Direction dir, int length);
        void show(int page);
        // void Notebook::setTitle(string title);
        // void Notebook::setDescription(string des);
    };

}