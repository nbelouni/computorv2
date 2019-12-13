#include "../inc/LexerParser.hpp"

LexerParser::LexerParser()
{
	state_ = NONE;
	brackets_ = 0;
	par_ = 0;

	lexems_ref_.push_back(LexerParser::t_s_lexem{"[", O_BRACKET_L, &LexerParser::isLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"]", C_BRACKET_L, &LexerParser::isLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"(", O_PAR_L, &LexerParser::isLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{")", C_PAR_L, &LexerParser::isLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"*", MUL_L, &LexerParser::isMul});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"^", POW_L, &LexerParser::isLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"+", SUM_L, &LexerParser::isLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"/", DIV_L, &LexerParser::isLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"-", SUB_L, &LexerParser::isSub});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"%", MOD_L, &LexerParser::isLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"=", EQUAL_L, &LexerParser::isLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"[a-z_]", ALPHA_L, &LexerParser::isVar});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"[0-9]", DIGIT_L, &LexerParser::isNumber});
	lexems_ref_.push_back(LexerParser::t_s_lexem{"?", INT_POINT_L, &LexerParser::isLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{",", COMMA_L, &LexerParser::isLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{";", SEMICOL_L, &LexerParser::isLiteral});
	lexems_ref_.push_back(LexerParser::t_s_lexem{".", POINT_L, &LexerParser::isDecimal});

	//	POW
	//	INT / DEC
	//	VAR
	//	NEG
	//	SUM
	tokens_ref_.push_back(LexerParser::t_s_token{O_PAR, 1, &LexerParser::oParAndNext}); //
	tokens_ref_.push_back(LexerParser::t_s_token{C_PAR, 1, &LexerParser::cParAndNext}); // ADD TOKEN
	tokens_ref_.push_back(LexerParser::t_s_token{MUL, 1, &LexerParser::mulAndNext}); // ADD OP
	tokens_ref_.push_back(LexerParser::t_s_token{POW, 1, &LexerParser::powAndNext}); // ADD OP
	tokens_ref_.push_back(LexerParser::t_s_token{SUM, 1, &LexerParser::literalOperatorAndNext}); // ADD OP
	tokens_ref_.push_back(LexerParser::t_s_token{DIV, 1, &LexerParser::literalOperatorAndNext}); // ADD OP
	tokens_ref_.push_back(LexerParser::t_s_token{SUB, 1, &LexerParser::literalOperatorAndNext}); // ADD OP
	tokens_ref_.push_back(LexerParser::t_s_token{MOD, 1, &LexerParser::literalOperatorAndNext}); // ADD OP
	tokens_ref_.push_back(LexerParser::t_s_token{DOUBLE_MUL, 2, &LexerParser::literalOperatorAndNext}); // ADD OP
	tokens_ref_.push_back(LexerParser::t_s_token{NEG, 255, &LexerParser::negAndNext}); // ADD OP
//	tokens_ref_.push_back(LexerParser::t_s_token{POWER, 255, nullptr}); // ADD OP
	tokens_ref_.push_back(LexerParser::t_s_token{MATRIX_ROW, 255, nullptr}); //
	tokens_ref_.push_back(LexerParser::t_s_token{O_BRACKET, 1, &LexerParser::oBracketAndNext}); //
	tokens_ref_.push_back(LexerParser::t_s_token{C_BRACKET, 1, &LexerParser::cBracketAndNext}); //
	tokens_ref_.push_back(LexerParser::t_s_token{COMMA, 1, &LexerParser::commaAndNext}); // 
	tokens_ref_.push_back(LexerParser::t_s_token{SEMICOL, 1, &LexerParser::semicolAndNext}); //
	tokens_ref_.push_back(LexerParser::t_s_token{INT_NUMBER, 255, &LexerParser::realAndNext}); //
	tokens_ref_.push_back(LexerParser::t_s_token{DEC_NUMBER, 255, &LexerParser::realAndNext}); //
	tokens_ref_.push_back(LexerParser::t_s_token{REAL, 255, nullptr}); //
	tokens_ref_.push_back(LexerParser::t_s_token{COMPLEX, 255, nullptr}); //
	tokens_ref_.push_back(LexerParser::t_s_token{MATRIX, 1024, nullptr}); //
	tokens_ref_.push_back(LexerParser::t_s_token{UNKNOWN, 255, nullptr}); //
	tokens_ref_.push_back(LexerParser::t_s_token{MONOMIAL, 255, nullptr}); //
	tokens_ref_.push_back(LexerParser::t_s_token{ASSIGN, 1, &LexerParser::literalOperatorAndNext}); //
	tokens_ref_.push_back(LexerParser::t_s_token{VAR, 255, &LexerParser::varAndNext}); //
	tokens_ref_.push_back(LexerParser::t_s_token{FUNCTION, 255, nullptr}); //
	tokens_ref_.push_back(LexerParser::t_s_token{GET_RESULT, 2, &LexerParser::literalOperatorAndNext}); //
	tokens_ref_.push_back(LexerParser::t_s_token{EQUATION, 4096, nullptr}); //
	tokens_ref_.push_back(LexerParser::t_s_token{NONE, 0, nullptr});
	tokens_ref_.push_back(LexerParser::t_s_token{ERROR, 0, nullptr});
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
	brackets_ = 0;
	par_ =  0;
	eq_tokens_.clear();
}


LexerParser::t_token_def			LexerParser::isNumber(LexerParser::t_char &lexem)
{
	// Number : [SUM_L|SUB_L] {DIGIT_L} [.{DIGIT_L}]

	if (state_ == VAR)
		return isVar(lexem);
	if (state_ != DEC_NUMBER)
		return INT_NUMBER;
	return state_;
}

LexerParser::t_token_def			LexerParser::isDecimal(t_char &lexem)
{
	if (state_ != INT_NUMBER)
		return ERROR;
	else
		return DEC_NUMBER;
}

LexerParser::t_token_def			LexerParser::isVar(LexerParser::t_char &lexem)
{
	if (state_ != VAR)
		return VAR;
	else if (state_ == VAR && lexem == DIGIT_L)
		return state_;
	else
		return state_;
	return ERROR;
	
}

LexerParser::t_token_def			LexerParser::isMul(LexerParser::t_char &lexem)
{
	if (state_ == MUL)
		return DOUBLE_MUL;
	return MUL;
}

LexerParser::t_token_def			LexerParser::isSub(LexerParser::t_char &lexem)
{
	if (state_ == NONE || isOperator(state_))
		return NEG;
	return SUB;
}

LexerParser::t_token_def			LexerParser::isLiteral(t_char &lexem)
{
	switch (lexem)
	{
		case POW_L:
			return POW;
		case SUM_L:
			return SUM;
		case DIV_L:
			return DIV;
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
		case INT_POINT_L:
			return GET_RESULT;
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
	if (first == NEG && next == INT_NUMBER)
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
	std::string					trim_s = std::regex_replace(s, std::regex("([     ]+)"), "");
	std::string::iterator 		it = trim_s.begin();
	LexerParser::t_char			tmp_lexem;
	std::string					unknown_char;
	std::string					current_token;
	LexerParser::t_token_def	old_state;

	while (it != trim_s.end())
	{
		tmp_lexem = UNDEFINED;
		old_state = state_;
		tmp_lexem = setLexem(*it);

		if (tmp_lexem != UNDEFINED)
		{
			state_ = (this->*lexems_ref_[tmp_lexem].f)(tmp_lexem);
		}
		else
		{
			unknown_char.append("\'");
			unknown_char.append(1, *it);
			unknown_char.append("\' ");
		}
		if (state_ == ERROR)
		{
			std::cerr << "ERROR" << std::endl;
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
		it++;
	}
	if (!current_token.empty())
	{
		tokens_.push_back(LexerParser::t_token{std::string(current_token), state_});
	}

	try
	{
		if (!unknown_char.empty())
		{
			throw InvalidLineException("Unknown identifiers : " + unknown_char);
		}
	}
	catch (std::exception &e)
	{
		std::rethrow_exception(std::current_exception());
	}
	printTokens();
}

bool								LexerParser::nextIsEnd()
{
	return (it_ + 1 == tokens_.end());
}
void								LexerParser::push()
{
	stack_.push_back(&(*it_));
}

Token::t_type						LexerParser::lpTokenToTokenType(LexerParser::t_token_def t)
{
	switch(t) {
		case O_PAR:
			return Token::O_PAR;
		case C_PAR:
			return Token::C_PAR;
		case MUL:
			return Token::MUL;
		case POW:
			return Token::POW;
		case SUM:
			return Token::SUM;
		case DIV:
			return Token::DIV;
		case SUB:
			return Token::SUB;
		case MOD:
			return Token::MOD;
		case DOUBLE_MUL:
			return Token::DOUBLE_MUL;
		case UNKNOWN:
			return Token::UNKNOWN;
		default:
			return Token::MONOMIAL;
	}
}

const char *tokenTypetoString(Token::t_type t)
{
	switch(t) {
		case Token::O_PAR:
			return "O_PAR";
		case Token::C_PAR:
			return "C_PAR";
		case Token::MUL:
			return "MUL";
		case Token::POW:
			return "POW";
		case Token::SUM:
			return "SUM";
		case Token::DIV:
			return "DIV";
		case Token::SUB:
			return "SUB";
		case Token::MOD:
			return "MOD";
		case Token::DOUBLE_MUL:
			return "DOUBLE_MUL";
		case Token::UNKNOWN:
			return "UNKNOWN";
		default:
			return "MONOMIAL";	
	}
}

Token							*LexerParser::newUnknown()
{
	Token *tmp = new Token(lpTokenToTokenType(state_), new Monomial(NULL));
	if (stack_.back()->second == INT_NUMBER)
	{
		if (stack_.back()->first.find('.', 0) != std::string::npos)
		{
			std::cout << "ERROR fill() -> UNKNOWN -> !INT_NUMBER" << std::endl;
			return NULL;
		}
		tmp->getMonomial()->setPower(std::stoul(stack_.back()->first));
		stack_.pop_back();
		stack_.pop_back();
	}
	tmp->getMonomial()->setName(stack_.back()->first);
	stack_.pop_back();
	if (!stack_.empty() && stack_.back()->second == NEG)
	{
		tmp->getMonomial()->setNeg(true);
		stack_.pop_back();
	}
	if (!stack_.empty() && stack_.back()->second == MUL)
		stack_.pop_back();
	if (!stack_.empty() && isDigit(stack_.back()->second))
	{
		tmp->getMonomial()->setCoef(std::stod(stack_.back()->first));
	}
	else if (!stack_.empty() && isDigit(stack_.back()->second))
	{
		std::cout << "ERROR fill() -> UNKNOWN -> !REAL" << std::endl;
		return NULL;
	}

	return tmp;
}

Token							*LexerParser::newComplex()
{
	Token *tmp = new Token(lpTokenToTokenType(state_), new Monomial(new Complex()));
	if (stack_.back()->second == INT_NUMBER)
	{
		if (stack_.back()->first.find('.', 0) != std::string::npos)
		{
			std::cout << "ERROR fill() -> COMPLEX -> !INT_NUMBER" << std::endl;
			return NULL;
		}
		tmp->getMonomial()->setPower(std::stoul(stack_.back()->first));
		stack_.pop_back();
		stack_.pop_back();
	}
	stack_.pop_back();
	if (!stack_.empty() && stack_.back()->second == NEG)
	{
		tmp->getMonomial()->setNeg(true);
		stack_.pop_back();
	}
	if (!stack_.empty() && stack_.back()->second == MUL)
		stack_.pop_back();
	if (!stack_.empty() && isDigit(stack_.back()->second))
	{
		static_cast<Complex *>(tmp->getMonomial()->getOperand())->setImaginaryPart(std::stod(stack_.back()->first));
	}
	else if (!stack_.empty() && !isDigit(stack_.back()->second))
	{
		std::cout << "ERROR fill() -> COMPLEX -> !REAL" << std::endl;
		return NULL;
	}

	return tmp;
}

Token							*LexerParser::newMatrix()
{
	std::vector<double>	new_row;
	size_t row_size = 0;
	size_t tmp_row_size = 0;
	size_t col_size = 0;
	
	for (std::list<t_token *>::iterator it = stack_.begin(); it != stack_.end(); ++it)
	{
		std::cout << ". current : " << (*it)->first;
		if ((*it)->second == SEMICOL || (*it)->second == C_BRACKET)
		{
			if (row_size == 0)
				row_size = tmp_row_size;
			if (tmp_row_size != row_size)
			{
				std::cout << "ERROR fill() -> MATRIX -> ROW SIZE" << std::endl;
				return NULL;
			}
			++col_size;
			tmp_row_size = 0;
		}
		else
		{
			new_row.push_back(std::stod((*it)->first));
			++tmp_row_size;
		}
	}

	return new Token(lpTokenToTokenType(state_), new Monomial(new Matrix(new_row, row_size, col_size)));
}

void								LexerParser::fill()
{
	if (stack_.empty())
		return;
	if (state_ == UNKNOWN)
	{
		eq_tokens_.push_back(newUnknown());
	}
	else if (isOperator(state_))
	{
		eq_tokens_.push_back(new Token(lpTokenToTokenType(state_), nullptr));
	}
	else if (isOperand(state_))
	{
		if (state_ == REAL)
		{
			eq_tokens_.push_back(new Token(lpTokenToTokenType(state_), new Monomial(new Rational(std::stod(stack_.back()->first)))));
		}
		else if (state_ == COMPLEX)
		{
			eq_tokens_.push_back(newComplex());
		}
		else if (state_ == MATRIX)
		{
			eq_tokens_.push_back(newMatrix());
		}
	}
		
		std::cout << std::endl << "___________Token list " << std::endl;;
	for (int i = 0; i < eq_tokens_.size(); i++)
	{
		std::cout << "New " << tokenTypetoString(eq_tokens_[i]->getType()) << " : ";
		if (eq_tokens_[i]->getType() == Token::UNKNOWN)
		{
			std::cout << eq_tokens_[i]->getMonomial()->getCoef();
			std::cout << " * ";
			if (eq_tokens_[i]->getMonomial()->isNeg())
			std::cout << " -";
			std::cout << eq_tokens_[i]->getMonomial()->getName();
			std::cout << " ^ " << eq_tokens_[i]->getMonomial()->getPower();
		}
		if (eq_tokens_[i]->getType() == Token::MONOMIAL)
		{
			if (eq_tokens_[i]->getMonomial()->getOperand()->getType() == t_op::RATIONAL)
				std::cout << std::to_string(static_cast<Rational *>(eq_tokens_[i]->getMonomial()->getOperand())->getValue());
			else if (eq_tokens_[i]->getMonomial()->getOperand()->getType() == t_op::COMPLEX)
			{
				std::cout << "(";
				std::cout << std::to_string(static_cast<Complex *>(eq_tokens_[i]->getMonomial()->getOperand())->getRationalPart()) << " + ";
				std::cout << std::to_string(static_cast<Complex *>(eq_tokens_[i]->getMonomial()->getOperand())->getImaginaryPart()) << " * i) ^ ";
				std::cout << eq_tokens_[i]->getMonomial()->getPower();
			}
			else if (eq_tokens_[i]->getMonomial()->getOperand()->getType() == t_op::MATRIX)
			{
			 std::vector<double> tmp = static_cast<Matrix *>(eq_tokens_[i]->getMonomial()->getOperand())->getValues();
				std::cout << "Matrix " << static_cast<Matrix *>(eq_tokens_[i]->getMonomial()->getOperand())->getColumnsCount() << " * ";
				std::cout << static_cast<Matrix *>(eq_tokens_[i]->getMonomial()->getOperand())->getRowsCount() << " : ";
				std::cout << " [ ";
				for (int i = 0; i < static_cast<Matrix *>(eq_tokens_[i]->getMonomial()->getOperand())->getColumnsCount(); ++i)
				{
					std::cout << " [ ";
					for (int j = 0; j < static_cast<Matrix *>(eq_tokens_[i]->getMonomial()->getOperand())->getRowsCount(); ++j)
					{
						std::cout << tmp[static_cast<Matrix *>(eq_tokens_[i]->getMonomial()->getOperand())->getRowsCount() * i + j] << ", ";
					}
					std::cout << " ] ";
				}
				std::cout << " ] " << std::endl;
			}
		}
		std::cout << std::endl;
	}
		std::cout << std::endl << "___________" << std::endl;;
	while (!stack_.empty())
	{
		stack_.pop_back();
	}
	state_ = NONE;
}

void								LexerParser::findNext()
{
	++it_;
	if (it_ != tokens_.end())
	{
		if (this->tokens_ref_[it_->second].f != nullptr)
			(this->*tokens_ref_[it_->second].f)();
		else
		{
			state_ = NONE;
		}
	}
	else
		return;
	
}

bool								LexerParser::isDigit(t_token_def t)
{
	if (t == INT_NUMBER || t == DEC_NUMBER || t == REAL)
		return true;
	return false;
}

bool								LexerParser::isOperator(LexerParser::t_token_def t)
{
	if (t == SUM || t == SUB || t == POW || t == MUL || t == DIV || t == MOD || t == DOUBLE_MUL || t == ASSIGN)
		return true;
	return false;
}

bool								LexerParser::isOperand(LexerParser::t_token_def t)
{
	if (t == INT_NUMBER || t == DEC_NUMBER || t == VAR ||
		 state_ == REAL || state_ == UNKNOWN ||  state_ == COMPLEX ||  state_ == MATRIX || state_ == MONOMIAL)
		return true;
	return false;
}

bool								LexerParser::isPar(LexerParser::t_token_def t)
{
	if (t == O_PAR || t == C_PAR)
		return true;
	return false;
}

void								LexerParser::oBracketAndNext()
{
	brackets_++;
	try
	{
		if (brackets_ > 2)
			throw InvalidLineException("CA MARCHE PAS");
		if (!nextIsEnd())
		{
			if (state_ == MATRIX)
			{
				state_ = MATRIX_ROW;
			}
			else if (state_ != MATRIX_ROW)
			{
				state_ = MATRIX;
			}
			if ((it_ + 1)->second == O_BRACKET || isOperand((it_ + 1)->second))
			{
				findNext();
				return;
			}
		}
		throw InvalidLineException("CA MARCHE PAS");
	}
	catch(std::exception &e)
	{
		std::cout << "EXCEPTION : oBracketAndNext()" << std::endl;
		std::rethrow_exception(std::current_exception());
	}
}

void								LexerParser::cBracketAndNext()
{
	brackets_--;
	try
	{
		if (brackets_ < 0)
			throw InvalidLineException("CA MARCHE PAS");
		if (state_ == MATRIX_ROW)
		{
			if (brackets_ == 0)
			{
				state_ = MATRIX;
			}
			else if (!nextIsEnd() && ((it_ + 1)->second == SEMICOL || (it_ + 1)->second == C_BRACKET))
			{
				findNext();
				return;
			}
			else
				throw InvalidLineException("CA MARCHE PAS");
		}
		if (state_ == MATRIX)
		{
			push();
			fill();
			return;
		}
		throw InvalidLineException("CA MARCHE PAS");
	}
	catch(std::exception &e)
	{
		std::cout << "EXCEPTION : cBracketAndNext()" << std::endl;
		std::rethrow_exception(std::current_exception());
	}
}

void								LexerParser::oParAndNext()
{
	par_++;
	try
	{
		push();
		if (!nextIsEnd())
		{
			if (isOperand((it_ + 1)->second))
			{
				state_ = O_PAR;
				fill();
				return;
			}
		}
		throw InvalidLineException("CA MARCHE PAS");
	}
	catch(std::exception &e)
	{
		std::cout << "EXCEPTION : oParAndNext()" << std::endl;
		std::rethrow_exception(std::current_exception());
	}
}

void								LexerParser::cParAndNext()
{
	try
	{
		par_--;
		if (par_ < 0)
			throw InvalidLineException("CA MARCHE PAS");
		state_ = C_PAR;
		push();
		fill();
		return;
	}
	catch(std::exception &e)
	{
		std::cout << "EXCEPTION : cParAndNext()" << std::endl;
		std::rethrow_exception(std::current_exception());
	}
}

void								LexerParser::mulAndNext()
{
	try
	{
		if (!nextIsEnd())
		{
			if ((it_ + 1)->second == NEG || isOperand((it_ + 1)->second) || (it_ + 1)->second == O_PAR)
			{
				if ((it_ + 1)->second == VAR)
				{
					push();
					state_ = VAR;
					findNext();
					return;
				}
				else 
				{
					fill();
					push();
					state_ = MUL;
					fill();
					return;
				}
			}
		}
		throw InvalidLineException("CA MARCHE PAS");
	}
	catch(std::exception &e)
	{
		std::cout << "EXCEPTION : mulAndNext()" << std::endl;
		std::rethrow_exception(std::current_exception());
	}
}

void								LexerParser::literalOperatorAndNext()
{
	try
	{
		push();
		if (!nextIsEnd())
		{
			if ((it_ + 1)->second == NEG || isOperand((it_ + 1)->second) || (it_ + 1)->second == O_PAR)
			{
				state_ = it_->second;
				fill();
				return;
			}
		}
		throw InvalidLineException("CA MARCHE PAS");
	}
	catch(std::exception &e)
	{
		std::cout << "EXCEPTION : literalOperatorAndNext()" << std::endl;
		std::rethrow_exception(std::current_exception());
	}
}

void								LexerParser::powAndNext()
{
	try
	{
		if (!nextIsEnd())
		{
			if ((state_ == UNKNOWN || state_ == COMPLEX) && ((it_ + 1)->second == INT_NUMBER || (it_ + 1)->second == DEC_NUMBER))
			{
				push();
				findNext();
				return;
			}
			else if (isOperand((it_ + 1)->second))
			{
				fill();
				push();
				state_ = POW;
				fill();
				return;
			}
		}
		throw InvalidLineException("CA MARCHE PAS");
	}
	catch(std::exception &e)
	{
		std::cout << "EXCEPTION : powAndNext()" << std::endl;
		std::rethrow_exception(std::current_exception());
	}
}

void								LexerParser::varAndNext()
{
	try
	{
		push();
		if (!(it_)->first.compare("i"))
		{
			state_ = COMPLEX;
		}
		else
		{
			state_ = UNKNOWN;
		}
		if (!nextIsEnd() && ((it_ + 1)->second == POW || isPar((it_ + 1)->second)))
		{
			findNext();
			return;
		}
		if (nextIsEnd() || isOperator((it_ + 1)->second))
		{
			fill();
			return;
		}
		else
			throw InvalidLineException("CA MARCHE PAS");
	}
	catch(std::exception &e)
	{
		std::cout << "EXCEPTION : varAndNext()" << std::endl;
		std::rethrow_exception(std::current_exception());
	}
}

void								LexerParser::negAndNext()
{
	try
	{
		push();
		if (!nextIsEnd() && (it_ + 1)->second == VAR)
		{
			findNext();
		}
		else
			throw InvalidLineException("CA MARCHE PAS");
	}
	catch(std::exception &e)
	{
		std::cout << "EXCEPTION : realAndNext()" << std::endl;
		std::rethrow_exception(std::current_exception());
	}
	
}

void								LexerParser::semicolAndNext()
{
	try
	{
		push();
		if (!nextIsEnd() && state_ == MATRIX_ROW)
		{
			if ((it_ + 1)->second == O_BRACKET)
			{
				findNext();
				return;
			}
		}
		throw InvalidLineException("CA MARCHE PAS");
	}
	catch(std::exception &e)
	{
		std::cout << "EXCEPTION : realAndNext()" << std::endl;
		std::rethrow_exception(std::current_exception());
	}
}

void								LexerParser::commaAndNext()
{
	try
	{
		if (!nextIsEnd() && state_ == MATRIX_ROW)
		{
			if (isOperand((it_ + 1)->second))
			{
				findNext();
				return;
			}
		}
		else
			throw InvalidLineException("CA MARCHE PAS");
	}
	catch(std::exception &e)
	{
		std::cout << "EXCEPTION : realAndNext()" << std::endl;
		std::rethrow_exception(std::current_exception());
	}
}

void								LexerParser::realAndNext()
{
	try
	{
		push();
		if (state_ == MATRIX_ROW)
		{
			if ((it_ + 1)->second != COMMA && (it_ + 1)->second != C_BRACKET)
				throw InvalidLineException("CA MARCHE PAS");
			findNext();
		}
		else if (!nextIsEnd() && state_ != COMPLEX && state_ != UNKNOWN)
		{
			state_ = REAL;
			if ((it_ + 1)->second == VAR || (it_ + 1)->second == MUL)
				findNext();
			else if (isOperator((it_ + 1)->second) || (it_ + 1)->second == C_PAR)
				state_ = REAL;
			else
				throw InvalidLineException("CA MARCHE PAS");
		}
		if (state_ != COMPLEX && state_ != UNKNOWN)
			state_ = REAL;
		fill();
	}
	catch(std::exception &e)
	{
		std::cout << "EXCEPTION : realAndNext()" << std::endl;
		std::rethrow_exception(std::current_exception());
	}
}

Variable							LexerParser::parse()
{
	Variable			var;
	std::vector<Token>	tokens;
	it_ = tokens_.begin();
	state_ = NONE;
	try
	{
		if (this->tokens_ref_[it_->second].f != nullptr)
			(this->*tokens_ref_[it_->second].f)();
		else
		{
			state_ = NONE;
			std::cout << tokenToString(it_->second) << " not implemented yet." << std::endl;
		}
		while (it_ != tokens_.end())
		{
			findNext();
		}
	}
	catch(std::exception &e)
	{
		std::cout << "EXCEPTION : parse()" << std::endl;
		std::rethrow_exception(std::current_exception());
	}
	return var;
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
		case NEG:
			return "NEG";
		case MOD:
			return "MOD";
		case DOUBLE_MUL:
			return "DOUBLE_MUL";
//		case POWER:
//			return "POWER";
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
		case MONOMIAL:
			return "MONOMIAL";
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

void								LexerParser::printToken(LexerParser::t_token t)
{
	std::cout << "value : " << t.first;
	std::cout << " - ";
	std::cout << "type : " << tokenToString(t.second);
	std::cout << std::endl;
}

void								LexerParser::printTokens()
{
	for (int i = 0; i < tokens_.size(); ++i)
	{
		printToken(tokens_[i]);
	}
}
