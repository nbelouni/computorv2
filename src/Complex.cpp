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

Complex::Complex(double complex_part)
{
    this->setType(COMPLEX);
    this->real_part_ = 0.0;
    this->complex_part_ = complex_part;
}

Complex::Complex(double real_part, double complex_part)
{
    this->setType(COMPLEX);
    this->real_part_ = real_part;
    this->complex_part_ = complex_part;
}

Complex::Complex(Complex &cmp)
{
    this->setType(COMPLEX);
    this->real_part_ = cmp.getRealPart();
    this->complex_part_ = cmp.getComplexPart();
}

Complex::Complex(const Operand *op)
{
    if (op->getType() == COMPLEX)
    {
        this->real_part_ = dynamic_cast<Complex const *>(op)->real_part_;
        this->complex_part_ = dynamic_cast<Complex const *>(op)->complex_part_;
    }
    else
    {
        throw std::invalid_argument("in 'Complex::Complex(const Operand *op)' op is not Complex");
    }

}

void Complex::setRealPart(double n)
{
    this->real_part_ = n;
}

double Complex::getRealPart() const
{
    return this->real_part_;
}

void Complex::setComplexPart(double n)
{
    this->complex_part_ = n;
}

double Complex::getComplexPart() const
{
    return this->complex_part_;
}

std::ostream &operator<<(std::ostream &o, Complex const &i)
{
    o << "Complex: " << i.getRealPart()<< " + " << i.getComplexPart() << "i";
    return (o);
}
