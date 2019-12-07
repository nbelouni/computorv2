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
            throw std::invalid_argument("in 'Operand *Real::operator=(Operand const &rhs)' rhs is not Invalid.");
        }
    }
    return (dynamic_cast<Operand *>(this));
}

Operand *Complex::operator+(Operand const &rhs)
{
    if (rhs.getType() == COMPLEX)
    {
        Complex *tmp = new Complex(this->getRealPart() + dynamic_cast<const Complex *>(&rhs)->getRealPart(),
                                   this->getImaginaryPart() + dynamic_cast<const Complex *>(&rhs)->getImaginaryPart());
        return (dynamic_cast<Operand *>(tmp));
    }
    else if (rhs.getType() == REAL)
    {
        Complex *tmp = new Complex(this->getRealPart() + dynamic_cast<const Real *>(&rhs)->getValue(),
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
    else if (rhs.getType() == REAL)
    {
        Complex *tmp = new Complex(this->getRealPart() - dynamic_cast<const Real *>(&rhs)->getValue(),
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
        /// Truc complique
//        Complex *tmp = new Complex(this->getRealPart() * dynamic_cast<const Complex *>(&rhs)->getRealPart(),
//                                   this->getImaginaryPart() * dynamic_cast<const Complex *>(&rhs)->getImaginaryPart());
//        return (dynamic_cast<Operand *>(tmp));
    }
    else if (rhs.getType() == REAL)
    {
        Complex *tmp = new Complex(this->getRealPart() * dynamic_cast<const Real *>(&rhs)->getValue(),
                                   this->getImaginaryPart() * dynamic_cast<const Real *>(&rhs)->getValue());
        return (dynamic_cast<Operand *>(tmp));
    }
    else
    {
        throw std::invalid_argument(
                "in 'Operand *Complex::operator*(Operand const &rhs)' rhs is not Complex or inferior.");
    }
}

std::ostream &operator<<(std::ostream &o, Complex const &i)
{
    o << "[ COMPLEX | " << i.getRealPart() << " + " << i.getImaginaryPart() << "i | " << i.getSelf() << " ]";
    return (o);
}
