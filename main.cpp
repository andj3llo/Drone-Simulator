#include "IntVariableTable.h"
#include "LabelTable.h"
#include "DroneCommandTable.h"
#include "InstructionTable.h"
#include "FlightPlanParse.h"
#include "FlightPlanExecute.h"
#include <iostream>
#include <fstream>




// Provides an example of using the FlightPlanParse and FlightPlanExecute classes supporting
// FPL parsing, optional execution tracing and optional drone communication.
// The program prompts for the name of a FPL file, parses the file, displays the parse tables
// generated, and executes the FPL program according to the modes selected.


int main()
{
	std::cout << "Enter the FPL file name without the .txt suffix: ";

	std::string file_name;
	std::cin >> file_name;
	file_name += ".txt";

	std::ifstream fpl_file(file_name);

	if (fpl_file.is_open()) {
		IntVariableTable  int_variables;
		LabelTable        labels;
		DroneCommandTable drone_commands;
		InstructionTable  instructions;
		FlightPlanParse   fpl_parse(int_variables, labels, drone_commands, instructions);
		std::string            line;
		while (std::getline(fpl_file, line)) {
			line += ' ';
			fpl_parse.parseLine(line);
		}
		int_variables.display();
		labels.display();
		drone_commands.display();
		if (fpl_parse.parseSuccess()) {
			fpl_parse.displayInstructions();
			FlightPlanExecute fpl_execute(int_variables, labels, drone_commands, instructions);
			fpl_execute.executeProgram(DroneMode::SIMULATOR, TraceMode::ALL_OPCODES);
			std::cout << std::endl << "Press any letter followed by the return key to exit the application: ";
			char c;
			std::cin >> c;
		}
	}
	else {
		std::cout << "File " << file_name << " not found" << std::endl;
	}

	return 0;
}