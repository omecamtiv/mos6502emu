#include "lexer.hpp"

#include <cctype>
#include <cstring>
#include <sstream>
#include <string>

Lexer::Lexer(string line) {
	stringstream sstream(line);
	string s;
	while (getline(sstream, s, ' ')) {
		tokens.push_back(s);
	}
	lineNo = tokens[0];
	instr = tokens[1];
	arg = tokens[2];
	if (arg == "") {
		argType = "IMPL";
	} else {
		int n = arg.size();
		for (int i = 0; i < n; i++) {
			switch (arg[i]) {
				case '$':
					argType += '$';
					break;
				case '(':
					argType += '(';
					break;
				case ')':
					argType += ')';
					break;
				case '#':
					argType += '#';
					break;
				case 'X':
					argType += 'X';
					break;
				case 'Y':
					argType += 'Y';
					break;
				case ',':
					argType += ',';
					break;
				default:
					argType += 'H';
					value += arg[i];
			}
		}
	}
}

string Lexer::getInstr() { return instr; }

string Lexer::getArg() { return argType; }

string Lexer::getValue() {
	bool flag = 0;
	int n = value.size();
	for (int i = 0; i < n; i++) {
		if (!isxdigit(value[i])) {
			flag = 1;
			break;
		}
	}
	if (flag) value = "Error";
	return value;
}

string Lexer::getLine() {
	bool flag = 0;
	int n = lineNo.size();
	if (n != 4) flag = 1;
	for (int i = 0; i < n; i++) {
		if (!isxdigit(lineNo[i])) {
			flag = 1;
			break;
		}
	}
	if (flag) lineNo = "Error";
	return lineNo;
}
