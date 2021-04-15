#ifndef ADDRESS_MODE_HPP
#define ADDRESS_MODE_HPP

#include "bit_width.hpp"
#include "program_counter.hpp"
#include "ram.hpp"
#include "register.hpp"

class AddressMode {
       public:
	uWord addrm_rel(ProgramCounter& pc, Ram& ram);
	sByte addrm_imme(ProgramCounter& pc, Ram& ram);
	uWord addrm_zp(ProgramCounter& pc, Ram& ram);
	uWord addrm_zpx(ProgramCounter& pc, Ram& ram, Register& regx);
	uWord addrm_zpy(ProgramCounter& pc, Ram& ram, Register& regy);
	uWord addrm_abs(ProgramCounter& pc, Ram& ram);
	uWord addrm_absind(ProgramCounter& pc, Ram& ram);
	uWord addrm_absx(ProgramCounter& pc, Ram& ram, Register& regx);
	uWord addrm_absy(ProgramCounter& pc, Ram& ram, Register& regy);
	uWord addrm_idxidrx(ProgramCounter& pc, Register& regx, Ram& ram);
	uWord addrm_idridxy(ProgramCounter& pc, Register& regy, Ram& ram);
};

#endif
