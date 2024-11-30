#include "type.h"
#include "InterperterException.h"
#include "parser.h"
#include <iostream>

#define WELCOME "Welcome to Magshimim Python Interperter version 1.0 by "
#define YOUR_NAME "Lior Gleizer"


int main(int argc,char **argv)
{
	std::cout << WELCOME << YOUR_NAME << std::endl;

	std::string input_string;

	// get new command from user
	std::cout << ">>> ";
	std::getline(std::cin, input_string);
	
	while (input_string != "quit()")
	{
		// prasing command
		try {
			Type* value = Parser::parseString(input_string);

			if (value != NULL)
			{
				if (value->isPrintable())
					std::cout << value->toString() << std::endl;
				if (value->getIsTemp())
					delete value;
			}
		}
		catch (const std::exception& exep) {
			std::cout << exep.what() << std::endl;
		}


		// get new command from user
		std::cout << ">>> ";
		std::getline(std::cin, input_string);
	}

	Parser::FreeVars();

	return 0;
}


