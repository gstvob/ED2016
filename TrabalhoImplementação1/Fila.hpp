/*
     Copyright 2016 Gustavo Borges
*/
     template <typename T>
     #define FILA 100
     
     //! Classe de fila com vetor.
     /*!
      * A classe fila é a implementação de uma fila com vetor, dentro dela existem os
     * métodos de incluir elemento na fila, retirar um elemento da fila, retornar o
     * ultimo elemento da fila, em qual posição esse elemento está, verificar se a
     * fila está cheia ou vazia etc.
     */
    class Fila {
     private:
        T* m_dados; /*!<Ponteiro que vai receber os elementos da fila*/
        int ult; /*!<Inteiro que vai indicar a posição do ultimo elemento*/
        int TAMANHOFILA; /*!<Inteiro para indicar o tamanho da fila*/
   
     public:
        //! Construtor da fila com tamanho definido na constante
        /*!
         * Esse construtor inicializa a fila com tamanho que foi definido(a constante),
         * e seta o atributo que indica a posição do ultimo elemento para -1
        */
    	Fila() {
    	    TAMANHOFILA = FILA;
    	    m_dados = new T[TAMANHOFILA];
    	    ult = -1;
    	}
        //! Construtor da fila com tamanho passado como parâmetro
        /*!
         * A única diferença entre esse construtor é que o tamanho da fila nesse constr-
         * utor é passado como um parâmetro, o resto é igual.
        */
    	Fila<T>(int tam) {
    	    TAMANHOFILA = tam;
    	    m_dados = new T[TAMANHOFILA];
    	    ult = -1;
    	}
        //! Método para adicionar elementos na fila
        /*!
         * O método de incluir elementos na fila incrementa o indicador de posição do
         * último elemento e adiciona um elemento nessa posição, assim esse elemento
         * passa a se tornar o ultimo elemento da fila, e essa inclusão só ocorre se a
         * fila não estiver cheia.
        */
    	void inclui(T dado) {
    	    if (filaCheia()) {
    	        throw("Fila cheia, não é possivel adicionar mais elementos");
    	    } else {
    	        ult = ult + 1;
    	        m_dados[ult] = dado;
    	    }
    	}
        //! Método para retirar elementos da fila
        /*! 
         * O método retira caso a fila esteja vazia joga uma exceção, caso não esteja
         * tira o elemento que está na posição 0 da fila o coloca em uma variavel aux
         * e com um laço "joga" os elementos para frente e a posição do ultimo elemento
         * é decrementada, já que com a "jogada" de elementos para frente o ultimo
         * elemento também foi pra frente.
        */
    	T retira() {
    	    T aux = m_dados[0]; /*!<Atributo auxiliar para segurar o dado na pos 0*/
    	    if (filaVazia()) {
    	        throw("Fila vazia, não é possivel retirar nenhum elemento");
    	    } else {
    	        aux = m_dados[0];
    	        for (int i = 0; i < ult; i++) {
    	            m_dados[i] = m_dados[(i+1)];
    	        }
    	        m_dados[ult] = 0;
    	        ult--;
    	        return aux;
    	    }
    	}
        //! Método de retornar o ultimo elemento da fila
        /*!
         * Esse método simplesmente retorna o elemento de m_dados que se encontra na
         * ultima posição da fila, isso caso a fila não esteja vazia, se ela tiver é
         * jogada uma exceção.
        */
    	T ultimo() {
    	    if (filaVazia()) {
    	        throw("essa fila ta vazia como eu vo retorna o ultimo?");
    	    } else {
   	        return m_dados[ult];
   	    }
    	}
    	//! Método para retornar a posição do ultimo elemento
    	/*!
    	 * O método getUltimo simplesmente retorna a posição em que o está o ultimo
    	 * elemento.
    	*/
    	int getUltimo() {
    	   return ult;
    	}
    	//! Método de verificar se a fila está cheia
   	/*!
   	 * O método filaCheia verifica se a fila está cheia, retornando true caso
   	 * esteja e false caso não.
   	*/
   	bool filaCheia() {
   	    return(ult == TAMANHOFILA - 1);
   	}
   	//! Método para verificar se a fila está vazia
   	/*!
   	 * Já o método filaVazia verifica se a fila está vazia, retornando true caso
   	 * sim e false caso contrário.
   	*/
   	bool filaVazia() {
   	    return(ult == -1);
   	}
   	//! Método para "zerar" a fila
   	/*! 
   	 * Esse método seta o valor do atributo que indica a posição do ultimo para
   	 * 0, dessa forma "resetando" a fila.
   	*/
   	void inicializaFila() {
   	    ult = -1;
   	}
	 }; 
