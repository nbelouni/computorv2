//
// Created by Hugo JEANNIN on 12/3/19.
//

#include "../inc/Computorv2.hpp"

Operand::Operand()
{
    this->_type = UNDEFINED;
    std::cerr << "Operand constructed." << std::endl;
}

Operand::Operand(t_op type)
{
    this->_type = type;
    std::cerr << "Operand constructed: " << type << std::endl;
}

Operand::Operand(Operand &op)
{
    this->_type = op.getType();
}

Operand::~Operand()
{
    std::cerr << "Operand destroyed." << std::endl;
}

void Operand::setType(const t_op type)
{
    this->_type = type;
}

const t_op Operand::getType() const
{
    return _type;
}

const Operand * Operand::getSelf() const
{
    return this;
}
