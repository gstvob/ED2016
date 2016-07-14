#ifndef WORD_HPP_
#define WORD_HPP_

#include <string>

#include "../estruturas/Lista.hpp"


using namespace std;
class Word {
private:

	string word;

	Lista<string> cmdContain;

public:

	Word(string _word) {
		word = _word;
	}

	void addComandosQueTem(string cmd) {
		if (!cmdContain.contem(cmd)) {
			cmdContain.adiciona(cmd);
		}
	}

	Lista<string> returnCmdContain() {
		return cmdContain;
	}

	std::string returnWord() {
		return word;
	}

	bool operator<(const Word& rhs) const {
		return word < rhs.word;
	}

	bool operator==(const Word& rhs) const {
		return word == rhs.word;
	}

};
#endif
