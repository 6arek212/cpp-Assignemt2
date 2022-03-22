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
        map<int, map<int, char *>> _pages;

    private:
        void addLines(int page, int rows, Direction dir, int length = 1);
        int findFirstWirttenLine(int page);

    public:
        void write(int page, int row, int column, Direction dir, const string &data);
        string read(int page, int row, int column, Direction dir, int length);
        void erase(int page, int row, int column, Direction dir, int length);
        void show(int page);
        ~Notebook();
    };

}