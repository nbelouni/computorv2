//
// Created by Hugo JEANNIN on 12/2/19.
//

#include "../inc/Real.hpp"

Real::Real()
{
    this->setType(REAL);
    this->value_ = 0.0;
    this->power_ = 0;
}

Real::~Real(){}

Real::Real(double value)
{
    this->setType(REAL);
    this->value_ = value;
    this->power_ = 1;
}

Real::Real(double value, int power)
{
    this->setType(REAL);
    this->value_ = value;
    this->power_ = power;
}

Real::Real(Real &real)
{
    this->setType(REAL);
    this->value_ = real.getValue();
    this->power_ = real.getPower();
}

Real::Real(const Operand *op)
{
    if (op->getType() == REAL)
    {
        this->value_ = dynamic_cast<Real const *>(op)->value_;
        this->power_ = dynamic_cast<Real const *>(op)->power_;
    }
    else
    {
        throw std::invalid_argument("in 'Real::Real(const Operand *op)' op is not Real");
    }
}

void Real::setValue(double value)
{
    this->value_ = value;
}

double Real::getValue() const
{
    return this->value_;
}

void Real::setPower(int power)
{
    this->power_ = power;
}

int Real::getPower() const
{
    return this->power_;
}

Operand *Real::operator=(Operand const &rhs)
{
    std::cout << "___ Op = ___" << std::endl;
    if (this != &rhs)
    {
        if (rhs.getType() == REAL)
        {
            this->value_ = dynamic_cast<const Real *>(&rhs)->value_;
            this->power_ = dynamic_cast<const Real *>(&rhs)->power_;
        }
        else if (rhs.getType() == COMPLEX)
        {
            if (dynamic_cast<const Complex *>(&rhs)->getImaginaryPart() == 0.0)
            {
                this->value_ = dynamic_cast<const Complex *>(&rhs)->getRealPart();
                this->power_ = 1;
            }
            else
            {
                throw std::logic_error("in 'Operand *Real::operator=(Operand const &rhs)' rhs is Complex with imaginary_part_ != 0.0.");
            }
        }
        else
        {
            throw std::invalid_argument("in 'Operand *Real::operator=(Operand const &rhs)' rhs is not Invalid.");
        }
    }
    return (dynamic_cast<Operand *>(this));
}

Operand *Real::operator+(Operand const &rhs)
{
    std::cout << "___ Op + ___" << std::endl;
    if (this != &rhs)
    {
        if (rhs.getType() == REAL)
        {
            Real *tmp = new Real(getValue() + dynamic_cast<const Real *>(&rhs)->getValue(),
                                 getPower() + dynamic_cast<const Real *>(&rhs)->getPower());
            return dynamic_cast<Operand *>(tmp);
        }
        else if (rhs.getType() == COMPLEX)
        {
            // Complex can be -> Real
            if (dynamic_cast<const Complex *>(&rhs)->getImaginaryPart() == 0.0)
            {
                this->value_ = computePower();
                this->power_ = 1;
                this->value_ += dynamic_cast<const Complex *>(&rhs)->getRealPart();
            }
            // Must stay Complex
            else
            {
                Complex *tmp = new Complex(computePower() + dynamic_cast<const Complex *>(&rhs)->getRealPart(),
                                           dynamic_cast<const Complex *>(&rhs)->getImaginaryPart());
                return dynamic_cast<Operand *>(tmp);
            }
        }
        else
        {
            throw std::invalid_argument("in 'Operand *Real::operator+(Operand const &rhs)' rhs is not Invalid.");
        }
    }
    return (dynamic_cast<Operand *>(this));
}

Operand *Real::operator-(Operand const &rhs)
{
    std::cout << "___ Op - ___" << std::endl;
    if (this != &rhs)
    {
        if (rhs.getType() == REAL)
        {
            Real *tmp = new Real(getValue() - dynamic_cast<const Real *>(&rhs)->getValue(),
                                 getPower() - dynamic_cast<const Real *>(&rhs)->getPower());
            return dynamic_cast<Operand *>(tmp);
        }
        else if (rhs.getType() == COMPLEX)
        {
            // Complex can be -> Real
            if (dynamic_cast<const Complex *>(&rhs)->getImaginaryPart() == 0.0)
            {
                this->value_ = computePower();
                this->power_ = 1;
                this->value_ -= dynamic_cast<const Complex *>(&rhs)->getRealPart();
            }
                // Must stay Complex
            else
            {
                Complex *tmp = new Complex(computePower() - dynamic_cast<const Complex *>(&rhs)->getRealPart(),
                                           dynamic_cast<const Complex *>(&rhs)->getImaginaryPart());
                return dynamic_cast<Operand *>(tmp);
            }
        }
        else
        {
            throw std::invalid_argument("in 'Operand *Real::operator-(Operand const &rhs)' rhs is not Real.");
        }
    }
    return (dynamic_cast<Operand *>(this));
}

const double Real::computePower() const
{
    return pow(this->value_, this->power_);
}

std::ostream &operator<<(std::ostream &o, Real const &i)
{
    o << "[ REAL | " << i.getValue() << "^" << i.getPower() << " | " << i.getSelf() << " ]";
    return (o);
}
