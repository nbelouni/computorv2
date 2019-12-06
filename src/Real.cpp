//
// Created by Hugo JEANNIN on 12/2/19.
//

#include "../inc/Real.hpp"

Real::Real()
{
    this->setType(REAL);
    this->value_ = 0.0;
    this->power_ = 0;
}

Real::~Real(){}

Real::Real(double value)
{
    this->setType(REAL);
    this->value_ = value;
    this->power_ = 1;
}

Real::Real(double value, int power)
{
    this->setType(REAL);
    this->value_ = value;
    this->power_ = power;
}

Real::Real(Real &real)
{
    this->setType(REAL);
    this->value_ = real.getValue();
    this->power_ = real.getPower();
}

Real::Real(const Operand *op)
{
    if (op->getType() == REAL)
    {
        this->value_ = dynamic_cast<Real const *>(op)->value_;
        this->power_ = dynamic_cast<Real const *>(op)->power_;
    }
    else
    {
        throw std::invalid_argument("in 'Real::Real(const Operand *op)' op is not Real");
    }
}

void Real::setValue(double value)
{
    this->value_ = value;
}

double Real::getValue() const
{
    return this->value_;
}

void Real::setPower(int power)
{
    this->power_ = power;
}

int Real::getPower() const
{
    return this->power_;
}

Operand const *Real::operator=(Operand const &rhs)
{
    std::cout << "___ Op = ___" << std::endl;
    if (this != &rhs)
    {
        if (rhs.getType() == REAL)
        {
            this->value_ = dynamic_cast<const Real *>(rhs.getSelf())->value_;
            this->power_ = dynamic_cast<const Real *>(rhs.getSelf())->power_;
        }
        else if (rhs.getType() == COMPLEX)
        {
            if (dynamic_cast<const Complex *>(rhs.getSelf())->getComplexPart() == 0.0)
            {
                this->value_ = dynamic_cast<const Complex *>(rhs.getSelf())->getRealPart();
                this->power_ = 1;
            }
            else
            {
                throw std::logic_error("in 'Operand const *Real::operator=(Operand const &rhs)' rhs is Complex with complex_part_ != 0.0.");
            }
        }
        else
        {
            throw std::invalid_argument("in 'Operand const *Real::operator=(Operand const &rhs)' rhs is not Real.");
        }
    }
    return (dynamic_cast<Operand const *>(this));
}

Operand const *Real::operator+(Operand const &rhs)
{
    std::cout << "___ Op + ___" << std::endl;
    if (this != &rhs)
    {
        if (rhs.getType() == REAL)
        {
            this->value_ += dynamic_cast<const Real *>(rhs.getSelf())->value_;
            this->power_ += dynamic_cast<const Real *>(rhs.getSelf())->power_;
        }
        else
        {
            throw std::invalid_argument("in 'Operand const *Real::operator+(Operand const &rhs)' rhs is not Real.");
        }
    }
    return (dynamic_cast<Operand const *>(this));
}

Operand const *Real::operator-(Operand const &rhs)
{
    std::cout << "___ Op - ___" << std::endl;
    if (this != &rhs)
    {
        if (rhs.getType() == REAL)
        {
            this->value_ -= dynamic_cast<const Real *>(rhs.getSelf())->value_;
            this->power_ -= dynamic_cast<const Real *>(rhs.getSelf())->power_;
        }
        else
        {
            throw std::invalid_argument("in 'Operand const *Real::operator+(Operand const &rhs)' rhs is not Real.");
        }
    }
    return (dynamic_cast<Operand const *>(this));
}

const double Real::computePower() const
{
    return pow(this->value_, this->power_);
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
//            value_ += r->value_;
//            power_ += r->power_;
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
