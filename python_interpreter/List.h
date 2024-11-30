#pragma once

#include "Sequence.h"
#include <vector>


class List : public Sequence {
private:
	std::vector<Type*> _list;

public:
	List(const std::vector<Type*>& list);
	~List();
	virtual const bool isPrintable() override;
	virtual const std::string toString() override;
	virtual std::string getType() override;
	virtual int GetLength() override;
};
