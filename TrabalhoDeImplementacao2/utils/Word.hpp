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
	/*!
	 * @brief Metodo addComandosQueTem
	 * @details Verifica se o comando ja existe caso ele não exista, adiciona o mesmo
	 * @param 'cmd' é o comando a ser adicionado
	 */
	void addComandosQueTem(string cmd) {
		if (!cmdContain.contem(cmd)) {
			cmdContain.adiciona(cmd);
		}
	}
	/*!
	 * @brief Metodo returnCmdContain
	 * @details Metodo para retorna a lista com os comandos
	 * @return Retorna a variavel 'cmdContain'
	 */
	Lista<string> returnCmdContain() {
		return cmdContain;
	}
	/*!
	 * @brief Metodo returnWord
	 * @details Metodo para retornar uma string word
	 * @return Retorna a string word
	 */
	std::string returnWord() {
		return word;
	}
	/*!
	 * @brief Metodo para sobrecarga do operador '<'
	 */
	bool operator<(const Word& rhs) const {
		return word < rhs.word;
	}
	/*!
	 * @brief Metodo para sobrecarga do operador '=='
	 */
	bool operator==(const Word& rhs) const {
		return word == rhs.word;
	}

};
#endif
