#include "instructions.hpp"

#include <cstdio>

#include "bit_width.hpp"
// Misc Instructions:
void Instructions::brk(ProcessorStatus& ps) {
	ps.StatusFlag.B = 1;
	ps.StatusFlag.I = 1;
	return;
}

// Load Instruction:
void Instructions::ldr(sByte arg, Register& reg, ProcessorStatus& ps) {
	reg.setData(arg);
	if (arg == 0)
		ps.StatusFlag.Z = 1;
	else
		ps.StatusFlag.Z = 0;

	if (arg < 0)
		ps.StatusFlag.N = 1;
	else
		ps.StatusFlag.N = 0;
	return;
}

// Store Instructions:
void Instructions::str(uWord addr, Register& reg, Ram& ram) {
	sByte a = reg.getData();
	ram.write(addr, a);
	return;
}

// Arithmetic Instructions:
void Instructions::adc(sByte arg, Register& rega, ProcessorStatus& ps) {
	sByte carry = (sByte)ps.StatusFlag.C;
	sByte a = rega.getData();
	sByte value = a + arg + carry;
	rega.setData(value);
	if (value == 0)
		ps.StatusFlag.Z = 1;
	else
		ps.StatusFlag.Z = 0;

	if (value < 0)
		ps.StatusFlag.N = 1;
	else
		ps.StatusFlag.N = 0;

	if (value > (sByte)0xFF)
		ps.StatusFlag.C = 1;
	else
		ps.StatusFlag.C = 0;

	if ((a ^ value) & (arg ^ value) & 0x80)
		ps.StatusFlag.V = 1;
	else
		ps.StatusFlag.V = 0;
	return;
}

void Instructions::sbc(sByte arg, Register& rega, ProcessorStatus& ps) {
	sByte carry = (sByte)ps.StatusFlag.C;
	sByte a = rega.getData();
	sByte value = a + (~arg) + carry;
	rega.setData(value);
	if (value == 0)
		ps.StatusFlag.Z = 1;
	else
		ps.StatusFlag.Z = 0;

	if (value < 0)
		ps.StatusFlag.N = 1;
	else
		ps.StatusFlag.N = 0;

	if (value > (sByte)0xFF)
		ps.StatusFlag.C = 1;
	else
		ps.StatusFlag.C = 0;

	if ((a ^ value) & (arg ^ value) & 0x80)
		ps.StatusFlag.V = 1;
	else
		ps.StatusFlag.V = 0;
	return;
}

// Increment Instructions:
void Instructions::inc(uWord addr, Ram& ram, ProcessorStatus& ps) {
	ram.incMem(addr);
	sByte value = ram.read(addr);
	if (value == 0)
		ps.StatusFlag.Z = 1;
	else
		ps.StatusFlag.Z = 0;

	if (value < 0)
		ps.StatusFlag.N = 1;
	else
		ps.StatusFlag.N = 0;
	return;
}

void Instructions::inr(Register& reg, ProcessorStatus& ps) {
	reg.incData();
	sByte value = reg.getData();
	if (value == 0)
		ps.StatusFlag.Z = 1;
	else
		ps.StatusFlag.Z = 0;

	if (value < 0)
		ps.StatusFlag.N = 1;
	else
		ps.StatusFlag.N = 0;
	return;
}

// Decrement Instructions:
void Instructions::dec(uWord addr, Ram& ram, ProcessorStatus& ps) {
	ram.decMem(addr);
	sByte value = ram.read(addr);
	if (value == 0)
		ps.StatusFlag.Z = 1;
	else
		ps.StatusFlag.Z = 0;

	if (value < 0)
		ps.StatusFlag.N = 1;
	else
		ps.StatusFlag.N = 0;
	return;
}

void Instructions::der(Register& reg, ProcessorStatus& ps) {
	reg.decData();
	sByte value = reg.getData();
	if (value == 0)
		ps.StatusFlag.Z = 1;
	else
		ps.StatusFlag.Z = 0;

	if (value < 0)
		ps.StatusFlag.N = 1;
	else
		ps.StatusFlag.N = 0;
	return;
}

