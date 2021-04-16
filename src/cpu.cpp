#include "cpu.hpp"

#include "bit_width.hpp"
#define MAX 5

CPU::CPU() {}

void CPU::reset() {
	A.setData(0x00);
	X.setData(0x00);
	Y.setData(0x00);
	PC.setCounter(0x0600);
	RAM.setStackPointer(0xFF);
	PS.StatusFlag.N = 0;
	PS.StatusFlag.V = 0;
	PS.StatusFlag.U = 0;
	PS.StatusFlag.B = 0;
	PS.StatusFlag.D = 0;
	PS.StatusFlag.I = 0;
	PS.StatusFlag.Z = 0;
	PS.StatusFlag.C = 0;
	return;
}

void CPU::dump() {
	uByte a, x, y, ps;
	uWord pc, st;
	a = (uByte)A.getData();
	x = (uByte)X.getData();
	y = (uByte)Y.getData();
	pc = PC.getCounter();
	st = (uByte)RAM.getStackPointer() + 0x0100;
	ps = (uByte)PS.getPS();
	printf("\n        PC  AC XR YR  SP  NV-BDIZC\n");
	printf("[6502] %04X %02X %02X %02X %04X ", pc, a, x, y, st);
	int mask = 0x80;
	while (mask > 0) {
		printf("%d", (ps & mask) > 0);
		mask >>= 1;
	}
	printf("\n");
	return;
}

void CPU::memDump(uWord sBlock, uWord eBlock) {
	printf("\t ADDR  =>> DATA\n");
	for (uWord addr = sBlock; addr <= eBlock; addr++) {
		uByte data = (uByte)RAM.read(addr);
		printf("\t0x%04X =>> 0x%02X \n", addr, data);
		if (addr == 0xFFFF) {
			break;
		}
	}
}

void CPU::run() {
	while (PS.StatusFlag.B == 0) {
		fetch();
		decode();
		execute();
	}
	return;
}

void CPU::fetch() {
	uWord counter = PC.getCounter();
	current_instruction = (uByte)RAM.read(counter);
	return;
}

void CPU::decode() {
	current_instruction_decoded = (int)current_instruction;
	PC.incCounter();
	return;
}

void CPU::execute() {
	switch (current_instruction_decoded) {
		// Misc Instructions:
		//
		// BRK:
		case BRK_IMPL: {
			ins.brk(PS);
			break;
		}
		case NOP_IMPL: {
			ins.nop();
			break;
		}
		// Load Instructions:
		//
		// LDA:
		case LDA_ABS: {
			uWord addr = adm.addrm_abs(PC, RAM);
			sByte arg = RAM.read(addr);
			ins.ldr(arg, A, PS);
			break;
		}
		case LDA_ABSX: {
			uWord addr = adm.addrm_absx(PC, RAM, X);
			sByte arg = RAM.read(addr);
			ins.ldr(arg, A, PS);
			break;
		}
		case LDA_ABSY: {
			uWord addr = adm.addrm_absy(PC, RAM, Y);
			sByte arg = RAM.read(addr);
			ins.ldr(arg, A, PS);
			break;
		}
		case LDA_IMME: {
			sByte arg = adm.addrm_imme(PC, RAM);
			ins.ldr(arg, A, PS);
			break;
		}
		case LDA_ZP: {
			uWord addr = adm.addrm_zp(PC, RAM);
			sByte arg = RAM.read(addr);
			ins.ldr(arg, A, PS);
			break;
		}
		case LDA_ZPX: {
			uWord addr = adm.addrm_zpx(PC, RAM, X);
			sByte arg = RAM.read(addr);
			ins.ldr(arg, A, PS);
			break;
		}
		case LDA_IDXIDRX: {
			uWord addr = adm.addrm_idxidrx(PC, X, RAM);
			sByte arg = RAM.read(addr);
			ins.ldr(arg, A, PS);
			break;
		}
		case LDA_IDRIDXY: {
			uWord addr = adm.addrm_idridxy(PC, Y, RAM);
			sByte arg = RAM.read(addr);
			ins.ldr(arg, A, PS);
			break;
		}
		// LDX:
		case LDX_ABS: {
			uWord addr = adm.addrm_abs(PC, RAM);
			sByte arg = RAM.read(addr);
			ins.ldr(arg, X, PS);
			break;
		}
		case LDX_ABSY: {
			uWord addr = adm.addrm_absy(PC, RAM, Y);
			sByte arg = RAM.read(addr);
			ins.ldr(arg, X, PS);
			break;
		}
		case LDX_IMME: {
			sByte arg = adm.addrm_imme(PC, RAM);
			ins.ldr(arg, X, PS);
			break;
		}
		case LDX_ZP: {
			uWord addr = adm.addrm_zp(PC, RAM);
			sByte arg = RAM.read(addr);
			ins.ldr(arg, X, PS);
			break;
		}
		case LDX_ZPY: {
			uWord addr = adm.addrm_zpy(PC, RAM, Y);
			sByte arg = RAM.read(addr);
			ins.ldr(arg, X, PS);
			break;
		}
		// LDY:
		case LDY_ABS: {
			uWord addr = adm.addrm_abs(PC, RAM);
			sByte arg = RAM.read(addr);
			ins.ldr(arg, Y, PS);
			break;
		}
		case LDY_ABSX: {
			uWord addr = adm.addrm_absx(PC, RAM, X);
			sByte arg = RAM.read(addr);
			ins.ldr(arg, Y, PS);
			break;
		}
		case LDY_IMME: {
			sByte arg = adm.addrm_imme(PC, RAM);
			ins.ldr(arg, Y, PS);
			break;
		}
		case LDY_ZP: {
			uWord addr = adm.addrm_zp(PC, RAM);
			sByte arg = RAM.read(addr);
			ins.ldr(arg, Y, PS);
			break;
		}
		case LDY_ZPX: {
			uWord addr = adm.addrm_zpx(PC, RAM, X);
			sByte arg = RAM.read(addr);
			ins.ldr(arg, Y, PS);
			break;
		}
		// Store Instructions:
		//
		// STA:
		case STA_ABS: {
			uWord addr = adm.addrm_abs(PC, RAM);
			ins.str(addr, A, RAM);
			break;
		}
		case STA_ABSX: {
			uWord addr = adm.addrm_absx(PC, RAM, X);
			ins.str(addr, A, RAM);
			break;
		}
		case STA_ABSY: {
			uWord addr = adm.addrm_absy(PC, RAM, Y);
			ins.str(addr, A, RAM);
			break;
		}
		case STA_ZP: {
			uWord addr = adm.addrm_zp(PC, RAM);
			ins.str(addr, A, RAM);
			break;
		}
		case STA_ZPX: {
			uWord addr = adm.addrm_zpx(PC, RAM, X);
			ins.str(addr, A, RAM);
			break;
		}
		case STA_IDXIDRX: {
			uWord addr = adm.addrm_idxidrx(PC, X, RAM);
			ins.str(addr, A, RAM);
			break;
		}
		case STA_IDRIDXY: {
			uWord addr = adm.addrm_idridxy(PC, Y, RAM);
			ins.str(addr, A, RAM);
			break;
		}
		// STX:
		case STX_ABS: {
			uWord addr = adm.addrm_abs(PC, RAM);
			ins.str(addr, X, RAM);
			break;
		}
		case STX_ZP: {
			uWord addr = adm.addrm_zp(PC, RAM);
			ins.str(addr, X, RAM);
			break;
		}
		case STX_ZPY: {
			uWord addr = adm.addrm_zpx(PC, RAM, Y);
			ins.str(addr, X, RAM);
			break;
		}
		// STY:
		case STY_ABS: {
			uWord addr = adm.addrm_abs(PC, RAM);
			ins.str(addr, Y, RAM);
			break;
		}
		case STY_ZP: {
			uWord addr = adm.addrm_zp(PC, RAM);
			ins.str(addr, Y, RAM);
			break;
		}
		case STY_ZPX: {
			uWord addr = adm.addrm_zpx(PC, RAM, X);
			ins.str(addr, Y, RAM);
			break;
		}
		// Arithmetic Instructions:
		//
		// ADC:
		case ADC_ABS: {
			uWord addr = adm.addrm_abs(PC, RAM);
			sByte arg = RAM.read(addr);
			ins.adc(arg, A, PS);
			break;
		}
		case ADC_ABSX: {
			uWord addr = adm.addrm_absx(PC, RAM, X);
			sByte arg = RAM.read(addr);
			ins.adc(arg, A, PS);
			break;
		}
		case ADC_ABSY: {
			uWord addr = adm.addrm_absy(PC, RAM, Y);
			sByte arg = RAM.read(addr);
			ins.adc(arg, A, PS);
			break;
		}
		case ADC_IMME: {
			sByte arg = adm.addrm_imme(PC, RAM);
			ins.adc(arg, A, PS);
			break;
		}
		case ADC_ZP: {
			uWord addr = adm.addrm_zp(PC, RAM);
			sByte arg = RAM.read(addr);
			ins.adc(arg, A, PS);
			break;
		}
		case ADC_ZPX: {
			uWord addr = adm.addrm_zpx(PC, RAM, X);
			sByte arg = RAM.read(addr);
			ins.adc(arg, A, PS);
			break;
		}
		case ADC_IDXIDRX: {
			uWord addr = adm.addrm_idxidrx(PC, X, RAM);
			sByte arg = RAM.read(addr);
			ins.adc(arg, A, PS);
			break;
		}
		case ADC_IDRIDXY: {
			uWord addr = adm.addrm_idridxy(PC, Y, RAM);
			sByte arg = RAM.read(addr);
			ins.adc(arg, A, PS);
			break;
		}
		// SBC:
		case SBC_ABS: {
			uWord addr = adm.addrm_abs(PC, RAM);
			sByte arg = RAM.read(addr);
			ins.sbc(arg, A, PS);
			break;
		}
		case SBC_ABSX: {
			uWord addr = adm.addrm_absx(PC, RAM, X);
			sByte arg = RAM.read(addr);
			ins.sbc(arg, A, PS);
			break;
		}
		case SBC_ABSY: {
			uWord addr = adm.addrm_absy(PC, RAM, Y);
			sByte arg = RAM.read(addr);
			ins.sbc(arg, A, PS);
			break;
		}
		case SBC_IMME: {
			sByte arg = adm.addrm_imme(PC, RAM);
			ins.sbc(arg, A, PS);
			break;
		}
		case SBC_ZP: {
			uWord addr = adm.addrm_zp(PC, RAM);
			sByte arg = RAM.read(addr);
			ins.sbc(arg, A, PS);
			break;
		}
		case SBC_ZPX: {
			uWord addr = adm.addrm_zpx(PC, RAM, X);
			sByte arg = RAM.read(addr);
			ins.sbc(arg, A, PS);
			break;
		}
		case SBC_IDXIDRX: {
			uWord addr = adm.addrm_idxidrx(PC, X, RAM);
			sByte arg = RAM.read(addr);
			ins.sbc(arg, A, PS);
			break;
		}
		case SBC_IDRIDXY: {
			uWord addr = adm.addrm_idridxy(PC, Y, RAM);
			sByte arg = RAM.read(addr);
			ins.sbc(arg, A, PS);
			break;
		}
		// Increment Instructions:
		//
		// INC:
		case INC_ABS: {
			uWord addr = adm.addrm_abs(PC, RAM);
			ins.inc(addr, RAM, PS);
			break;
		}
		case INC_ABSX: {
			uWord addr = adm.addrm_absx(PC, RAM, X);
			ins.inc(addr, RAM, PS);
			break;
		}
		case INC_ZP: {
			uWord addr = adm.addrm_zp(PC, RAM);
			ins.inc(addr, RAM, PS);
			break;
		}
		case INC_ZPX: {
			uWord addr = adm.addrm_zpx(PC, RAM, X);
			ins.inc(addr, RAM, PS);
			break;
		}
		// INX:
		case INX_IMPL: {
			ins.inr(X, PS);
			break;
		}
		// INY:
		case INY_IMPL: {
			ins.inr(Y, PS);
			break;
		}
		// Decrement Instructions:
		//
		// DEC:
		case DEC_ABS: {
			uWord addr = adm.addrm_abs(PC, RAM);
			ins.dec(addr, RAM, PS);
			break;
		}
		case DEC_ABSX: {
			uWord addr = adm.addrm_absx(PC, RAM, X);
			ins.dec(addr, RAM, PS);
			break;
		}
		case DEC_ZP: {
			uWord addr = adm.addrm_zp(PC, RAM);
			ins.dec(addr, RAM, PS);
			break;
		}
		case DEC_ZPX: {
			uWord addr = adm.addrm_zpx(PC, RAM, X);
			ins.dec(addr, RAM, PS);
			break;
		}
		// DEX:
		case DEX_IMPL: {
			ins.der(X, PS);
			break;
		}
		// DEY:
		case DEY_IMPL: {
			ins.der(Y, PS);
			break;
		}
		// Logic Instructions:
		//
		// AND:
		case AND_ABS: {
			uWord addr = adm.addrm_abs(PC, RAM);
			sByte arg = RAM.read(addr);
			ins.logicAND(arg, A, PS);
			break;
		}
		case AND_ABSX: {
			uWord addr = adm.addrm_absx(PC, RAM, X);
			sByte arg = RAM.read(addr);
			ins.logicAND(arg, A, PS);
			break;
		}
		case AND_ABSY: {
			uWord addr = adm.addrm_absy(PC, RAM, Y);
			sByte arg = RAM.read(addr);
			ins.logicAND(arg, A, PS);
			break;
		}
		case AND_IMME: {
			sByte arg = adm.addrm_imme(PC, RAM);
			ins.logicAND(arg, A, PS);
			break;
		}
		case AND_ZP: {
			uWord addr = adm.addrm_zp(PC, RAM);
			sByte arg = RAM.read(addr);
			ins.logicAND(arg, A, PS);
			break;
		}
		case AND_ZPX: {
			uWord addr = adm.addrm_zpx(PC, RAM, X);
			sByte arg = RAM.read(addr);
			ins.logicAND(arg, A, PS);
			break;
		}
		case AND_IDXIDRX: {
			uWord addr = adm.addrm_idxidrx(PC, X, RAM);
			sByte arg = RAM.read(addr);
			ins.logicAND(arg, A, PS);
			break;
		}
		case AND_IDRIDXY: {
			uWord addr = adm.addrm_idridxy(PC, Y, RAM);
			sByte arg = RAM.read(addr);
			ins.logicAND(arg, A, PS);
			break;
		}
		// ORA:
		case ORA_ABS: {
			uWord addr = adm.addrm_abs(PC, RAM);
			sByte arg = RAM.read(addr);
			ins.logicOR(arg, A, PS);
			break;
		}
		case ORA_ABSX: {
			uWord addr = adm.addrm_absx(PC, RAM, X);
			sByte arg = RAM.read(addr);
			ins.logicOR(arg, A, PS);
			break;
		}
		case ORA_ABSY: {
			uWord addr = adm.addrm_absy(PC, RAM, Y);
			sByte arg = RAM.read(addr);
			ins.logicOR(arg, A, PS);
			break;
		}
		case ORA_IMME: {
			sByte arg = adm.addrm_imme(PC, RAM);
			ins.logicOR(arg, A, PS);
			break;
		}
		case ORA_ZP: {
			uWord addr = adm.addrm_zp(PC, RAM);
			sByte arg = RAM.read(addr);
			ins.logicOR(arg, A, PS);
			break;
		}
		case ORA_ZPX: {
			uWord addr = adm.addrm_zpx(PC, RAM, X);
			sByte arg = RAM.read(addr);
			ins.logicOR(arg, A, PS);
			break;
		}
		case ORA_IDXIDRX: {
			uWord addr = adm.addrm_idxidrx(PC, X, RAM);
			sByte arg = RAM.read(addr);
			ins.logicOR(arg, A, PS);
			break;
		}
		case ORA_IDRIDXY: {
			uWord addr = adm.addrm_idridxy(PC, Y, RAM);
			sByte arg = RAM.read(addr);
			ins.logicOR(arg, A, PS);
			break;
		}
		// EOR:
		case EOR_ABS: {
			uWord addr = adm.addrm_abs(PC, RAM);
			sByte arg = RAM.read(addr);
			ins.logicXOR(arg, A, PS);
			break;
		}
		case EOR_ABSX: {
			uWord addr = adm.addrm_absx(PC, RAM, X);
			sByte arg = RAM.read(addr);
			ins.logicXOR(arg, A, PS);
			break;
		}
		case EOR_ABSY: {
			uWord addr = adm.addrm_absy(PC, RAM, Y);
			sByte arg = RAM.read(addr);
			ins.logicXOR(arg, A, PS);
			break;
		}
		case EOR_IMME: {
			sByte arg = adm.addrm_imme(PC, RAM);
			ins.logicXOR(arg, A, PS);
			break;
		}
		case EOR_ZP: {
			uWord addr = adm.addrm_zp(PC, RAM);
			sByte arg = RAM.read(addr);
			ins.logicXOR(arg, A, PS);
			break;
		}
		case EOR_ZPX: {
			uWord addr = adm.addrm_zpx(PC, RAM, X);
			sByte arg = RAM.read(addr);
			ins.logicXOR(arg, A, PS);
			break;
		}
		case EOR_IDXIDRX: {
			uWord addr = adm.addrm_idxidrx(PC, X, RAM);
			sByte arg = RAM.read(addr);
			ins.logicXOR(arg, A, PS);
			break;
		}
		case EOR_IDRIDXY: {
			uWord addr = adm.addrm_idridxy(PC, Y, RAM);
			sByte arg = RAM.read(addr);
			ins.logicXOR(arg, A, PS);
			break;
		}
		// Branch Instructions:
		case BCC_REL: {
			uWord addr = adm.addrm_rel(PC, RAM);
			ins.bcc(addr, PS, PC);
			break;
		}
		case BCS_REL: {
			uWord addr = adm.addrm_rel(PC, RAM);
			ins.bcs(addr, PS, PC);
			break;
		}
		case BNE_REL: {
			uWord addr = adm.addrm_rel(PC, RAM);
			ins.bne(addr, PS, PC);
			break;
		}
		case BEQ_REL: {
			uWord addr = adm.addrm_rel(PC, RAM);
			ins.beq(addr, PS, PC);
			break;
		}
		case BPL_REL: {
			uWord addr = adm.addrm_rel(PC, RAM);
			ins.bpl(addr, PS, PC);
			break;
		}
		case BMI_REL: {
			uWord addr = adm.addrm_rel(PC, RAM);
			ins.bmi(addr, PS, PC);
			break;
		}
		case BVC_REL: {
			uWord addr = adm.addrm_rel(PC, RAM);
			ins.bvc(addr, PS, PC);
			break;
		}
		case BVS_REL: {
			uWord addr = adm.addrm_rel(PC, RAM);
			ins.bvs(addr, PS, PC);
			break;
		}
	}
}
