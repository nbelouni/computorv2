//
// Created by Hugo JEANNIN on 12/2/19.
//

#ifndef COMPUTERV2_REAL_HPP
#define COMPUTERV2_REAL_HPP

#include "Operand.hpp"
#include "Computorv2.hpp"

class Rational: public Operand
{
	private:
        double	value_;

	public:
		Rational();
		Rational(double value);
        Rational(int value);
		Rational(Rational &real);
        Rational(const Operand *op);
		virtual ~Rational();

		Operand * operator=( Operand const & rhs ); // Equal
		Operand * operator+( Operand const & rhs ); // Sum
		Operand * operator-( Operand const & rhs ); // Difference
		Operand * operator*( Operand const & rhs ); // Product
		Operand * operator/( Operand const & rhs ); // Quotient
		Operand * operator%( Operand const & rhs ); // Modulo

		void		setValue(double value);
		double		getValue() const;

        bool const  isInteger() const;
        void        reset();
};

std::ostream &operator<<(std::ostream &o, Rational const &i);

#endif //COMPUTERV2_REAL_HPP
