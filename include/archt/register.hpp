#ifndef REGISTER_HPP
#define REGISTER_HPP
#include "bit_width.hpp"

class Register {
	sByte data;

       public:
	Register();
	void setData(sByte byte);
	void incData();
	void decData();
	sByte getData();
};

#endif
