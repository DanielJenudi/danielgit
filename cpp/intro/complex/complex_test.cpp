#include <iostream> /* i/o operations */
#include <cstdio>   /* oldstyle macro i/o use */
#include <ctime>    /*for clock()*/

#include "complex.hpp" /* complex implementation */

using namespace ilrd;

#define RUNTEST(test)                     \
    {                                     \
        if (!test)                        \
        {                                 \
            printf("\x1b[0;32m");         \
            printf("OK!\n\n");            \
            printf("\x1b[0m");            \
        }                                 \
        else                              \
        {                                 \
            printf("\x1b[1;31m");         \
            printf("\nTest Failed!\n\n"); \
            printf("\x1b[0m");            \
        }                                 \
    }

int total_fails = 0;
int ValCheck(int recieved_val, int expected_val, int line);
int TestSetGet(void);
int TestPlusEquals(void);
int TestMinusEquals(void);
int TestMultEquals(void);
int TestDivEquals(void);
int TestPlus(void);
int TestMinus(void);
int TestMult(void);
int TestDiv(void);
int TestEquals(void);
int TestNotEquals(void);
int TestCinCout(void);
void BenchMarkTest(void);

int main()
{
    RUNTEST(TestSetGet());
    RUNTEST(TestPlusEquals());
    RUNTEST(TestMinusEquals());
    RUNTEST(TestMultEquals());
    RUNTEST(TestDivEquals());
    RUNTEST(TestPlus());
    RUNTEST(TestMult());
    RUNTEST(TestDiv());
    RUNTEST(TestMinus());
    RUNTEST(TestEquals());
    RUNTEST(TestNotEquals());
    /* RUNTEST(TestCinCout()); */

    if (0 < total_fails)
    {
        printf("\n\n****** TOTAL FAILS = %d ******\n\n", total_fails);
    }

    BenchMarkTest();

    return 0;
}

int TestSetGet(void)
{
    int result = 0;
    Complex c1;
    Complex c2;
    Complex c3;

    std::cout << "--------- Testing Set  + Get ---------" << std::endl;

    result += ValCheck(c1.GetReal(), 0, __LINE__);
    result += ValCheck(c1.GetImaginary(), 0, __LINE__);

    c1.SetReal(1.5);
    c1.SetImaginary(2.5);
    result += ValCheck(c1.GetReal(), 1.5, __LINE__);
    result += ValCheck(c1.GetImaginary(), 2.5, __LINE__);

    c2.SetReal(3.5);
    c2.SetImaginary(4.5);
    result += ValCheck(c2.GetReal(), 3.5, __LINE__);
    result += ValCheck(c2.GetImaginary(), 4.5, __LINE__);

    c3.SetReal(5.5);
    c3.SetImaginary(6.5);
    result += ValCheck(c3.GetReal(), 5.5, __LINE__);
    result += ValCheck(c3.GetImaginary(), 6.5, __LINE__);

    return result;
}
int TestPlusEquals(void)
{
    int result = 0;
    Complex c1(3.5, 1.5);
    Complex c2(2.5, 2.5);
    Complex c3(1.5, 3.5);

    std::cout << "--------- Testing += ---------" << std::endl;

    c3 += c1;
    result += ValCheck(c3.GetReal(), 5.0, __LINE__);
    result += ValCheck(c3.GetImaginary(), 5.0, __LINE__);

    return result;
}

int TestMinusEquals(void)
{
    int result = 0;
    Complex c1(3.5, 1.5);
    Complex c2(2.5, 2.5);
    Complex c3(1.5, 3.5);

    std::cout << "--------- Testing -= ---------" << std::endl;

    c3 -= c1;

    result += ValCheck(c3.GetReal(), -2.0, __LINE__);
    result += ValCheck(c3.GetImaginary(), 2.0, __LINE__);

    return result;
}

int TestMultEquals(void)
{
    int result = 0;
    Complex c1(3.5, 1.5);
    Complex c2(2.5, 2.5);
    Complex c3(1.5, 3.5);

    std::cout << "--------- Testing *= ---------" << std::endl;

    c3 *= c1;
    result += ValCheck(c3.GetReal(), 7.0, __LINE__);
    result += ValCheck(c3.GetImaginary(), 7.0, __LINE__);

    return result;
}

int TestDivEquals(void)
{
    int result = 0;
    Complex c1(3.5, 1.5);
    Complex c2(2.5, 2.5);
    Complex c3(1.5, 3.5);

    std::cout << "--------- Testing /= ---------" << std::endl;

    c3 /= c1;
    result += ValCheck(c3.GetReal(), 7.0, __LINE__);
    result += ValCheck(c3.GetImaginary(), 7.0, __LINE__);

    return result;
}

int TestPlus(void)
{
    int result = 0;
    Complex c1(3.5, 1.5);
    Complex c2(2.5, 2.5);
    Complex c3(1.5, 3.5);

    std::cout << "--------- Testing + ---------" << std::endl;

    result += ValCheck((c1 + c3).GetReal(), 5.0, __LINE__);
    result += ValCheck((c1 + c3).GetImaginary(), 5.0, __LINE__);

    return result;
}

int TestMinus(void)
{
    int result = 0;
    Complex c1(3.5, 1.5);
    Complex c2(2.5, 2.5);
    Complex c3(1.5, 3.5);

    std::cout << "--------- Testing -  ---------" << std::endl;

    result += ValCheck((c1 - c3).GetReal(), 2.0, __LINE__);
    result += ValCheck((c1 - c3).GetImaginary(), -2.0, __LINE__);

    return result;
}

int TestMult(void)
{
    int result = 0;
    Complex c1(3.5, 1.5);
    Complex c2(2.5, 2.5);
    Complex c3(1.5, 3.5);

    std::cout << "--------- Testing * ---------" << std::endl;

    result += ValCheck((c1 * c3).GetReal(), 7.0, __LINE__);
    result += ValCheck((c1 * c3).GetImaginary(), 7.0, __LINE__);

    return result;
}

int TestDiv(void)
{
    int result = 0;
    Complex c1(3.5, 1.5);
    Complex c2(2.5, 2.5);
    Complex c3(1.5, 3.5);

    std::cout << "--------- Testing / ---------" << std::endl;

    result += ValCheck((c1 / c3).GetReal(), 7.0, __LINE__);
    result += ValCheck((c1 / c3).GetImaginary(), 7.0, __LINE__);

    return result;
}

int TestEquals(void)
{
    int result = 0;
    Complex c1(3.5, 1.5);
    Complex c2(c1);
    Complex c3(1.5, 3.5);

    std::cout << "--------- Testing == ---------" << std::endl;

    result += ValCheck((c1 == c2), true, __LINE__);
    result += ValCheck((c1 == c3), false, __LINE__);

    return result;
}

int TestNotEquals(void)
{
    int result = 0;
    Complex c1(3.5, 1.5);
    Complex c2(c1);
    Complex c3(1.5, 3.5);

    std::cout << "--------- Testing != ---------" << std::endl;

    result += ValCheck((c1 != c2), false, __LINE__);
    result += ValCheck((c1 != c3), true, __LINE__);

    return result;
}

int TestCinCout(void)
{
    int result = 0;
    Complex c1(3.5, 1.5);
    Complex c2(c1);
    Complex c3(1.5, 3.5);

    std::cout << "--------- Testing Cin + Cout ---------" << std::endl;

    std::cout << c1 << std::endl;
    std::cout << c2 << std::endl;
    std::cout << c3 << std::endl;

    std::cin >> c2;
    std::cout << c2 << std::endl;

    return result;
}

int ValCheck(int recieved_val, int expected_val, int line)
{
    if (recieved_val != expected_val)
    {
        printf("----------------FAIL line %d----------------\n", line);
        printf("got %d, when wanted %d\n", recieved_val, expected_val);

        ++total_fails;

        return 1;
    }

    return 0;
}

void BenchMarkTest(void)
{
    Complex c1(1, 1);
    Complex c2(1, 1);
    clock_t now = clock();

    std::cout << "--------- STARTING BENCHMARKING 100K TEST ---------" << std::endl;

    for (int i = 0; i < 100000; ++i)
    {
        c1 + c2;
    }

    std::cout << "Duration: " << clock() - now << std::endl;
}