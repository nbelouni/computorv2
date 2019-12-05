#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "Operand.hpp"

typedef enum	e_op
{
	REAL,
	COMPLEX,
	MATRIX
}				t_op;

class Operand
{
	private:
		t_op	_type;
	
	public:
		Operand();
		Operand(t_op type);
		Operand(Operand &op);
		virtual ~Operand();

		void		setType(const t_op type);
		const t_op  getType() const;
	
//		virtual Operand const * operator=( Operand const & rhs ) const = 0; // Equal
//		virtual Operand const * operator+( Operand const & rhs ) const = 0; // Sum
//		virtual Operand const * operator-( Operand const & rhs ) const = 0; // Difference
//		virtual Operand const * operator*( Operand const & rhs ) const = 0; // Product
//		virtual Operand const * operator/( Operand const & rhs ) const = 0; // Quotient
//		virtual Operand const * operator%( Operand const & rhs ) const = 0; // Modulo
};

#endif
