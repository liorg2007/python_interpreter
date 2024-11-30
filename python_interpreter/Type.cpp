#include "type.h"

Type::Type()
	:_isTemp(false)
{
}

const bool Type::getIsTemp()
{
	return _isTemp;
}

void Type::setIsTemp(bool isTemp)
{
	_isTemp = isTemp;
}
