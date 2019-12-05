//
// Created by Hugo JEANNIN on 12/2/19.
//

#include "../inc/Complex.hpp"

Complex::Complex()
{
    this->setType(COMPLEX);
    std::cerr << "Complex constructed." << std::endl;
}

Complex::~Complex()
{
    std::cerr << "Complex destroyed." << std::endl;
}