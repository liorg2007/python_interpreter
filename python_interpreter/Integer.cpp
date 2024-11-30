#include "Integer.h"

Integer::Integer(int val)
	:_val(val)
{
}

const bool Integer::isPrintable()
{
	return true;
}

const std::string Integer::toString()
{
	return std::to_string(_val);
}

std::string Integer::getType()
{
	return "int";
}

