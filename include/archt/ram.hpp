#ifndef RAM_HPP
#define RAM_HPP
#include <map>

#include "bit_width.hpp"

class Ram {
	uWord pointer;
	std::map<uWord, sByte> ram;

       public:
	Ram();
	void write(uWord address, sByte data);
	sByte read(uWord address);
	void incMem(uWord address);
	void decMem(uWord address);
	sByte getStackPointer();
	void setStackPointer(sByte byte);
	void stackPush(sByte byte);
	sByte stackPull();
};

#endif
