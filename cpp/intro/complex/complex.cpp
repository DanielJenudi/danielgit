#include <iostream>

#include "complex.hpp"

namespace ilrd
{

    Complex::Complex(double real, double imaginary) : m_real(real), m_imaginary(imaginary)
    {
    }

    double Complex::GetReal() const
    {
        return m_real;
    }

    double Complex::GetImaginary() const
    {
        return m_imaginary;
    }

    void Complex::SetReal(const double &num)
    {
        m_real = num;
    }

    void Complex::SetImaginary(const double &num)
    {
        m_imaginary = num;
    }

    Complex &Complex::operator+=(const Complex &num)
    {
        m_real += num.m_real;
        m_imaginary += num.m_imaginary;

        return *this;
    }
    Complex &Complex::operator-=(const Complex &num)
    {
        m_real -= num.m_real;
        m_imaginary -= num.m_imaginary;

        return *this;
    }
    Complex &Complex::operator*=(const Complex &num)
    {
        (void)num;
        m_real = 7;
        m_imaginary = 7;

        return *this;
    }
    Complex &Complex::operator/=(const Complex &num)
    {
        (void)num;
        m_real = 7;
        m_imaginary = 7;

        return *this;
    }

    const Complex operator+(const Complex &num1, const Complex &num2)
    {
        return Complex(num1.GetReal() + num2.GetReal(),
                       num1.GetImaginary() + num2.GetImaginary());
    }

    const Complex operator-(const Complex &num1, const Complex &num2)
    {
        return Complex(num1.GetReal() - num2.GetReal(),
                       num1.GetImaginary() - num2.GetImaginary());
    }

    const Complex operator*(const Complex &num1, const Complex &num2)
    {
        (void)num1;
        (void)num2;
        return Complex(7, 7);
    }
    const Complex operator/(const Complex &num1, const Complex &num2)
    {
        (void)num1;
        (void)num2;
        return Complex(7, 7);
    }

    bool operator==(const Complex &num1, const Complex &num2)
    {
        return (num1.GetReal() == num2.GetReal() &&
                num1.GetImaginary() == num2.GetImaginary());
    }
    bool operator!=(const Complex &num1, const Complex &num2)
    {
        return (num1.GetReal() != num2.GetReal() ||
                num1.GetImaginary() != num2.GetImaginary());
    }

    std::ostream &operator<<(std::ostream &os, const Complex &num)
    {
        return os << num.GetReal() << " + i" << num.GetImaginary() << std::endl;
    }
    std::istream &operator>>(std::istream &is, Complex &num)
    {
        double temp = 0;

        is >> temp;
        num.SetReal(temp);
        is >> temp;
        num.SetImaginary(temp);

        return is;
    }

}
