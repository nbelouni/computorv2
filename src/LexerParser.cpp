#include "../inc/LexerParser.hpp"

LexerParser::LexerParser()
{
	state_ = NONE;
	brackets_ = 0;
	par_ = 0;

	lexems_ref_.push_back(LexerParser::t_s_lexem{"[", O_BRACKET_L, &LexerParser::setLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"]", C_BRACKET_L, &LexerParser::setLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"(", O_PAR_L, &LexerParser::setLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{")", C_PAR_L, &LexerParser::setLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"*", MUL_L, &LexerParser::isMul});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"^", POW_L, &LexerParser::setLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"+", SUM_L, &LexerParser::setLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"/", DIV_L, &LexerParser::setLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"-", SUB_L, &LexerParser::setLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"%", MOD_L, &LexerParser::setLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"=", EQUAL_L, &LexerParser::setLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"[a-z_]", ALPHA_L, &LexerParser::isVar});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"[0-9]", DIGIT_L, &LexerParser::isNumber});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"?", INT_POINT_L, &LexerParser::isIntPoint});
	lexems_ref_.push_back(LexerParser::t_s_lexem{",", COMMA_L, &LexerParser::setLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{";", SEMICOL_L, &LexerParser::setLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{".", POINT_L, &LexerParser::isDecimal});

	tokens_ref_.push_back(LexerParser::t_s_token{O_PAR, 1});
	tokens_ref_.push_back(LexerParser::t_s_token{C_PAR, 1});
	tokens_ref_.push_back(LexerParser::t_s_token{MUL, 1});
	tokens_ref_.push_back(LexerParser::t_s_token{POW, 1});
	tokens_ref_.push_back(LexerParser::t_s_token{SUM, 1});
	tokens_ref_.push_back(LexerParser::t_s_token{DIV, 1});
	tokens_ref_.push_back(LexerParser::t_s_token{SUB, 1});
	tokens_ref_.push_back(LexerParser::t_s_token{MOD, 1});
	tokens_ref_.push_back(LexerParser::t_s_token{DOUBLE_MUL, 2});
	tokens_ref_.push_back(LexerParser::t_s_token{POWER, 255});
	tokens_ref_.push_back(LexerParser::t_s_token{MATRIX_ROW, 255});
	tokens_ref_.push_back(LexerParser::t_s_token{O_BRACKET, 1});
	tokens_ref_.push_back(LexerParser::t_s_token{C_BRACKET, 1});
	tokens_ref_.push_back(LexerParser::t_s_token{COMMA, 1});
	tokens_ref_.push_back(LexerParser::t_s_token{SEMICOL, 1});
	tokens_ref_.push_back(LexerParser::t_s_token{INT_NUMBER, 255});
	tokens_ref_.push_back(LexerParser::t_s_token{DEC_NUMBER, 255});
	tokens_ref_.push_back(LexerParser::t_s_token{REAL, 255});
	tokens_ref_.push_back(LexerParser::t_s_token{COMPLEX, 255});
	tokens_ref_.push_back(LexerParser::t_s_token{MATRIX, 1024});
	tokens_ref_.push_back(LexerParser::t_s_token{UNKNOWN, 255});
	tokens_ref_.push_back(LexerParser::t_s_token{ASSIGN, 1});
	tokens_ref_.push_back(LexerParser::t_s_token{VAR, 255});
	tokens_ref_.push_back(LexerParser::t_s_token{FUNCTION, 255});
	tokens_ref_.push_back(LexerParser::t_s_token{GET_RESULT, 2});
	tokens_ref_.push_back(LexerParser::t_s_token{EQUATION, 4096});
	tokens_ref_.push_back(LexerParser::t_s_token{NONE, 0});
	tokens_ref_.push_back(LexerParser::t_s_token{ERROR, 0});
}

LexerParser::LexerParser(LexerParser &lp)
{
	*this = lp;
}

LexerParser::~LexerParser()
{
	clear();
	lexems_ref_.clear();
}

LexerParser							&LexerParser::operator=(LexerParser &rhs)
{
	lexems_ = rhs.getLexems();
	return *this;
}

std::vector<LexerParser::t_lexem>	LexerParser::getLexems()
{
	return lexems_;
}

void								LexerParser::clear()
{
	state_ = NONE;
	brackets_ = 0;
	par_ = 0;
	lexems_.clear();
	tokens_.clear();
}

const char							*LexerParser::charToString(t_char l)
{
	switch (l)
	{
		case O_BRACKET_L:
			return "O_BRACKET_L";
		case C_BRACKET_L:
			return "C_BRACKET_L";
		case O_PAR_L:
			return "O_PAR_L";
		case C_PAR_L:
			return "C_PAR_L";
		case MUL_L:
			return "MUL_L";
		case POW_L:
			return "POW_L";
		case SUM_L:
			return "SUM_L";
		case DIV_L:
			return "DIV_L";
		case SUB_L:
			return "SUB_L";
		case MOD_L:
			return "MOD_L";
		case EQUAL_L:
			return "EQUAL_L";
		case ALPHA_L:
			return "ALPHA_L";
		case DIGIT_L:
			return "DIGIT_L";
		case INT_POINT_L:
			return "INT_POINT_L";
		case COMMA_L:
			return "COMMA_L";
		case SEMICOL_L:
			return "SEMICOL_L";
		case POINT_L:
			return "POINT_L";
		default:
			return "UNDEFINED";
	}
}

const char							*LexerParser::tokenToString(LexerParser::t_token_def t)
{
	switch (t)
	{
		case O_PAR:
			return "O_PAR";
		case C_PAR:
			return "C_PAR";
		case MUL:
			return "MUL";
		case POW:
			return "POW";
		case SUM:
			return "SUM";
		case DIV:
			return "DIV";
		case SUB:
			return "SUB";
		case MOD:
			return "MOD";
		case DOUBLE_MUL:
			return "DOUBLE_MUL";
		case POWER:
			return "POWER";
		case MATRIX_ROW:
			return "MATRIX_ROW";
		case INT_NUMBER:
			return "INT_NUMBER";
		case DEC_NUMBER:
			return "DEC_NUMBER";
		case REAL:
			return "REAL";
		case COMPLEX:
			return "COMPLEX";
		case MATRIX:
			return "MATRIX";
		case O_BRACKET:
			return "O_BRACKET";
		case COMMA:
			return "COMMA";
		case SEMICOL:
			return "SEMICOL";
		case C_BRACKET:
			return "C_BRACKET";
		case UNKNOWN:
			return "UNKNOWN";
		case ASSIGN:
			return "ASSIGN";
		case VAR:
			return "VAR";
		case FUNCTION:
			return "FUNCTION";
		case GET_RESULT:
			return "GET_RESULT";
		case EQUATION:
			return "EQUATION";
		case NONE:
			return "NONE";
		default:
			return "ERROR";
	}
}

void								LexerParser::printLexems()
{
	for (int i = 0; i < lexems_.size(); ++i)
	{
		std::cout << "value : " << lexems_[i].first;
		std::cout << " - ";
		std::cout << "type : " << charToString(lexems_[i].second);
		std::cout << std::endl;
	}
}

void								LexerParser::printStates(std::vector<LexerParser::t_char> s)
{
	for (int i = 0; i < s.size(); ++i)
	{
		std::cout << "type : " << charToString(s[i]);
		std::cout << std::endl;
	}
}

void								LexerParser::printTokens()
{
	for (int i = 0; i < tokens_.size(); ++i)
	{
		std::cout << "value : " << tokens_[i].first;
		std::cout << " - ";
		std::cout << "type : " << tokenToString(tokens_[i].second);
		std::cout << std::endl;
	}
}

LexerParser::t_token_def			LexerParser::isNumber(LexerParser::t_char &lexem)
{
	// Number : [SUM_L|SUB_L] {DIGIT_L} [.{DIGIT_L}]
	std::cout << "isNumber()" << std::endl;

	if (state_ == VAR)
		return isVar(lexem);
	if (lexem == DIGIT_L)
	{
		if (state_ != DEC_NUMBER)
			return INT_NUMBER;
		else
			return state_;
	}
	return ERROR;
}

LexerParser::t_token_def			LexerParser::isDecimal(t_char &lexem)
{
	if (lexem == POINT_L)
	{
		if (state_ != INT_NUMBER)
			return ERROR;
		else
			return DEC_NUMBER;
	}
	return ERROR;
	
}

LexerParser::t_token_def			LexerParser::isVar(LexerParser::t_char &lexem)
{
	// Var : ALPHA_L {ALPHA_L|DIGIT_L}
	std::cout << "isVar()" << std::endl;

	if (lexem == ALPHA_L)
	{
		if (state_ != UNKNOWN && state_ != VAR)
			return UNKNOWN;
		else if (state_ == UNKNOWN)
			return VAR;
		else
			return state_;
	}
	if (state_ == VAR && lexem == DIGIT_L)
		return state_;
	return ERROR;
	
}

LexerParser::t_token_def			LexerParser::isMul(LexerParser::t_char &lexem)
{
	std::cout << "isMul()" << std::endl;

	if (lexem == MUL_L)
	{
		if (state_ == MUL)
			return DOUBLE_MUL;
		return MUL;
	}
	return ERROR;
}

LexerParser::t_token_def			LexerParser::isIntPoint(LexerParser::t_char &lexem)
{
	if (state_ == ASSIGN && lexem == INT_POINT_L)
		return GET_RESULT;
	return ERROR;
}

bool								LexerParser::isOperator(LexerParser::t_token_def t)
{
	if (t == SUM || t == SUB || t == MUL || t == DIV || t == MOD || t == DOUBLE_MUL)
		return true;
	return false;
}


LexerParser::t_token_def			LexerParser::setLiteral(t_char &lexem)
{
	switch (lexem)
	{
		case POW_L:
			return POW;
		case SUM_L:
			return SUM;
		case DIV_L:
			return DIV;
		case SUB_L:
			return SUB;
		case MOD_L:
			return MOD;
		case EQUAL_L:
			return ASSIGN;
		case O_PAR_L:
			return O_PAR;
		case C_PAR_L:
			return C_PAR;
		case O_BRACKET_L:
			return O_BRACKET;
		case C_BRACKET_L:
			return C_BRACKET;
		case COMMA_L:
			return COMMA;
		case SEMICOL_L:
			return SEMICOL;
		default:
			return ERROR;
	}
}

bool								LexerParser::isLogicSequence(LexerParser::t_token_def first, LexerParser::t_token_def next)
{
	if (first == next && tokens_ref_[first].size > 1)
		return true;
	// NUMBER : integer to decimal
	if (first == INT_NUMBER && next == DEC_NUMBER)
		return true;
	if (first == SUB && next == INT_NUMBER)
		return true;

	// VAR : unknown to var
	if (first == UNKNOWN && next == VAR)
		return true;

	// MUL : mul to double_mul
	if (first == MUL && next == DOUBLE_MUL)
		return true;

	// EQUAL : assign to get_result
	if (first == ASSIGN && next == GET_RESULT)
		return true;

	return false;
}

LexerParser::t_char					LexerParser::setLexem(const char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
	{
		return ALPHA_L;
	}
	else if (c >= '0' && c <= '9')
	{
		return DIGIT_L;
	}
	else
	{
		for (int i = 0; i < lexems_ref_.size(); ++i)
		{
			if (c == lexems_ref_[i].value[0])
			{
				return static_cast<LexerParser::t_char>(i);
			}
		}
	}
	return UNDEFINED;
}

void								LexerParser::lineToTokens(std::string &s)
{
	std::string::iterator 		it = s.begin();
	LexerParser::t_char			tmp_lexem;
	std::string					unknown_char;
	std::string					current_token;
	LexerParser::t_token_def	old_state;

	while (it != s.end())
	{
		tmp_lexem = UNDEFINED;
		old_state = state_;
		if (*it != ' ' && *it !='\t')
		{
			tmp_lexem = setLexem(*it);
			if (tmp_lexem != UNDEFINED)
			{
				if (this->lexems_ref_[tmp_lexem].f != nullptr)
				{
					state_ = (this->*lexems_ref_[tmp_lexem].f)(tmp_lexem);
				}
				else
				{
					tmp_lexem = UNDEFINED;
				}
			}
			if (tmp_lexem == UNDEFINED)
			{
				unknown_char.append("\'");
				unknown_char.append(1, *it);
				unknown_char.append("\' ");
			}
			if (state_ == ERROR)
			{
				unknown_char.append("Should never happen.");
			}
			
			if (state_ != ERROR && state_ != NONE)
			{
				if (!current_token.empty() && !isLogicSequence(old_state, state_))
				{
					tokens_.push_back(LexerParser::t_token{std::string(current_token), old_state});
					current_token.clear();
				}
				current_token.append(1, *it);
			}
		}
		else
		{ 
			if (!current_token.empty())
			{
				tokens_.push_back(LexerParser::t_token{std::string(current_token), old_state});
				current_token.clear();
			}
			state_ = NONE;
		}
		it++;
	}
	if (!current_token.empty())
	{
		tokens_.push_back(LexerParser::t_token{std::string(current_token), state_});
	}
	if (!unknown_char.empty())
	{
		try
		{
			throw InvalidLineException("Unknown identifiers : " + unknown_char);
		}
		catch (std::exception &e)
		{
			std::rethrow_exception(std::current_exception());
		}
	}
	else
	{
		printTokens();
	}
}

LexerParser::InvalidLineException::InvalidLineException(std::string errors)
{
	_message = errors.c_str();
}

LexerParser::InvalidLineException::InvalidLineException(InvalidLineException const &i)
{
	*this = i;
}

LexerParser::InvalidLineException::~InvalidLineException() throw()
{
}

LexerParser::InvalidLineException &LexerParser::InvalidLineException::operator=(InvalidLineException const &d)
{
	(void)d;
	return *this;
}

char const	*LexerParser::InvalidLineException::what() const throw()
{
	return _message;
}

