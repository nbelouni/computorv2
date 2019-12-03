//
// Created by Hugo JEANNIN on 12/2/19.
//

#ifndef COMPUTERV2_COMPLEX_HPP
#define COMPUTERV2_COMPLEX_HPP

#include <iostream>
#include "Operand.hpp"

class Complex: Operand
{
	private:
	    double  _real_part;
	    double	_complex_part;

	public:
		Complex();
		Complex(double real_part, double complex_part);
		Complex(Complex &cmp);
		~Complex();

		Operand const * operator=( Operand const & rhs ); // Sum
		Operand const * operator+( Operand const & rhs ); // Sum
		Operand const * operator-( Operand const & rhs ); // Difference
		Operand const * operator*( Operand const & rhs ); // Product
		Operand const * operator/( Operand const & rhs ); // Quotient
		Operand const * operator%( Operand const & rhs ); // Modulo

		void	setRealPart(double n);
		double	getRealPart();
		void	setComplexPart(double n);
		double	getComplexPart();
};

#endif //COMPUTERV2_COMPLEX_HPP
