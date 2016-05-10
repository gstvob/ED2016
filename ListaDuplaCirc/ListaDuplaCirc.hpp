//! Copyright 2016 Gustavo Borges França
#include "ElementoDuplo.hpp"

template <typename T>
/*!
 * @brief Implementação de uma lista duplamente circular.
 */
class ListaDuplaCirc {
 private:
    ElementoDuplo<T> *head; /*<! Ponteiro do elemento cabeça da lista.*/
    ElementoDuplo<T> *sentry;/*<! Ponteiro do elemento sentinela da lista*/
    int size;/*<! inteiro para indicar o tamanho da lista>*/

 public:
 /*!
  * @brief construtor que inicializa a cabeça, o sentinela e o tamanho da lista.
  */
	ListaDuplaCirc() {
	    sentry = new ElementoDuplo<T>(0, nullptr, nullptr);
	    head = sentry;
	    size = 0;
	}
/*!
 * @brief destrutor que deleta a lista chamando o método destroiListaDuplo()
 * @see destroiListaDuplo().
 */
	~ListaDuplaCirc() {
	    destroiListaDuplo();
	}
/*!
 * @brief método para adicionar um dado no inicio da lista duplamente circular.
 * @param posição na memória de um genérico que é o dado que vai ser adicionado.
 * sem valor de retorno.
 */
	void adicionaNoInicioDuplo(const T& dado) {
	    ElementoDuplo<T> *novo;
	    novo = new ElementoDuplo<T>(dado, sentry, nullptr);
        if (sentry->getSucessor() != nullptr) {
        	sentry->getSucessor()->setAnterior(novo);
        	novo->setSucessor(sentry->getSucessor());
        } else {
        	novo->setSucessor(sentry);
        	novo->setAnterior(sentry);
        	sentry->setAnterior(novo);
        }
        sentry->setSucessor(novo);
        size++;
	}
/*!
 * @brief Método para retirar o dado que está no inicio da lista.
 * @return um genérico que é o dado retirado.
 * @see listaVazia()
 */
	T retiraDoInicioDuplo() {
	    if (listaVazia()) {
	        throw "Erro lista vazia";
	    } else {
	        ElementoDuplo<T>* sai;
	        sai = sentry->getSucessor();
	        T volta = sai->getInfo();
	       	sentry->setSucessor(sai->getSucessor());
	        sentry->getSucessor()->setAnterior(sentry);
	        delete sai;
	        size--;
	        return volta;
	    }
	}
/*!
 * @brief método igual ao retiraDoInicio, só que sem o valor de retorno.
 * @see retiraDoInicio().
 * sem valor de retorno e sem parametros.
 */
	void eliminaDoInicioDuplo() {
	    if (listaVazia()) {
	        throw "ERROLISTAVAZIA";
	    } else {
	        ElementoDuplo<T>* remover = sentry->getSucessor();
	        sentry->setSucessor(remover->getSucessor());
	        sentry->getSucessor()->setAnterior(sentry);
	        delete remover;
	        size--;
	    }
	}
/*!
 * @brief Método para adicionar um dado em uma determinada posição da lista
 * @param dado, a posição na memória de um genérico que é o dado que vai ser add
 * @param inteiro que indica a posição em que se quer adicionar o dado.
 * Método faz as verificações, e se tudo ocorrer certo adiciona o dado aonde se
 * quer adicionar.
 * @see listaVazia()
 */
	void adicionaNaPosicaoDuplo(const T& dado, int pos) {
	    if (pos < 0 || pos > size) {
	        throw "ERROPOSICAO";
	    } else {
	        if (pos == 0 || listaVazia()) {
	            adicionaNoInicioDuplo(dado);
	        } else if (pos == size) {
	            ElementoDuplo<T> *nov, *anterior;
	            nov = new ElementoDuplo<T>(dado, nullptr, sentry);
	            anterior = sentry->getAnterior();
	            anterior->setSucessor(nov);
	            nov->setAnterior(anterior);
	            sentry->setAnterior(nov);
	            size++;
	        } else {
	            ElementoDuplo<T> *novo, *walker;
	            walker = sentry->getSucessor();
	            for (int i = 0; i < pos - 1; i++) {
	                walker = walker->getSucessor();
	            }
	            novo = new ElementoDuplo<T>(dado, walker, walker->getSucessor());
	            novo->getSucessor()->setAnterior(novo);
	            walker->setSucessor(novo);
	            size++;
	        }
	    }
	}
/*!
 * @brief método para saber a posição de um determinado dado.
 * @param posição na memória do dado que se quer saber a posição.
 * @return inteiro, a posição do dado passado como parâmetro.
 * método faz as verificações e retorna a posição ou joga uma exceção dependendo
 * @see listaVazia()
 */
	int posicaoDuplo(const T& dado) const {
	    if (listaVazia()) {
	        throw "LISTAVAZIA";
	    } else {
	        ElementoDuplo<T>* walker = sentry->getSucessor();
	        int i = 0;
	        for (i; i < size; i++) {
	            if (walker->getInfo() == dado) {
	                return i;
	            }
	            walker = walker->getSucessor();
	        }
	        throw "ELEMENTOINEXISTENTE";
	    }
	}
/*!
 * @brief Método para retornar a posição na memória de um dado especifico.
 * @param dado, A posição na memória de um genérico.
 * @return a posição na memória do dado.
 * método faz as verificações e laços e retorna a posição, ou joga uma exceção
 * estrutura do método quase igual ao posicaoDuplo()
 * @see posicaoDuplo, listaVazia
 */
	T* posicaoMemDuplo(const T& dado) const {
		    if (listaVazia()) {
	        throw "LISTAVAZIA";
	    } else {
	        ElementoDuplo<T> * walker = sentry;
	        int i;
	        for (i = 0; i <= size; i++) {
	            if (walker->getInfo() == dado) {
	                return &walker->getInfo();
	            }
	            walker = walker->getSucessor();
	        }
	        throw "ELEMENTOINEXISTENTE";
	    }
	}
/*!
 * @brief método para verificar se um dado existe na lista.
 * @param dado, A posição na memória de um genérico.
 * @return boolean, verdadeiro caso o dado exista na lista, falso caso não.
 * O método tem uma estrutura muito similar aos posicaoMemDuplo e posicaoDuplo,
 * diferença é que seu retorno é boolean.
 * @see posicaoMemDuplo(), posicao(), listaVazia()
 */
	bool contemDuplo(const T& dado) {
	    if (listaVazia()) {
	        return false;
	    } else {
	        ElementoDuplo<T> * walker = sentry->getSucessor();
	        int i;
	        for (i = 0; i < size; i++) {
	            if (walker->getInfo() == dado) {
	                return true;
	            }
	            walker = walker->getSucessor();
	        }
	        return false;
	    }
	}
/*!
 * @brief método para retirar um elemento de uma determinada posição.
 * @param inteiro que é a posição em que se encontra o dado que se quer retirar.
 * @return genérico que é o dado do elemento retirado.
 * o método faz suas verificações, que são similares ao adicionaNaPosicaoDuplo,
 * e retira o dado quando chega na posição que foi especificada.
 * @see adicionaNaPosicaoDuplo().
 */
	T retiraDaPosicaoDuplo(int pos) {
	    if (pos < 0 || pos > size) {
	        throw "ERRPOSICAO";
	    } else {
	        if (pos == 0) {
	            return retiraDoInicioDuplo();
	        } else if (pos == size) {
	        	ElementoDuplo<T>* remover;
	        	remover = sentry->getAnterior();
	        	remover->getAnterior()->setSucessor(sentry);
	        	remover->getSucessor()->setAnterior(remover->getAnterior());
	        	T volta = remover->getInfo();
	        	delete remover;
	        	size--;
	        	return volta;
	        } else {
	            ElementoDuplo<T> *remover, *walker;
	            walker = sentry->getSucessor();
	            for (int i = 0; i < pos - 1; i++) {
	                walker = walker->getSucessor();
	            }
	            remover = walker->getSucessor();
	            T ret = remover->getInfo();
	            walker->setSucessor(remover->getSucessor());
				remover->getSucessor()->setAnterior(walker);
	            delete remover;
	            size--;
	            return ret;
	        }
	    }
	}
/*!
 * @brief método para adicionar um dado na ultima posição da lista.
 * @param posição na memória do dado que quer se adicionar.
 * @see adicionaNoInicioDuplo(), adicionaNaPosicaoDuplo()
 */
	void adicionaDuplo(const T& dado) {
	    if (listaVazia()) {
	        adicionaNoInicioDuplo(dado);
	    } else {
	        adicionaNaPosicaoDuplo(dado, size);
	    }
	}
/*!
 * @brief método para retirar o ultimo elemento da lista.
 * @return genérico que é o dado do elemento retirado da lista.
 * @see retiraDaPosicaoDuplo()
 */
	T retiraDuplo() {
	    if (listaVazia()) {
	        throw "ERROLISTAVAZIA";
	    } else {
	       return retiraDaPosicaoDuplo(size-1);
	    }
	}
/*!
 * @brief retira um dado especifico da lista
 * @param posição na memória do generico que se quer retirar da lista.
 * @return o dado do elemetno retirado.
 * @see retiraDaPosicaoDUplo(), posicaoDuplo().
 */
	T retiraEspecificoDuplo(const T& dado) {
		if (listaVazia()) {
	        throw "ERROLISTAVAZIA";
	    } else {
	        return retiraDaPosicaoDuplo(posicaoDuplo(dado));
	    }
	}
/*!
 * @brief mostra o dado do elemento que está em determinada posição.
 * @param inteiro posição em que está o dado que se quer ver.
 * @return dado que está na posição passada como parametro.
 * @see listaVazia().
 */
	T mostra(int pos) {
	    if (listaVazia()) {
	        throw "ERROLISTAVAZIA()";
	    } else if (pos < 0 || pos > size) {
	        throw "ERROPOSICAO";
	    } else {
	        ElementoDuplo<T>* walker = sentry->getSucessor();
	        for (int i = 0; i < pos; i++) {
	            walker = walker->getSucessor();
	        }
	        return walker->getInfo();
	    }
	}
/*!
 * @brief método que adiciona os elementos em ordem.
 * @param data, posição na memória do dado que vai ser adicionado
 * o método faz as suas verificações, e procura onde o dado deve ser adicionado
 * @see adicionaNaPosicaoDuplo(), listaVazia(), adicionaNoInicio(), maior().
 */
	void adicionaEmOrdem(const T& data) {
	    ElementoDuplo<T> *atual;
	    int posi;
	    if (listaVazia()) {
	        adicionaNoInicioDuplo(data);
	    } else {
	        atual = sentry->getSucessor();
	        posi = 1;
	        while (atual->getSucessor() != sentry &&
	                maior(data, atual->getInfo())) {
	            atual = atual->getSucessor();
	            posi++;
	       }
	       if (maior(data, atual->getInfo())) {
	            adicionaNaPosicaoDuplo(data, posi+1);
	       } else {
	            adicionaNaPosicaoDuplo(data, posi-1);
	       }
	    }
	}
/*!
 * @brief método para saber a posição do ultimo elemento.
 * @return inteiro que é a posição do ultimo elemento.
 */
	int verUltimo() {
	    return size-1;
	}
/*!
 * @brief método para saber se a lista está vazia.
 * @return boolean que é verdadeiro se ela estiver, falso caso não.
 */
	bool listaVazia() const {
	    return size == 0;
	}
/*!
 * @brief método para saber se um dado é igual a outro.
 * @param dado1, um genérico que será comparado a outro.
 * @param dado2, outro genérico que sera comparado a um.
 * @return boolean verdadeiro se os dados forem iguais, falso caso não.
 */
	bool igual(T dado1, T dado2) {
	    return dado1 == dado2;
	}
/*!
 * @brief método para saber se um dado é maior que outro.
 * @param dado1, um genérico que será comparado a outro.
 * @param dado2, outro genérico que sera comparado a um.
 * @return boolean verdadeiro se dado1 for maior que dado2, falso caso não.
 */
	bool maior(T dado1, T dado2) {
	    return dado1 > dado2;
	}
/*!
 * @brief método para saber se um dado é menor que outro.
 * @param dado1, um genérico que será comparado a outro.
 * @param dado2, outro genérico que sera comparado a um.
 * @return boolean verdadeiro se dado1 for menor que dado2, falso caso não.
 */
	bool menor(T dado1, T dado2) {
	    return dado1 < dado2;
	}
/*!
 * @brief método para destruir/deletar a lista.
 * método apenas faz um laço e vai chamando o método eliminaDoInicioDuplo()
 * e só irá parar quando a lista estiver vazia, ou seja, seu size == 0;
 * @see eliminaDoInicioDuplo();
 */
	void destroiListaDuplo() {
	   while (!listaVazia()) {
	   		eliminaDoInicioDuplo();
	   }
	   head = sentry;
	   size = 0;
	}
};

