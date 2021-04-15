#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include "bit_width.hpp"
#include "processor_status.hpp"
#include "ram.hpp"
#include "register.hpp"

class Instructions {
       public:
	// Misc Instructions:
	void brk(ProcessorStatus& ps);
	void nop();
	// Load Instruction:
	void ldr(sByte arg, Register& reg, ProcessorStatus& ps);

	// Store Instructions:
	void str(uWord addr, Register& rega, Ram& ram);

	// Arithmetic Instructions:
	void adc(sByte arg, Register& rega, ProcessorStatus& ps);
	void sbc(sByte arg, Register& rega, ProcessorStatus& ps);

	// Increment Instructions:
	void inc(uWord addr, Ram& ram, ProcessorStatus& ps);
	void inr(Register& reg, ProcessorStatus& ps);

	// Decrement Instructions:
	void dec(uWord addr, Ram& ram, ProcessorStatus& ps);
	void der(Register& reg, ProcessorStatus& ps);
};

#endif
