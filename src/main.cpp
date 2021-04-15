#include <dirent.h>
#include <linux/limits.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

#include "bit_width.hpp"
#include "compiler.hpp"
#include "cpu.hpp"

vector<string> getFileList() {
	vector<string> list;
	DIR* dirp = opendir(SAVED_FILES);
	struct dirent* dp;
	while ((dp = readdir(dirp)) != NULL) {
		if (dp->d_type == DT_REG) {
			list.push_back(dp->d_name);
		}
	}
	return list;
}

int main() {
	char cfilename[20];
	system("clear");
	CPU cpu = CPU();
	cpu.reset();
	while (true) {
		char test[10];
		printf("[emu6502]$ ");
		scanf("%s", test);
		if (strcmp(test, "exit") == 0) {
			exit(0);
		} else if (strcmp(test, "dump") == 0) {
			cpu.dump();
		} else if (strcmp(test, "memdump") == 0) {
			unsigned int sBlock, eBlock;
			printf("[*] Enter Block [sBlock eBlock]: ");
			scanf("%04X %04X", &sBlock, &eBlock);
			cpu.memDump((uWord)sBlock, (uWord)eBlock);
		} else if (strcmp(test, "reset") == 0) {
			cpu.reset();
		} else if (strcmp(test, "run") == 0) {
			cpu.run();
			printf("[✓] Program Executed.\n");
		} else if (strcmp(test, "clear") == 0) {
			system("clear");
		} else if (strcmp(test, "compile") == 0) {
			printf("[*] List Of Files:\n");
			vector<string> vector;
			vector = getFileList();
			int i = 1;
			for (string file : vector) {
				printf("[%d] %s\n", i, file.c_str());
			}
			printf("\n");
			printf("[*] Enter File No: ");
			int n;
			scanf("%d", &n);
			if (n > vector.size()) {
				printf("[!] Invalid File No.\n");
			} else {
				string slash = "/";
				string file = vector[n - 1];
				string filename = SAVED_FILES + slash + file;
				ifstream cfile(filename.c_str());
				Compiler compiler(cfile, cpu.RAM);
				compiler.compile();
				if (compiler.flag)
					printf("[!] Compilation Error\n");
				else
					printf("[✓] Compiled.\n");
			}
		} else {
			printf("[!] Invalid Command.\n");
		}
	}
	return 0;
}
