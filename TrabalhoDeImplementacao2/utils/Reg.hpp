#ifndef	REG_HPP_
#define REG_HPP_

#include <cstring>

class Reg {
public:

	char content[200000];

	char command[80];
	
	Reg() {}

	Reg(char command[80], char content[200000]) {
		strcpy(this->command, command);
		strcpy(this->content, content);
	}

	char* getContent() {
		return content;
	}

	char* getCommand() {
		return command;
	}

	bool operator<(const Reg& m) const {
		return command < m.command;
	}
};
#endif
