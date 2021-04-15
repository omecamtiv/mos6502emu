#include "ram.hpp"

#include "bit_width.hpp"

Ram::Ram() {
	uWord addr;
	// Initializing Zero Page Memory
	for (addr = 0x0000; addr <= 0x00FF; addr++) {
		ram[addr] = 0x00;
	}
	// Initializing Stack Memory
	for (addr = 0x0100; addr <= 0x01FF; addr++) {
		ram[addr];
	}
	// Initializing General Purpose Memory
	for (addr = 0x0200; addr <= 0xFFFF; addr++) {
		ram[addr] = 0x00;
		if (addr == 0xFFFF) {
			break;
		}
	}
}

void Ram::write(uWord address, sByte data) {
	ram[address] = data;
	return;
}

sByte Ram::read(uWord address) {
	sByte data;
	data = ram[address];
	return data;
}

void Ram::incMem(uWord address) {
	ram[address]++;
	return;
}

void Ram::decMem(uWord address) {
	ram[address]--;
	return;
}

sByte Ram::getStackPointer() {
	sByte stp;
	stp = (uWord)pointer - 0x0100;
	return stp;
}

void Ram::setStackPointer(sByte byte) {
	pointer = (uWord)byte + 0x0100;
	return;
}

void Ram::stackPush(sByte byte) {
	ram[pointer] = byte;
	--pointer;
	if (pointer < 0x0100) {
		pointer = 0x0100;
	}
	return;
}

sByte Ram::stackPull() { return ram[pointer]; }
