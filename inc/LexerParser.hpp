#ifndef LEXER_PARSER_HPP
# define LEXER_PARSER_HPP

#include "Computorv2.hpp"
#include "Variable.hpp"

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
	//	OPERATOR

		O_PAR,		//	(	OK
		C_PAR,		//	)	OK
		MUL,		//	*	OK
		POW,		//	^	OK
		SUM,		//	+	OK
		DIV,		//	/	OK
		SUB,		//	-	OK
		MOD,		//	%	OK
		DOUBLE_MUL,	//	**	OK

	//	NAN

		NEG,		//	-	OK
		POWER,		//	POW INT_NUMBER
		MATRIX_ROW,	//	O_BRACKET REAL (COMMA REAL)* C_BRACKET
		O_BRACKET,	//	[	OK
		C_BRACKET,	//	]	OK
		COMMA,		//	,	OK
		SEMICOL,	//	;	OK
		

	//	OPERANDS

		INT_NUMBER,	//	OK
		DEC_NUMBER,	//	OK
		REAL, 		//	[INT_NUMBER DEC_NUMBER]
		COMPLEX,	//	(REAL)?i (POWER)?
		MATRIX,		//	O_BRACKET MATRIX_ROW (SEMICOL MATRIX_ROW)+ C_BRACKET

	//	MONOMIAL

		UNKNOWN,	//	(SUB)? VAR (POWER)?	OK
		MONOMIAL,	//	[OPERAND UNKNOWN]

	//	OTHERS

		ASSIGN,		//	OK
		VAR,		//	OK
		FUNCTION,	//	VAR O_PAR (VAR|UNKNOWN) C_PAR
		GET_RESULT,	//	OK

		EQUATION,	//	(O_PAR)? OPERAND (C_PAR)? ((OPERATOR)? EQUATION)? (C_PAR if O_PAR == true)
		NONE,
		BEGIN,
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
		void (LexerParser::*f)();
	}				t_s_token;

	private:
		std::vector<t_s_lexem>	lexems_ref_;
		std::vector<t_lexem>	lexems_;
		std::vector<t_s_token>	tokens_ref_;
		std::vector<t_token>	tokens_;
		t_token_def				state_;
		int						brackets_;
		int						par_;
		std::vector<LexerParser::t_token>::iterator it_;
		std::stack<t_token *>	fill_it_;
		
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
		void					printToken(t_token t);
		void					printTokens();
		void					printStates(std::vector<t_char> s);

		void					lineToTokens(std::string &s);
		t_char					setLexem(const char c);

		t_token_def				isNumber(t_char &l);
		t_token_def				isDecimal(t_char &l);
		t_token_def				isVar(t_char &l);
		t_token_def				isMul(t_char &l);
		t_token_def				isSub(t_char &l);
		t_token_def				isLiteral(t_char &lexem);

		bool					isLogicSequence(t_token_def first, t_token_def next);

		Variable				parse();
		bool					isOperator(t_token_def t);
		bool					isOperand(t_token_def t);

		bool					nextIsEnd();
		void					push();
		void					fill();
		void					findNext();
		void					subAndNext();
		void					modAndNext();
		void					divAndNext();
		void					sumAndNext();
		void					powAndNext();
		void					varAndNext();
		void					realAndNext();

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
