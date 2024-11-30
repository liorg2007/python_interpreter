#pragma once

#include "InterperterException.h"
#include <string>

class TypeErrorException : public InterperterException {
private:
	std::string _message;
public:
	TypeErrorException(const std::string& name, const std::string& method) :_message("TypeError : object of type '" + name + "' has no " + method) {}

	virtual const char* what() const throw() {
		return  _message.c_str();
	}
};