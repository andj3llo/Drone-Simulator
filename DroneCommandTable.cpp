#include "DroneCommandTable.h"
#include "Tokens.h"
#include <cassert>
#include <iostream>
#include <iomanip>



// The DroneCommandTable constructor dynamically allocates the fixed size array of drone commands.

DroneCommandTable::DroneCommandTable()
{
	drone_command_table = new std::string[MAX_DRONE_COMMANDS];
}


// The DroneCommandTable destructor deallocates the drone command array.

DroneCommandTable::~DroneCommandTable()
{
	delete[] drone_command_table;
}


// Returns the current number of commands added to the drone command table.

int DroneCommandTable::numCommands() const
{
	return num_drone_commands;
}


// Returns the index of the string token argument in the drone command table, or -1 if the
// argument is not found in the drone command table.
// The drone command argument should include the '<' and '>' delimiters.

int DroneCommandTable::lookupCommand(const std::string& token) const
{
	int index{ -1 };

	for (int i{ 0 }; i < num_drone_commands; i++) {
		if (drone_command_table[i] == token) {
			index = i;
			break;
		}
	}

	return index;
}


// Accepts a string consisting of a drone command (including the '<' and '>' delimiters)
// and adds the command to the end of the drone command table if the command is not already
// in the table.
// A message is generated and -1 is returned if the drone command table has no available entry.
// Otherwise the index of the table entry for the drone command is returned.

int DroneCommandTable::addCommand(const std::string& token)
{
	int index{ lookupCommand(token) };

	if (index == -1) {
		if (num_drone_commands < MAX_DRONE_COMMANDS) {
			index = num_drone_commands;
			drone_command_table[index] = token;
			num_drone_commands++;
		}
		else {
			std::cout << "MAX_DRONE_COMMANDS (" << MAX_DRONE_COMMANDS << ") exceeded" << std::endl;
		}
	}

	return index;
}


// Returns the drone command string (including the '<' and '>' delimiters) in the
// drone command table entry specified by the index argument.
// An assertion is triggered if the index argument is out of bounds.

std::string DroneCommandTable::getCommand(int index) const
{
	assert(validIndex(index));

	return drone_command_table[index];
}


// Returns whether the argument is a valid drone command table index.

bool DroneCommandTable::validIndex(int index) const
{
	return ((index >= 0) && (index < num_drone_commands));
}


// Displays the contents of the used drone command table entries on the console.

void DroneCommandTable::display() const
{
	if (num_drone_commands == 0) {
		std::cout << std::endl << "The drone command table is empty" << std::endl;
	}
	else {
		std::cout << std::endl << "Drone command table: [index | command]" << std::endl << std::endl;
		for (int i = 0; i < num_drone_commands; i++) {
			std::cout << std::right << std::setw(8)  << i << "    "
				 << std::left  << std::setw(24) << addQuotes(drone_command_table[i]) << std::endl;
		}
	}
}
