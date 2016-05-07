//! Copyright 2016 Gustavo Borges França
#include "Elemento.hpp"
template <typename T>
//! Classe de implementação de uma Lista Circular Simples.
class ListaCirc {
 private:
    Elemento<T>* sentry; /*<! ponteiro de elemento para auxiliar na lista.>*/
 	Elemento<T>* head;
 	int size;

 public:
//! Construtor da Lista circular
/*!
 * Construtor que inicializa o sentinela como um elemento sem info e aponta para si mesmo
 * o elemento head que aponta para o sentinela e o size que é o tamanho da lista recebe
 * zero.
 */
	ListaCirc() {
	   sentry = new Elemento<T>(0,sentry);
	   head = sentry;
	   size = 0;
	}
//! Destrutor da lista circular
/*!
 * @see destroiLista()
 */
    ~ListaCirc() {
	    destroiLista();
	}
//! Método para adicionar no inicio da lista
/*!
 * @param o endereço da memoria do dado que será adicionado da lista.
 * é criado um novo ponteiro de elemento, que é alocado, e o sentinela aponta
 * para esse elemento. se a lista não estiver vazia, o proximo do novo recebe o
 * proximo do sentry e o tamanho é incrementado.
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
//! Método para retirar um elemento do inicio da lista.
/*!
 * @return um genérico que é a info do elemento retirado.
 * método testa se a lista está vazia, se sim joga uma exceção caso não, um
 * ponteiro de elemento é criado e esse elemento recebe o sentinela, um generico
 * é criado e recebe a info do elemento que recebeu o sentinela, e o sentinela
 * passa a apontar para o próximo elemento, e por fim é deletado o primeiro
 * elemento, o tamanho é decrementado e o genérico que foi criado anteriormente
 * é retornado.
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
//! Método para remover um elemento do inicio.
/*!
 * método muito igual ao de retirar do inicio, unica diferença é que esse não
 * tem valor de retorno.
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
//! Método para adicionar um elemento em uma determinada posição na lista.
/*!
 * @param posição na memoria de um generico que será o dado adicionado na lista.
 * @param inteiro que irá indicar a posição que o dado será colocado na lista.
 * método verifica se a posição é valida, se ela for válida e for a posição
 * inicial, chama o método adicionaNoinicio senão, cria 2 ponteiro Elemento<T>
 * o primeiro recebe o sentinela, e um laço é criado para fazer esse ponteiro
 * andar na lista, quando o laço termina, o segundo ponteiro recebe o proximo
 * do primeiro o proximo do primeiro é setado para um novo elemento, o elemento
 * que foi adicionado na lista.
 */
	void adicionaNaPosicao(const T& dado, int pos) {
        if (pos < 0 || pos > this->size) {
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
//! Método para retornar a posição de um determinado dado na lista.
/*!
 * @param a posição na memória de um genérico que é o dado que se quer encontrar
 * @return inteiro que vai ser a posição que o dado se encontra na lista
 * método simplesmente verifica se a lista está vazia, se não estiver, é criado
 * um ponteiro de elemento para caminhar na lista, e se enquanto ele faz essa 
 * "caminhada" for achado o dado, é retornado a posição que ele tá, se não for
 * achado, uma exceção é jogada.
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
//! Método para retornar a posição na memória de um determinado dado na lista.
/*!
 * @param a posição na memória de um genérico que é o dado que se quer encontrar
 * @return ponteiro que vai ser a posição na memória do dado passado como param
 * método simplesmente verifica se a lista está vazia, se não estiver, é criado
 * um ponteiro de elemento para caminhar na lista, e se enquanto ele faz essa 
 * "caminhada" for achado o dado, é retornado a posição na memória em que ele tá
 * se não for achado, uma exceção é jogada.
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
//! Método para saber se um dado existe na lista.
/*!
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
//! Método para retirar o dado de uma determinada posição.
/*!
 * @param inteiro que é a posição que vai ser retirado o elemento.
 * @return um genérico que vai ser o dado do elemento retirado.
 * método testa se a posição é valida, se for valida se for a posição inicial,
 * chama o método retiraDoInicio(), senão caminha na lista com um laço for, 
 * um ponteiro de Elemento<T> recebe o proximo do elemento que caminhou no laço
 * um generico que recebe a info desse ponteiro, e o proximo do elemento que 
 * caminhou no laço recebe o proximo do ponteiro deleter, o tamanho da lista é
 * decrementado, e o elemento é deletado.
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
//! Método para adicionar no fim da lista.
/*!
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
//! método para retirar o ultimo elemento da lista.
/*!
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
//! Método para retirar um determinado dado da lista.
/*!
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
//! método para mostrar a info de um elemento em uma posição na lista.
/*!
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
//! Método para adicionar os elementos em ordem.
/*!
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
//! Método para saber a posição do ultimo elemento.
/*!
 * @return a posição do ultimo elemento.
 */
	int verUltimo() {
	  return size - 1;
	}
//! Método para saber se a lista está vazia
/*!
 * @return boolean, verdadeiro se o size for igual a zero, falso se não
 * O método vai retornar verdadeiro quando a lista estiver vazia.
 */
	bool listaVazia() const {
	    return size == 0;
	}
//! Método para saber se um genérico é igual ao outro
/*!
 * @return boolean, verdadeiro caso os dados forem iguais, falso caso não.
 */
	bool igual(T dado1, T dado2) {
	    return dado1 == dado2;
	}
//! Método para saber se um genérico é maior ao outro
/*!
 * @return boolean, verdadeiro caso dado1 for maior que dado2, falso caso não.
 */
	bool maior(T dado1, T dado2) {
	    return dado1 > dado2;
	}
//! Método para saber se um genérico é menor ao outro
/*!
 * @return boolean, verdadeiro caso dado1 for menor que dado2, falso caso não.
 */
	bool menor(T dado1, T dado2) {
	    return dado1 < dado2;
	}
//! Método para destruir a lista.
/*!
 * método destroi lista cria dois ponteiros do tipo Elemento<T> e o primeiro
 * vai caminhar na lista, o segundo vai recebendo o que caminha, e vai deletando
 * quando a caminhada tem fim, size recebe 0 e o sentinela recebe nullptr;
 */
    void destroiLista() {
	    Elemento<T> *caminha, *deleter;
	    caminha = sentry->getProximo();
	    while (!listaVazia()) {
	    	eliminaDoInicio();
	    }
	    size = 0;
	    sentry->setProximo(sentry);
	}
};
