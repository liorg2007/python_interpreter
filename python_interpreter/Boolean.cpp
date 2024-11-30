#include "Boolean.h"

Boolean::Boolean(bool val)
	:_val(val)
{
}

const bool Boolean::isPrintable()
{
	return true;
}

const std::string Boolean::toString()
{
	return _val? "True" : "False";
}

std::string Boolean::getType()
{
	return "bool";
}

