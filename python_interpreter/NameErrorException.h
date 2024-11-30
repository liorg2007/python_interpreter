#pragma once
#include "InterperterException.h"
#include <string>

class NameErrorException : public InterperterException {
private:
	std::string _message;
public:
	NameErrorException(const std::string& name) :_message("NameError : name '" + name + "' is not defined") {}

	virtual const char* what() const throw() {
		return  _message.c_str();
	}
};