#ifndef PROCESSOR_STATUS_HPP
#define PROCESSOR_STATUS_HPP

#include "bit_width.hpp"

class ProcessorStatus {
       public:
	struct Flag {
		uByte C : 1;
		uByte Z : 1;
		uByte I : 1;
		uByte D : 1;
		uByte B : 1;
		uByte U : 1;
		uByte V : 1;
		uByte N : 1;
	};
	union {
		uByte Status;
		Flag StatusFlag;
	};
	ProcessorStatus();
	void setPS(sByte byte);
	sByte getPS();
};

#endif
