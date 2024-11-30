#pragma once

#include "Type.h"

class TypeFunc : public Type
{
private:
	Type* _innerType;
public:
	TypeFunc(Type* innerType);
	~TypeFunc();

	virtual const bool isPrintable();
	virtual const std::string toString();
	virtual std::string getType();
};