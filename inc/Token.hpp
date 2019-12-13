#ifndef TOKEN_HPP
# define TOKEN_HPP

#include "Computorv2.hpp"
#include "Monomial.hpp"

class Monomial;

class Token
{
	public:
		typedef enum		e_type
		{
			O_PAR,		//	(	OK
			C_PAR,		//	)	OK
			MUL,		//	*	OK
			POW,		//	^	OK
			SUM,		//	+	OK
			DIV,		//	/	OK
			SUB,		//	-	OK
			MOD,		//	%	OK
			DOUBLE_MUL,	//	**	OK
			MONOMIAL,
			UNKNOWN
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
