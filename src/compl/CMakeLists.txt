add_library(compl
	lexer.cpp
	compiler.cpp)

target_include_directories(compl 
	PUBLIC ${PROJECT_SOURCE_DIR}/include/compl/
	PUBLIC ${PROJECT_SOURCE_DIR}/include/archt/)
