add_library(asmbl
	address_mode.cpp
	instructions.cpp)

target_include_directories(asmbl 
	PUBLIC ${PROJECT_SOURCE_DIR}/include/asmbl/
	PUBLIC ${PROJECT_SOURCE_DIR}/include/archt/)
