#pragma once
#include <string>
#include "Type.h"

class Boolean : public Type {
private:
	bool _val;

public:
	Boolean(bool val);
	virtual const bool isPrintable() override;
	virtual const std::string toString() override;
	virtual std::string getType() override;
};