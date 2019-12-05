//
// Created by Hugo JEANNIN on 12/2/19.
//

#include "../inc/Real.hpp"

Real::Real()
{
    this->setType(REAL);
    this->_value = 0;
    this->_power = 0;
    std::cerr << "Real constructed." << std::endl;
}

Real::~Real()
{
    std::cerr << "Real destroyed." << std::endl;
}

Real::Real(double value)
{
    this->setType(REAL);
    this->_value = value;
    this->_power = 1;
}

Real::Real(double value, int power)
{
    this->setType(REAL);
    this->_value = value;
    this->_power = power;
}

Real::Real(Real &real)
{
    this->setType(REAL);
    this->_value = real.getValue();
    this->_power = real.getPower();
}

Real::Real(const Operand *op)
{
    if (op->getType() == REAL)
    {
        this->_value = dynamic_cast<Real const *>(op)->_value;
        this->_power = dynamic_cast<Real const *>(op)->_power;
    }
    else
    {
        throw std::invalid_argument("rhs is not Real");
    }
}

void Real::setValue(double value)
{
    this->_value = value;
}

double Real::getValue() const
{
    return _value;
}

void Real::setPower(int power)
{
    this->_power = power;
}

int Real::getPower() const
{
    return _power;
}

Operand const *Real::operator=(Operand const &rhs)
{
    if (this != &rhs)
    {
        std::cout << "___ Op = ___" << std::endl;
        this->_value = 0;
        this->_power = 0;
    }
    return (dynamic_cast<Operand const *>(this));
//    return nullptr;
}

Operand const *Real::operator+(Operand const &rhs)
{
    std::cout << "___ Op + ___" << std::endl;
    if (this != &rhs)
    {
        if (rhs.getType() == REAL)
        {
            this->_value += dynamic_cast<const Real *>(rhs.getSelf())->_value;
            this->_power += dynamic_cast<const Real *>(rhs.getSelf())->_power;
        }
        else
        {
            throw std::invalid_argument("rhs is not Real");
        }
    }
    return (dynamic_cast<Operand const *>(this));
//    return nullptr;
}

std::ostream &operator<<(std::ostream &o, Real const &i)
{
    o << "Real: " << i.getValue() << "^" << i.getPower();
    return (o);
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
