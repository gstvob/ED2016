//! Copyright 2016 Gustavo Borges França && Nathan Werlich
#ifndef ELEMENTO_HPP
#define ELEMENTO_HPP
template<typename T>
//! Classe dos elementos da lista encadeada.
class Elemento {
 private:
	T *info;/*<Atributo que vai ser a informação que o elemento vai carregar*/
	Elemento<T>* _next; /*<Atributo que vai ser o segurar o próximo elemento*/

 public:
//! Construtor que inicializa o elemento com uma informação e o proximo elemento
/*!
 * @param info, endereço de memória de um generico que é a info do elemento.
 * @param next, ponteiro Elemento<T> que vai ser o indicador do prox elemento.
 */
	Elemento(const T& info, Elemento<T>* next) : info(new T(info)), _next(next) {}
//! Destrutor
/*!
 * apenas deleta a informação do elemento
 * @see Elemento()
 */
	~Elemento() {
		delete info;
	}
//! Getter do proximo elemento;
/*!
 * @return o proximo elemento da lista.
 */
	Elemento<T>* getProximo() const {
		return _next;
	}
//! Getter da informação do elemento.
/*!
 * @return a informação que o elemento carrega
 */
	T getInfo() const {
		return *info;
	}
//! Setter do proximo elemento
/*!
 * @param next, o proximo elemento que vai ser passado para setar como proximo
 * do elemento que chamou o set.
 */
	void setProximo(Elemento<T>* next) {
		_next = next;
	}
};

#endif
