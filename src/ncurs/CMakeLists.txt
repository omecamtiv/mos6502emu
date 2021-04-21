set(CURSES_NEED_NCURSES TRUE)

find_package(Curses REQUIRED)

add_library(ncurs
	ui.cpp)

include_directories(${CURSES_INCLUDE_DIR})

target_include_directories(ncurs
	PUBLIC ${PROJECT_SOURCE_DIR}/include/ncurs)

target_link_libraries(ncurs
	${CURSES_LIBRARIES})
