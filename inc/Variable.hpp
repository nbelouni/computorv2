#ifndef VARIABLE_HPP
# define VARIABLE_HPP

#include "Computorv2.hpp"
#include "Equation.hpp"

class Variable
{
	public:
		typedef	enum				e_type
		{
			VARIABLE,
			FUNCTION,
			RESOLVE,
			FIND_UNKNOWN
		}							t_type;
	private:
		t_type						type_;
		Equation					equation_;
		std::string					name_;
		std::vector<std::string>	args_;

	public:
		Variable();
		Variable(t_type t, Equation e);
		Variable(t_type t, Equation e, std::string n);
		Variable(t_type t, Equation e, std::string n, std::vector<std::string> a);
		~Variable();

		void						clear();

		Equation					getEquation();

		void						setType(t_type s);
		t_type						getType();

		void						setName(std::string s);
		std::string					getName();

		void						setArgs(std::vector<std::string> a);
		void						addArg(std::string s);
		std::string					getArg(size_t i);
		std::vector<std::string>	getAllArgs();
};
#endif
