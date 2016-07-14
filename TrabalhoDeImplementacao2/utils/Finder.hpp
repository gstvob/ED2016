#ifndef Finder_HPP_
#define Finder_HPP_
#include <strings.h>
#include <fstream>
#include "word_helper.hpp"

class Finder {
private:
	string search;

public:
	//Construtor
	Finder(string _search) {
		search = _search;
	}
	
	void BuscaChaveSecundaria() {
		cout << "Os termos não foram encontrados" << endl;
	}

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
