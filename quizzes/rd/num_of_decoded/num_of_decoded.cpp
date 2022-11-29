#include <string>

using namespace std;

size_t NumOfDecoded(string str)
{
    size_t counter = 0;
    size_t runner_index = 0;

    while ('\0' != str[runner_index])
    {
        switch (static_cast<size_t>(str[runner_index]))
        {
        case (1):
            if ('\0' != str[runner_index + 1])
            {
                counter += 2;
                static_cast<size_t>(str[runner_index + 1])
            }

            break;

        default:
            break;
        }
    }
}

int main()
{
    return 0;
}