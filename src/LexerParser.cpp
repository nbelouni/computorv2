#include "../inc/LexerParser.hpp"

LexerParser::LexerParser()
{
	lexems_ref_.push_back(LexerParser::t_lexem{"[", O_BRACKET_L});
	lexems_ref_.push_back(LexerParser::t_lexem{"]", C_BRACKET_L});
	lexems_ref_.push_back(LexerParser::t_lexem{"(", O_PAR_L});
	lexems_ref_.push_back(LexerParser::t_lexem{")", C_PAR_L});
	lexems_ref_.push_back(LexerParser::t_lexem{"*", MUL_L});
	lexems_ref_.push_back(LexerParser::t_lexem{"^", POW_L});
	lexems_ref_.push_back(LexerParser::t_lexem{"+", SUM_L});
	lexems_ref_.push_back(LexerParser::t_lexem{"/", DIV_L});
	lexems_ref_.push_back(LexerParser::t_lexem{"-", SUB_L});
	lexems_ref_.push_back(LexerParser::t_lexem{"%", MOD_L});
	lexems_ref_.push_back(LexerParser::t_lexem{"=", ASSIGN_L});
	lexems_ref_.push_back(LexerParser::t_lexem{"[a-z_]", ALPHA_L});
	lexems_ref_.push_back(LexerParser::t_lexem{"[0-9]", NUMBER_L});
	lexems_ref_.push_back(LexerParser::t_lexem{"?", INT_POINT_L});
	lexems_ref_.push_back(LexerParser::t_lexem{",", COMMA_L});
	lexems_ref_.push_back(LexerParser::t_lexem{";", SEMICOL_L});
}

LexerParser::LexerParser(LexerParser &lp)
{
	*this = lp;
}

LexerParser::~LexerParser()
{
	lexems_ref_.clear();
	lexems_.clear();
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
}

const char							*LexerParser::lexemDefToString(t_lexem_def l)
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
		case NUMBER_L:
			return "NUMBER_L";
		case INT_POINT_L:
			return "INT_POINT_L";
		case COMMA_L:
			return "COMMA_L";
		case SEMICOL_L:
			return "SEMICOL_L";
		default:
			return "NONE";
	}
}

void								LexerParser::printLexems()
{
	for (int i = 0; i < lexems_.size(); ++i)
	{
		std::cout << "value : " << lexems_[i].first;
		std::cout << " - ";
		std::cout << "type : " << lexemDefToString(lexems_[i].second);
		std::cout << std::endl;
	}
}

void								LexerParser::lineToLexems(std::string &s)
{
	std::string::iterator 		it = s.begin();
	LexerParser::t_lexem_def	tmp_lexem;
	std::string					unknown_char;

	while (it != s.end())
	{
		tmp_lexem = NONE;
		if (*it != ' ' && *it !='\t')
		{
			if ((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z') || *it == '_')
			{
				tmp_lexem = ALPHA_L;
			}
			else if (*it >= '0' && *it <= '9')
			{
				tmp_lexem = NUMBER_L;
			}
			else
			{
				for (int j = 0; j < lexems_ref_.size(); ++j)
				{
					if (*it == lexems_ref_[j].first[0])
					{
						tmp_lexem = static_cast<LexerParser::t_lexem_def>(j);
						break;
					}
				}
			}
			if (tmp_lexem != NONE)
			{
				lexems_.push_back(LexerParser::t_lexem{std::string(1, *it), tmp_lexem});
			}
			else
			{
				unknown_char.append("\'");
				unknown_char.append(1, *it);
				unknown_char.append("\' ");
			}
		}
		it++;
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
		printLexems();
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

