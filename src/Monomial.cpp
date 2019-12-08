#include "../inc/Monomial.hpp"

Monomial::Monomial(std::string name): name_(name)
{
	coef_ = 1;
	operand_ = NULL;
	power_ = 1;
}

Monomial::Monomial(Operand *op): operand_(op)
{
	coef_ = 1;
	power_ = 1;
}

Monomial::Monomial(double coef, Operand *op): coef_(coef), operand_(op)
{
	power_ = 1;
}

Monomial::Monomial(double coef, Operand *op, size_t pow): coef_(coef), operand_(op), power_(pow)
{
}

Monomial::Monomial(double coef, size_t pow, std::string name):  coef_(coef), power_(pow), name_(name)
{
	operand_ = NULL;
}

Monomial::~Monomial()
{
	delete operand_;
}

void		Monomial::setName(std::string s)
{
	name_ = s;
}

std::string	Monomial::getName()
{
	return name_;
}

void		Monomial::setCoef(double c)
{
	coef_ = c;
}

double		Monomial::getCoef()
{
	return coef_;
}

void		Monomial::setOperand(Operand *op)
{
	operand_ = op;
}

Operand		*Monomial::getOperand()
{
	return operand_;
}

void		Monomial::setPower(size_t pow)
{
	power_ = pow;
}

size_t		Monomial::getPower()
{
	return power_;
}
