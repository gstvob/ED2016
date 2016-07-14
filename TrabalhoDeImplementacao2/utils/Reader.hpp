#ifndef READER_HPP_
#define READER_HPP_

#include <cstring>
#include <fstream>
#include <sstream>
#include <string>

#include "Reg.hpp"

class Reader {
private:
	std::string arch;

public:
	Reader(std::string archive) {
		arch = archive;
	}

	Reg readManpages() {

		//transforma em uma filestream a cstring do arquivo.
		std::ifstream arquivoLido(arch.c_str());
		//se o arquivo que foi lido esta aberto então
		if (arquivoLido.is_open()) {

			int pos_barra = arch.find_last_of("/") + 1;
			int pos_ponto = arch.find_last_of(".");
			int quantidadeDeCaracteres = pos_ponto - pos_barra;
			std::string nomeDoComando = arch.substr(pos_barra,
					quantidadeDeCaracteres);

			char conteudo[200000];
			std::stringstream buffer;
			buffer << arquivoLido.rdbuf();
			strcpy(conteudo, buffer.str().c_str());

			char comando[80];
			strcpy(comando, nomeDoComando.c_str());

			Reg registroFinal(comando, conteudo);

			arquivoLido.close();

			return registroFinal;

		} else {
			throw "Arquivo não pode ser lido. Método ler_arquivo.";
		}
	}
};
#endif
