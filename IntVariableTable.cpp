#include "IntVariableTable.h"
#include "Tokens.h"
#include <assert.h>
#include <iostream>
#include <iomanip>


//Had assistance from ChatGPT



// The IntVariableTable constructor dynamically allocates the fixed size array of integer variables.

IntVariableTable::IntVariableTable()
{
	int_variable_table = new IntVariableEntry[MAX_INT_VARIABLES];
}


// The IntVariableTable destructor deallocates the integer variable array.

IntVariableTable::~IntVariableTable()
{
	delete[] int_variable_table;
}


// Returns the number of variables added to the integer variable table.

int IntVariableTable::numVariables() const
{
	return num_int_variables;
}


// Returns the index of the string token argument in the integer variable table,
// or -1 if the variable name is not found in the integer variable table.

int IntVariableTable::lookupVariable(const std::string& token) const
{
	for (int i = 0; i < num_int_variables; i++) {
		if (int_variable_table[i].name == token) {
			return i;
		}
	}
	return -1;
	// TODO
}


// Adds integer variable name and initial value string tokens to the integer variable
// table, and returns the index of the table entry used to store the variable.
// If the variable name is already present in the integer variable table, a message is
// generated and the table entry index is returned.
// If there is no available entry in the integer variable table, a message is generated
// and -1 is returned.

int IntVariableTable::defineVariable(const std::string& token1, const std::string& token2)
{
	if (num_int_variables >= MAX_INT_VARIABLES)
	{
		std::cout << "Variable table is full! Can't take any more values";
		return -1;
	}

	int existindex = lookupVariable(token1);
	if (existindex != -1) {
		std::cout << "Error! Variable '" << token1 << "' is already defined" << '\n';
		return existindex;
	}

	int integerValue = 0;

	try {
		integerValue = std::stoi(token2);
	}
	catch (const std::invalid_argument& p) {
		std::cout << "This is an Invalid int value" << token2 << "' for variable '" << token1 << '\n';
		return -1;
	}

	int_variable_table[num_int_variables].name = token1;
	int_variable_table[num_int_variables].value = integerValue;
	num_int_variables = num_int_variables + 1;

	return num_int_variables - 1;
	
	// TODO
}


// Returns the name string present in the integer variable table entry specified
// by the index argument.
// An assertion is triggered if the index argument is out of bounds.

std::string IntVariableTable::getName(int index) const
{
	assert(validIndex(index));

	return int_variable_table[index].name;
}


// Returns the numeric value present in the integer variable table entry specified
// by the index argument.
// An assertion is triggered if the index argument is out of bounds.

int IntVariableTable::getValue(int index) const
{
	assert(validIndex(index));

	return int_variable_table[index].value;
}


// Sets the numeric value in the integer variable table entry specified by the index argument.
// An assertion is triggered if the index argument is out of bounds.

void IntVariableTable::setValue(int index, int value)
{
	assert(validIndex(index));

	int_variable_table[index].value = value;
}


// Returns whether the argument is a valid integer variable table index.

bool IntVariableTable::validIndex(int index) const
{
	return ((index >= 0) && (index < num_int_variables));
}


// Displays the contents of the integer variable table on the console.

void IntVariableTable::display() const
{
	if (num_int_variables == 0) {
		std::cout << std::endl << "The integer variable table is empty" << std::endl;
	}
	else {
		std::cout << std::endl << "Integer variable table: [index | variable name | initial value]" << std::endl << std::endl;
		for (int i = 0; i < num_int_variables; i++) {
			std::cout << std::right << std::setw(8)  << i << "    "
				 << std::left  << std::setw(24) << addQuotes(int_variable_table[i].name)
				 << std::right << std::setw(8)  << int_variable_table[i].value << std::endl;
		}
	}
}
