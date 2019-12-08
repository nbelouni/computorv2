#include "../inc/Token.hpp"

Token::Token()
{
	monomial_ = NULL;
}

Token::Token(Token::t_type type): type_(type)
{
	monomial_ = NULL;
}

Token::Token(Token::t_type type,Monomial *monomial): type_(type), monomial_(monomial)
{
}

Token::~Token()
{
	delete monomial_;
}

void			Token::setType(Token::t_type type)
{
	type_ = type;
}

Token::t_type	Token::getType()
{
	return type_;
}

void			Token::setMonomial(Monomial *monomial)
{
	monomial_ = monomial;
}

Monomial		*Token::getMonomial()
{
	return monomial_;
}
