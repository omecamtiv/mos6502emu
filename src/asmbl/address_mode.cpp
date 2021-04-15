#include "address_mode.hpp"

#include "bit_width.hpp"
#include "ram.hpp"

uWord AddressMode::addrm_rel(ProgramCounter& pc, Ram& ram) {
	uWord arg = (uWord)(uByte)ram.read(pc.getCounter());
	uWord counter = pc.getCounter();
	uWord addr = counter + arg;
	pc.incCounter();
	return addr;
}

sByte AddressMode::addrm_imme(ProgramCounter& pc, Ram& ram) {
	uByte value = (uByte)ram.read(pc.getCounter());
	pc.incCounter();
	return value;
}

uWord AddressMode::addrm_zp(ProgramCounter& pc, Ram& ram) {
	uWord addr = (uWord)(uByte)ram.read(pc.getCounter());
	pc.incCounter();
	return addr;
}

uWord AddressMode::addrm_zpx(ProgramCounter& pc, Ram& ram, Register& regx) {
	uByte x = (uByte)regx.getData();
	uByte zpx = (uByte)ram.read(pc.getCounter()) + x;
	uWord addr = (uWord)zpx;
	pc.incCounter();
	return addr;
}

uWord AddressMode::addrm_zpy(ProgramCounter& pc, Ram& ram, Register& regy) {
	uByte y = (uByte)regy.getData();
	uByte zpy = (uByte)ram.read(pc.getCounter()) + y;
	uWord addr = (uWord)zpy;
	pc.incCounter();
	return addr;
}

uWord AddressMode::addrm_abs(ProgramCounter& pc, Ram& ram) {
	uWord lsb = (uWord)(uByte)ram.read(pc.getCounter());
	pc.incCounter();
	uWord msb = (uWord)(uByte)ram.read(pc.getCounter());
	msb <<= 8;
	uWord addr = msb + lsb;
	pc.incCounter();
	return addr;
}

uWord AddressMode::addrm_absind(ProgramCounter& pc, Ram& ram) {
	uWord arg_lsb = (uWord)(uByte)ram.read(pc.getCounter());
	pc.incCounter();
	uWord arg_msb = (uWord)(uByte)ram.read(pc.getCounter());
	arg_msb <<= 8;
	uWord arg = arg_msb + arg_lsb;
	uWord lsb_addr = arg;
	uWord msb_addr = arg + 0x0001;
	uWord lsb = (uWord)(uByte)ram.read(lsb_addr);
	uWord msb = (uWord)(uByte)ram.read(msb_addr);
	msb <<= 8;
	uWord addr = msb + lsb;
	pc.incCounter();
	return addr;
}

uWord AddressMode::addrm_absx(ProgramCounter& pc, Ram& ram, Register& regx) {
	uWord lsb = (uWord)(uByte)ram.read(pc.getCounter());
	pc.incCounter();
	uWord msb = (uWord)(uByte)ram.read(pc.getCounter());
	msb <<= 8;
	uWord arg = msb + lsb;
	uWord x = (uWord)(uByte)regx.getData();
	uWord addr = arg + x;
	pc.incCounter();
	return addr;
}

uWord AddressMode::addrm_absy(ProgramCounter& pc, Ram& ram, Register& regy) {
	uWord lsb = (uWord)(uByte)ram.read(pc.getCounter());
	pc.incCounter();
	uWord msb = (uWord)(uByte)ram.read(pc.getCounter());
	msb <<= 8;
	uWord arg = msb + lsb;
	uWord y = (uWord)(uByte)regy.getData();
	uWord addr = arg + y;
	pc.incCounter();
	return addr;
}

uWord AddressMode::addrm_idxidrx(ProgramCounter& pc, Register& regx, Ram& ram) {
	uByte arg = (uByte)ram.read(pc.getCounter());
	uByte x = (uByte)regx.getData();
	uByte zpx = arg + x;
	uWord lsb_addr = (uWord)zpx;
	uWord msb_addr = lsb_addr + 0x0001;
	uWord lsb = (uWord)(uByte)ram.read(lsb_addr);
	uWord msb = (uWord)(uByte)ram.read(msb_addr);
	msb <<= 8;
	uWord addr = msb + lsb;
	sByte value = ram.read(addr);
	pc.incCounter();
	return value;
}

uWord AddressMode::addrm_idridxy(ProgramCounter& pc, Register& regy, Ram& ram) {
	uByte y = (uByte)regy.getData();
	uWord arg = (uWord)(uByte)ram.read(pc.getCounter());
	uWord lsb_addr = arg;
	uWord msb_addr = arg + 0x0001;
	uWord lsb = (uWord)(uByte)ram.read(lsb_addr);
	uWord msb = (uWord)(uByte)ram.read(msb_addr);
	msb <<= 8;
	uWord addr = msb + lsb + y;
	sByte value = ram.read(addr);
	pc.incCounter();
	return value;
}
