#include "Tokens.h"
#include "Opcodes.h"
#include <cctype>




//Had assistance from ChatGPT

// Returns whether the string token argument represents an identifier such as a variable name.
// Identifier names are non-empty, begin with an alphabetic character, are not terminated with a ':' character,
// and are not an opcode.
// No other error checking is performed.

bool isIdentifier(const std::string& token)
{
	if (token.empty() || !std::isalpha(token[0]) || token.back() == ':' || isOpcode(token)) {
		return false;
	}
	return true;

	
}


// Returns whether the string token argument represents an integer constant.
// Integer constants are non-empty and contain only digits optionally preceded by a '+' or '-' sign.

bool isIntConstant(const std::string& token)
{
	if (token.empty()) {
		return false;
	}

	size_t startingPos = 0;

	if (token[0] == '+' || token[0] == '-') {
		startingPos = 1;
	}


	for (size_t i = startingPos; i < token.length(); i++) {
		if (!isdigit(token[i])) {
			return false;
		}
	}
	return true;

	
	// TODO
}


// Returns whether the string token argument represents a label definition.
// Labels are non-empty, begin with an alphabetic character, and are terminated with a ':' character.
// No other error checking is performed.

bool isLabelDefinition(const std::string& token)
{
	if (token.empty() || !isalpha(token[0]) || token.back() != ':') {
		return false;
	}
	return true;
	// TODO
}


// Returns whether the string token argument represents a drone command.
// Drone commands consist of at least 2 characters where the first character is '<'
// and the last character is '>'.
// No other error checking is performed.

bool isDroneCommand(const std::string& token)
{
	if (token.length() < 2 || token[0] != '<' || token.back() != '>') {
		return false;
	}
		return true;
}
	// TODO


// Returns whether the string token argument represents an opcode.

bool isOpcode(const std::string& token)
{
	return (stringToOpcode(token) != Opcodes::UNDEFINED);
}


// Return the string argument surrounded with double quotes.

std::string addQuotes(const std::string& token)
{
	return ('"' + token + '"');
}
