#ifndef LEXER_PARSER_HPP
# define LEXER_PARSER_HPP

#include "Computorv2.hpp"

#include <vector>

class LexerParser
{
	/*
	**	LEXEM : base entity
	*/
	typedef	enum	e_char
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
		EQUAL_L,	//	=
		ALPHA_L,	//	[a-z_]
		DIGIT_L,	//	[0-9]
		INT_POINT_L,//	?
		COMMA_L,	//	_L,
		SEMICOL_L,	//	;
		POINT_L,	//	.
		UNDEFINED
	}				t_char;

	typedef	std::pair<std::string, t_char>		t_lexem;

	/*
	**	TOKEN : sets of lexems
	*/
	typedef enum	e_token
	{
	//	OPERATORS

		O_PAR,		//	(	OK
		C_PAR,		//	)		OK
		MUL,		//	*	OK
		POW,		//	^	OK
		SUM,		//	+	OK
		DIV,		//	/	OK
		SUB,		//	-	OK
		MOD,		//	%	OK
		DOUBLE_MUL,	//	**	OK

	//	NAN

		POWER,		//	POW_L[-\+]?[\d]+
		MATRIX_ROW,	//	O_BRACKET_L NUMBER (COMMA_L NUMBER)* C_BRACKET_L
		O_BRACKET,	//	[	OK
		C_BRACKET,	//	]	OK
		COMMA,		//	,	OK
		SEMICOL,	//	;	OK
		

	//	OPERANDS

		INT_NUMBER,		//	OK
		DEC_NUMBER,		//	OK
		REAL, 		//	NUMBER (POWER)?
		COMPLEX,	//	(NUMBER [AND_L OR_L])? (NUMBER)?i (POWER)?
		MATRIX,	//	O_BRACKET_L MATRIX_ROW (SEMICOL_L MATRIX_ROW)+ C_BRACKET_L
		UNKNOWN,	//	[a-z] (POWER)?	OK

	//	OTHERS

		ASSIGN,		//	EQUAL_L	OK
		VAR,		//	OK 	OK
		FUNCTION,	//	VAR O_PAR_L (VAR|UNKNOWN) C_PAR_L
		GET_RESULT,	//	EQUAL_L INT_POINT_L	OK

		EQUATION,	//	(O_PAR_L)? OPERAND (C_PAR_L)? ((OPERATOR)? EQUATION)? (C_PAR_L if O_PAR_L == true)
		NONE,
		ERROR
	}				t_token_def;

	typedef	std::pair<std::string, t_token_def>		t_token;

	typedef	struct	s_lexem_ref
	{
		std::string	value;
		t_char		type;
		t_token_def (LexerParser::*f)(t_char &);
	}				t_s_lexem;

	typedef	struct	s_token
	{
		t_token_def	type;
		size_t		size;
	}				t_s_token;

	private:
		std::vector<t_s_lexem>	lexems_ref_;
		std::vector<t_lexem>	lexems_;
		std::vector<t_s_token>	tokens_ref_;
		std::vector<t_token>	tokens_;
		t_token_def				state_;
		int						brackets_;
		int						par_;
		
		LexerParser(LexerParser &lp);
		

	public:
		LexerParser();
		~LexerParser();

		LexerParser				&operator=(LexerParser &rhs);

		std::vector<t_lexem>	getLexems();	
		void					clear();

		const char				*charToString(t_char l);
		const char				*tokenToString(t_token_def t);
		void					printLexems();
		void					printTokens();
		void					printStates(std::vector<t_char> s);

		void					lineToTokens(std::string &s);
		t_char					setLexem(const char c);

		t_token_def				isNumber(t_char &l);
		t_token_def				isDecimal(t_char &l);
		t_token_def				isVar(t_char &l);
		t_token_def				isMul(t_char &l);
		t_token_def				isLiteral(t_char &lexem);

		bool					isLogicSequence(t_token_def first, t_token_def next);
		bool					isOperator(t_token_def t);

//		std::vector<Token>		parse();

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
