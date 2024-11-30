#include "parser.h"
#include <iostream>

std::vector<std::string> Parser::_functionNames = { "type(", "del", "len(" };
std::unordered_map<std::string, Type*> Parser::_variables;

Type* Parser::parseString(std::string str) throw()
{
	Type* type = nullptr;
	std::string tmpStr = str;
	if (str.length() > 0)
	{
		if (str[0] == ' ' || str[0] == '\t')
			throw IndentationException();

		Helper::trim(tmpStr);

		// Get variable value
		type = getVariableValue(tmpStr);

		if (type != nullptr)
			return type;

		// Assing to variable
		if (makeAssignment(str))
		{
			Type* type = new Void();
			type->setIsTemp(true);
			return type;
		}

		// Regular number
		type = getType(tmpStr);

		if (type == nullptr)
			throw SyntaxException();

		type->setIsTemp(true);

		return type;
	}

	return NULL;
}

void Parser::FreeVars()
{
	for (auto& var : _variables)
		delete var.second;
}

Type* Parser::getType(const std::string& value)
{
	Type* type = nullptr;
	if (Helper::isBoolean(value)) 
	{
		type = new Boolean(value == "True");
	}
	else if (Helper::isString(value))
	{
		type = new String(value);
	}
	else if (Helper::isInteger(value))
	{
		type = new Integer(std::stoi(value));
	}
	else if (isFunction(value))
	{
		type = getFunction(value);
	}
	else if(canBeList(value)){
		type = createList(value);
	}

	return type;
}

bool Parser::isLegalVarName(const std::string& value)
{
	if (Helper::isDigit(value[0]) || value == "True" || value == "False")
		return false;

	for (const auto& ch : value)
		if (!(Helper::isDigit(ch) || Helper::isUnderscore(ch) || Helper::isLetter(ch)))
			return false;

	return true;
}

bool Parser::makeAssignment(const std::string& value)
{
	std::string lValue, rValue;
	int equalsIndex = value.find('=');
	int ch = 0;
	Type* type = nullptr;

	if (equalsIndex == std::string::npos || equalsIndex == value.size() - 1)
		return false;

	while (value[ch] != '=')
	{
		lValue += value[ch];
		++ch;
	}
	++ch;

	while (ch < value.size())
	{
		rValue += value[ch];
		++ch;
	}

	Helper::trim(lValue);
	Helper::trim(rValue);

	if (!isLegalVarName(lValue))
		throw SyntaxException();

	if (isLegalVarName(rValue))
	{
		assignFromVar(lValue, rValue);
		return true;
	}

	type = getType(rValue);
	type->setIsTemp(false);

	if (type == nullptr)
		throw SyntaxException();

	Type* previous = getVariableValue(lValue);

	if (previous != nullptr)
	{
		_variables.erase(lValue);
		delete previous;
	}

	_variables.insert({ lValue, type });
	return true;
}

Type* Parser::getVariableValue(const std::string& name)
{
	Type* val = nullptr;
	try {
		val = _variables.at(name);
	}
	catch (...) {
		return nullptr;
	}
	return val;
}

void Parser::assignFromVar(const std::string& dst, const std::string& src)
{
	Type* source = nullptr;
	Type* copySrc = nullptr;
	try {
		source = _variables.at(src);
	}
	catch (...) {
		throw NameErrorException(src);
	}

	Type* previous = getVariableValue(dst);

	if (previous != nullptr)
	{
		_variables.erase(dst);
		delete previous;
	}

	copySrc = getType(source->toString());

	_variables.insert({ dst, copySrc });
}

bool Parser::canBeList(const std::string& name)
{
	return name[0] == '[' && name[name.size() - 1] == ']';
}

Type* Parser::createList(const std::string& value)
{
	std::vector<Type*> list;
	int start = 1;
	int end = 1;

	while (value[start] != ']')
	{
		Type* val = nullptr;
		std::string name;
		end = value.find(',', start);

		if (end == std::string::npos)
		{
			end = value.size() - 1; // dont include the ]
		}

		if (end < start)
			return new List(list);

		name = value.substr(start, end - start);
		Helper::trim(name);

		if (isLegalVarName(name))
		{
			val = getVariableValue(name);

			if (val == nullptr)
				throw NameErrorException(name);

			val = getType(val->toString());
		}
		else
		{
			val = getType(name);
			if (val == nullptr)
				throw SyntaxException();
		}

		list.push_back(val);
		start = end + 1;
	}

	return new List(list);
}

bool Parser::isFunction(const std::string& value)
{
	for (const auto& possible : _functionNames)
	{
		if (value.find(possible) == 0)
			return true;
	}

	return false;
}

Type* Parser::getFunction(const std::string& value)
{
	std::string arg;
	if (value.find("type(") != std::string::npos)
	{
		Type* innerType = nullptr;
		int bracket = value.find("(");
		arg = value.substr(bracket + 1, value.size() - bracket - 2);
		
		if (isLegalVarName(arg))
		{
			innerType = getVariableValue(arg);

			if (innerType == nullptr)
				throw NameErrorException(arg);
		}
		else
		{
			innerType = getType(arg);

			if (innerType == nullptr)
				throw NameErrorException(arg);
		}

		return new TypeFunc(innerType);
	}
	else if (value.find("del") != std::string::npos)
	{
		arg = value.substr(4, value.size());
		Helper::trim(arg);

		if (isLegalVarName(arg))
		{
			if (_variables.find(arg) == _variables.end())
				throw NameErrorException(arg);
			_variables.erase(arg);
		}
		else
		{
			throw SyntaxException();
		}

		return new Void();
	}
	else if (value.find("len(") == 0)
	{
		Type* innerType = nullptr;
		int bracket = value.find("(");
		arg = value.substr(bracket + 1, value.size() - bracket - 2);

		if (isLegalVarName(arg))
		{
			innerType = getVariableValue(arg);

			if (innerType == nullptr)
				throw NameErrorException(arg);
		}
		else
		{
			innerType = getType(arg);

			if (innerType == nullptr)
				throw NameErrorException(arg);
		}

		if (innerType->getType() != "list" && innerType->getType() != "string") {
			throw TypeErrorException(innerType->getType(), "len()");
		}

		Sequence* seq = reinterpret_cast<Sequence*>(innerType);

		return new Integer(seq->GetLength());
	}

	throw SyntaxException();
}

