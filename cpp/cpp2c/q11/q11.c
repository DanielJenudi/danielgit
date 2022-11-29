/* class Base
{
public:
    Base(int inX, int inY);

private:
    int x;
    int y;
};
Base::Base(int inX, int inY) : x(inX), y(inY)
{
}

class Derived : public Base
{
public:
    Derived(int inX, int inY, int inZ);

private:
    int z;
};
Derived::Derived(int inX, int inY, int inZ) : Base(inX, inY), z(inZ)
{
} */

typedef void (*foo_t)();
typedef void (*dtor_t)(void *s_type);

typedef struct VT
{
    dtor_t dtor;
    foo_t foo;
} vt_t;

typedef struct Base
{
    vt_t vt;
    int x;
    int y;

} base_t;

typedef struct Derived
{
    base_t base;
    int z;
} derived_t;

void CtorBase(base_t *base, int inx, int iny);
void DtorBase(void *base);
void CtorDerived(derived_t *derived, int inx, int iny, int inz);
void DtorDerived(void *derived);
void Foo();

void CtorBase(base_t *base, int inx, int iny)
{
    base->vt.dtor = &DtorBase;
    base->vt.foo = &Foo;
    base->x = inx;
    base->y = iny;
}

void DtorBase(void *base)
{
    (void)(base_t *)base;
}

void CtorDerived(derived_t *derived, int inx, int iny, int inz)
{
    CtorBase(&derived->base, inx, iny);
    derived->base.vt.dtor = &DtorDerived;
    derived->z = inz;
}

void DtorDerived(void *derived)
{
    DtorBase(&((derived_t *)derived)->base);
}

void Foo()
{
}

int main()
{
    base_t b;
    derived_t d;

    CtorBase(&b, 5, 6);
    CtorDerived(&d, 5, 6, 7);

    DtorBase(&b);
    DtorDerived(&d);

    return 0;
}
