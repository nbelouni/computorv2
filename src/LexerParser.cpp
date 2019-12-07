#include "../inc/LexerParser.hpp"

LexerParser::LexerParser()
{
	state_ = NONE;
	lexems_ref_.push_back(LexerParser::t_s_lexem{"[", O_BRACKET_L, nullptr});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"]", C_BRACKET_L, nullptr});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"(", O_PAR_L, nullptr});
	lexems_ref_.push_back(LexerParser::t_s_lexem{")", C_PAR_L, nullptr});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"*", MUL_L, nullptr});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"^", POW_L, nullptr});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"+", SUM_L, &LexerParser::isSum});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"/", DIV_L, &LexerParser::isDiv});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"-", SUB_L, nullptr});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"%", MOD_L, nullptr});
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
	tokens_ref_.push_back(LexerParser::t_s_token{NUMBER, 255});
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
		case NUMBER:
			return "NUMBER";
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

LexerParser::t_token_def			LexerParser::isNumber(std::vector<LexerParser::t_char> &states)
{
	// Number : [SUM_L|SUB_L] {DIGIT_L} [.{DIGIT_L}]
	std::cout << "isNumber()" << std::endl;

	std::vector<LexerParser::t_char>::iterator	it = states.begin();

	printStates(states);
	if (state_ == VAR)
		return isVar(states);
	if (*it ==SUB_L)
		it++;
	while (!IS_END(it, states) && *it == DIGIT_L)
		it++;
	if (!IS_END(it, states))
		return ERROR;
	return NUMBER;
	
}

LexerParser::t_token_def			LexerParser::isDecimal(std::vector<LexerParser::t_char> &states)
{
	std::vector<LexerParser::t_char>::iterator	it = states.begin();

	if (*it == POINT_L)
	{
		if (state_ != NUMBER)
			return ERROR;
		if (!IS_END(it, states))
		{
			it++;
			// SOUCIS ICI
			return isNumber(&(states.at(it - states.begin())));
		}
	}
	if (!IS_END(it, states))
		return ERROR;
	return NUMBER;
	
}

LexerParser::t_token_def			LexerParser::isVar(std::vector<LexerParser::t_char> &states)
{
	// Var : ALPHA_L {ALPHA_L|DIGIT_L}
	std::cout << "isVar()" << std::endl;

	std::vector<LexerParser::t_char>::iterator	it = states.begin();

	printStates(states);
	if (!IS_END(it, states) && *it == ALPHA_L)
		*it++;
	while (!IS_END(it, states) && (*it == ALPHA_L || *it == DIGIT_L))
		*it++;
	if (!IS_END(it, states) && it != states.end())
		return ERROR;
	return VAR;
	
}

//	isOperator

//LexerParser::t_token_def			LexerParser::isMul(std::vector<LexerParser::t_char> &states)
//{
//}
//LexerParser::t_token_def			LexerParser::isPow(std::vector<LexerParser::t_char> &states)
//{
//}

LexerParser::t_token_def			LexerParser::isSum(std::vector<LexerParser::t_char> &states)
{
	// SUM : +
	std::cout << "isSum()" << std::endl;

	std::vector<LexerParser::t_char>::iterator	it = states.begin();

	printStates(states);
	if (!IS_END(it, states) && *it == SUM_L)
		*it++;
	if (!IS_END(it, states) && it != states.end())
		return ERROR;
	return SUM;
}

LexerParser::t_token_def			LexerParser::isDiv(std::vector<LexerParser::t_char> &states)
{
	std::cout << "isDiv()" << std::endl;

	std::vector<LexerParser::t_char>::iterator	it = states.begin();

	printStates(states);
	if (!IS_END(it, states) && *it == DIV_L)
		*it++;
	if (!IS_END(it, states) && it != states.end())
		return ERROR;
	return DIV;
}

//LexerParser::t_token_def			LexerParser::isSub(std::vector<LexerParser::t_char> &states)
//{
//}
//LexerParser::t_token_def			LexerParser::isMod(std::vector<LexerParser::t_char> &states)
//{
//}
void								LexerParser::lineToTokens(std::string &s)
{
	std::string::iterator 				it = s.begin();
	LexerParser::t_char					tmp_lexem;
	std::string							unknown_char;
	std::vector<LexerParser::t_char>	states;
	std::string							current_token;
	LexerParser::t_token_def			old_state;

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
				states.push_back(tmp_lexem);
				std::cout << "tmp_lexem : " << tmp_lexem  << std::endl;
				if (this->lexems_ref_[tmp_lexem].f != nullptr)
					state_ = (this->*lexems_ref_[tmp_lexem].f)(states);
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

			if (state_ != ERROR && state_ != NONE)
			{
				if ((old_state == NONE || state_ == old_state) && states.size() <= tokens_ref_[state_].size)
				{
					current_token.append(1, *it);
				}
				else if (!current_token.empty())
				{
					std::cout << "_________1" << std::endl;
					tokens_.push_back(LexerParser::t_token{std::string(current_token), old_state});
					current_token.clear();
					states.clear();
					current_token.append(1, *it);
					states.push_back(tmp_lexem);
			printTokens();
				}
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
				states.clear();
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

