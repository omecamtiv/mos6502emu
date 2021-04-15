#include "register.hpp"

Register::Register() { data = 0x00; };

void Register::setData(sByte byte) {
	data = byte;
	return;
}
void Register::incData() {
	data++;
	return;
}
void Register::decData() {
	data--;
	return;
}
sByte Register::getData() { return data; }
