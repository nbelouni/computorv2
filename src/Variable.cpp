#include "../inc/Variable.hpp"

Variable::Variable()
{
}

Variable::Variable(Variable::t_type t, Equation e): type_(t), equation_(e)
{
}

Variable::Variable(Variable::t_type t, Equation e, std::string n): type_(t),  equation_(e), name_(n)
{
}

Variable::Variable(Variable::t_type t, Equation e, std::string n, std::vector<std::string> a): type_(t),  equation_(e), name_(n), args_(a)
{
}

Variable::~Variable()
{
	clear();
}

void						Variable::clear()
{
	name_.clear();
	args_.clear();
}

Equation					Variable::getEquation()
{
	return equation_;
}

void						Variable::setType(Variable::t_type s)
{
	type_ = s;
}
Variable::t_type			Variable::getType()
{
	return type_;
}

void						Variable::setName(std::string s)
{
	name_ = s;
}
std::string					Variable::getName()
{
	return name_;
}

void						Variable::setArgs(std::vector<std::string> a)
{
	args_ = a;
}
void						Variable::addArg(std::string s)
{
	args_.push_back(s);
}

std::string					Variable::getArg(size_t i)
{
	return args_[i];
}

std::vector<std::string>	Variable::getAllArgs()
{
	return args_;
}
