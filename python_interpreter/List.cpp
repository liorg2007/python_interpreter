#include "List.h"

List::List(const std::vector<Type*>& list)
	:_list(list)
{
}

List::~List()
{
	for (auto& l : _list)
		delete l;
}

const bool List::isPrintable()
{
	return true;
}

const std::string List::toString()
{
	std::string finalStr = "[";

	for (const auto& var : _list) {
		finalStr += var->toString();
		finalStr += ", ";
	}
	finalStr.pop_back();
	finalStr.pop_back();
	finalStr += ']';

	return finalStr;
}

std::string List::getType()
{
	return "list";
}

int List::GetLength()
{
	return _list.size();
}
