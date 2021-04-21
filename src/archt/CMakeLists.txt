add_library(archt 
	register.cpp
	program_counter.cpp
	processor_status.cpp
	ram.cpp)

target_include_directories(archt
	PUBLIC ${PROJECT_SOURCE_DIR}/include/archt/)
