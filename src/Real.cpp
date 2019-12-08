//
// Created by Hugo JEANNIN on 12/2/19.
//

#include "../inc/Real.hpp"

Real::Real()
{
    this->setType(REAL);
    this->value_ = 0.0;
}

Real::~Real()
{}

Real::Real(double value)
{
    this->setType(REAL);
    this->value_ = value;
}

Real::Real(int value)
{
    this->setType(REAL);
    this->value_ = value;
}

Real::Real(Real &real)
{
    this->setType(REAL);
    this->value_ = real.getValue();
}

Real::Real(const Operand *op)
{
    if (op->getType() == REAL)
    {
        this->value_ = dynamic_cast<Real const *>(op)->value_;
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

Operand *Real::operator=(Operand const &rhs)
{
    if (this != &rhs)
    {
        if (rhs.getType() == REAL)
        {
            this->value_ = dynamic_cast<const Real *>(&rhs)->value_;
        }
        else if (rhs.getType() == COMPLEX)
        {
            if (dynamic_cast<const Complex *>(&rhs)->getImaginaryPart() == 0.0)
            {
                this->value_ = dynamic_cast<const Complex *>(&rhs)->getRealPart();
            }
            else
            {
                throw std::logic_error(
                        "in 'Operand *Real::operator=(Operand const &rhs)' rhs is Complex with imaginary_part_ != 0.0.");
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
    if (rhs.getType() == REAL)
    {
        Real *tmp = new Real(getValue() + dynamic_cast<const Real *>(&rhs)->getValue());
        return (dynamic_cast<Operand *>(tmp));
    }
    else if (rhs.getType() == COMPLEX)
    {
            // Complex can be -> Real
        if (dynamic_cast<const Complex *>(&rhs)->getImaginaryPart() == 0.0)
        {
            Real *tmp = new Real(getValue() + dynamic_cast<const Complex *>(&rhs)->getRealPart());
            return (dynamic_cast<Operand *>(tmp));
        }
            // Must stay Complex
        else
        {
            Complex *tmp = new Complex(getValue() + dynamic_cast<const Complex *>(&rhs)->getRealPart(),
                                       dynamic_cast<const Complex *>(&rhs)->getImaginaryPart());
            return (dynamic_cast<Operand *>(tmp));
        }
    }
    else
    {
        throw std::invalid_argument("in 'Operand *Real::operator+(Operand const &rhs)' rhs is Invalid.");
    }
}

Operand *Real::operator-(Operand const &rhs)
{
    if (rhs.getType() == REAL)
    {
        Real *tmp = new Real(getValue() - dynamic_cast<const Real *>(&rhs)->getValue());
        return (dynamic_cast<Operand *>(tmp));
    }
    else if (rhs.getType() == COMPLEX)
    {
            // Complex can be -> Real
        if (dynamic_cast<const Complex *>(&rhs)->getImaginaryPart() == 0.0)
        {
            Real *tmp = new Real(getValue() - dynamic_cast<const Complex *>(&rhs)->getRealPart());
            return (dynamic_cast<Operand *>(tmp));
        }
            // Must stay Complex
        else
        {
            Complex *tmp = new Complex(getValue() - dynamic_cast<const Complex *>(&rhs)->getRealPart(),
                                       dynamic_cast<const Complex *>(&rhs)->getImaginaryPart());
            return (dynamic_cast<Operand *>(tmp));
        }
    }
    else
    {
        throw std::invalid_argument("in 'Operand *Real::operator-(Operand const &rhs)' rhs is Invalid.");
    }
}

Operand *Real::operator*(Operand const &rhs)
{
    if (rhs.getType() == REAL)
    {
        Real *tmp = new Real(getValue() * dynamic_cast<const Real *>(&rhs)->getValue());
        return (dynamic_cast<Operand *>(tmp));
    }
    else if (rhs.getType() == COMPLEX)
    {
            // Complex can be -> Real
        if (dynamic_cast<const Complex *>(&rhs)->getImaginaryPart() == 0.0)
        {
            Real *tmp = new Real(getValue() * dynamic_cast<const Complex *>(&rhs)->getRealPart());
            return (dynamic_cast<Operand *>(tmp));
        }
            // Must stay Complex
        else
        {
            Complex *tmp = new Complex(getValue() * dynamic_cast<const Complex *>(&rhs)->getRealPart(),
                                       getValue() * dynamic_cast<const Complex *>(&rhs)->getImaginaryPart());
            return (dynamic_cast<Operand *>(tmp));
        }
    }
    else
    {
        throw std::invalid_argument("in 'Operand *Real::operator*(Operand const &rhs)' rhs is Invalid.");
    }
}

Operand *Real::operator/(Operand const &rhs)
{
    if (rhs.getType() == REAL)
    {
        if (dynamic_cast<const Real *>(&rhs)->getValue() != 0.0)
        {
            Real *tmp = new Real(getValue() / dynamic_cast<const Real *>(&rhs)->getValue());
            return (dynamic_cast<Operand *>(tmp));
        }
        else
        {
            throw std::logic_error("in 'Operand *Real::operator/(Operand const &rhs)' rhs is 0.0.");
        }
    }
    else if (rhs.getType() == COMPLEX)
    {
            // Complex can be -> Real
        if (dynamic_cast<const Complex *>(&rhs)->getImaginaryPart() == 0.0)
        {
            if (dynamic_cast<const Complex *>(&rhs)->getRealPart() != 0.0)
            {
                Real *tmp = new Real(getValue() / dynamic_cast<const Complex *>(&rhs)->getRealPart());
                return (dynamic_cast<Operand *>(tmp));
            }
            else
            {
                throw std::logic_error("in 'Operand *Real::operator/(Operand const &rhs)' rhs is 0.0.");
            }

        }
            // Must stay Complex
        else
        {
            Complex *tmp;
            tmp = Complex::solveDiv(this->getValue(),
                           0.0,
                           dynamic_cast<const Complex *>(&rhs)->getRealPart(),
                           dynamic_cast<const Complex *>(&rhs)->getImaginaryPart());
            return (dynamic_cast<Operand *>(tmp));
        }
    }
    else
    {
        throw std::invalid_argument("in 'Operand *Real::operator/(Operand const &rhs)' rhs is Invalid.");
    }
}

Operand *Real::operator%(Operand const &rhs)
{
    if (rhs.getType() == REAL)
    {
        if (dynamic_cast<const Real *>(&rhs)->getValue() != 0.0)
        {
            if (isInteger() && dynamic_cast<const Real *>(&rhs)->isInteger())
            {
                Real *tmp = new Real(static_cast<int>(value_) % static_cast<int>(dynamic_cast<const Real *>(&rhs)->value_));
                return (dynamic_cast<Operand *>(tmp));
            }
            else
            {
                throw std::invalid_argument("in 'Operand *Real::operator%(Operand const &rhs)' rhs or self is not Integer.");
            }
        }
        else
        {
            throw std::logic_error("in 'Operand *Real::operator/(Operand const &rhs)' rhs is 0.0.");
        }
    }
/*
    else if (rhs.getType() == COMPLEX)
    {
        // Complex can be -> Real
        if (dynamic_cast<const Complex *>(&rhs)->getImaginaryPart() == 0.0)
        {
            if (dynamic_cast<const Complex *>(&rhs)->getRealPart() != 0.0)
            {
                this->value_ /= dynamic_cast<const Complex *>(&rhs)->getRealPart();
                return (dynamic_cast<Operand *>(this));
            }
            else
            {
                throw std::logic_error("in 'Operand *Real::operator/(Operand const &rhs)' rhs is 0.0.");
            }

        }
            // Must stay Complex
        else
        {
            /// LA CA DEVIENS CHAUD https://www.youtube.com/watch?v=FGGC3mF0rOc
//            Complex *tmp = new Complex(getValue() * dynamic_cast<const Complex *>(&rhs)->getRealPart(),
//                                       getValue() * dynamic_cast<const Complex *>(&rhs)->getImaginaryPart());
//            return (dynamic_cast<Operand *>(tmp));
        }
    }
*/
    else
    {
        throw std::invalid_argument("in 'Operand *Real::operator%(Operand const &rhs)' rhs is not Real.");
    }
}

void Real::reset()
{
    value_ = 0.0;
}

bool const Real::isInteger() const
{
    if (floor(value_) == value_)
        return true;
    else
        return false;
}

std::ostream &operator<<(std::ostream &o, Real const &i)
{
    o << "[ REAL | " << i.getValue() << " | " << i.getSelf() << " ]";
    return (o);
}
