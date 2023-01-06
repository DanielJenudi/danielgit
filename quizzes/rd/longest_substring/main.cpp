#include <string>   // string
#include <cstring>  // memset
#include <iostream> // cout

using namespace std;

#define ASCII_SIZE (256)

int LongestSubstring(string str);

int main()
{
    cout << LongestSubstring("baca") << endl;
    cout << LongestSubstring("bbaacd") << endl;
    cout << LongestSubstring("bbaacdxa") << endl;

    return 0;
}

int LongestSubstring(string str)
{
    string::iterator runner = str.begin();
    string::iterator start_of_sub = runner;

    int max = 0;

    int cur = 0;
    int lut[ASCII_SIZE] = {0};

    while (str.end() != runner)
    {

        if (0 == lut[static_cast<int>(*runner)])
        {
            ++cur;
            lut[static_cast<int>(*runner)] = cur;
            ++runner;
        }
        else
        {
            max = cur > max ? cur : max;
            runner = start_of_sub + lut[static_cast<int>(*runner)];
            start_of_sub = runner;

            cur = 0;
            memset(lut, 0, sizeof(int) * ASCII_SIZE);
        }
    }

    max = cur > max ? cur : max;

    return max;
}
