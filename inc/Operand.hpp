#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "Computorv2.hpp"

class Rational;
class Complex;
class Matrix;

typedef enum	e_op
{
    UNDEFINED,
	RATIONAL,
	COMPLEX,
	MATRIX
}				t_op;

class Operand
{
	private:
		t_op	type_;
	
	public:
		Operand();
		Operand(t_op type);
		Operand(Operand &op);
		virtual ~Operand();

		void		    setType(const t_op type);
		const t_op      getType() const;
        const Operand * getSelf() const;

        bool const  isInteger(double d) const;

//		virtual Operand const * operator=( Operand const & rhs ) const = 0; // Equal
//		virtual Operand const * operator+( Operand const & rhs ) const = 0; // Sum
//		virtual Operand const * operator-( Operand const & rhs ) const = 0; // Difference
//		virtual Operand const * operator*( Operand const & rhs ) const = 0; // Product
//		virtual Operand const * operator/( Operand const & rhs ) const = 0; // Quotient
//		virtual Operand const * operator%( Operand const & rhs ) const = 0; // Modulo
};

std::ostream &operator<<(std::ostream &o, Operand const &i);

#endif
