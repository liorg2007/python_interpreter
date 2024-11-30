#include "Void.h"


Void::Void()
{
}

const bool Void::isPrintable()
{
	return false;
}

const std::string Void::toString()
{
	return "";
}

std::string Void::getType()
{
	return "Void";
}
