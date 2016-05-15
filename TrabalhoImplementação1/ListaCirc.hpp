//! Copyright 2016 Gustavo Borges França
#include "Elemento.hpp"
template <typename T>
//! Classe de implementação de uma Lista Circular Simples.
class ListaCirc {
 private:
    Elemento<T>* sentry; /*<! ponteiro do elemento sentinela para auxiliar na lista.>*/
 	Elemento<T>* head; /*<! ponteiro do elemento cabeça da lista.>*/
 	int size; /*<! inteiro para indicar o tamanho da lista.>*/

 public:
/*!
 * @brief Construtor que inicializa sentinela, faz a cabeça apontar para ele, e seta
 * o tamanho para 0.
 */
	ListaCirc() {
	   sentry = new Elemento<T>(0,sentry);
	   head = sentry;
	   size = 0;
	}
/*!
 * @brief destrutor da lista circular.
 * @see destroiLista()
 */
    ~ListaCirc() {
	    destroiLista();
	}
/*!
 * @brief método para adicionar um elemento no inicio da lista.
 * @param o endereço da memoria do dado que será adicionado da lista.
 * sem valor de retorno, e joga uma exceção caso algo dê errado.
 */
	void adicionaNoInicio(const T& dado) {
	    Elemento<T>* newE = new Elemento<T>(dado, nullptr);
	    if (newE != nullptr) {
	    	newE->setProximo(sentry->getProximo());
	    	sentry->setProximo(newE);
	    	size++;
	    } else {
	    	throw "ERROLISTACHEIA";
	    }
	}
/*!
 * @brief método que retira o primeiro elemento da lista e retorna seu dado.
 * @return um genérico que é a info do elemento retirado.
 * sem parâmetros, joga uma exceção caso a lista esteja vazia.
 * @see listaVazia()
 */
	T retiraDoInicio() {
	    if (listaVazia()) {
	       throw "ERROLISTAVAZIA";
	    } else {
	    	Elemento<T>* deleter = sentry->getProximo();
	        T volta = deleter->getInfo();
	        sentry->setProximo(deleter->getProximo());
	        delete(deleter);
	        size--;
	        return volta;
	    }
	}
/*!
 * @brief método para retirar o elemento do inicio sem retornar seu dado.
 * método similar ao de retirar do inicio, unica diferença é que esse não
 * tem valor de retorno, e como o retira do inicio joga uma exceção caso a
 * lista esteja vazia.
 * @see listaVazia(), retiraDoInicio()
 */
	void eliminaDoInicio() {
	    if (listaVazia()) {
	       throw "ERROLISTAVAZIA";
	    } else {
	    	Elemento<T>* deleter = sentry->getProximo();
	        sentry->setProximo(deleter->getProximo());
	        size--;
	        delete(deleter);
	   }
	}
/*!
 * @brief método que adiciona um elemento em uma determinada posição da lista.
 * @param posição na memoria de um generico que será o dado adicionado na lista.
 * @param inteiro que irá indicar a posição que o dado será colocado na lista.
 * sem valor de retorno, o método joga uma exceção caso a posição que lhe foi
 * passada for invalida.
 */
	void adicionaNaPosicao(const T& dado, int pos) {
        if (pos < 0 || pos > size) {
	        throw "ERROPOSICAO";
	    } else if (pos == 0 || listaVazia()) {
	        adicionaNoInicio(dado);
	    } else {
	        Elemento<T> *anterior, *atual;
	        anterior = sentry->getProximo();
	        for (int i = 0; i < pos-1; i++) {
	            anterior = anterior->getProximo();
	        }
	        atual = anterior->getProximo();
	        anterior->setProximo(new Elemento<T>(dado, atual));
	        size++;
	    }
	}
/*!
 * @brief método que retorna a posição na lista de um dado específico.
 * @param a posição na memória de um genérico que é o dado que se quer encontrar
 * @return inteiro que vai ser a posição que o dado se encontra na lista
 * se a lista estiver vazia, o método retorna -1, o que seria algo parecido com
 * uma exceção, e se o dado não existir na lista ele joga uma exceção.
 * @see listaVazia()
 */
	int posicao(const T& dado) const {
	    if (listaVazia()) {
	        return -1;
	    } else {
	         Elemento<T>* caminha = sentry->getProximo();
	         int i = 0;
	         while(i < size) {
	            if (caminha->getInfo() == dado) {
	                return i;
	            }
	            caminha = caminha->getProximo();
	            i++;
	         }
	         throw "ERROELEMENTOINEXISTENTE";
	   }
	}
/*!
 * @brief método para buscar a posição na memória de um dado específico.
 * @param a posição na memória de um genérico que é o dado que se quer encontrar
 * @return ponteiro que vai ser a posição na memória do dado passado como param
 * joga uma exceção se a lista estiver vazia, e joga outra se o dado não existir
 * na lista.
 * @see listaVazia()
 */
	T* posicaoMem(const T& dado) const {
	    if (listaVazia()) {
	        throw "ERROLISTAVAZIA";
	    } else {
	         Elemento<T>* caminha = sentry->getProximo();
	         int i;
	         for (i = 0; i < size; i++) {
	            if (caminha->getInfo() == dado) {
	                return &caminha->getInfo();
	            }
	            caminha = caminha->getProximo();
	         }
	         throw "ERROELEMENTOINEXISTENTE";
	   }
	}
/*!
 * @brief método para saber se um determinado dado está presente na lista.
 * @param posição na memoria de um generico que é o dado que vai ser procurado.
 * @return boolean, verdadeiro se o dado existir na lista, falso caso não.
 * método tem uma estrutura muito parecida com o que procura a posição, o que
 * difere é que o retorno é boolean.
 * @see posicao(), posicaoMem()
 */
	bool contem(const T& dado) {
	    if (listaVazia()) {
	        return false;
	    } else {
	         Elemento<T>* caminha = sentry->getProximo();
	         int i;
	         for (i = 0; i < size; i++) {
	            if (caminha->getInfo() == dado) {
	                return true;
	            }
	            caminha = caminha->getProximo();
	         }
	    }
	    return false;
	}
/*!
 * @brief método para retirar um dado de uma determinada posição.
 * @param inteiro que é a posição que vai ser retirado o elemento.
 * @return um genérico que vai ser o dado do elemento retirado.
 * joga uma exceção caso a posição seja invalida, e chama o retira do inicio
 * caso essa posição seja a posição inicial.
 * @see retiraDoInicio()
 */
	T retiraDaPosicao(int pos) {
	    Elemento<T> *anterior, *deleter;
	    T volta;
        if (pos < 0 || pos > this->size - 1) {
	        throw "ERROPOSICAO";
	    } else {
	       if (pos == 0) {
	        return(retiraDoInicio());
	       } else {
	            anterior = sentry->getProximo();
	            for (int i = 1; i < pos; i++) {
	                anterior = anterior->getProximo();
	            }
                deleter = anterior->getProximo();
	            volta = deleter->getInfo();
	            anterior->setProximo(deleter->getProximo());
	            size--;
	            delete(deleter);
	       }
	       return volta;
	    }
	    throw "ERROPOSICAO";
	}
/*
 * @brief método para adicionar um elemento ao fim da lista.
 * @param posição na memória de um generico que é o dado a ser adicionado.
 * se a lista estiver vazia o fim da lista é o inicio, logo chama o método
 * adicionaNoInicio(), se não estiver vazia, adicionaNaPosicao passando como
 * parametros o dado, e o tamanho da lista (já que sera adicionado no fim dela).
 * @see adicionaNoInicio(), listaVazia(), adicionaNaPosicao()
 */
	void adiciona(const T& dado) {
	    if (listaVazia()) {
	        adicionaNoInicio(dado);
	    } else {
	        adicionaNaPosicao(dado, size);
	    }
	}
/*!
 * @brief método para retirar um elemento do fim da lista.
 * @return um generico que é a info do elemento retirado.
 * é verificado se a lista está vazia, caso esteja uma exceção é jogada, caso
 * não esteja é retornado um retiraDaPosicao() assim deletando o ultimo elemento
 * da lista.
 * @see retiraDaPosicao(), listaVazia()
 */
	T retira() {
	    if (listaVazia()) {
	        throw "errolistavazia";
	    } else {
	        return retiraDaPosicao(size-1);
	    }
	}
/*!
 * @brief método para retirar um dado específico da lista.
 * @param a posição na memória de um genérico que vai ser a info de um elemento.
 * @return um genérico que é a info do elemento retirado.
 * verifica se a lista está vazia, caso não retorna um retiraDaPosicao() e passa
 * como parametro deste o método posicao().
 * @see listaVazia(), retiraDaPosicao(), posicao()
 */
	T retiraEspecifico(const T& dado) {
	    if (listaVazia()) {
	        throw "ERROLISTAVAZIA";
	    } else {
	        return retiraDaPosicao(posicao(dado));
	    }
	}
/*!
 * @brief método para mostrar o dado que se encontra em uma determinada posição.
 * @param int que serve para indicar onde tá o elemento que se quer saber o dado
 * @return um genérico que é a info do elemento que está na posição pos.
 * método apenas caminha na lista até a posição passada como parâmetro e 
 * retorna a info do elemento que está na posição.
 * @see listaVazia()
 */
	T mostra(int pos) {
	   if (listaVazia()) {
	        throw "ERRO";
	   }
	   Elemento<T>* walker = sentry;
	   for (int i = 0; i <= pos; i++) {
	        walker = walker->getProximo();
	   }
	   return walker->getInfo();
	}
/*!
 * @brief método para adicionar os elemento em ordem na lista.
 * @param a posição na memória do dado que vai ser add na lista.
 * método verifica se a lista está vazia, se estiver, é adicionado um elemento
 * no inicio da lista, senão é feita uma caminhada por toda a lista, até ela
 * chegar ao fim ou encontrar um elemento que seja maior que o dado, após isso
 * é feita a verificação para saber se o laço terminou pelo fim da fila ou 
 * foi achado um elemento que é maior que o data, e é chamado o método adiciona
 * NaPosicao()
 * @see listaVazia(), maior(), adicionaNaPosicao()
 */
	void adicionaEmOrdem(const T& data) {
	   	Elemento<T> *atual;
	    int pos;
	    if (listaVazia()) {
	        adicionaNoInicio(data);
	    } else {
	        atual = sentry->getProximo();
	        pos = 1;
	        while ((atual->getProximo() != sentry)
	               && (maior(data, atual->getInfo()))) {
	            atual = atual->getProximo();
	            pos++;
	        }
	        if (maior(data, atual->getInfo())) {
	            adicionaNaPosicao(data, pos+1);
	        } else {
	            adicionaNaPosicao(data, pos-1);
	        }
	    }
	}
/*!
 * @brief método para saber em que posição se encontra o ultimo elemento.
 * @return a posição do ultimo elemento.
 */
	int verUltimo() {
	  return size - 1;
	}
/*!
 * @brief método que retorna se a lista está vazia ou não.
 * @return boolean, verdadeiro se o size for igual a zero, falso se não
 * O método vai retornar verdadeiro quando a lista estiver vazia.
 */
	bool listaVazia() const {
	    return size == 0;
	}
/*! 
 * @brief Método para saber se um genérico é igual ao outro
 * @return boolean, verdadeiro caso os dados forem iguais, falso caso não.
 */
	bool igual(T dado1, T dado2) {
	    return dado1 == dado2;
	}
/*! 
 * @brief Método para saber se um genérico é maior ao outro
 * @return boolean, verdadeiro caso dado1 for maior que dado2, falso caso não.
 */
	bool maior(T dado1, T dado2) {
	    return dado1 > dado2;
	}
/*! 
 * @brief Método para saber se um genérico é menor ao outro
 * @return boolean, verdadeiro caso dado1 for menor que dado2, falso caso não.
 */
	bool menor(T dado1, T dado2) {
	    return dado1 < dado2;
	}
/*
 * @brief método para destruir a lista.
 * método destroi lista destroi a lista chamando o método elimina do inicio
 * até a lista ficar vazia.
 * @see eliminaDoInicio();
 */
    void destroiLista() {
		while (!listaVazia()) {
	 		eliminaDoInicio();
		}
	size = 0;
	sentry->setProximo(sentry);
	}
};
