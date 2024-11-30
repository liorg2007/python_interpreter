#pragma once

#include "Sequence.h"

class String : public Sequence {
private:
	std::string _val;

public:
	String(const std::string& str);
	virtual const bool isPrintable() override;
	virtual const std::string toString() override;
	virtual std::string getType() override;
	virtual int GetLength() override;
};