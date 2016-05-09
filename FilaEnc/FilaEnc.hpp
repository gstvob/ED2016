//! Copyright 2016 Gustavo Borges França
#include "ListaEnc.hpp"
template <typename T>
//! Classe de uma Fila encadeada que tem como sua classe pai Lista encadeada.
class FilaEnc : ListaEnc<T>{
 public:
//! Construtor vazio;
	FilaEnc<T>() {
	}
//! Destrutor da fila encadeada.
/*!
 * O destrutor da fila encadeada simplesmente chama o método limparFila() que
 * irá destruir a fila.
 * @see limparFila()
 */
	~FilaEnc() {
	    limparFila();
	}
//! Método para adicionar dados no fim da fila.
/*!
 * @param o endereço da memoria do dado generico que vai ser adicionado.
 * Método de incluir apenas chama o método adiciona da lista encadeada, dessa
 * forma adicionando o dado no ultimo lugar da fila.
 * @see ListaEnc adiciona()
 */
	void inclui(const T& dado) {
	    this->adiciona(dado);
    }
//! Método para retirar o dado que está no inicio da fila.
/*!
 * @return um generico que é a info do dado retirado.
 * o método faz uma verificação para saber se a fila está vazia, sim joga uma
 * exceção, caso não chama o método retiraDoInicio da lista encadeada e retorna
 * ele.
 * @see filaVazia(), Lista Enc retiraDoInicio()
 */
	T retira() {
	    if (filaVazia()) {
	        throw "ERROFILAVAZIA";
	    } else {
	        return this->retiraDoInicio();
	    }
	}
//! Método para saber qual o ultimo elemento da fila.
/*!
 * @return um genérico que é o ultimo elemento da fila, o elemento que foi add
 * recentemente.
 * o método verifica se a fila está vazia, se sim joga uma exceção, se não ele
 * cria três variaveis internas, uma do tipo generica, um ponteiro de tElemento
 * e um inteiro inicializado em 1.
 * o ponteiro andante recebe o elemento head da listaEncadeada, e equanto o cont
 * for menor que o size da listaEncadeada, a variavel andante recebe o proximo
 * elemento da fila, e o cont é incrementado. após o fim do laço o generico
 * recebe a info do andante e é retornado.
 * @see filaVazia()
 */
	T ultimo() {
	   if (filaVazia()) {
	        throw "errofilavazia";
	    } else {
	       Elemento<T> *andante;
	       andante = this->head;
	       int cont = 1;
	       T ultimo;
	       while (cont < this->size) {
	            andante = andante->getProximo();
	            cont++;
	       }
	       ultimo = andante->getInfo();
	       return ultimo;
	    }
	}
//! Método para retornar o primeiro elemento da fila.
/*!
 * @return um genérico que vai ser a info do primeiro elemento da fila.
 * o método começa fazendo a verificação se a fila está vazia ou não, se sim
 * joga a exceção, se não é retornado a info do elemento head da listaEnc.
 * o primeiro elemento da fila é o primeiro elemento que foi adicionado a ela,
 * que no caso, é o head da lista.
 * @see filaVazia()
 */
	T primeiro() {
	   if (filaVazia()) {
	        throw "ERROFILAVAZIA";
	   } else {
	        return this->head->getInfo();
	   }
	}
//! Método para saber se a lista está vazia.
/*!
 * @return um bool que vai ser true se a listaEnc estiver vazia, false caso não
 * o método apenas retorna o valor do método listaVazia() da lista encadeada.
 * @see ListaEnc listaVazia()
 */
	bool filaVazia() {
	    return this->listaVazia();
	}
//! método para apagar a fila
/*!
 * método sem retorno apenas chama o método destroi lista da listaEncadeada.
 * @see ListaEnc destroiLista(), ~FilaEnc()
 */
	void limparFila() {
	    this->destroiLista();
	}
};

