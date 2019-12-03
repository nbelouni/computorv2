//
// Created by Hugo JEANNIN on 12/2/19.
//

#include "../inc/Real.hpp"

Real::Real()
{
    std::cerr << "Real constructed." << std::endl;
}

Real::~Real()
{
    std::cerr << "Real destroyed." << std::endl;
}


Real Real::operator=(Operand const &rhs)
{
    if (this != &rhs)
    {
        const t_op type = rhs.getType();
    }
    return (*this);
}
