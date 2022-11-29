enum E
{
    AA,
    BB,
    CC,
    DD
};
enum E2
{
    TT,
    KK
};

int main()
{
    int i = 0;
    enum E e = 2;
    enum E2 e2 = AA;
    ++e;
    i = e;

    return 0;
}