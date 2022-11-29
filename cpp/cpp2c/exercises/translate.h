#ifndef __ILRD_CPP2C_H__
#define __ILRD_CPP2C_H__

#define TEMPLATEMAX(T)        \
    T MAX##T(T a, T b)        \
    {                         \
        return a > b ? a : b; \
    }

typedef struct PublicTransport pub_trans_t;
typedef struct Minibus minibus_t;
typedef struct Taxi taxi_t;
typedef struct Special_Taxi spec_taxi_t;
typedef struct PublicConvoy pub_conv_t;

void Ctor_PublicTransport(pub_trans_t *pub_trans);
void CCtor_PublicTransport(pub_trans_t *pub_trans, const pub_trans_t *other);

void Ctor_Minibus(minibus_t *minibus);
void CCtor_Minibus(minibus_t *minibus, const minibus_t *other);

void Ctor_Taxi(taxi_t *taxi);
void CCtor_Taxi(taxi_t *taxi, const taxi_t *other);

void Ctor_Spec_Taxi(spec_taxi_t *this);
void CCtor_Spec_Taxi(spec_taxi_t *this, const spec_taxi_t *other);

void Ctor_PublicConvoy(pub_conv_t *this);
void CCtor_PublicConvoy(pub_conv_t *this, const pub_conv_t *other);

#endif /* __ILRD_CPP2C_H__ */