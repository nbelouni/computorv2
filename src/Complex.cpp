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

Complex::~Complex(){}

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

Operand const *Complex::operator=(Operand const &rhs)
{
    std::cout << "___ Op = ___" << std::endl;
    if (this != &rhs)
    {
        if (rhs.getType() == COMPLEX)
        {
            this->real_part_ = dynamic_cast<const Complex *>(rhs.getSelf())->real_part_;
            this->imaginary_part_ = dynamic_cast<const Complex *>(rhs.getSelf())->imaginary_part_;
        }
        else
        {
            throw std::invalid_argument("in 'const Operand *Complex::operator=(const Operand &rhs)' rhs is not Complex.");
        }
    }
    return (dynamic_cast<Operand const *>(this));
}

const Operand *Complex::operator+(const Operand &rhs)
{
    std::cout << "___ Op + ___" << std::endl;
    if (this != &rhs)
    {
        if (rhs.getType() == COMPLEX)
        {
            this->real_part_ += dynamic_cast<const Complex *>(rhs.getSelf())->real_part_;
            this->imaginary_part_ += dynamic_cast<const Complex *>(rhs.getSelf())->imaginary_part_;
        }
        else if (rhs.getType() == REAL)
        {
            const Real *tmp = dynamic_cast<const Real *>(rhs.getSelf());
            this->real_part_ += tmp->computePower();;
        }
        else
        {
            throw std::invalid_argument("in 'const Operand *Complex::operator+(const Operand &rhs)' rhs is not Complex or inferior.");
        }
    }
    return (dynamic_cast<Operand const *>(this));
}

std::ostream &operator<<(std::ostream &o, Complex const &i)
{
    o << "[ COMPLEX | " << i.getRealPart()<< " + " << i.getImaginaryPart() << "i | " << i.getSelf() << " ]";
    return (o);
}
