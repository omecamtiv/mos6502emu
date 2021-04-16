#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include "bit_width.hpp"
#include "processor_status.hpp"
#include "program_counter.hpp"
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

	// Logic Instructions:
	void logicAND(sByte arg, Register& rega, ProcessorStatus& ps);
	void logicOR(sByte arg, Register& rega, ProcessorStatus& ps);
	void logicXOR(sByte arg, Register& rega, ProcessorStatus& ps);

	// Branch Instructions:
	void bcc(uWord addr, ProcessorStatus& ps, ProgramCounter& pc);
	void bcs(uWord addr, ProcessorStatus& ps, ProgramCounter& pc);
	void bne(uWord addr, ProcessorStatus& ps, ProgramCounter& pc);
	void beq(uWord addr, ProcessorStatus& ps, ProgramCounter& pc);
	void bpl(uWord addr, ProcessorStatus& ps, ProgramCounter& pc);
	void bmi(uWord addr, ProcessorStatus& ps, ProgramCounter& pc);
	void bvc(uWord addr, ProcessorStatus& ps, ProgramCounter& pc);
	void bvs(uWord addr, ProcessorStatus& ps, ProgramCounter& pc);
};

#endif
