//
// Created by Hugo JEANNIN on 12/2/19.
//

#ifndef COMPUTERV2_COMPLEX_HPP
#define COMPUTERV2_COMPLEX_HPP

#include "Computorv2.hpp"
#include "Operand.hpp"

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
		Operand * operator/( Operand const & rhs ); // Quotient
		Operand * operator%( Operand const & rhs ); // Modulo

		void	setRationalPart(double n);
		double	getRationalPart() const;
		void	setImaginaryPart(double n);
		double	getImaginaryPart() const;

        Complex *solveMul(double lhs_rational, double lhs_imaginary, double rhs_rational, double rhs_imaginary);
        static Complex *solveDiv(double lhs_rational, double lhs_imaginary, double rhs_rational, double rhs_imaginary);
        static std::ostream &print(std::ostream &o, Operand const &i);

        Operand *endCheck(Complex *cp);
};

std::ostream &operator<<(std::ostream &o, Complex const &i);

#endif //COMPUTERV2_COMPLEX_HPP
