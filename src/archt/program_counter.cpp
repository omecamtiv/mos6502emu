#include "program_counter.hpp"

ProgramCounter::ProgramCounter() { counter = 0x0000; }

uWord ProgramCounter::getCounter() { return counter; }

void ProgramCounter::setCounter(uWord word) {
	counter = word;
	return;
}

void ProgramCounter::incCounter() {
	counter++;
	return;
}

void ProgramCounter::decCounter() {
	counter--;
	return;
}
