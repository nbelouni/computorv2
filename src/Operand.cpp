//
// Created by Hugo JEANNIN on 12/3/19.
//

#include "../inc/Computorv2.hpp"

Operand::Operand()
{
    this->type_ = UNDEFINED;
}

Operand::Operand(t_op type)
{
    this->type_ = type;
}

Operand::Operand(Operand &op)
{
    this->type_ = op.getType();
}

Operand::~Operand(){}

void Operand::setType(const t_op type)
{
    this->type_ = type;
}

const t_op Operand::getType() const
{
    return type_;
}

const Operand * Operand::getSelf() const
{
    return this;
}

bool const Operand::isInteger(double d) const
{
    return floor(d) == d;
}

std::ostream &operator<<(std::ostream &o, Operand const &i)
{
    t_op type;

    o << "{OPERAND of type: ";
    type = i.getType();
    if (type == UNDEFINED)
        o << "UNDEFINED | " << i.getSelf() << "}";
    else if (type == RATIONAL)
        Rational::print(o , i);
    else if (type == COMPLEX)
        Complex::print(o , i);
    else if (type == MATRIX)
        Matrix::print(o, i);
    o << "}";
    return (o);
}
