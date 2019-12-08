//
// Created by Hugo JEANNIN on 12/2/19.
//

#include "../inc/Complex.hpp"

Complex::Complex()
{
    this->setType(COMPLEX);
    this->real_part_ = 0.0;
    this->imaginary_part_ = 0.0;
}

Complex::~Complex()
{}

Complex::Complex(double imaginary_part)
{
    this->setType(COMPLEX);
    this->real_part_ = 0.0;
    this->imaginary_part_ = imaginary_part;
}

Complex::Complex(double real_part, double imaginary_part)
{
    this->setType(COMPLEX);
    this->real_part_ = real_part;
    this->imaginary_part_ = imaginary_part;
}

Complex::Complex(Complex &cmp)
{
    this->setType(COMPLEX);
    this->real_part_ = cmp.getRealPart();
    this->imaginary_part_ = cmp.getImaginaryPart();
}

Complex::Complex(const Operand *op)
{
    if (op->getType() == COMPLEX)
    {
        this->real_part_ = dynamic_cast<Complex const *>(op)->real_part_;
        this->imaginary_part_ = dynamic_cast<Complex const *>(op)->imaginary_part_;
    }
    else
    {
        throw std::invalid_argument("in 'Complex::Complex(const Operand *op)' op is not Complex");
    }

}

void Complex::setRealPart(double n)
{
    this->real_part_ = n;
}

double Complex::getRealPart() const
{
    return this->real_part_;
}

void Complex::setImaginaryPart(double n)
{
    this->imaginary_part_ = n;
}

double Complex::getImaginaryPart() const
{
    return this->imaginary_part_;
}

Operand *Complex::operator=(Operand const &rhs)
{
    if (this != &rhs)
    {
        if (rhs.getType() == COMPLEX)
        {
            real_part_ = dynamic_cast<const Complex *>(&rhs)->getRealPart();
            imaginary_part_ = dynamic_cast<const Complex *>(&rhs)->getImaginaryPart();
        }
        else
        {
            throw std::invalid_argument("in 'Operand *Rational::operator=(Operand const &rhs)' rhs is not Invalid.");
        }
    }
    return (dynamic_cast<Operand *>(this));
}

Operand *Complex::operator+(Operand const &rhs)
{
    if (rhs.getType() == COMPLEX)
    {
        double a;
        double b;
        Operand *tmp;

        a = this->getRealPart() + dynamic_cast<const Complex *>(&rhs)->getRealPart();
        b = this->getImaginaryPart() + dynamic_cast<const Complex *>(&rhs)->getImaginaryPart();

        if (b == 0.0)
            tmp = new Rational(a);
        else
            tmp = new Complex(a, b);
        return (tmp);
    }
    else if (rhs.getType() == RATIONAL)
    {
        Complex *tmp = new Complex(this->getRealPart() + dynamic_cast<const Rational *>(&rhs)->getValue(),
                                   this->getImaginaryPart());
        return (dynamic_cast<Operand *>(tmp));
    }
    else
    {
        throw std::invalid_argument(
                "in 'Operand *Complex::operator+(Operand const &rhs)' rhs is not Complex or inferior.");
    }
}

Operand *Complex::operator-(Operand const &rhs)
{
    if (rhs.getType() == COMPLEX)
    {
        Complex *tmp = new Complex(this->getRealPart() - dynamic_cast<const Complex *>(&rhs)->getRealPart(),
                                   this->getImaginaryPart() - dynamic_cast<const Complex *>(&rhs)->getImaginaryPart());
        return (dynamic_cast<Operand *>(tmp));
    }
    else if (rhs.getType() == RATIONAL)
    {
        Complex *tmp = new Complex(this->getRealPart() - dynamic_cast<const Rational *>(&rhs)->getValue(),
                                   this->getImaginaryPart());
        return (dynamic_cast<Operand *>(tmp));
    }
    else
    {
        throw std::invalid_argument(
                "in 'Operand *Complex::operator-(Operand const &rhs)' rhs is not Complex or inferior.");
    }
}

Operand *Complex::operator*(Operand const &rhs)
{
    if (rhs.getType() == COMPLEX)
    {
        Complex *tmp;
        tmp = solveMul(this->getRealPart(),
                       this->getImaginaryPart(),
                       dynamic_cast<const Complex *>(&rhs)->getRealPart(),
                       dynamic_cast<const Complex *>(&rhs)->getImaginaryPart());
        return (dynamic_cast<Operand *>(tmp));
    }
    else if (rhs.getType() == RATIONAL)
    {
        Complex *tmp = new Complex(this->getRealPart() * dynamic_cast<const Rational *>(&rhs)->getValue(),
                                   this->getImaginaryPart() * dynamic_cast<const Rational *>(&rhs)->getValue());
        return (dynamic_cast<Operand *>(tmp));
    }
    else
    {
        throw std::invalid_argument(
                "in 'Operand *Complex::operator*(Operand const &rhs)' rhs is not Complex or inferior.");
    }
}

Operand *Complex::operator/(Operand const &rhs)
{
    if (rhs.getType() == COMPLEX)
    {
        Complex *tmp;
        tmp = solveDiv(this->getRealPart(),
                       this->getImaginaryPart(),
                       dynamic_cast<const Complex *>(&rhs)->getRealPart(),
                       dynamic_cast<const Complex *>(&rhs)->getImaginaryPart());
        return (dynamic_cast<Operand *>(tmp));
    }
    else if (rhs.getType() == RATIONAL)
    {
        Complex *tmp;
        tmp = solveDiv(this->getRealPart(),
                       this->getImaginaryPart(),
                       dynamic_cast<const Rational *>(&rhs)->getValue(),
                       0.0);
        return (dynamic_cast<Operand *>(tmp));
    }
    else
    {
        throw std::invalid_argument(
                "in 'Operand *Complex::operator*(Operand const &rhs)' rhs is not Complex or inferior.");
    }
}

Operand *Complex::operator%(Operand const &rhs)
{
    throw std::invalid_argument("in 'Operand *Complex::operator%(Operand const &rhs)' cannot % with Complex.");
}


Complex *Complex::solveMul(double a, double b, double c, double d)
{
    Complex *tmp = new Complex(
            a * c - b * d, a * d + b * c
    );
    return tmp;
}

Complex *Complex::solveDiv(double a, double b, double c, double d)
{
    Complex *tmp = new Complex(
            ((a * c + b * d) / (c * c + d * d)),
            ((b * c - a * d) / (c * c + d * d))
    );
    return tmp;
}

std::ostream &Complex::print(std::ostream &o, Operand const &i)
{
    o << "[COMPLEX | " << dynamic_cast<const Complex *>(&i)->getRealPart() << " + "
      << dynamic_cast<const Complex *>(&i)->getImaginaryPart() << "i | " << i.getSelf() << "]";
    return (o);
}

std::ostream &operator<<(std::ostream &o, Complex const &i)
{
    Complex::print(o, i);
    return (o);
}
