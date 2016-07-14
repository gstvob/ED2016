#ifndef INDEXER_HPP_
#define INDEXER_HPP_

#include "../estruturas/NoAVL.hpp"
#include "word_helper.hpp"
#include "Reader.hpp"
#include "Reg.hpp"

#include <sstream>
#include <iostream> //cout
#include <fstream> //fstream
#include <cstring> //strcpy
#include <dirent.h>
#include <strings.h>
#include <vector>
#include <cstdlib>
#include <list>
#include <string>


using namespace std;
class Indexer {


private:
	NoAVL<Word> secondaryKeys;
	NoAVL<Reg> primaryKeys;
	int argc;
	char **argv;

public:
	Indexer(int _argc, char **_argv) {
		argc = _argc;
		argv = _argv;
		secondaryKeys = new NoAVL<Word>(NULL);
		primaryKeys = new NoAVL<Reg>(NULL);
		BeginIndex();

	}

	void BeginIndex() {
		cout << "Aguarde enquanto as indexações ocorrem " << endl;
		Index();
		Primariasdat();
		Secundariasdat();
	}

	void Index() {
		word_helper conectivos;

		//Indexa duas arvores : indices primarios e indices secundarios.
		for (int i = 1; i < argc; i++) {
			cout << "Indexando " << (i+1) << " de " << argc << endl;
			Reader *leitor = new Reader(argv[i]);
			Reg registro = leitor->readManpages();
			primaryKeys.inserir(registro, primaryKeys);

			//dai enquanto ele gera a arvore de primarios ele ja gera a de secundarios a partir dela.
			string temp, comando = registro.getCommand();
			stringstream stream(registro.getContent());
			while (stream >> temp) {

				//passa temp tudo pra minusculo.
				transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

				// cria string com todos os conectivos removidos o temp.
				string limpa = conectivos.remover_conectivo_unica_palavra(temp);
				if (limpa.size() > 2) {
					secondaryKeys.busca(limpa).addComandosQueTem(comando);
					Word p(limpa);
					p.addComandosQueTem(comando);
					secondaryKeys.insere(p);
				}
				temp.clear();
			}
		}
	}

	void Primariasdat() {
		ofstream output("BuscaPorPrimarias.dat");

		if (output.is_open()) {

			vector<Reg> regPosOrdem = primaryKeys.posOrdem(primaryKeys); // colocar o pós ordem aqui
			for (unsigned int i = 0; i < regPosOrdem.size(); i++) {
				output << regPosOrdem.at(i).getCommand();
				output << " ";
				output << regPosOrdem.at(i).getContent();
				output << "\3";
			}
			output.close();
		}
	}
	void Secundariasdat() {
		ofstream output("BuscaPorSecundarias.dat");

		if (output.is_open()) {
			vector<Word> wordPosOrdem = secondaryKeys.posOrdem(secondaryKeys); // colocar o pós ordem aqui depois
			for (unsigned int i = 0; i < wordPosOrdem.size(); i++) {
				output << wordPosOrdem.at(i).returnWord();
				Lista<string> comandos = wordPosOrdem.at(i).returnCmdContain();
				for (int j = 0; j < comandos.getTamanho(); j++) {
					output << ' ' << comandos.getDado(j);
				}
				output << endl;
			}
			output.close();
		}
	}
};

#endif
