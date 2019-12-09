#ifndef TOKEN_HPP
# define TOKEN_HPP

#include "Computorv2.hpp"
#include "Monomial.hpp"

class Monomial;

class Token
{
	typedef enum		e_type
	{
		OPERATOR,
		MONOMIAL
	}					t_type;

	private:
		t_type			type_;
		Monomial		*monomial_;

	public:
		Token();
		Token(t_type type);
		Token(t_type type,Monomial *monomial);
		~Token();

		void		setType(t_type type);
		t_type		getType();

		void		setMonomial(Monomial *monomial);
		Monomial	*getMonomial();
};

#endif
