/*Copyright Gustavo Borges, Nathan Werlich*/
#include <iostream>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include "utils/Indexer.hpp"
#include "utils/Finder.hpp"

using namespace std;

/*!
 * @brief método main que faz a indexação das manpages e cuida das buscas.
 */

int main(int argc, char **argv) {
	if (argc <= 2) {
		cout << "INSTRUÇÕES DE USO \n" <<
				"./main ManPages/* " << endl;
		return 1;
	} else {
		int cont = 0;
		if (cont < 1) {
			Indexer *index;
			index = new Indexer(argc, argv);
			cout << "Indexado com sucesso!" << endl;
			cont++;
		}
		int opcao = 1;
		while (opcao != 0) {
			cout << "MANPAGES SEARCH PROGRAM -- ESCOLHA UMA OPÇÃO \n " <<
					" 1 - Busca por chave primaria \n " <<
					" 2 - Busca por chave secundaria simples \n " <<
					" 3 - Busca por chave secundaria dupla \n " <<
					" 0 - Sair" << endl;
			cin >> opcao;
			
			switch(opcao) {
				case 0: {
					return 0;
					break;
				}
				case 1: {
					string busca;
					cout << "CHAVE PRIMARIA PARA BUSCAR : " << endl;
					cin >> busca;
					Finder *find = new Finder(busca);
					find->BuscaChavePrimaria();
					break;
				}
				case 2: {
					cout << "nao funfa" << endl;
					break;
				}		
				case 3: {
					cout << "nao funfa" << endl;
					break;
				}	
				default: {
					cout << "ERRO" << endl;
					break;
				}
			}			
		}
	}
}

