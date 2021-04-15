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
		BRK = 0x00,
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
		DEY_IMPL = 0X88

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
