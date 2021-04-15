cmake_minimum_required(VERSION 3.19)

project(mos6502emu)

add_compile_definitions(SAVED_FILES="${PROJECT_BINARY_DIR}/${PROJECT_NAME}/files")

add_compile_definitions(OPCODES_JSON="${PROJECT_BINARY_DIR}/${PROJECT_NAME}/res/opcodes.json")

include_directories(
	include/
	include/archt/
	include/asmbl/
	include/compl/)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EXECUTABLE_OUTPUT_PATH
	${PROJECT_BINARY_DIR}/${PROJECT_NAME})

set(LIBRARY_OUTPUT_PATH
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}/lib)

file(COPY ${PROJECT_SOURCE_DIR}/res
	DESTINATION ${PROJECT_BINARY_DIR}/${PROJECT_NAME})

file(MAKE_DIRECTORY
	${PROJECT_BINARY_DIR}/${PROJECT_NAME}/files)

add_subdirectory(src/archt)
add_subdirectory(src/asmbl)
add_subdirectory(src/compl)

add_executable(emu6502 
	${PROJECT_SOURCE_DIR}/src/main.cpp
	${PROJECT_SOURCE_DIR}/src/cpu.cpp
	${PROJECT_SOURCE_DIR}/res/opcodes.json)

target_link_libraries(emu6502 PUBLIC 
	archt
	asmbl
	compl)
