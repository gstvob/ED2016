#ifndef	REG_HPP_
#define REG_HPP_

#include <cstring>

class Reg {
public:

	char content[200000];  //Conteudo da ManPage

	char command[80];  // Comando
	
	Reg() {}
	/*!
	 * @brief Construtor
	 * @details Faz a copia de uma string para outra
	 */
	Reg(char command[80], char content[200000]) {
		strcpy(this->command, command);
		strcpy(this->content, content);
	}
	/*!
	 * @brief Metodo 'getContent'
	 * @details Metodo geter da variavel content
	 * @return Retorna a variavel 'content'
	 */
	char* getContent() {
		return content;
	}
	/*!
	 * @brief Metodo 'getCommand'
	 * @details Metodo geter da variavel command
	 * @return Retorna a variavel 'command'
	 */
	char* getCommand() {
		return command;
	}
	/*!
	 * @brief Metodo 'operator<'
	 * Faz a sobrecagar de operadores
	 */
	bool operator<(const Reg& m) const {
		return command < m.command;
	}
};
#endif
