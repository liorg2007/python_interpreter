#pragma once
#include <string>
#include "Type.h"

class Integer : public Type {
private:
	int _val;

public:
	Integer(int val);
	virtual const bool isPrintable() override;
	virtual const std::string toString() override;
	virtual std::string getType() override;
};