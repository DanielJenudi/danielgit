#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* printf */

#include "translate.h"

TEMPLATEMAX(int)
TEMPLATEMAX(float)

/* virtual fancs typedef */
typedef void (*dtor_func_t)(void *type);
typedef void (*display_func_t)(void *type);
typedef void (*wash_func_t)(void *type, int minutes);

/* vt structs */
typedef struct VT_PublicTransport
{
    dtor_func_t dtor;
    display_func_t display;
} vt_pub_trans_t;

typedef struct VT_Minibus
{
    vt_pub_trans_t vt_pub_trans;
    wash_func_t wash;
} vt_minibus_t;

typedef struct VT_Taxi
{
    vt_pub_trans_t vt_pub_trans;
} vt_taxi_t;

typedef struct VT_Special_Taxi
{
    vt_taxi_t vt_taxi;
} vt_spec_taxi_t;

typedef struct VT_PublicConvoy
{
    vt_pub_trans_t vt_pub_trans;
} vt_pub_conv_t;

/* structs */
struct PublicTransport
{
    void *vt_ptr;

    int m_license_plate;
};

struct Minibus
{
    pub_trans_t base_pub_trans;

    int m_num_seats;
};

struct Taxi
{
    pub_trans_t base_pub_trans;
};

struct Special_Taxi
{
    taxi_t base_taxi;
};

struct PublicConvoy
{
    pub_trans_t base_pub_trans;

    pub_trans_t *p1;
    pub_trans_t *p2;
    minibus_t m_m;
    taxi_t m_t;
};

/* PublicTransport declerations */
/* methods */
static void PrintCount(void);
static int GetID(pub_trans_t *pub_trans);
/* virtual */
static void Dtor_PublicTransport(void *type);
static void Display_PublicTransport(void *type);
/* help funcs */
static pub_trans_t *Init_VT_PublicTransport(pub_trans_t *this);

/* Minibus declerations */
/* virtual */
static void DtorMinibus(void *type);
static void Display_Minibus(void *type);
static void Wash_Minibus(void *type, int minutes);
/* help funcs */
static minibus_t *Init_VT_Minibus();

/* Taxi declerations */
/* virtual */
static void DtorTaxi(void *type);
static void Display_Taxi(void *type);
/* help funcs */
static taxi_t *Init_VT_Taxi(taxi_t *this);

/* special Taxi declerations */
/* virtual */
static void DtorSpec_Taxi(void *type);
static void Display_Spec_Taxi(void *type);
/* help funcs */
static spec_taxi_t *Init_VT_Spec_Taxi(spec_taxi_t *this);

/* PublicConvoy declerations */
/* virtual */
static void DtorPublicConvoy(void *type);
static void Display_PublicConvoy(void *type);
/* help funcs */
static pub_conv_t *Init_VT_PublicConvoy(pub_conv_t *this);

/* user functions declerations */
void Print_Info_PT_Display(pub_trans_t *pub_trans);
void Print_Info_PT_Print_Count();
void Print_Info_Minibus_Wash(minibus_t minibus);
pub_trans_t Print_Info_Ret_PT(int i);
void Taxi_Display(taxi_t taxi);

/***** global virtual tables *****/

vt_pub_trans_t g_vt_pub_trans =
    {&Dtor_PublicTransport, &Display_PublicTransport};
vt_minibus_t g_vt_minibus =
    {{&DtorMinibus, &Display_Minibus}, &Wash_Minibus};
vt_taxi_t g_vt_taxi =
    {{&DtorTaxi, &Display_Taxi}};
vt_spec_taxi_t g_vt_spec_taxi =
    {{{&DtorSpec_Taxi, &Display_Spec_Taxi}}};
vt_pub_conv_t g_vt_pub_conv =
    {{&DtorPublicConvoy, &Display_PublicConvoy}};

/***** PublicTransport *****/

/* PublicTransport global static */
static int s_pub_trans_count_g = 0;

void Ctor_PublicTransport(pub_trans_t *this)
{
    Init_VT_PublicTransport(this);
    printf("PublicTransport::Ctor(), m_license_plate: %d\n",
           this->m_license_plate);
}

void CCtor_PublicTransport(pub_trans_t *this, const pub_trans_t *other)
{
    Init_VT_PublicTransport(this);
    printf("PublicTransport::CCtor(), m_license_plate: %d\n",
           this->m_license_plate);

    (void)other;
}

static pub_trans_t *Init_VT_PublicTransport(pub_trans_t *this)
{
    this->vt_ptr = &g_vt_pub_trans;

    this->m_license_plate = ++s_pub_trans_count_g;

    return this;
}

static void Dtor_PublicTransport(void *type)
{
    pub_trans_t *pub_trans = (pub_trans_t *)type;

    --s_pub_trans_count_g;

    printf("PublicTransport::Dtor(), m_license_plate: %d\n",
           pub_trans->m_license_plate);
}

static void Display_PublicTransport(void *type)
{
    pub_trans_t *pub_trans = (pub_trans_t *)type;
    printf("PublicTransport::Display(), m_license_plate: %d\n",
           pub_trans->m_license_plate);
}

static void PrintCount(void)
{
    printf("s_pub_trans_count_g: %d\n", s_pub_trans_count_g);
}

static int GetID(pub_trans_t *pub_trans)
{
    return pub_trans->m_license_plate;
}

/***** Minibus *****/

void Ctor_Minibus(minibus_t *this)
{
    Ctor_PublicTransport(&this->base_pub_trans);
    Init_VT_Minibus(this);
    printf("Minibus::Ctor()\n");

    this->m_num_seats = 20;
}

void CCtor_Minibus(minibus_t *this, const minibus_t *other)
{
    CCtor_PublicTransport(&this->base_pub_trans, &other->base_pub_trans);
    Init_VT_Minibus(this);

    this->m_num_seats = other->m_num_seats;

    printf("Minibus::CCtor()\n");
}

static minibus_t *Init_VT_Minibus(minibus_t *this)
{
    this->base_pub_trans.vt_ptr = &g_vt_minibus;

    return this;
}

static void DtorMinibus(void *type)
{
    minibus_t *minibus = (minibus_t *)type;

    printf("Minibus::Dtor()\n");

    Dtor_PublicTransport(&minibus->base_pub_trans);
}

static void Display_Minibus(void *type)
{
    minibus_t *minibus = (minibus_t *)type;

    printf("Minibus::display() ID: %d", GetID(&minibus->base_pub_trans));

    printf(" num seats: %d\n", minibus->m_num_seats);
}

static void Wash_Minibus(void *type, int minutes)
{
    minibus_t *minibus = (minibus_t *)type;
    printf("Minibus::wash(%d) ID: %d\n", minutes, GetID(&minibus->base_pub_trans));
}

/***** Taxi *****/

void Ctor_Taxi(taxi_t *this)
{
    Ctor_PublicTransport(&this->base_pub_trans);
    Init_VT_Taxi(this);
    printf("Taxi::Ctor()\n");
}

void CCtor_Taxi(taxi_t *this, const taxi_t *other)
{
    CCtor_PublicTransport(&this->base_pub_trans, &other->base_pub_trans);
    Init_VT_Taxi(this);
    printf("Taxi::CCtor()\n");
}

static taxi_t *Init_VT_Taxi(taxi_t *this)
{
    this->base_pub_trans.vt_ptr = &g_vt_taxi;

    return this;
}

static void DtorTaxi(void *type)
{
    taxi_t *taxi = (taxi_t *)type;

    printf("Taxi::Dtor()\n");

    Dtor_PublicTransport(&taxi->base_pub_trans);
}

static void Display_Taxi(void *type)
{
    taxi_t *taxi = (taxi_t *)type;

    printf("Taxi::display() ID: %d\n", GetID(&taxi->base_pub_trans));
}

/***** Special Taxi *****/

void Ctor_Spec_Taxi(spec_taxi_t *this)
{
    Ctor_Taxi(&this->base_taxi);
    Init_VT_Spec_Taxi(this);
    printf("SpecialTaxi::Ctor()\n");
}

void CCtor_Spec_Taxi(spec_taxi_t *this, const spec_taxi_t *other)
{
    CCtor_Taxi(&this->base_taxi, &other->base_taxi);
    Init_VT_Spec_Taxi(this);
    printf("SpecialTaxi::CCtor()\n");
}

static spec_taxi_t *Init_VT_Spec_Taxi(spec_taxi_t *this)
{
    this->base_taxi.base_pub_trans.vt_ptr = &g_vt_spec_taxi;

    return this;
}

static void DtorSpec_Taxi(void *type)
{
    spec_taxi_t *spec_taxi = (spec_taxi_t *)type;

    printf("SpecialTaxi::Dtor()\n");

    DtorTaxi(&spec_taxi->base_taxi);
}

static void Display_Spec_Taxi(void *type)
{
    spec_taxi_t *spec_taxi = (spec_taxi_t *)type;

    printf("SpecialTaxi::display() ID: %d\n",
           GetID(&spec_taxi->base_taxi.base_pub_trans));
}

/***** PublicConvoy *****/

void Ctor_PublicConvoy(pub_conv_t *this)
{
    Ctor_PublicTransport(&this->base_pub_trans);
    Init_VT_PublicConvoy(this);

    this->p1 = (pub_trans_t *)malloc(sizeof(minibus_t));
    Ctor_Minibus(((minibus_t *)this->p1));

    this->p2 = (pub_trans_t *)malloc(sizeof(taxi_t));
    Ctor_Taxi(((taxi_t *)this->p2));

    Ctor_Minibus(&this->m_m);
    Ctor_Taxi(&this->m_t);

    printf("PublicConvoy::Ctor()\n");
}

void CCtor_PublicConvoy(pub_conv_t *this, const pub_conv_t *other)
{
    CCtor_PublicTransport(&this->base_pub_trans, &other->base_pub_trans);
    Init_VT_PublicConvoy(this);

    this->p1 = malloc(sizeof(minibus_t));
    CCtor_Minibus(((minibus_t *)this->p1), (minibus_t *)other->p1);

    this->p2 = malloc(sizeof(taxi_t));
    CCtor_Taxi((taxi_t *)this->p2, (taxi_t *)other->p2);

    CCtor_Minibus(&this->m_m, &other->m_m);
    CCtor_Taxi(&this->m_t, &other->m_t);

    printf("PublicConvoy::CCtor()\n");
}

static pub_conv_t *Init_VT_PublicConvoy(pub_conv_t *this)
{
    this->base_pub_trans.vt_ptr = &g_vt_pub_conv;

    return this;
}

static void DtorPublicConvoy(void *type)
{
    pub_conv_t *pub_conv = (pub_conv_t *)type;

    printf("PublicConvoy::Dtor()\n");

    DtorMinibus((minibus_t *)pub_conv->p1);
    free(pub_conv->p1);

    DtorTaxi((taxi_t *)pub_conv->p2);
    free(pub_conv->p2);

    DtorTaxi(&pub_conv->m_t);

    DtorMinibus(&pub_conv->m_m);

    Dtor_PublicTransport(&pub_conv->base_pub_trans);
}

static void Display_PublicConvoy(void *type)
{
    pub_conv_t *pub_conv = (pub_conv_t *)type;

    printf("PublicConvoy::display()\n");

    ((vt_pub_trans_t *)(pub_conv->p1->vt_ptr))->display(pub_conv->p1);
    ((vt_pub_trans_t *)(pub_conv->p2->vt_ptr))->display(pub_conv->p2);
    Display_Minibus(&pub_conv->m_m);
    Display_Taxi(&pub_conv->m_t);
}

/***** user function *****/

void Print_Info_PT_Display(pub_trans_t *pub_trans)
{
    ((vt_pub_trans_t *)(pub_trans->vt_ptr))->display(pub_trans);
}

void Print_Info_PT_Print_Count()
{
    PrintCount();
}

void Print_Info_Minibus_Wash(minibus_t minibus)
{
    ((vt_minibus_t *)(minibus.base_pub_trans.vt_ptr))->wash(&minibus, 3);
}

pub_trans_t Print_Info_Ret_PT(int i)
{
    minibus_t minibus;
    pub_trans_t ret_val;
    Ctor_Minibus(&minibus);
    printf("print_info(int i = %d\n)", i);
    ((vt_minibus_t *)(minibus.base_pub_trans.vt_ptr))->vt_pub_trans.display(&minibus);

    CCtor_PublicTransport(&ret_val, &minibus.base_pub_trans);

    ((vt_minibus_t *)(minibus.base_pub_trans.vt_ptr))->vt_pub_trans.dtor(&minibus);
    return ret_val;
}

void Taxi_Display(taxi_t taxi)
{
    ((vt_taxi_t *)(taxi.base_pub_trans.vt_ptr))->vt_pub_trans.display(&taxi);
}

int main()
{
    size_t i = 0;

    minibus_t m;
    pub_trans_t ret_val;

    pub_trans_t *arr1[3] = {0};
    minibus_t *arr1_mini1 = (minibus_t *)malloc(sizeof(minibus_t));
    taxi_t *arr1_taxi2 = (taxi_t *)malloc(sizeof(taxi_t));
    minibus_t *arr1_mini3 = (minibus_t *)malloc(sizeof(minibus_t));

    pub_trans_t arr2[3] = {0};
    minibus_t arr2_minibus1;
    taxi_t arr2_taxi2;

    minibus_t m2;

    minibus_t arr3[4];
    taxi_t *arr4 = (taxi_t *)malloc(sizeof(taxi_t) * 4);

    spec_taxi_t st;
    taxi_t temp_taxi;

    pub_conv_t *pc1;
    pub_conv_t *pc2;

    /* print_info(m); */
    Ctor_Minibus(&m);
    Print_Info_Minibus_Wash(m);

    /* print_info(3).display(); */
    ret_val = Print_Info_Ret_PT(3);
    ((vt_pub_trans_t *)(ret_val.vt_ptr))->display(&ret_val);
    ((vt_pub_trans_t *)(ret_val.vt_ptr))->dtor(&ret_val);

    Ctor_Minibus(arr1_mini1);
    Ctor_Taxi(arr1_taxi2);
    Ctor_Minibus(arr1_mini3);

    arr1[0] = &arr1_mini1->base_pub_trans;
    arr1[1] = &arr1_taxi2->base_pub_trans;
    arr1[2] = &arr1_mini3->base_pub_trans;

    for (i = 0; i < 3; ++i)
    {
        ((vt_pub_trans_t *)(arr1[i]->vt_ptr))->display(arr1[i]);
    }

    for (i = 0; i < 3; ++i)
    {
        ((vt_pub_trans_t *)(arr1[i]->vt_ptr))->dtor(arr1[i]);
        free(arr1[i]);
        arr1[i] = NULL;
    }

    Ctor_Minibus(&arr2_minibus1);
    CCtor_PublicTransport(&arr2[0], &arr2_minibus1.base_pub_trans);
    ((vt_minibus_t *)(arr2_minibus1.base_pub_trans.vt_ptr))->vt_pub_trans.dtor(&arr2_minibus1);

    Ctor_Taxi(&arr2_taxi2);
    CCtor_PublicTransport(&arr2[1], &arr2_taxi2.base_pub_trans);
    ((vt_taxi_t *)(arr2_taxi2.base_pub_trans.vt_ptr))->vt_pub_trans.dtor(&arr2_taxi2);

    Ctor_PublicTransport(&arr2[2]);

    for (i = 0; i < 3; ++i)
    {
        ((vt_pub_trans_t *)(arr2[i].vt_ptr))->display(&arr2[i]);
    }

    /* print_info(arr2[0]); */
    Print_Info_PT_Display(&arr2[0]);

    PrintCount();
    Ctor_Minibus(&m2);
    PrintCount();

    for (i = 0; i < 4; ++i)
    {
        Ctor_Minibus(&arr3[i]);
    }

    for (i = 0; i < 4; ++i)
    {
        Ctor_Taxi(&arr4[i]);
    }

    for (i = 4; i > 0; --i)
    {
        ((vt_taxi_t *)(arr4[i - 1].base_pub_trans.vt_ptr))->vt_pub_trans.dtor(&arr4[i - 1]);
    }
    free(arr4);
    arr4 = NULL;

    printf("%d\n", MAXint(1, 2));
    printf("%d\n", (int)MAXfloat(1, 2.0));

    Ctor_Spec_Taxi(&st);
    CCtor_Taxi(&temp_taxi, &st.base_taxi);
    Taxi_Display(temp_taxi);
    ((vt_taxi_t *)(temp_taxi.base_pub_trans.vt_ptr))
        ->vt_pub_trans.dtor(&temp_taxi);

    /* Phase2 */

    pc1 = malloc(sizeof(pub_conv_t));
    Ctor_PublicConvoy(pc1);

    pc2 = malloc(sizeof(pub_conv_t));
    CCtor_PublicConvoy(pc2, pc1);

    ((vt_pub_conv_t *)(pc1->base_pub_trans.vt_ptr))->vt_pub_trans.display(pc1);
    ((vt_pub_conv_t *)(pc2->base_pub_trans.vt_ptr))->vt_pub_trans.display(pc2);

    ((vt_pub_conv_t *)(pc1->base_pub_trans.vt_ptr))->vt_pub_trans.dtor(pc1);
    free(pc1);
    pc1 = NULL;

    ((vt_pub_conv_t *)(pc2->base_pub_trans.vt_ptr))->vt_pub_trans.display(pc2);

    ((vt_pub_conv_t *)(pc2->base_pub_trans.vt_ptr))->vt_pub_trans.dtor(pc2);
    free(pc2);
    pc2 = NULL;

    /* ~~~~~ Start Dtors ~~~~~*/

    ((vt_spec_taxi_t *)(st.base_taxi.base_pub_trans.vt_ptr))->vt_taxi.vt_pub_trans.dtor(&st);

    for (i = 4; i > 0; --i)
    {
        ((vt_minibus_t *)(arr3[i - 1].base_pub_trans.vt_ptr))->vt_pub_trans.dtor(&arr3[i - 1]);
    }

    ((vt_minibus_t *)(m2.base_pub_trans.vt_ptr))->vt_pub_trans.dtor(&m2);

    for (i = 3; i > 0; --i)
    {
        ((vt_pub_trans_t *)(arr2[i - 1].vt_ptr))->dtor(&arr2[i - 1]);
    }

    ((vt_minibus_t *)(m.base_pub_trans.vt_ptr))->vt_pub_trans.dtor(&m);

    return 0;
}