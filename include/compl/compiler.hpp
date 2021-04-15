#ifndef COMPILER_HPP
#define COMPILER_HPP
#include <fstream>
#include <string>
#include <vector>

#include "json.hpp"
#include "program_counter.hpp"
#include "ram.hpp"
using namespace std;
using json = nlohmann::json;
class Compiler {
	vector<string> tokens;
	string line;
	json json_root;
	Ram& ram_;

       public:
	bool flag;
	Compiler(ifstream& iFile, Ram& ram);
	void compile();
};

#endif
