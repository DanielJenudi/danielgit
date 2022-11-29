#include <iostream> /* i/o operations */
#include <cstdio>   /* oldstyle macro i/o use */
#include <cstring>

#include "rcstring.hpp"

using namespace ilrd;

static void RunTest(bool test);
static bool Size_tCmp(int s1, int s2);

static void Test1();
static void Test2();

int main()
{
    printf("Test1:\n");
    Test1();
    printf("Test2:\n");
    Test2();

    return 0;
}

static void Test1()
{
    RCString s1("hello");
    RCString s2(s1);
    RCString s3;

    printf("test ==:\n");
    RunTest(s1 == s2);

    printf("test !=:\n");
    RunTest(s1 != s3);

    printf("test []:\n");
    s1[1] = 'f';
    RunTest(s1 != s2);

    printf("test [] - s1:\n");
    RunTest(s1 == "hfllo");

    printf("test [] - s2:\n");
    RunTest(s2 == "hello");

    s3 = s1;
    printf("test ==:\n");
    RunTest(s3 == s1);

    printf("test !=:\n");
    RunTest(s1 != s2);

    const char *s1_ptr = s1.RCstr();

    printf("test Length() s1:\n");
    RunTest(Size_tCmp(s1.Length(), strlen(s1_ptr)));

    s2 = "blalalalab";
    const char *s2_ptr = s2.RCstr();

    printf("test Length() s2:\n");
    RunTest(Size_tCmp(s2.Length(), strlen(s2_ptr)));
}

static void Test2()
{
    const RCString s1("hello");
    RCString s2(s1);
    RCString s3("world");

    char c = s1[0];

    printf("test const []:\n");
    RunTest('h' == c);

    printf("test std <<:\n");
    std::cout << s1 << " " << s3 << std::endl;

    printf("\ntest std >>:\n");
    std::cout << "enter: " << std::endl;
    std::cin >> s3;
    std::cout << "result: " << s3 << std::endl;
}

static void RunTest(bool test)
{
    if (test)
    {
        printf("\x1b[0;32m");
        printf("OK!\n\n");
        printf("\x1b[0m");
    }
    else
    {
        printf("\x1b[1;31m");
        printf("\nTest Failed!\n\n");
        printf("\x1b[0m");
    }
}

static bool Size_tCmp(int s1, int s2)
{
    return (s1 == s2);
}