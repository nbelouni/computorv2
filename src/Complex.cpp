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
    this->real_part_ = cmp.getRationalPart();
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

void Complex::setRationalPart(double n)
{
    this->real_part_ = n;
}

double Complex::getRationalPart() const
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
            real_part_ = dynamic_cast<const Complex *>(&rhs)->getRationalPart();
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
    Complex *tmp;

    if (rhs.getType() == COMPLEX)
    {
        tmp = new Complex(
                this->getRationalPart() + dynamic_cast<const Complex *>(&rhs)->getRationalPart(),
                this->getImaginaryPart() + dynamic_cast<const Complex *>(&rhs)->getImaginaryPart()
        );
    }
    else if (rhs.getType() == RATIONAL)
    {
        tmp = new Complex(
                this->getRationalPart() + dynamic_cast<const Rational *>(&rhs)->getValue(),
                this->getImaginaryPart()
        );
    }
    else
    {
        throw std::invalid_argument(
                "in 'Operand *Complex::operator+(Operand const &rhs)' rhs is not Complex or inferior.");
    }
    return endCheck(tmp);
}

Operand *Complex::operator-(Operand const &rhs)
{
    Complex *tmp;

    if (rhs.getType() == COMPLEX)
    {
        tmp = new Complex(
                this->getRationalPart() - dynamic_cast<const Complex *>(&rhs)->getRationalPart(),
                this->getImaginaryPart() - dynamic_cast<const Complex *>(&rhs)->getImaginaryPart()
        );
    }
    else if (rhs.getType() == RATIONAL)
    {
        tmp = new Complex(
                this->getRationalPart() - dynamic_cast<const Rational *>(&rhs)->getValue(),
                this->getImaginaryPart()
        );
    }
    else
    {
        throw std::invalid_argument(
                "in 'Operand *Complex::operator-(Operand const &rhs)' rhs is not Complex or inferior.");
    }
    return endCheck(tmp);
}

Operand *Complex::operator*(Operand const &rhs)
{
    Complex *tmp;

    if (rhs.getType() == COMPLEX)
    {
        tmp = solveMul(
                this->getRationalPart(),
                this->getImaginaryPart(),
                dynamic_cast<const Complex *>(&rhs)->getRationalPart(),
                dynamic_cast<const Complex *>(&rhs)->getImaginaryPart()
        );
    }
    else if (rhs.getType() == RATIONAL)
    {
        tmp = new Complex(
                this->getRationalPart() * dynamic_cast<const Rational *>(&rhs)->getValue(),
                this->getImaginaryPart() * dynamic_cast<const Rational *>(&rhs)->getValue()
        );
    }
    else
    {
        throw std::invalid_argument(
                "in 'Operand *Complex::operator*(Operand const &rhs)' rhs is not Complex or inferior.");
    }
    return (endCheck(tmp));
}

Operand *Complex::operator/(Operand const &rhs)
{
    Complex *tmp;

    if (rhs.getType() == COMPLEX)
    {
        tmp = solveDiv(
                this->getRationalPart(),
                this->getImaginaryPart(),
                dynamic_cast<const Complex *>(&rhs)->getRationalPart(),
                dynamic_cast<const Complex *>(&rhs)->getImaginaryPart()
        );
    }
    else if (rhs.getType() == RATIONAL)
    {
        tmp = solveDiv(
                this->getRationalPart(),
                this->getImaginaryPart(),
                dynamic_cast<const Rational *>(&rhs)->getValue(),
                0.0
        );
    }
    else
    {
        throw std::invalid_argument(
                "in 'Operand *Complex::operator*(Operand const &rhs)' rhs is not Complex or inferior.");
    }
    return (endCheck(tmp));
}

Operand *Complex::operator%(Operand const &rhs)
{
    throw std::invalid_argument("in 'Operand *Complex::operator%(Operand const &rhs)' cannot % with Complex.");
}

Complex *Complex::solveMul(double a, double b, double c, double d)
{
    auto *tmp = new Complex(
            a * c - b * d, a * d + b * c
    );
    return tmp;
}

Complex *Complex::solveDiv(double a, double b, double c, double d)
{
    auto *tmp = new Complex(
            ((a * c + b * d) / (c * c + d * d)),
            ((b * c - a * d) / (c * c + d * d))
    );
    return tmp;
}

std::ostream &Complex::print(std::ostream &o, Operand const &i)
{
    o << "[COMPLEX | " << dynamic_cast<const Complex *>(&i)->getRationalPart() << " + "
      << dynamic_cast<const Complex *>(&i)->getImaginaryPart() << "i | " << i.getSelf() << "]";
    return (o);
}

Operand *Complex::endCheck(Complex *cp)
{
    Operand *tmp;

    if (cp->getImaginaryPart() == 0.0)
    {
        tmp = new Rational(cp->getRationalPart());
        delete cp;
    }
    else
        tmp = cp;
    return tmp;
}

std::ostream &operator<<(std::ostream &o, Complex const &i)
{
    Complex::print(o, i);
    return (o);
}
