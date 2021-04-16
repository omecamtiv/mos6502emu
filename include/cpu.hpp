#ifndef CPU_HPP
#define CPU_HPP
#include <cstdio>

#include "address_mode.hpp"
#include "bit_width.hpp"
#include "instructions.hpp"
#include "processor_status.hpp"
#include "program_counter.hpp"
#include "ram.hpp"
#include "register.hpp"

class CPU {
	uByte current_instruction;
	int current_instruction_decoded;
	Instructions ins;
	AddressMode adm;
	typedef enum {
		// Misc Instructions:
		//
		// BRK:
		BRK_IMPL = 0x00,
		NOP_IMPL = 0xEA,
		// Load Instructions:
		//
		// LDA:
		LDA_ABS = 0xAD,
		LDA_ABSX = 0xBD,
		LDA_ABSY = 0xB9,
		LDA_IMME = 0xA9,
		LDA_ZP = 0xA5,
		LDA_ZPX = 0xB5,
		LDA_IDXIDRX = 0xA1,
		LDA_IDRIDXY = 0xB1,
		// LDX:
		LDX_ABS = 0xAE,
		LDX_ABSY = 0xBE,
		LDX_IMME = 0xA2,
		LDX_ZP = 0xA6,
		LDX_ZPY = 0xB6,
		// LDY:
		LDY_ABS = 0xAC,
		LDY_ABSX = 0xBC,
		LDY_IMME = 0xA0,
		LDY_ZP = 0xA4,
		LDY_ZPX = 0xB4,
		// Store Instructions:
		//
		// STA:
		STA_ABS = 0x8D,
		STA_ABSX = 0x9D,
		STA_ABSY = 0x99,
		STA_ZP = 0x85,
		STA_ZPX = 0x95,
		STA_IDXIDRX = 0x81,
		STA_IDRIDXY = 0x91,
		// STX:
		STX_ABS = 0x8E,
		STX_ZP = 0x86,
		STX_ZPY = 0x96,
		// STY:
		STY_ABS = 0x8C,
		STY_ZP = 0x84,
		STY_ZPX = 0x94,
		// Arithmetic Instructions:
		//
		// ADC:
		ADC_ABS = 0x6D,
		ADC_ABSX = 0x7D,
		ADC_ABSY = 0x79,
		ADC_IMME = 0x69,
		ADC_ZP = 0x65,
		ADC_ZPX = 0x75,
		ADC_IDXIDRX = 0x61,
		ADC_IDRIDXY = 0x71,
		// SBC:
		SBC_ABS = 0xED,
		SBC_ABSX = 0xFD,
		SBC_ABSY = 0xF9,
		SBC_IMME = 0xE9,
		SBC_ZP = 0xE5,
		SBC_ZPX = 0xF5,
		SBC_IDXIDRX = 0xE1,
		SBC_IDRIDXY = 0xF1,
		// Increment Instructions:
		//
		// INC:
		INC_ABS = 0XEE,
		INC_ABSX = 0XFE,
		INC_ZP = 0XE6,
		INC_ZPX = 0XF6,
		// INX:
		INX_IMPL = 0XE8,
		// INY:
		INY_IMPL = 0XC8,
		// Decrement Instructions:
		//
		// INC:
		DEC_ABS = 0XCE,
		DEC_ABSX = 0XDE,
		DEC_ZP = 0XC6,
		DEC_ZPX = 0XD6,
		// INX:
		DEX_IMPL = 0XCA,
		// INY:
		DEY_IMPL = 0X88,
		// Logic Instructions:
		//
		// AND:
		AND_ABS = 0x2D,
		AND_ABSX = 0x3D,
		AND_ABSY = 0x39,
		AND_IMME = 0x29,
		AND_ZP = 0x25,
		AND_ZPX = 0x35,
		AND_IDXIDRX = 0x21,
		AND_IDRIDXY = 0x31,
		// ORA:
		ORA_ABS = 0x0D,
		ORA_ABSX = 0x1D,
		ORA_ABSY = 0x19,
		ORA_IMME = 0x09,
		ORA_ZP = 0x05,
		ORA_ZPX = 0x15,
		ORA_IDXIDRX = 0x01,
		ORA_IDRIDXY = 0x11,
		// EOR:
		EOR_ABS = 0x4D,
		EOR_ABSX = 0x5D,
		EOR_ABSY = 0x59,
		EOR_IMME = 0x49,
		EOR_ZP = 0x45,
		EOR_ZPX = 0x55,
		EOR_IDXIDRX = 0x41,
		EOR_IDRIDXY = 0x51,
		// Branch Instructions:
		BCC_REL = 0x90,
		BCS_REL = 0xB0,
		BNE_REL = 0xD0,
		BEQ_REL = 0xF0,
		BPL_REL = 0x10,
		BMI_REL = 0x30,
		BVC_REL = 0x50,
		BVS_REL = 0x70
	} instructions;

       public:
	Register A, X, Y;
	Ram RAM;
	ProgramCounter PC;
	ProcessorStatus PS;
	CPU();
	void reset();
	void fetch();
	void decode();
	void execute();
	void run();
	void dump();
	void memDump(uWord sBlock, uWord eBlock);
};

#endif
