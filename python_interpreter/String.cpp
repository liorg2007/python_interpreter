#include "String.h"

String::String(const std::string& val)
	:_val(val)
{
	// find if there is ' in the middle
	if (val.find('\'') == -1)
	{
		_val[0] = '\'';
		_val[val.size() - 1] = '\'';
	}
}

const bool String::isPrintable()
{
	return true;
}

const std::string String::toString()
{
	return _val;
}

std::string String::getType()
{
	return "string";
}

int String::GetLength()
{
	return _val.size() - 2;
}

