#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "DroneCommandTable.h"
#include "FlightPlanParse.h"
#include "InstructionTable.h"
#include "IntVariableTable.h"
#include "LabelTable.h"
#include "Opcodes.h"
#include "Tokens.h"

//Had assistance from ChatGPT

TEST_CASE("Is Identifier", "[isIdentifier]") {
    SECTION("If The string is empty") {
        std::string testtoken = "";
        isIdentifier(testtoken);
        REQUIRE(isIdentifier(testtoken) == false); //checks to that the pointer points to something
    }

    SECTION("Invalid Case 1 with a no alphabet beginning") {
        std::string testtoken = "677";
        isIdentifier(testtoken);
        REQUIRE(isIdentifier(testtoken) == false); //checks to that the pointer points to something
    }

    SECTION("Invalid Case 2, ends with :") {
        std::string testtoken = "A009:";
        isIdentifier(testtoken);
        REQUIRE(isIdentifier(testtoken) == false); //checks to that the pointer points to something
    }


    SECTION("Valid Case 1") {
        std::string testtoken = "A089";
        isIdentifier(testtoken);
        REQUIRE(isIdentifier(testtoken) == true); //checks to that the pointer points to something
    }

    SECTION("Valid Case 2") {
        std::string testtoken = "B278";
        isIdentifier(testtoken);
        REQUIRE(isIdentifier(testtoken) == true); //checks to that the pointer points to something
    }
}


TEST_CASE("Is Integer Constant", "[isIntConstant]") {
    SECTION("If The string is empty") {
        std::string testtoken = "";
        isIntConstant(testtoken);
        REQUIRE(isIntConstant(testtoken) == false) ; //checks to that the pointer points to something
    }

    SECTION("Invalid Case 1 with a word") {
        std::string testtoken = "hello";
        isIntConstant(testtoken);
        REQUIRE(isIntConstant(testtoken) == false); //checks to that the pointer points to something
    }

    SECTION("Invalid Case 2") {
        std::string testtoken = "+4p5";
        isIntConstant(testtoken);
        REQUIRE(isIntConstant(testtoken) == false); //checks to that the pointer points to something
    }

    SECTION("Valid Case 1") {
        std::string testtoken = "+495";
        isIntConstant(testtoken);
        REQUIRE(isIntConstant(testtoken) == true); //checks to that the pointer points to something
    }

    SECTION("Valid Case 2") {
        std::string testtoken = "-982";
        isIntConstant(testtoken);
        REQUIRE(isIntConstant(testtoken) == true); //checks to that the pointer points to something
    }

}


TEST_CASE("Is Label Definition", "[isLabelDefinition]") {
    SECTION("If The string is empty") {
        std::string testtoken = "";
        isLabelDefinition(testtoken);
        REQUIRE(isLabelDefinition(testtoken) == false); //checks to that the pointer points to something
    }

    SECTION("Invalid Case 1, didn't start with alphabet") {
        std::string testtoken = "9ello";
        isLabelDefinition(testtoken);
        REQUIRE(isLabelDefinition(testtoken) == false); //checks to that the pointer points to something
    }

    SECTION("Invalid Case 2, doesnt end with :" ) {
        std::string testtoken = "A986";
        isLabelDefinition(testtoken);
        REQUIRE(isLabelDefinition(testtoken) == false); //checks to that the pointer points to something
    }

    SECTION("Valid Case 1") {
        std::string testtoken = "B071:";
        isLabelDefinition(testtoken);
        REQUIRE(isLabelDefinition(testtoken) == true); //checks to that the pointer points to something
    }

    SECTION("Valid Case 2") {
        std::string testtoken = "J562:";
        isLabelDefinition(testtoken);
        REQUIRE(isLabelDefinition(testtoken) == true); //checks to that the pointer points to something
    }

}


TEST_CASE("Is Drone Command", "[isDroneCommand]") {
    SECTION("If The string is empty") {
        std::string testtoken = "";
        isDroneCommand(testtoken);
        REQUIRE(isDroneCommand(testtoken) == false); //checks to that the pointer points to something
    }

    SECTION("Invalid Case 1, only has <") {
        std::string testtoken = "<9ll";
        isDroneCommand(testtoken);
        REQUIRE(isDroneCommand(testtoken) == false); //checks to that the pointer points to something
    }

    SECTION("Invalid Case 2, only has >") {
        std::string testtoken = "k0L>";
        isDroneCommand(testtoken);
        REQUIRE(isDroneCommand(testtoken) == false); //checks to that the pointer points to something
    }

    SECTION("Invalid Case 3, not two characters") {
        std::string testtoken = "<";
        isDroneCommand(testtoken);
        REQUIRE(isDroneCommand(testtoken) == false); //checks to that the pointer points to something
    }

    SECTION("Valid Case 1") {
        std::string testtoken = "<move% x% y% z>";
        isDroneCommand(testtoken);
        REQUIRE(isDroneCommand(testtoken) == true); //checks to that the pointer points to something
    }

    SECTION("Valid Case 2") {
        std::string testtoken = "<initialize>";
        isDroneCommand(testtoken);
        REQUIRE(isDroneCommand(testtoken) == true); //checks to that the pointer points to something
    }

}

TEST_CASE("Look Up Variable", "[lookupVariable]") {
    IntVariableTable intVariableTable;
    SECTION("Valid Variable") {
        intVariableTable.defineVariable("a", "107");
        intVariableTable.defineVariable("b", "205");
        intVariableTable.defineVariable("c", "28");

        REQUIRE(intVariableTable.lookupVariable("a") == 0);
        REQUIRE(intVariableTable.lookupVariable("b") == 1);
        REQUIRE(intVariableTable.lookupVariable("c") == 2);
    }

    SECTION("Non-existing Variable Test") {
        intVariableTable.defineVariable("a", "57");
        intVariableTable.defineVariable("b", "67");

        REQUIRE(intVariableTable.lookupVariable("c") == -1);
        REQUIRE(intVariableTable.lookupVariable("var") == -1);

    }
}

TEST_CASE("defineVariable", "[IntVariableTable]") {
    IntVariableTable intVariableTable;
    SECTION("Adding Variables Test") {
        intVariableTable.defineVariable("a", "56");
        intVariableTable.defineVariable("b", "89");
        intVariableTable.defineVariable("c", "99");
       
        REQUIRE(intVariableTable.numVariables() == 3);
        REQUIRE(intVariableTable.lookupVariable("a") == 0);
        REQUIRE(intVariableTable.lookupVariable("b") == 1);
        REQUIRE(intVariableTable.lookupVariable("c") == 2);


        
    }

    SECTION("Duplicate Variable Test") {
        intVariableTable.defineVariable("a", "61");
        intVariableTable.defineVariable("a", "69");

        REQUIRE(intVariableTable.numVariables() == 1);
        REQUIRE(intVariableTable.lookupVariable("a") == 0);
        REQUIRE(intVariableTable.getValue(intVariableTable.lookupVariable("a")) == 61);

    }
}



