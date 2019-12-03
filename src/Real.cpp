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

Real::Real(double value)
{
    this->_value = value;
    this->_power = 1;
}

Real::Real(double value, int power)
{
    this->_value = value;
    this->_power = power;
}

Real::Real(Real &real)
{
    this->_value = real.getValue();
    this->_power = real.getPower();
}

void Real::setValue(double value)
{
    this->_value = value;
}

double Real::getValue()
{
    return _value;
}

void Real::setPower(int power)
{
    this->_power = power;
}

int Real::getPower()
{
    return _power;
}


//Operand const *
//Real::operator+(Operand const &rhs)
//{
//    if (this != &rhs)
//    {
//        const t_op type = rhs.getType();
//        if (type == REAL)
//        {
//            Real *r;
//            r = dynamic_cast<Real*>(rhs);
//            _value += r->_value;
//            _power += r->_power;
//        }
//    }
//    return (dynamic_cast<Operand*>(this));
//}
/*


Operand const *Real::operator=(Operand const &rhs)
{
    if (this != &rhs)
    {}
    return (dynamic_cast<Operand *>(this));
}
*/
