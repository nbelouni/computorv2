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
	    double	imaginary_part_;

	public:
		Complex();
		Complex(double imaginary_part);
		Complex(double real_part, double imaginary_part);
		Complex(Complex &cmp);
        Complex(const Operand *op);
		~Complex();

		Operand * operator=( Operand const & rhs ); // Equal
		Operand * operator+( Operand const & rhs ); // Sum
		Operand * operator-( Operand const & rhs ); // Difference
		Operand * operator*( Operand const & rhs ); // Product
//		Operand * operator/( Operand const & rhs ); // Quotient
//		Operand * operator%( Operand const & rhs ); // Modulo

		void	setRealPart(double n);
		double	getRealPart() const;
		void	setImaginaryPart(double n);
		double	getImaginaryPart() const;
};

std::ostream &operator<<(std::ostream &o, Complex const &i);

#endif //COMPUTERV2_COMPLEX_HPP
