#ifndef LEXER_HPP
#define LEXER_HPP
#include <string>
#include <vector>
using namespace std;
class Lexer {
	string lineNo, instr, arg, argType, value;
	vector<string> tokens;

       public:
	Lexer(string line);
	string getLine();
	string getInstr();
	string getArg();
	string getValue();
};

#endif
