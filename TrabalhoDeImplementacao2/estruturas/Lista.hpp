#ifndef LISTA_ENCADEDADA_HPP_
#define LISTA_ENCADEDADA_HPP_

#include <vector>

template<typename T>
class Lista {
private:
	std::vector<T> l;

public:

	Lista() {
	}

	Lista<T>* interseccao(Lista<T> *outra) {
		Lista<T> *interseccao = new Lista<T>();
		T info;

		for (int i = this->getTamanho() - 1; i > 0; i--) {
			info = this->getDado(i);
			for (int j = outra->getTamanho() - 1; j > 0; j--) {
				if (outra->getDado(j) == info) {
					interseccao->adiciona(info);
				}
			}
		}

		std::swap(this->l, interseccao->l);
		return interseccao;
	}

	void adiciona(T dado) {
		l.push_back(dado);
	}

	bool contem(T dado) {
		return std::find(l.begin(), l.end(), dado) != l.end();
	}

	T getDado(int posicao) {
		return l.at(posicao);
	}

	int getTamanho() {
		return l.size();
	}
};
#endif