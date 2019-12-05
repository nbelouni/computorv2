#ifndef LEXER_PARSER_HPP
# define LEXER_PARSER_HPP

#include "Computorv2.hpp"

#include "vector"

class LexerParser
{
	/*
	**	LEXEM : base entity
	*/
	typedef	enum	e_lexem
	{
		O_BRACKET_L,//	[
		C_BRACKET_L,//	]
		O_PAR_L,	//	(
		C_PAR_L,	//	)
		MUL_L,		//	*
		POW_L,		//	^
		SUM_L,		//	+
		DIV_L,		//	/
		SUB_L,		//	-
		MOD_L,		//	%
		ASSIGN_L,	//	=
		ALPHA_L,	//	[a-z_]
		NUMBER_L,	//	[0-9]
		INT_POINT_L,//	?
		COMMA_L,	//	_L,
		SEMICOL_L,	//	;
		NONE
	}				t_lexem_def;

	typedef	std::pair<std::string, t_lexem_def>		t_lexem;

	/*
	**	TOKEN : sets of lexems
	*/
	typedef enum	e_token
	{
	//	OPERATORS

		O_PAR,		//	(
		C_PAR,		//	)
		MUL,		//	*
		POW,		//	^
		SUM,		//	+
		DIV,		//	/
		SUB,		//	-
		MOD,		//	%
		DOUBLE_MUL,	//	**

	//	NAN

		POWER,		//	POW_L[-\+]?[\d]+
		MATRIX_ROW,	//	O_BRACKET_L DECIMAL (COMMA_L DECIMAL)* C_BRACKET_L

	//	OPERANDS

		DECIMAL,	//	([-\+])?[\d]+(\.[\d]+)?
		REAL, 		//	DECIMAL (POWER)?
		COMPLEX,	//	(DECIMAL [AND_L OR_L])? (DECIMAL)?i (POWER)?
		MAXTRIX,	//	O_BRACKET_L MATRIX_ROW (SEMICOL_L MATRIX_ROW)+ C_BRACKET_L
		UNKNOWN,	//	[a-z] (POWER)?

	//	OTHERS

		ASSIGN,		//	EQUAL_L
		VAR,		//	ALPHA_L [ALPHA_L NUMBER_L]+
		FUNCTION,	//	VAR O_PAR_L (VAR|UNKNOWN) C_PAR_L
		GET_RESULT,	//	EQUAL_L INT_POINT_L
		EQUATION	//	(O_PAR_L)? OPERAND (C_PAR_L)? ((OPERATOR)? EQUATION)? (C_PAR_L if O_PAR_L == true)
	}				t_token_def;

	private:
		std::vector<t_lexem>	lexems_ref_;
		std::vector<t_lexem>	lexems_;
		
		LexerParser(LexerParser &lp);
		

	public:
		LexerParser();
		~LexerParser();

		LexerParser				&operator=(LexerParser &rhs);

		std::vector<t_lexem>	getLexems();	
		void					clear();
		const char				*lexemDefToString(t_lexem_def l);
		void					printLexems();
		void					lineToLexems(std::string &s);

		class	InvalidLineException : public std::exception
		{
			private:
				std::vector<std::string>	_messages;
				const char					*_message;

			public:
				InvalidLineException(std::string errors);
				InvalidLineException(InvalidLineException const &);
				virtual ~InvalidLineException() throw();
				virtual const char *what() const throw();
		
			private:
			InvalidLineException &operator=(InvalidLineException const &);
		};
};

#endif
