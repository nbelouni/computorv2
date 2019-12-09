#ifndef VARIABLE_HPP
# define VARIABLE_HPP

#include "Computorv2.hpp"
#include "Equation.hpp"

class Variable
{
	private:
		Equation					equation_;
		std::string					name_;
		std::vector<std::string>	args_;

	public:
		Variable();
		Variable(Equation e);
		Variable(Equation e, std::string n);
		Variable(Equation e, std::string n, std::vector<std::string> a);
		~Variable();

		void						clear();

		Equation					getEquation();

		void						setName(std::string s);
		std::string					getName();

		void						setArgs(std::vector<std::string> a);
		void						addArg(std::string s);
		std::string					getArg(size_t i);
		std::vector<std::string>	getAllArgs();
};
#endif
