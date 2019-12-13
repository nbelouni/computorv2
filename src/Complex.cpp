//
// Created by Hugo JEANNIN on 12/2/19.
//

#include "../inc/Complex.hpp"

Complex::Complex()
{
    std::cerr << "Complex constructed." << std::endl;
}

Complex::~Complex()
{
    std::cerr << "Complex destroyed." << std::endl;
}


void	Complex::setRealPart(double n)
{
	real_part_ = n;
}

double	Complex::getRealPart()
{
	return real_part_;
}

void	Complex::setComplexPart(double n)
{
	complex_part_ = n;
}

double	Complex::getComplexPart()
{
	return complex_part_;
}
