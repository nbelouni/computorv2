//
// Created by Hugo JEANNIN on 12/3/19.
//

#include "../inc/Computorv2.hpp"

Operand::Operand()
{
    this->type_ = UNDEFINED;
    std::cerr << "Operand constructed." << std::endl;
}

Operand::Operand(t_op type)
{
    this->type_ = type;
    std::cerr << "Operand constructed: " << type << std::endl;
}

Operand::Operand(Operand &op)
{
    this->type_ = op.getType();
}

Operand::~Operand()
{
    std::cerr << "Operand destroyed." << std::endl;
}

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
