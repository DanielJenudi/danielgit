/* class Point
{
public:
    Point(int x = 0, int y = 0);

private:
    int m_x;
    int m_y;
};

Point::Point(int x, int y) : m_x(0), m_y(0)
{
}

class A
{
};

class B
{
private:
    int x;
    int y;
    Point p;
};
 */

#include <stdlib.h>

typedef void (*setfunc_t)(int src, int *dest);
typedef void (*blafunc_t)();

typedef struct Point
{
    int m_x;
    int m_y;
} point_t;

typedef struct A
{
    char a;
} a_t;

typedef struct B
{
    point_t point;
    int x;
    int y;
    setfunc_t set_x;
    setfunc_t set_y;
    blafunc_t bla;
} b_t;

/***** Decleration *****/
void SetX(int inX, int *x);
void SetY(int inY, int *y);
void Bla();

/***** struct Point *****/
void CtorPoint(point_t *point)
{
    point->m_x = 0;
    point->m_y = 0;
}

void DtorPoint(point_t *point)
{
    (void)point;
}

/***** struct A *****/
void CtorA(a_t *a)
{
    (void)a;
}

void DtorA(a_t *a)
{
    (void)a;
}

/***** struct B *****/
void CtorB(b_t *b)
{
    CtorPoint(&b->point);
    b->set_x = &SetX;
    b->set_y = &SetY;
    b->bla = &Bla;
}

void CopyB(b_t *b_dest, b_t *b_src)
{
    b_dest->point = b_src->point;
    b_dest->x = b_src->x;
    b_dest->y = b_src->y;
}

void DtorB(b_t *b)
{
    DtorPoint(&b->point);
}

void SetX(int inX, int *x)
{
    *x = inX;
}

void SetY(int inY, int *y)
{
    *y = inY;
}

/***** Foo *****/
void Foo()
{
    b_t arr1[100];
    b_t *arr2 = malloc(sizeof(b_t) * 100);
    size_t i = 0;

    for (i = 0; i < 100; i++)
    {
        CtorB(&arr1[i]);
    }

    for (i = 0; i < 100; i++)
    {
        CtorB(&arr2[i]);
    }

    for (i = 0; i < 100; i++)
    {
        DtorB(&arr2[i]);
    }
    free(arr2);

    for (i = 0; i < 100; i++)
    {
        DtorB(&arr1[i]);
    }
}

b_t Bar(b_t b1, b_t *b2, const b_t *b3)
{
    (void)b1;
    (void)b2;
    (void)b3;

    return b1;
}

void Bla()
{
}

int main()
{
    a_t a;
    b_t b;
    b_t b2;
    b_t *p = NULL;

    /* A a; */
    CtorA(&a);

    /* B b; */
    CtorB(&b);

    /* B b2(b); */
    CtorB(&b2);
    CopyB(&b2, &b);

    /* b2 = b; */
    CopyB(&b2, &b);

    (*b.set_x)(5, &b.x);
    (*b.set_y)(6, &b.y);

    p = (b_t *)malloc(sizeof(b_t));
    CtorB(p);

    p->set_x(5, &p->x);
    p->set_y(6, &p->y);

    DtorB(p);
    free(p);

    Foo();
    Bar(b, &b, &b);

    Bla();
    b.bla();

    DtorA(&a);
    DtorB(&b);
    DtorB(&b2);

    return 0;
}