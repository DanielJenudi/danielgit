
#include <string>   // string
#include <cstddef>  // size_t
#include <iostream> // cout

using namespace std;

string Convert(string str, int nrows);

int main()
{
    cout << Convert("PAYPALISHIRING", 3) << endl;
    cout << Convert("PAYPALISHIRING", 4) << endl;

    return 0;
}

string Convert(string str, int nrows)
{
    if (1 == nrows)
    {
        return str;
    }

    string *str_array = new string[nrows];

    bool add_or_decrese = true;
    size_t index = 0;

    for (size_t i = 0; i < str.length(); ++i)
    {
        str_array[index].push_back(str[i]);

        if ((0 == index) && (false == add_or_decrese))
        {
            add_or_decrese = !add_or_decrese;
        }
        else if ((static_cast<size_t>(nrows - 1) == index) && (true == add_or_decrese))
        {
            add_or_decrese = !add_or_decrese;
        }

        if (add_or_decrese)
        {
            ++index;
        }
        else
        {
            --index;
        }
    }

    string result = "";

    for (int i = 0; i < nrows; ++i)
    {
        result += str_array[i];
    }

    delete[] str_array;

    return result;
}