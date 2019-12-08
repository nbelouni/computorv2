#include "../inc/Variable.hpp"

Variable::Variable(Equation e): equation_(e)
{
}

Variable::Variable(Equation e, std::string n): equation_(e), name_(n)
{
}

Variable::Variable(Equation e, std::string n, std::vector<std::string> a): equation_(e), name_(n), args_(a)
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
