#include "compiler.hpp"

#include <fstream>
#include <sstream>

#include "bit_width.hpp"
#include "lexer.hpp"
using namespace std;

Compiler::Compiler(ifstream& iFile, Ram& ram) : ram_(ram) {
	flag = 0;
	while (getline(iFile, line)) {
		tokens.push_back(line);
	}
	iFile.close();
	ifstream jsonFile(OPCODES_JSON);
	jsonFile >> json_root;
	jsonFile.close();
}

void Compiler::compile() {
	for (string s : tokens) {
		vector<string> list;
		Lexer lexer(s);
		string instr = lexer.getInstr();
		string arg = lexer.getArg();
		string value = lexer.getValue();
		string line = lexer.getLine();
		json j = json_root[instr];
		if (value == "Error" || line == "Error") {
			flag = 1;
			break;
		}
		list.push_back(j[arg]);
		if (arg != "IMPL") {
			if (value.size() == 4) {
				list.push_back(value.substr(2, 2));
				list.push_back(value.substr(0, 2));
			} else {
				list.push_back(value);
			}
		}
		stringstream sstream;
		unsigned templine;
		sstream << line;
		sstream >> hex >> templine;
		uWord counter = (uWord)templine;
		if (!flag) {
			for (string h : list) {
				unsigned temp;
				sByte data;
				stringstream ss;
				ss << h;
				ss >> hex >> temp;
				data = (sByte)temp;
				ram_.write(counter, data);
				counter++;
			}
		}
	}
	return;
}
