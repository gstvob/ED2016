#ifndef WORD_HELPER_HPP_
#define WORD_HELPER_HPP_

#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>

#include "Word.hpp"

using namespace std;

class word_helper{
private:

	Lista<string>* conectivos; /*<! Lista de string dos conectivos proibidos>*/
	
	/*!
	 * @brief método para adicionar a lista de conectivos os proibidos.
	 */
	void Conectivos() {
		conectivos->adiciona("I");
		conectivos->adiciona("me");
		conectivos->adiciona("we");
		conectivos->adiciona("us");
		conectivos->adiciona("you");
		conectivos->adiciona("she");
		conectivos->adiciona("her");
		conectivos->adiciona("he");
		conectivos->adiciona("him");
		conectivos->adiciona("it");
		conectivos->adiciona("they");
		conectivos->adiciona("them");
		conectivos->adiciona("what");
		conectivos->adiciona("which");
		conectivos->adiciona("who");
		conectivos->adiciona("whom");
		conectivos->adiciona("whose");
		conectivos->adiciona("whichever");
		conectivos->adiciona("whoever");
		conectivos->adiciona("whomever");
		conectivos->adiciona("this");
		conectivos->adiciona("these");
		conectivos->adiciona("that");
		conectivos->adiciona("those");
		conectivos->adiciona("anybody");
		conectivos->adiciona("anyone");
		conectivos->adiciona("anything");
		conectivos->adiciona("each");
		conectivos->adiciona("either");
		conectivos->adiciona("everybody");
		conectivos->adiciona("everyone");
		conectivos->adiciona("everything");
		conectivos->adiciona("neither");
		conectivos->adiciona("nobody");
		conectivos->adiciona("nothing");
		conectivos->adiciona("one");
		conectivos->adiciona("somebody");
		conectivos->adiciona("someone");
		conectivos->adiciona("something");
		conectivos->adiciona("both");
		conectivos->adiciona("few");
		conectivos->adiciona("many");
		conectivos->adiciona("several");
		conectivos->adiciona("all");
		conectivos->adiciona("any");
		conectivos->adiciona("most");
		conectivos->adiciona("none");
		conectivos->adiciona("some");
		conectivos->adiciona("myself");
		conectivos->adiciona("ourselves");
		conectivos->adiciona("yourself");
		conectivos->adiciona("yourselves");
		conectivos->adiciona("himself");
		conectivos->adiciona("herself");
		conectivos->adiciona("itself");
		conectivos->adiciona("themselves");
		conectivos->adiciona("my");
		conectivos->adiciona("your");
		conectivos->adiciona("his");
		conectivos->adiciona("its");
		conectivos->adiciona("is");
		conectivos->adiciona("our");
		conectivos->adiciona("your");
		conectivos->adiciona("their");
		conectivos->adiciona("mine");
		conectivos->adiciona("yours");
		conectivos->adiciona("his");
		conectivos->adiciona("hers");
		conectivos->adiciona("ours");
		conectivos->adiciona("yours");
		conectivos->adiciona("theirs");
		conectivos->adiciona("aboard");
		conectivos->adiciona("about");
		conectivos->adiciona("above");
		conectivos->adiciona("across");
		conectivos->adiciona("after");
		conectivos->adiciona("against");
		conectivos->adiciona("ahead");
		conectivos->adiciona("along");
		conectivos->adiciona("amid");
		conectivos->adiciona("amidst");
		conectivos->adiciona("among");
		conectivos->adiciona("around");
		conectivos->adiciona("as");
		conectivos->adiciona("aside");
		conectivos->adiciona("at");
		conectivos->adiciona("athwart");
		conectivos->adiciona("atop");
		conectivos->adiciona("barring");
		conectivos->adiciona("because");
		conectivos->adiciona("before");
		conectivos->adiciona("behind");
		conectivos->adiciona("below");
		conectivos->adiciona("beneath");
		conectivos->adiciona("beside");
		conectivos->adiciona("besides");
		conectivos->adiciona("between");
		conectivos->adiciona("beyond");
		conectivos->adiciona("but");
		conectivos->adiciona("by");
		conectivos->adiciona("circa");
		conectivos->adiciona("concerning");
		conectivos->adiciona("despite");
		conectivos->adiciona("down");
		conectivos->adiciona("during");
		conectivos->adiciona("except");
		conectivos->adiciona("excluding");
		conectivos->adiciona("following");
		conectivos->adiciona("for");
		conectivos->adiciona("from");
		conectivos->adiciona("in");
		conectivos->adiciona("including");
		conectivos->adiciona("inside");
		conectivos->adiciona("instead");
		conectivos->adiciona("into");
		conectivos->adiciona("like");
		conectivos->adiciona("minus");
		conectivos->adiciona("near");
		conectivos->adiciona("of");
		conectivos->adiciona("off");
		conectivos->adiciona("on");
		conectivos->adiciona("onto");
		conectivos->adiciona("opposite");
		conectivos->adiciona("out");
		conectivos->adiciona("outside");
		conectivos->adiciona("over");
		conectivos->adiciona("past");
		conectivos->adiciona("plus");
		conectivos->adiciona("prior");
		conectivos->adiciona("regarding");
		conectivos->adiciona("regardless");
		conectivos->adiciona("save");
		conectivos->adiciona("since");
		conectivos->adiciona("tan");
		conectivos->adiciona("through");
		conectivos->adiciona("till");
		conectivos->adiciona("to");
		conectivos->adiciona("toward");
		conectivos->adiciona("towards");
		conectivos->adiciona("under");
		conectivos->adiciona("underneath");
		conectivos->adiciona("unlike");
		conectivos->adiciona("until");
		conectivos->adiciona("up");
		conectivos->adiciona("upon");
		conectivos->adiciona("versus");
		conectivos->adiciona("via");
		conectivos->adiciona("with");
		conectivos->adiciona("within");
		conectivos->adiciona("without");
		conectivos->adiciona("for");
		conectivos->adiciona("and");
		conectivos->adiciona("nor");
		conectivos->adiciona("but");
		conectivos->adiciona("or");
		conectivos->adiciona("yet");
		conectivos->adiciona("so");
		conectivos->adiciona("a");
		conectivos->adiciona("an");
		conectivos->adiciona("the");
		conectivos->adiciona("no");
	}

public:
	
	/*!
	 * @brief Construtor método helper. 
	 */
	word_helper() {
		conectivos = new Lista<string>();
		Conectivos();
	}

	/*!
	 * @brief método para remover os conectivos de uma string
	 * @param String que se deseja retirar os conectivos.
	 * @return string sem os conectivos.
	 */
	string remover_conectivo_unica_palavra(string palavra) {

		palavra = remover_caracteres_especiais(palavra);
		if (palavra.size() >= 3) {
			for (int i = 0; i < conectivos->getTamanho(); i++) {
				if (conectivos->getDado(i) == palavra) {
					return "";
				}
			}
		}
		return palavra;
	}

	/*!
	 * @brief método para remove os caracteres especiais de uma string.
	 * @param string que se deseja retirar os conectivos.
	 * @return string sem os caracteres especiais. 
	 */
	string remover_caracteres_especiais(string palavra) {
		char caracteres[] = "<>():'#;,.";
		for (unsigned int i = 0; i < strlen(caracteres); ++i) {
			palavra.erase(remove(palavra.begin(), palavra.end(), caracteres[i]),
					palavra.end());
		}
		return palavra;
	}

	/*!
	 * @brief método que separa uma string em uma lista de palavras.
	 * @param string que se deseja separar.
	 * @return Lista de string separadas em que cada elemento é uma palavra.
	 */
	Lista<string> separar_em_palavras(string busca) {
		Lista<string> termos;
		string temp;
		stringstream stream(busca);
		while (stream >> temp) {
			termos.adiciona(temp);
		}

		return termos;
	}

};
#endif
