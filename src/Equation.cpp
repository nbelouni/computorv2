#include "../inc/Equation.hpp"


Equation::Equation()
{
	power_max_ = 0;
}

Equation::Equation(std::vector<Token> t, size_t pow): tokens_(t), power_max_(pow)
{
}

Equation::Equation(std::vector<Token> t, size_t pow, std::vector<std::string> u): tokens_(t), power_max_(pow), unknowns_(u)
{
}

Equation::~Equation()
{
	clear();
}

void						Equation::clear()
{
	tokens_.clear();
	unknowns_.clear();
}

void						Equation::setTokens(std::vector<Token> t)
{
	tokens_ = t;
}

void						Equation::addToken(Token t)
{
	tokens_.push_back(t);
}

Token						Equation::getToken(size_t i)
{
	return tokens_[i];
}
std::vector<Token>			Equation::getAllTokens()
{
	return tokens_;
}

void						Equation::setPowerMax(size_t p)
{
	power_max_ = p;
}

size_t						Equation::getPowerMax()
{
	return power_max_;
}

void						Equation::setUnknowns(std::vector<std::string> t)
{
	unknowns_ = t;
}

void						Equation::addUnknown(std::string t)
{
	unknowns_.push_back(t);
}

std::string					Equation::getUnknown(size_t i)
{
	return unknowns_[i];
}

std::vector<std::string>	Equation::getAllUnknowns()
{
	return unknowns_;
}
