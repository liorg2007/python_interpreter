#pragma once
#include <string>

class Type
{
private:
	bool _isTemp;
public:
	Type();

	const bool getIsTemp();
	void setIsTemp(bool isTemp);

	virtual const bool isPrintable() = 0;
	virtual const std::string toString() = 0;
	virtual std::string getType() = 0;
};
