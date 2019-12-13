#include "../inc/Monomial.hpp"

Monomial::Monomial(std::string name, bool neg): name_(name), neg_(neg)
{
	coef_ = 1;
	operand_ = NULL;
	power_ = 1;
}

Monomial::Monomial(Operand *op): operand_(op)
{
	coef_ = 1;
	power_ = 1;
	neg_ = false;
}

Monomial::Monomial(double coef, Operand *op): coef_(coef), operand_(op)
{
	power_ = 1;
	neg_ = false;
}

Monomial::Monomial(double coef, Operand *op, size_t pow): coef_(coef), operand_(op), power_(pow)
{
	neg_ = false;
}

Monomial::Monomial(double coef, size_t pow, std::string name, bool neg):  coef_(coef), power_(pow), name_(name), neg_(neg)
{
	operand_ = NULL;
}

Monomial::~Monomial()
{
	delete operand_;
}

void		Monomial::setName(std::string s)
{
	std::cout << "setName : " << s << std::endl;
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

void		Monomial::setNeg(bool n)
{
	neg_ = n;
}

bool		Monomial::isNeg()
{
	return neg_;
}
