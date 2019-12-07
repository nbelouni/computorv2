//
// Created by Hugo JEANNIN on 12/2/19.
//

#ifndef COMPUTERV2_REAL_HPP
#define COMPUTERV2_REAL_HPP

#include "Operand.hpp"
#include "Computorv2.hpp"

class Real: public Operand
{
	private:
        double	value_;
		int		power_;

	public:
		Real();
		Real(double value); // power == 1
		Real(double value, int power);
		Real(Real &real);
        Real(const Operand *op);
		virtual ~Real();

		Operand * operator=( Operand const & rhs ); // Equal
		Operand * operator+( Operand const & rhs ); // Sum
		Operand * operator-( Operand const & rhs ); // Difference
//		Operand const * operator*( Operand const & rhs ); // Product
//		Operand const * operator/( Operand const & rhs ); // Quotient
//		Operand const * operator%( Operand const & rhs ); // Modulo

        const double      computePower() const;
//        void        add(Real &lhs, Real &rhs);
//        void        add(Complex &lhs, Real &rhs);

		void		setValue(double value);
		double		getValue() const;
		void		setPower(int power);
		int			getPower() const;
};

std::ostream &operator<<(std::ostream &o, Real const &i);

#endif //COMPUTERV2_REAL_HPP
