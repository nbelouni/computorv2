//
// Created by Hugo JEANNIN on 12/2/19.
//

#ifndef COMPUTERV2_REAL_HPP
#define COMPUTERV2_REAL_HPP

#include "Computor.hpp"
#include "Operand.hpp"

class Real: Operand
{
	private:
	    double	_value;
		int		_power;

	public:
		Real();
		Real(double value); // power == 1
		Real(double value, int power);
		Real(Real &real);
		virtual ~Real();

//		Operand const * operator=(Operand const & rhs ); // Sum
//		Operand const * operator+( Operand const & rhs ); // Sum
//		Operand const * operator-( Operand const & rhs ); // Difference
//		Operand const * operator*( Operand const & rhs ); // Product
//		Operand const * operator/( Operand const & rhs ); // Quotient
//		Operand const * operator%( Operand const & rhs ); // Modulo

		void		setValue(double value);
		double		getValue() const;
		void		setPower(int power);
		int			getPower() const;
};

std::ostream &operator<<(std::ostream &o, Real const &i);

#endif //COMPUTERV2_REAL_HPP
