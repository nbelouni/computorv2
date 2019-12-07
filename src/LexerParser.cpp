#include "../inc/LexerParser.hpp"

LexerParser::LexerParser()
{
	state_ = NONE;
	lexems_ref_.push_back(LexerParser::t_s_lexem{"[", O_BRACKET_L, nullptr});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"]", C_BRACKET_L, nullptr});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"(", O_PAR_L, nullptr});
	lexems_ref_.push_back(LexerParser::t_s_lexem{")", C_PAR_L, nullptr});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"*", MUL_L, &LexerParser::isMul});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"^", POW_L, &LexerParser::isPow});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"+", SUM_L, &LexerParser::isSum});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"/", DIV_L, &LexerParser::isDiv});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"-", SUB_L, &LexerParser::isSub});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"%", MOD_L, &LexerParser::isMod});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"=", ASSIGN_L, nullptr});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"[a-z_]", ALPHA_L, &LexerParser::isVar});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"[0-9]", DIGIT_L, &LexerParser::isNumber});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"?", INT_POINT_L, nullptr});
	lexems_ref_.push_back(LexerParser::t_s_lexem{",", COMMA_L, nullptr});
	lexems_ref_.push_back(LexerParser::t_s_lexem{";", SEMICOL_L, nullptr});
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
	lexems_.clear();
	tokens_.clear();
	state_ = NONE;
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
		case ASSIGN_L:
			return "ASSIGN_L";
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

# define	IS_END(x, y)	(x != y.end())

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

//	isOperator

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
LexerParser::t_token_def			LexerParser::isPow(LexerParser::t_char &lexem)
{
	if (lexem == POW_L)
		return POW;
	return ERROR;
}

LexerParser::t_token_def			LexerParser::isSum(LexerParser::t_char &lexem)
{
	// SUM : +
	std::cout << "isSum()" << std::endl;
	if (lexem == SUM_L)
		return SUM;
	return ERROR;
}

LexerParser::t_token_def			LexerParser::isDiv(LexerParser::t_char &lexem)
{
	std::cout << "isDiv()" << std::endl;

	if (lexem == DIV_L)
		return DIV;
	return ERROR;
}

LexerParser::t_token_def			LexerParser::isSub(LexerParser::t_char &lexem)
{
	if (lexem == SUB_L)
		return SUB;
	return ERROR;
}

LexerParser::t_token_def			LexerParser::isMod(LexerParser::t_char &lexem)
{
	if (lexem == MOD_L)
		return MOD;
	return ERROR;
}

bool								LexerParser::isOperator(LexerParser::t_token_def t)
{
	if (t == SUM || t == SUB || t == MUL || t == DIV || t == MOD || t == DOUBLE_MUL)
		return true;
	return false;
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

	return false;
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
			if ((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z') || *it == '_')
			{
				tmp_lexem = ALPHA_L;
			}

			else if (*it >= '0' && *it <= '9')
			{
				tmp_lexem = DIGIT_L;
			}
			else
			{
				for (int j = 0; j < lexems_ref_.size(); ++j)
				{
					if (*it == lexems_ref_[j].value[0])
					{
						tmp_lexem = static_cast<LexerParser::t_char>(j);
						break;
					}
				}
			}
			if (tmp_lexem != UNDEFINED)
			{
				std::cout << "tmp_lexem : " << charToString(tmp_lexem)  << std::endl;
				if (this->lexems_ref_[tmp_lexem].f != nullptr)
				{
					state_ = (this->*lexems_ref_[tmp_lexem].f)(tmp_lexem);
				}
				else
				{
					std::cout << "function for " << charToString(tmp_lexem) << " not implemented yet." << std::endl;
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
				std::cerr << "ERROR" << std::endl;
				return;
			}
			
			std::cout << "state_ : " << tokenToString(state_) << std::endl;
			std::cout << "old_state : " << tokenToString(old_state) << std::endl;

			if (state_ != ERROR && state_ != NONE)
			{
				if (!current_token.empty() && !isLogicSequence(old_state, state_))
				{
					std::cout << "_________1" << std::endl;
					tokens_.push_back(LexerParser::t_token{std::string(current_token), old_state});
					current_token.clear();
					printTokens();
				}
				current_token.append(1, *it);
			}
		}
		else
		{ 
			if (!current_token.empty())
			{
					std::cout << "_________2" << std::endl;
				std::cout << "token size : " << current_token.size() << std::endl;
				tokens_.push_back(LexerParser::t_token{std::string(current_token), old_state});
				current_token.clear();
				printTokens();
			}
			state_ = NONE;
		}
		it++;
	}
	if (!current_token.empty())
	{
					std::cout << "_________3" << std::endl;
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
		std::cout << "print tokens ?" << std::endl;
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

