#include "TypeFunc.h"

TypeFunc::TypeFunc(Type* innerType)
  :_innerType(innerType)
{
}

TypeFunc::~TypeFunc()
{
  if (_innerType->getIsTemp())
    delete _innerType;
}

const bool TypeFunc::isPrintable()
{
    return true;
}

const std::string TypeFunc::toString()
{
  return "<type '" + _innerType->getType() + "'>";
}

std::string TypeFunc::getType()
{
  return "<built-in function type>";
}
