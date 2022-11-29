#include <string>
#include <cstring>
#include <iostream>

using namespace std;

string SubStringKdistinct(const string &str, size_t k);

int main()
{
    string str = "aabaacccccvs";

    cout << str << endl;
    cout << "k = 0: " << SubStringKdistinct(str, 0) << endl;
    cout << "k = 1: " << SubStringKdistinct(str, 1) << endl;
    cout << "k = 2: " << SubStringKdistinct(str, 2) << endl;
    cout << "k = 3: " << SubStringKdistinct(str, 3) << endl;

    return 0;
}

string SubStringKdistinct(const string &str, size_t k)
{
    char ascii_lut[256] = {0};
    string max_str;
    string cur_str;
    size_t counter = 0;

    string::const_iterator return_back;
    size_t diff_char_counter = 0;

    if (k == 0)
    {
        return cur_str;
    }

    for (string::const_iterator runner = str.begin(); runner != str.end(); ++runner)
    {
        if (ascii_lut[static_cast<size_t>(*runner)] == 0)
        {
            if (k > 1)
            {
                if (1 == diff_char_counter)
                {
                    return_back = runner;
                }

                ++diff_char_counter;
            }

            if (k == counter)
            {
                if (cur_str.length() > max_str.length())
                {
                    max_str = cur_str;
                }

                if (k > 1)
                {
                    diff_char_counter = 0;
                    runner = return_back;
                }

                memset(ascii_lut, 0, 256);
                counter = 0;
                cur_str.clear();
            }
            else
            {
                ++counter;
                ascii_lut[static_cast<size_t>(*runner)] = 1;
                cur_str.push_back(*runner);
            }
        }
        else
        {
            cur_str.push_back(*runner);
        }
    }

    if (cur_str.length() > max_str.length())
    {
        return cur_str;
    }
    else
    {
        return max_str;
    }
}
