#ifndef PROGRAM_COUNTER_HPP
#define PROGRAM_COUNTER_HPP
#include "bit_width.hpp"

class ProgramCounter {
	uWord counter;

       public:
	ProgramCounter();
	uWord getCounter();
	void setCounter(uWord word);
	void incCounter();
};

#endif
