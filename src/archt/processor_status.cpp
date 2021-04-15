#include "processor_status.hpp"

#include "bit_width.hpp"

ProcessorStatus::ProcessorStatus() {
	StatusFlag.C = 0;
	StatusFlag.Z = 0;
	StatusFlag.I = 0;
	StatusFlag.D = 0;
	StatusFlag.B = 0;
	StatusFlag.U = 0;
	StatusFlag.V = 0;
	StatusFlag.N = 0;
}

void ProcessorStatus::setPS(sByte byte) {
	Status = (uByte)byte;
	StatusFlag.U = 0;
	return;
}

sByte ProcessorStatus::getPS() { return (sByte)Status; }
