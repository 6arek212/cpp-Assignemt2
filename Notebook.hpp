#include "Direction.hpp"
#include <string>
#include <map>
using namespace std;

namespace ariel
{
    const int _COLUMN_LENGTH = 100;

    class Notebook
    {

    private:
        string _title;
        map<unsigned int, map<unsigned int, char *>> _pages;

    private:
        void addLines(unsigned int page, unsigned int rows, Direction dir, unsigned int length = 1);
        unsigned int findFirstWirttenLine(unsigned int page);

    public:
        void write(unsigned int page, unsigned int row, unsigned int column, Direction dir, const string &data);
        string read(unsigned int page, unsigned int row, unsigned int column, Direction dir, unsigned int length);
        void erase(unsigned int page, unsigned int row, unsigned int column, Direction dir, unsigned int length);
        void show(unsigned int page);
        ~Notebook();
        Notebook(string title = "Note 1");
    };

}