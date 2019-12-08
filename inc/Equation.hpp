#ifndef EQUATION_HPP
# define EQUATION_HPP


#include "Computorv2.hpp"
#include "Token.hpp"

class Token;

class Equation
{
	private:
		std::vector<Token>			tokens_;
		size_t						power_max_;
		std::vector<std::string>	unknowns_;

	public:
		Equation();
		Equation(std::vector<Token>, size_t pow);
		Equation(std::vector<Token>, size_t pow, std::vector<std::string> u);
		~Equation();

		void						clear();
		void						setTokens(std::vector<Token> t);
		void						addToken(Token t);
		Token						getToken(size_t i);
		std::vector<Token>			getAllTokens();

		void						setPowerMax(size_t p);
		size_t						getPowerMax();

		void						setUnknowns(std::vector<std::string> t);
		void						addUnknown(std::string t);
		std::string					getUnknown(size_t i);
		std::vector<std::string>	getAllUnknowns();
};

#endif
