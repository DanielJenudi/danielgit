#include <string>
#include <exception>
#include <iostream>

using namespace std;

long RomanToDecimal(string roman);
void InitLut(long *lut);

int main()
{
    cout << "input: IV, output: " << RomanToDecimal("IV") << endl;
    cout << "input: XIV, output: " << RomanToDecimal("XIV") << endl;
    cout << "input: LXVIII, output: " << RomanToDecimal("LXVIII") << endl;
    cout << "input: XCVIII, output: " << RomanToDecimal("XCVIII") << endl;
    cout << "input: MDCLXVI, output: " << RomanToDecimal("MDCLXVI") << endl;
    cout << "input: CML, output: " << RomanToDecimal("CML") << endl;
    cout << "input: -CML, output: " << RomanToDecimal("-CML") << endl;

    // cout << "input: DMLCVXI, output: " << RomanToDecimal("aaa") << endl;

    return 0;
}

long RomanToDecimal(string roman)
{
    static long lut[256] = {0};
    static bool is_init = false;

    if (false == is_init)
    {
        InitLut(lut);
        is_init = true;
    }

    bool is_negativ = false;
    if ('-' == roman[0])
    {
        is_negativ = true;
        roman.erase(roman.begin());
    }

    long result = 0;
    long prev_val = 0;

    for (long i = (roman.length() - 1); i >= 0; --i)
    {
        long cur_val = lut[static_cast<long>(roman[i])];
        if (0 == cur_val)
        {
            string error = "Unvalid Input Of Roman Number: ";
            error += roman[i];
            error += "\n";

            throw std::runtime_error(error);
        }

        if (cur_val < prev_val)
        {
            result -= cur_val;
        }
        else
        {
            prev_val = cur_val;
            result += cur_val;
        }
    }

    if (true == is_negativ)
    {
        result *= -1;
    }

    return result;
}

void InitLut(long *lut)
{
    lut['I'] = 1;
    lut['V'] = 5;
    lut['X'] = 10;
    lut['L'] = 50;
    lut['C'] = 100;
    lut['D'] = 500;
    lut['M'] = 1000;
}