//
// Created by Hugo JEANNIN on 12/2/19.
//

#ifndef COMPUTERV2_COMPLEX_HPP
#define COMPUTERV2_COMPLEX_HPP

#include "Operand.hpp"
#include "Computorv2.hpp"

class Complex: public Operand
{
	private:
	    double  real_part_;
	    double	complex_part_;

	public:
		Complex();
		Complex(double complex_part);
		Complex(double real_part, double complex_part);
		Complex(Complex &cmp);
        Complex(const Operand *op);
		~Complex();

		Operand const * operator=( Operand const & rhs ); // Equal
		Operand const * operator+( Operand const & rhs ); // Sum
//		Operand const * operator-( Operand const & rhs ); // Difference
//		Operand const * operator*( Operand const & rhs ); // Product
//		Operand const * operator/( Operand const & rhs ); // Quotient
//		Operand const * operator%( Operand const & rhs ); // Modulo

		void	setRealPart(double n);
		double	getRealPart() const;
		void	setComplexPart(double n);
		double	getComplexPart() const;
};

std::ostream &operator<<(std::ostream &o, Complex const &i);

#endif //COMPUTERV2_COMPLEX_HPP
