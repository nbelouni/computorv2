#ifndef MONOMIAL_HPP
# define MONOMIAL_HPP

#include "Computorv2.hpp"
#include "Operand.hpp"

class Monomial
{
	private:
		std::string	name_;
		double		coef_;
		Operand		*operand_;
		size_t		power_;
		bool		neg_;

	public:
		Monomial(std::string name, bool neg);
		Monomial(Operand *op);
		Monomial(double coef, Operand *op);
		Monomial(double coef, size_t pow, std::string name, bool neg);
		Monomial(double coef, Operand *op, size_t pow);
		~Monomial();

		void		setName(std::string s);
		std::string	getName();
		
		void		setCoef(double c);
		double		getCoef();
		
		void		setOperand(Operand *op);
		Operand		*getOperand();

		void		setPower(size_t pow);
		size_t		getPower();

		void		setNeg(bool n);
		bool		isNeg();
};

#endif
