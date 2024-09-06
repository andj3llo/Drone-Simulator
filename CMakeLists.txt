cmake_minimum_required(VERSION 3.9...3.19)
project(proj CXX)


# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
	set(SFML "C:/SFML-2.5.1-windows-vc16-64-bit")
	include_directories("${SFML}/include")
else()
	find_package(SFML 2.5 COMPONENTS audio graphics network system window)
endif()


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fpl.txt ${CMAKE_CURRENT_BINARY_DIR}/fpl.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fpl_proj03.txt ${CMAKE_CURRENT_BINARY_DIR}/fpl_proj03.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/parse_test1.txt ${CMAKE_CURRENT_BINARY_DIR}/parse_test1.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/parse_test2.txt ${CMAKE_CURRENT_BINARY_DIR}/parse_test2.txt COPYONLY)

set(SOURCES DroneCommandTable.h DroneCommandTable.cpp DroneSimulatorApi.h DroneSimulatorApi.cpp
  FlightPlanExecute.h FlightPlanExecute.cpp FlightPlanParse.h FlightPlanParse.cpp
  FlightPlanSimulator.cpp FlightPlanTello.cpp InstructionTable.h InstructionTable.cpp
  IntVariableTable.h IntVariableTable.cpp LabelTable.h LabelTable.cpp
  Opcodes.h Opcodes.cpp main.cpp TelloApi.h TelloApi.cpp Tokens.h Tokens.cpp)

add_executable(main ${SOURCES})

if (WIN32)
	target_link_libraries(main
		"${SFML}/lib/sfml-audio-d.lib" "${SFML}/lib/sfml-graphics-d.lib" "${SFML}/lib/sfml-main-d.lib"
		"${SFML}/lib/sfml-network-d.lib" "${SFML}/lib/sfml-system-d.lib" "${SFML}/lib/sfml-window-d.lib"
	)
	add_custom_command(
		TARGET main POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/arial.ttf $<TARGET_FILE_DIR:main>
		COMMAND ${CMAKE_COMMAND} -E copy ${SFML}/bin/sfml-audio-d-2.dll $<TARGET_FILE_DIR:main>
		COMMAND ${CMAKE_COMMAND} -E copy ${SFML}/bin/sfml-graphics-d-2.dll $<TARGET_FILE_DIR:main>
		COMMAND ${CMAKE_COMMAND} -E copy ${SFML}/bin/sfml-network-d-2.dll $<TARGET_FILE_DIR:main>
		COMMAND ${CMAKE_COMMAND} -E copy ${SFML}/bin/sfml-system-d-2.dll $<TARGET_FILE_DIR:main>
		COMMAND ${CMAKE_COMMAND} -E copy ${SFML}/bin/sfml-window-d-2.dll $<TARGET_FILE_DIR:main>
		COMMAND ${CMAKE_COMMAND} -E copy ${SFML}/bin/openal32.dll $<TARGET_FILE_DIR:main>
	)
else()
	target_link_libraries(main sfml-audio sfml-graphics sfml-network sfml-system sfml-window)
endif()

set(SOURCES_TEST FlightPlanParse.h FlightPlanParse.cpp Tokens.h Tokens.cpp Opcodes.h Opcodes.cpp IntVariableTable.h IntVariableTable.cpp LabelTable.h LabelTable.cpp InstructionTable.h InstructionTable.cpp DroneCommandTable.h DroneCommandTable.cpp)

add_executable(tests catch.hpp ${SOURCES_TEST} "tests.cpp")

enable_testing()

add_test(tests tests)
