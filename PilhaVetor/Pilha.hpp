/*
     "Copyright 2016 Gustavo Borges"
*/
template<typename T>
#define MAX_PILHA 100

//! Classe pilha com vetor
/*!
 * essa classe contém metodos de empilhar, desempilhar, verificar se está vazia
 * ou cheia, de retornar a posição do ultimo elemento posto na pilha,
 * limpar a pilha além dos construtores e algumas outras.
 */
class Pilha {
 private:
    int MAXPILHA; /*!<Inteiro para controlar o tamanho da pilha */
	T* m_dados; /*!<Ponteiro que receberá os elementos da fila*/
	int top; /*!<Inteiro para manter "controle" da posição do ultimo elemento */

 public:
    //! Construtor da pilha com tamanho da constante
    /*!
     * Esse construtor inicializa a pilha com o tamanho da constante ja definida
     * e seta o topo para -1 (topo = -1 significa que a pilha está vazia).    
     */
    Pilha() {
        MAXPILHA = MAX_PILHA;
        m_dados = new T[MAXPILHA];
        top = -1;
    }
    //! Construtor da pilha com o tamanho passado como parâmetro.
    /*!
     * Já esse construtor inicializa a pilha com o tamanho do inteiro passado
     * como parâmetro, e o topo recebe -1.
     */
    Pilha<T>(int t) {
        MAXPILHA = t;
        m_dados = new T[t];
        top = -1;
    }
    //! Método para adicionar elementos na pilha.
    /*!
     * O método empilha recebe um dado de tipo "T" se a pilha não estiver cheia
     * o topo é acrescentado em 1 e adiciona o dado na posição topo, e uma
     * exceção é "jogada" caso a pilha esteja cheia.
     */
	void empilha(T dado) {
	    if (PilhaCheia()) {
	        throw("Pilha cheia");
	    } else {
	        top = top + 1;
	        m_dados[top] = dado;
	    }
	}
	//! Método para retirar elementos da pilha.
	/*!
	 * O método desempilha caso a pilha não esteja vazia ele decresce o topo e
	 * e retorna o dado na posição do topo na qual estava anteriormente.
	 * O desempilhamento é feito da forma que retira o ultimo dado que foi
	 * "empilhado", ou seja o dado que está no topo da pilha.
	 */
	T desempilha() {
	    if (PilhaVazia()) {
	        throw("Pilha Vazia");
	    } else {
	        top = top - 1;
	        return (m_dados[top+1]);
	    }
	}
    //! Método para retornar o ultimo dado posto na pilha
    /*!
     * O método topo retorna o dado da pilha que foi posto por ultimo na pilha 
     * caso a pilha não esteja vazia, se ela estiver vazia uma exceção é lançada
     */
	T topo() {
	    if (PilhaVazia()) {
	        throw("Pilha vazia");
	    } else {
	        return (m_dados[top]);
	    }
	}
	//! Método que retorna a posição do ultimo elemento posto na pilha.
	/*!
	 * O método getpostopo apena retorna a posição do ultimo elemento posto na
	 * pilha, sendo o ultimo o mais "Acima" ou adicionado por ultimo, e retorna
	 * uma exceção caso a pilha esteja vazia.
	 */
	int getPosTopo() {
	    if (PilhaVazia()) {
	        throw("A pilha está vazia");
	    } else {
	        return top;
	    }
	}
	//! Metodo para "resetar" a pilha
	/*!
	 * O método de limpar pilha seta o topo para -1 dessa forma "apagando" os
	 * dados da pilha, note que ele não efetivamente remove os dados mas sim
	 * reseta o topo para sobrescrever os dados que estavam lá, dessa forma os
	 * apagando.
	 */
	void limparPilha() {
        top = -1;
	}
	//! Método de verificar se a pilha está vazia
	/*!
	 * Esse método retorna true se a pilha estiver vazia, ou seja se o topo for
	 * igual a -1.
	 */
	bool PilhaVazia() {
	  return (top == -1);
	}
	//! Método de verificar se a pilha está cheia
	/*!
	 * O método pilha cheia faz o que o próprio nome diz, verificando se o topo
	 * é igual a variavel MAXPILHA menos um, a qual recebe um tamanho dependendo
	 * do construtor utilizado.
	 */
	bool PilhaCheia() {
	  return (top == MAXPILHA - 1);
	}
};
