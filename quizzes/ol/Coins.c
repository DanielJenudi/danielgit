#include <stdio.h> /* printf */

size_t FindCoinRepresent(size_t num);
size_t ReqCalc(size_t num, size_t counter, size_t sum, size_t adder);

int main()
{
    printf("%lu\n", FindCoinRepresent(15));

    return 0;
}

size_t FindCoinRepresent(size_t num)
{
    return ReqCalc(num, 0, 0, 1);
}

size_t ReqCalc(size_t num, size_t counter, size_t sum, size_t adder)
{
    if (sum > num)
    {
        return counter;
    }

    if (sum == num)
    {
        return (counter + 1);
    }

    switch (adder)
    {
    case 1:
        counter = ReqCalc(num, counter, sum + 1, 1);
        counter = ReqCalc(num, counter, sum + 5, 5);
        counter = ReqCalc(num, counter, sum + 10, 10);
        counter = ReqCalc(num, counter, sum + 25, 25);

        break;

    case 5:
        counter = ReqCalc(num, counter, sum + 5, 5);
        counter = ReqCalc(num, counter, sum + 10, 10);
        counter = ReqCalc(num, counter, sum + 25, 25);

        break;

    case 10:
        counter = ReqCalc(num, counter, sum + 10, 10);
        counter = ReqCalc(num, counter, sum + 25, 25);

        break;

    case 25:
        counter = ReqCalc(num, counter, sum + 25, 25);

        break;

    default:
        break;
    }

    return counter;
}