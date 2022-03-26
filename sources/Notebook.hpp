#include "Direction.hpp"
#include <string>
#include <map>
using namespace std;

namespace ariel
{
    const int _COLUMN_LENGTH = 100;

    struct placeholder
    {
        char ch = '_';
    };

    struct page
    {
        map<int, placeholder[_COLUMN_LENGTH]> page;
        int first_written_row = -1;
        int last_written_row = -1;
    };

    class Notebook
    {

    private:
        string _title;
        map<int, page> _pages;

    private:
        void updatePageIndexs(int page, int row, Direction dir, int length = 0);
        void printPage(int page, bool flag, int start_row = 0, int end_row = 100);

    public:
        void write(int page, int row, int column, Direction dir, const string &data);
        string read(int page, int row, int column, Direction dir, int length);
        void erase(int page, int row, int column, Direction dir, int length);
        void show(int page);
    };

}