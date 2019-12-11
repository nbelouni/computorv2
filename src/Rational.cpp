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

Rational::Rational(Rational &rational)
{
    this->setType(RATIONAL);
    this->value_ = rational.getValue();
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
                this->value_ = dynamic_cast<const Complex *>(&rhs)->getRationalPart();
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
    Operand *tmp;

    if (rhs.getType() == RATIONAL)
    {
        tmp = new Rational(getValue() + dynamic_cast<const Rational *>(&rhs)->getValue());
    }
    else if (rhs.getType() == COMPLEX)
    {
        // Complex can be -> Rational
        if (dynamic_cast<const Complex *>(&rhs)->getImaginaryPart() == 0.0)
        {
            tmp = new Rational(getValue() + dynamic_cast<const Complex *>(&rhs)->getRationalPart());
        }
            // Must stay Complex
        else
        {
            tmp = new Complex(getValue() + dynamic_cast<const Complex *>(&rhs)->getRationalPart(),
                              dynamic_cast<const Complex *>(&rhs)->getImaginaryPart());
        }
    }
    else if (rhs.getType() == MATRIX)
    {
        throw std::logic_error("in 'Operand *Rational::operator-(Operand const &rhs)' cannot add a matrix to a rational, did you mean to add a rational to a matrix instead?");
    }
    else
    {
        throw std::invalid_argument("in 'Operand *Rational::operator+(Operand const &rhs)' rhs is Invalid.");
    }
    return (tmp);
}

Operand *Rational::operator-(Operand const &rhs)
{
    Operand *tmp;

    if (rhs.getType() == RATIONAL)
    {
        tmp = new Rational(getValue() - dynamic_cast<const Rational *>(&rhs)->getValue());
    }
    else if (rhs.getType() == COMPLEX)
    {
        // Complex can be -> Rational
        if (dynamic_cast<const Complex *>(&rhs)->getImaginaryPart() == 0.0)
        {
            tmp = new Rational(getValue() - dynamic_cast<const Complex *>(&rhs)->getRationalPart());
        }
            // Must stay Complex
        else
        {
            tmp = new Complex(getValue() - dynamic_cast<const Complex *>(&rhs)->getRationalPart(),
                              dynamic_cast<const Complex *>(&rhs)->getImaginaryPart());
        }
    }
    else if (rhs.getType() == MATRIX)
    {
        throw std::logic_error("in 'Operand *Rational::operator-(Operand const &rhs)' cannot subtract a matrix to a rational, did you mean to subtract a rational to a matrix instead?");
    }
    else
    {
        throw std::invalid_argument("in 'Operand *Rational::operator-(Operand const &rhs)' rhs is Invalid.");
    }
    return (tmp);
}

Operand *Rational::operator*(Operand const &rhs)
{
    Operand *tmp;

    if (rhs.getType() == RATIONAL)
    {
        tmp = new Rational(getValue() * dynamic_cast<const Rational *>(&rhs)->getValue());
    }
    else if (rhs.getType() == COMPLEX)
    {
        // Complex can be -> Rational
        if (dynamic_cast<const Complex *>(&rhs)->getImaginaryPart() == 0.0)
        {
            tmp = new Rational(getValue() * dynamic_cast<const Complex *>(&rhs)->getRationalPart());
        }
            // Must stay Complex
        else
        {
            tmp = new Complex(getValue() * dynamic_cast<const Complex *>(&rhs)->getRationalPart(),
                              getValue() * dynamic_cast<const Complex *>(&rhs)->getImaginaryPart());
        }
    }
    else if (rhs.getType() == MATRIX)
    {
        throw std::logic_error("in 'Operand *Rational::operator*(Operand const &rhs)' cannot multiply a matrix to a rational, did you mean to multiply a rational to a matrix instead?");
    }
    else
    {
        throw std::invalid_argument("in 'Operand *Rational::operator*(Operand const &rhs)' rhs is Invalid.");
    }
    return (tmp);
}

Operand *Rational::operator/(Operand const &rhs)
{
    Operand *tmp;

    if (rhs.getType() == RATIONAL)
    {
        if (dynamic_cast<const Rational *>(&rhs)->getValue() != 0.0)
        {
            tmp = new Rational(getValue() / dynamic_cast<const Rational *>(&rhs)->getValue());
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
            if (dynamic_cast<const Complex *>(&rhs)->getRationalPart() != 0.0)
            {
                tmp = new Rational(getValue() / dynamic_cast<const Complex *>(&rhs)->getRationalPart());
            }
            else
            {
                throw std::logic_error("in 'Operand *Rational::operator/(Operand const &rhs)' rhs is 0.0.");
            }

        }
            // Must stay Complex
        else
        {
            tmp = Complex::solveDiv(this->getValue(),
                                    0.0,
                                    dynamic_cast<const Complex *>(&rhs)->getRationalPart(),
                                    dynamic_cast<const Complex *>(&rhs)->getImaginaryPart());
        }
    }
    else if (rhs.getType() == MATRIX)
    {
        throw std::logic_error("in 'Operand *Rational::operator/(Operand const &rhs)' cannot divide a matrix to a rational, did you mean to divide a rational to a matrix instead?");
    }
    else
    {
        throw std::invalid_argument("in 'Operand *Rational::operator/(Operand const &rhs)' rhs is Invalid.");
    }
    return (tmp);
}

Operand *Rational::operator%(Operand const &rhs)
{
    if (rhs.getType() == RATIONAL)
    {
        if (dynamic_cast<const Rational *>(&rhs)->getValue() != 0.0)
        {
            if (isInteger() && dynamic_cast<const Rational *>(&rhs)->isInteger())
            {
                Operand *tmp = new Rational(
                        static_cast<int>(value_) % static_cast<int>(dynamic_cast<const Rational *>(&rhs)->value_));
                return (tmp);
            }
            else
            {
                throw std::invalid_argument(
                        "in 'Operand *Rational::operator%(Operand const &rhs)' rhs or self is not Integer.");
            }
        }
        else
        {
            throw std::logic_error("in 'Operand *Rational::operator/(Operand const &rhs)' rhs is 0.0.");
        }
    }
    else
    {
        throw std::invalid_argument("in 'Operand *Rational::operator%(Operand const &rhs)' rhs is not Rational.");
    }
}

bool const Rational::isInteger() const
{
    return floor(value_) == value_;
}

std::ostream &Rational::print(std::ostream &o, Operand const &i)
{
    o << "[RATIONAL | " << dynamic_cast<const Rational *>(&i)->getValue() << " | "
      << dynamic_cast<const Rational *>(&i)->getSelf() << "]";
    return (o);
}

std::ostream &operator<<(std::ostream &o, Rational const &i)
{
    Rational::print(o, i);
    return (o);
}
