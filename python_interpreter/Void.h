#pragma once
#include <string>
#include "Type.h"

class Void : public Type {
private:
public:
	Void();
	virtual const bool isPrintable() override;
	virtual const std::string toString() override;
	virtual std::string getType() override;
};