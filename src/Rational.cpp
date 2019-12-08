//
// Created by Hugo JEANNIN on 12/2/19.
//

#include "../inc/Rational.hpp"

Rational::Rational()
{
    this->setType(RATIONAL);
    this->value_ = 0.0;
}

Rational::~Rational()
{}

Rational::Rational(double value)
{
    this->setType(RATIONAL);
    this->value_ = value;
}

Rational::Rational(int value)
{
    this->setType(RATIONAL);
    this->value_ = value;
}

Rational::Rational(Rational &real)
{
    this->setType(RATIONAL);
    this->value_ = real.getValue();
}

Rational::Rational(const Operand *op)
{
    if (op->getType() == RATIONAL)
    {
        this->value_ = dynamic_cast<Rational const *>(op)->value_;
    }
    else
    {
        throw std::invalid_argument("in 'Rational::Rational(const Operand *op)' op is not Rational");
    }
}

void Rational::setValue(double value)
{
    this->value_ = value;
}

double Rational::getValue() const
{
    return this->value_;
}

Operand *Rational::operator=(Operand const &rhs)
{
    if (this != &rhs)
    {
        if (rhs.getType() == RATIONAL)
        {
            this->value_ = dynamic_cast<const Rational *>(&rhs)->value_;
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
                        "in 'Operand *Rational::operator=(Operand const &rhs)' rhs is Complex with imaginary_part_ != 0.0.");
            }
        }
        else
        {
            throw std::invalid_argument("in 'Operand *Rational::operator=(Operand const &rhs)' rhs is not Invalid.");
        }
    }
    return (dynamic_cast<Operand *>(this));
}

Operand *Rational::operator+(Operand const &rhs)
{
    if (rhs.getType() == RATIONAL)
    {
        Rational *tmp = new Rational(getValue() + dynamic_cast<const Rational *>(&rhs)->getValue());
        return (dynamic_cast<Operand *>(tmp));
    }
    else if (rhs.getType() == COMPLEX)
    {
            // Complex can be -> Rational
        if (dynamic_cast<const Complex *>(&rhs)->getImaginaryPart() == 0.0)
        {
            Rational *tmp = new Rational(getValue() + dynamic_cast<const Complex *>(&rhs)->getRealPart());
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
        throw std::invalid_argument("in 'Operand *Rational::operator+(Operand const &rhs)' rhs is Invalid.");
    }
}

Operand *Rational::operator-(Operand const &rhs)
{
    if (rhs.getType() == RATIONAL)
    {
        Rational *tmp = new Rational(getValue() - dynamic_cast<const Rational *>(&rhs)->getValue());
        return (dynamic_cast<Operand *>(tmp));
    }
    else if (rhs.getType() == COMPLEX)
    {
            // Complex can be -> Rational
        if (dynamic_cast<const Complex *>(&rhs)->getImaginaryPart() == 0.0)
        {
            Rational *tmp = new Rational(getValue() - dynamic_cast<const Complex *>(&rhs)->getRealPart());
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
        throw std::invalid_argument("in 'Operand *Rational::operator-(Operand const &rhs)' rhs is Invalid.");
    }
}

Operand *Rational::operator*(Operand const &rhs)
{
    if (rhs.getType() == RATIONAL)
    {
        Rational *tmp = new Rational(getValue() * dynamic_cast<const Rational *>(&rhs)->getValue());
        return (dynamic_cast<Operand *>(tmp));
    }
    else if (rhs.getType() == COMPLEX)
    {
            // Complex can be -> Rational
        if (dynamic_cast<const Complex *>(&rhs)->getImaginaryPart() == 0.0)
        {
            Rational *tmp = new Rational(getValue() * dynamic_cast<const Complex *>(&rhs)->getRealPart());
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
        throw std::invalid_argument("in 'Operand *Rational::operator*(Operand const &rhs)' rhs is Invalid.");
    }
}

Operand *Rational::operator/(Operand const &rhs)
{
    if (rhs.getType() == RATIONAL)
    {
        if (dynamic_cast<const Rational *>(&rhs)->getValue() != 0.0)
        {
            Rational *tmp = new Rational(getValue() / dynamic_cast<const Rational *>(&rhs)->getValue());
            return (dynamic_cast<Operand *>(tmp));
        }
        else
        {
            throw std::logic_error("in 'Operand *Rational::operator/(Operand const &rhs)' rhs is 0.0.");
        }
    }
    else if (rhs.getType() == COMPLEX)
    {
            // Complex can be -> Rational
        if (dynamic_cast<const Complex *>(&rhs)->getImaginaryPart() == 0.0)
        {
            if (dynamic_cast<const Complex *>(&rhs)->getRealPart() != 0.0)
            {
                Rational *tmp = new Rational(getValue() / dynamic_cast<const Complex *>(&rhs)->getRealPart());
                return (dynamic_cast<Operand *>(tmp));
            }
            else
            {
                throw std::logic_error("in 'Operand *Rational::operator/(Operand const &rhs)' rhs is 0.0.");
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
        throw std::invalid_argument("in 'Operand *Rational::operator/(Operand const &rhs)' rhs is Invalid.");
    }
}

Operand *Rational::operator%(Operand const &rhs)
{
    if (rhs.getType() == RATIONAL)
    {
        if (dynamic_cast<const Rational *>(&rhs)->getValue() != 0.0)
        {
            if (isInteger() && dynamic_cast<const Rational *>(&rhs)->isInteger())
            {
                Rational *tmp = new Rational(static_cast<int>(value_) % static_cast<int>(dynamic_cast<const Rational *>(&rhs)->value_));
                return (dynamic_cast<Operand *>(tmp));
            }
            else
            {
                throw std::invalid_argument("in 'Operand *Rational::operator%(Operand const &rhs)' rhs or self is not Integer.");
            }
        }
        else
        {
            throw std::logic_error("in 'Operand *Rational::operator/(Operand const &rhs)' rhs is 0.0.");
        }
    }
/*
    else if (rhs.getType() == COMPLEX)
    {
        // Complex can be -> Rational
        if (dynamic_cast<const Complex *>(&rhs)->getImaginaryPart() == 0.0)
        {
            if (dynamic_cast<const Complex *>(&rhs)->getRealPart() != 0.0)
            {
                this->value_ /= dynamic_cast<const Complex *>(&rhs)->getRealPart();
                return (dynamic_cast<Operand *>(this));
            }
            else
            {
                throw std::logic_error("in 'Operand *Rational::operator/(Operand const &rhs)' rhs is 0.0.");
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
        throw std::invalid_argument("in 'Operand *Rational::operator%(Operand const &rhs)' rhs is not Rational.");
    }
}

void Rational::reset()
{
    value_ = 0.0;
}

bool const Rational::isInteger() const
{
    if (floor(value_) == value_)
        return true;
    else
        return false;
}

std::ostream &operator<<(std::ostream &o, Rational const &i)
{
    o << "[ RATIONAL | " << i.getValue() << " | " << i.getSelf() << " ]";
    return (o);
}
