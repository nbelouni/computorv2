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

std::ostream &operator<<(std::ostream &o, Operand const &i)
{
    t_op type;

    o << "[ OPERAND of type: ";
    type = i.getType();
    if (type == UNDEFINED)
        o << "UNDEFINED";
    else if (type == RATIONAL)
        o << "RATIONAL";
    else if (type == COMPLEX)
        o << "COMPLEX";
    else if (type == MATRIX)
        o << "MATRIX";
    o <<  " " << i.getSelf() << " ]";
    return (o);
}
