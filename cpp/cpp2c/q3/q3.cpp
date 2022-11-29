union A
{
public:
    int a;
};

union B : public A
{
public:
    int b;
};

int main()
{
    B x;

    x.a;

    return 0;
}