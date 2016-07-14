/* Copyright Gustavo Borges França, Nathan Sargon Werlich */
#ifndef Finder_HPP_
#define Finder_HPP_
#include <strings.h>
#include <fstream>
#include "word_helper.hpp"
/*!
 * @brief classe que faz a busca por chaves-- sec ou prim.
 */
class Finder {
private:
	string search;

public:
	/*!
	 * @brief Construtor da classe finder
	 * @param string a busca que foi realizada.
	 */
	Finder(string _search) {
		search = _search;
	}
	
	/*!
	 * @brief método que realiza a busca por chave secundaria.
	 */
	void BuscaChaveSecundaria() {
		cout << "Os termos não foram encontrados" << endl;
	}
	/*!
	 * @brief método que realiza a busca por chave primaria.
	 * @details abre o arquivo .dat e vai até o fim do arquivo
	 * verificando se a busca existe em algum lugar.
	 */
	void BuscaChavePrimaria() {

		bool encontrouComando = false;
		ifstream chavesPrimarias("BuscaPorPrimarias.dat");
		string nomeDoComandoAtual, conteudo;
		while (!chavesPrimarias.eof()) {
			chavesPrimarias >> nomeDoComandoAtual;
			if (strcasecmp(nomeDoComandoAtual.c_str(), search.c_str()) == 0) {
				getline(chavesPrimarias, conteudo, '\3');
				cout << conteudo << endl;
				encontrouComando = true;
				break;
			} else {
				chavesPrimarias.ignore(numeric_limits<streamsize>::max(), '\3');
			}
		}
		chavesPrimarias.close();

		if (!encontrouComando) {
			cout << "Desculpe, não foi possível encontrar esse comando."
					<< endl;
		}
	}
};
#endif
