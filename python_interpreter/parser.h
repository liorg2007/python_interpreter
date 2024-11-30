#ifndef PARSER_H
#define PARSER_H

#include "InterperterException.h"
#include "IndentationException.h"
#include "SyntaxException.h"
#include "NameErrorException.h"
#include "TypeErrorException.h"

#include "Type.h"
#include "Integer.h"
#include "String.h"
#include "Boolean.h"
#include "Void.h"
#include "List.h"

#include "TypeFunc.h"
#include "Helper.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>

class Parser
{
public:
	static Type* parseString(std::string str) throw();
	static void FreeVars();
	
private:
	static Type* getType(const std::string& value);
	static bool isLegalVarName(const std::string& value);
	static bool makeAssignment(const std::string& value);
	static Type* getVariableValue(const std::string& name);
	static std::unordered_map<std::string, Type*> _variables;
	static void assignFromVar(const std::string& dst, const std::string& src);

	static bool canBeList(const std::string& name);
	static Type* createList(const std::string& value);

	static bool isFunction(const std::string& value);
	static Type* getFunction(const std::string& value);

	static std::vector<std::string> _functionNames;
};



#endif //PARSER_H
