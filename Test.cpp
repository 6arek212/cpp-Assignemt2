#include "Notebook.hpp"
#include "iostream"
#include "doctest.h"
#include <string>
using namespace std;
#include "Direction.hpp"
using namespace ariel;

const int COLUMN_LENGTH = 100;

void fillSquarePage(Notebook &notebook,unsigned int page)
{
    /**
     * @brief  filling a page like so :
     *
     *
     *              @@@@@@@@@@@@@@@
     *              @-------------@
     *              @-------------@
     *              @-------------@
     *              @-------------@
     *              @-------------@
     *              @-------------@
     *              @-------------@
     *              @@@@@@@@@@@@@@@
     *                              size COLUMN_LENGTH * COLUMN_LENGTH
     *
     *      then checking if it read correctly
     *
     *
     */
    int dir = 1;
    for (unsigned int k = 0; k < COLUMN_LENGTH; k++)
    {
        if (dir == 1)
        {
            notebook.write(/*page=*/page, /*row=*/0, /*column=*/k, Direction::Horizontal, "@");
            if (k + 1 == COLUMN_LENGTH)
            {
                k = 0;
                dir++;
            }
        }
        else if (dir == 2)
        {
            notebook.write(/*page=*/page, /*row=*/k, /*column=*/COLUMN_LENGTH - 1, Direction::Horizontal, "@");
            if (k + 1 == COLUMN_LENGTH)
            {
                k = 0;
                dir++;
            }
        }
        else if (dir == 3)
        {
            notebook.write(/*page=*/page, /*row=*/COLUMN_LENGTH - 1, /*column=*/COLUMN_LENGTH - 1 - k, Direction::Horizontal, "@");
            if (k + 1 == COLUMN_LENGTH)
            {
                k = 0;
                dir++;
            }
        }
        else
        {
            notebook.write(/*page=*/page, /*row=*/COLUMN_LENGTH - 1 - k, /*column=*/0, Direction::Horizontal, "@");
            if (COLUMN_LENGTH - 1 - k - 1 == 0)
            {
                break;
            }
        }
    }
}

TEST_CASE("Good input")
{
    Notebook notebook;

    notebook.write(/*page=*/100, /*row=*/100, /*column=*/50, Direction::Horizontal, "abcd");
    CHECK(notebook.read(100, 100, 50, Direction::Horizontal, 4) == "abcd");

    notebook.erase(/*page=*/100, /*row=*/99, /*column=*/51, Direction::Vertical, /*length=*/3);
    CHECK(notebook.read(100, 99, 51, Direction::Vertical, 3) == "~~~");

    CHECK(notebook.read(100, 100, 50, Direction::Horizontal, 4) == "a~cd");

    notebook.write(/*page=*/0, /*row=*/0, /*column=*/0, Direction::Horizontal, "Hello this is tarik");
    CHECK(notebook.read(0, 0, 0, Direction::Horizontal, 19) == "Hello this is tarik");

    notebook.erase(/*page=*/0, /*row=*/0, /*column=*/0, Direction::Horizontal, /*length=*/19);

    CHECK(notebook.read(0, 0, 0, Direction::Horizontal, 19) == "~~~~~~~~~~~~~~~~~~~");
}

TEST_CASE("Filling Page Horizontaly")
{
    Notebook notebook;

    for (unsigned int k = 0; k < 100; k++)
    {
        for (unsigned int i = 0; i < COLUMN_LENGTH; i++)
        {
            notebook.write(/*page=*/1, /*row=*/k, /*column=*/i, Direction::Horizontal, "1");
        }
    }

    for (unsigned  k = 0; k < 100; k++)
    {
        for (unsigned int i = 0; i < COLUMN_LENGTH; i++)
        {
            CHECK(notebook.read(1, k, 0, Direction::Horizontal, 1) == "1");
        }
    }
}

TEST_CASE("Erase all 100 line in page Horizontaly")
{
    Notebook notebook;

    for (unsigned int k = 0; k < 100; k++)
    {
        notebook.erase(/*page=*/1, /*row=*/k, /*column=*/0, Direction::Horizontal, COLUMN_LENGTH);
    }

    for (unsigned int k = 0; k < 100; k++)
    {
        for (unsigned int i = 0; i < COLUMN_LENGTH; i++)
        {
            CHECK(notebook.read(1, k, 0, Direction::Horizontal, 1) == "~");
        }
    }
}

TEST_CASE("Filling Page Verticaly")
{
    Notebook notebook;

    for (unsigned int k = 0; k < 100; k++)
    {
        for (unsigned int i = 0; i < COLUMN_LENGTH; i++)
        {
            notebook.write(/*page=*/1, /*row=*/k, /*column=*/i, Direction::Vertical, "1");
        }
    }

    for (unsigned int k = 0; k < 100; k++)
    {
        for (unsigned int i = 0; i < COLUMN_LENGTH; i++)
        {
            CHECK(notebook.read(1, k, 0, Direction::Vertical, 1) == "1");
        }
    }
}

TEST_CASE("Erase all 100 line in page Verticaly")
{
    Notebook notebook;

    for (unsigned int k = 0; k < 100; k++)
    {
        notebook.erase(/*page=*/1, /*row=*/k, /*column=*/0, Direction::Vertical, COLUMN_LENGTH);
    }

    for (unsigned int k = 0; k < 100; k++)
    {
        for (unsigned int i = 0; i < COLUMN_LENGTH; i++)
        {
            CHECK(notebook.read(1, k, 0, Direction::Vertical, 1) == "~");
        }
    }
}

TEST_CASE("Writing on different pages")
{
    Notebook notebook;

    for (unsigned int k = 0; k < 100; k++)
    {
        notebook.write(/*page=*/k, /*row=*/0, /*column=*/0, Direction::Horizontal, "tarik");
    }

    for (unsigned int k = 0; k < 100; k++)
    {
        CHECK(notebook.read(k, 0, 0, Direction::Horizontal, 5) == "tarik");
        CHECK(notebook.read(k, 0, 0, Direction::Horizontal, 4) == "tari");
        CHECK(notebook.read(k, 0, 0, Direction::Horizontal, 3) == "tar");
        CHECK(notebook.read(k, 0, 0, Direction::Horizontal, 2) == "ta");
        CHECK(notebook.read(k, 0, 0, Direction::Horizontal, 1) == "t");
    }
}

TEST_CASE("Fill square page")
{
    /**
     * @brief  filling a page like so :
     *
     *
     *              @@@@@@@@@@@@@@@
     *              @-------------@
     *              @-------------@
     *              @-------------@
     *              @-------------@
     *              @-------------@
     *              @-------------@
     *              @-------------@
     *              @@@@@@@@@@@@@@@
     *
     *
     *      then checking if it read correctly
     *
     *
     */

    Notebook notebook;
    fillSquarePage(notebook, 0);

    int dir = 0;
    for (unsigned int k = 0; k < COLUMN_LENGTH; k++)
    {

        for (unsigned int i = 0; i < COLUMN_LENGTH; i++)
        {
            if (k == 0 || k == COLUMN_LENGTH - 1)
            {
                CHECK(notebook.read(0, k, i, Direction::Horizontal, 1) == "@");
            }
            else
            {
                if (i == 0 || i == COLUMN_LENGTH - 1)
                {
                    CHECK(notebook.read(0, k, i, Direction::Horizontal, 1) == "@");
                }
                else
                {
                    CHECK(notebook.read(0, k, i, Direction::Horizontal, 1) == "_");
                }
            }
        }
    }

    // notebook.show(0);
}

TEST_CASE("ONE PAGE WITH 1000 ROWS")
{
    Notebook notebook;

    for (unsigned int k = 0; k < 1000; k++)
    {
        notebook.write(/*page=*/0, /*row=*/k, k % (COLUMN_LENGTH - 10), Direction::Horizontal, "1111111111");
    }

    for (unsigned int k = 0; k < 1000; k++)
    {
        CHECK(notebook.read(0, k, k % (COLUMN_LENGTH - 10), Direction::Horizontal, 10) == "1111111111");
    }
}

TEST_CASE("1000 PAGE WITH 10 ROWS EACH")
{
    Notebook notebook;

    for (unsigned int i = 0; i < 1000; i++)
    {
        for (unsigned int k = 0; k < 10; k++)
        {
            notebook.write(/*page=*/i, /*row=*/k, /*column=*/k % (COLUMN_LENGTH - 10), Direction::Horizontal, "1111111111");
        }
    }

    for (unsigned int i = 0; i < 1000; i++)
    {
        for (unsigned int k = 0; k < 10; k++)
        {
            CHECK(notebook.read(0, k, k % (COLUMN_LENGTH - 10), Direction::Horizontal, 10) == "1111111111");
        }
    }
}

TEST_CASE("Alphabet Page")
{
    /**
     * @brief  filling a page like so :
     *
     *
     *              abcdefghijklmnopqrstuwvxyz
     *              abcdefghijklmnopqrstuwvxyz
     *              abcdefghijklmnopqrstuwvxyz
     *              abcdefghijklmnopqrstuwvxyz
     *              abcdefghijklmnopqrstuwvxyz
     *              abcdefghijklmnopqrstuwvxyz
     *              abcdefghijklmnopqrstuwvxyz
     *              abcdefghijklmnopqrstuwvxyz
     *              abcdefghijklmnopqrstuwvxyz
     *
     *
     *      then checking if it read correctly
     *
     *
     */

    Notebook notebook;

    string str = "abcdefghijklmnopqrstuwvxyz";
    for (unsigned int i = 0; i < 10; i++)
    {
        notebook.write(/*page=*/0, /*row=*/i, /*column=*/COLUMN_LENGTH / 2, Direction::Horizontal, str);
    }

    for (unsigned int i = 0; i < 10; i++)
    {
        CHECK(notebook.read(0, i, COLUMN_LENGTH / 2, Direction::Horizontal, 26) == str);
    }
}

TEST_CASE("Bad input")
{

    Notebook notebook;

    // CHECK_THROWS(notebook.write(/*page=*/-100, /*row=*/100, /*column=*/50, Direction::Horizontal, "abcd"));
    // CHECK_THROWS(notebook.write(/*page=*/100, /*row=*/-100, /*column=*/50, Direction::Horizontal, "abcd"));
    // CHECK_THROWS(notebook.write(/*page=*/100, /*row=*/100, /*column=*/-50, Direction::Horizontal, "abcd"));
    // CHECK_THROWS(notebook.write(/*page=*/100, /*row=*/100, /*column=*/-50, Direction::Horizontal, "abcd"));
    // CHECK_THROWS(notebook.write(/*page=*/-100, /*row=*/-100, /*column=*/-50, Direction::Horizontal, "abcd"));

    // CHECK_THROWS(notebook.write(/*page=*/0, /*row=*/0, /*column=*/100, Direction::Horizontal, "a"));
    // CHECK_NOTHROW(notebook.write(/*page=*/0, /*row=*/0, /*column=*/99, Direction::Horizontal, "a"));

    // CHECK_THROWS(notebook.erase(/*page=*/-100, /*row=*/99, /*column=*/51, Direction::Vertical, /*length=*/3));
    // CHECK_THROWS(notebook.erase(/*page=*/100, /*row=*/-99, /*column=*/51, Direction::Vertical, /*length=*/3));
    // CHECK_THROWS(notebook.erase(/*page=*/100, /*row=*/99, /*column=*/-51, Direction::Vertical, /*length=*/3));
    // CHECK_THROWS(notebook.erase(/*page=*/100, /*row=*/99, /*column=*/51, Direction::Vertical, /*length=*/-3));
    // CHECK_THROWS(notebook.erase(/*page=*/-100, /*row=*/-99, /*column=*/-51, Direction::Vertical, /*length=*/-3));

    // CHECK_THROWS(notebook.read(-1, 1, 1, Direction::Horizontal, 1));
    // CHECK_THROWS(notebook.read(1, -1, 1, Direction::Horizontal, 1));
    // CHECK_THROWS(notebook.read(1, 1, -1, Direction::Horizontal, 1));
    // CHECK_THROWS(notebook.read(-1, -1, -1, Direction::Horizontal, 1));
}

TEST_CASE("Letter intersecting")
{
    /**
     * @brief  multipule tests with letters intercect each other
     *
     *
     */

    Notebook notebook;

    notebook.write(/*page=*/100, /*row=*/100, /*column=*/50, Direction::Horizontal, "abcd");
    CHECK_THROWS(notebook.write(/*page=*/100, /*row=*/99, /*column=*/52, Direction::Vertical, "xyz"));

    notebook.write(/*page=*/0, /*row=*/100, /*column=*/50, Direction::Horizontal, "abcd");
    CHECK_THROWS(notebook.write(/*page=*/0, /*row=*/100, /*column=*/50, Direction::Horizontal, "abcd"));

    CHECK_THROWS(notebook.write(/*page=*/0, /*row=*/100, /*column=*/50, Direction::Vertical, "abcd"));

    notebook.write(/*page=*/1, /*row=*/0, /*column=*/0, Direction::Horizontal, "tarik husin");
    CHECK_THROWS(notebook.write(/*page=*/1, /*row=*/0, /*column=*/0, Direction::Vertical, "tarik husin"));
    CHECK_THROWS(notebook.write(/*page=*/1, /*row=*/0, /*column=*/10, Direction::Horizontal, "tarik husin"));
    CHECK_THROWS(notebook.write(/*page=*/1, /*row=*/0, /*column=*/5, Direction::Vertical, "-"));
}

TEST_CASE("fill square page and check for out of border intersection")
{
    /**
     * @brief  filling a page like so :
     *
     *
     *              @@@@@@@@@@@@@@@
     *              @-------------@
     *              @-------------@
     *              @-------------@
     *              @-------------@
     *              @-------------@
     *              @-------------@
     *              @-------------@
     *              @@@@@@@@@@@@@@@
     *
     *
     *      Then if a word touches the edges it should throw an Exception !
     *      And when filling the inner rows it should not throw an Exception !
     *
     */

    Notebook notebook;
    fillSquarePage(notebook, 0);

    CHECK_THROWS(notebook.write(/*page=*/0, /*row=*/0, /*column=*/0, Direction::Horizontal, "-"));
    CHECK_THROWS(notebook.write(/*page=*/0, /*row=*/0, /*column=*/COLUMN_LENGTH - 1, Direction::Horizontal, "-"));
    CHECK_THROWS(notebook.write(/*page=*/0, /*row=*/COLUMN_LENGTH - 1, /*column=*/COLUMN_LENGTH - 1, Direction::Horizontal, "-"));
    CHECK_THROWS(notebook.write(/*page=*/0, /*row=*/COLUMN_LENGTH - 1, /*column=*/COLUMN_LENGTH / 2, Direction::Horizontal, "-"));

    for (unsigned int i = 1; i < COLUMN_LENGTH - 1; i++)
    {
        for (unsigned int k = 1; k < COLUMN_LENGTH - 1; k++)
        {
            CHECK_NOTHROW(notebook.write(/*page=*/0, /*row=*/i, /*column=*/k, Direction::Vertical, "H"));
        }
    }
}
