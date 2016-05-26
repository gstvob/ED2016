/*
    Copyright 2016 Gustavo Borges && Nathan Werlich 2016.
*/
template<typename T>
#define TAMANHOLISTA 100

/*!
 * @brief Implementação de uma classe de fila de vetores.
 */
class Lista {
 private:
    T* dados; /*!<ponteiro de tipo T para guardar os elementos da lista*/
    int ult; /*!<inteiro para indicar a posição do ultimo elemento*/
    int tamanho; /*!<inteiro para "controlar" o tamanho da lista*/

 public:
	/*!
	 * @brief Construtor que incializa a lista com tamanho constante definido.
	 */
	Lista() {
	    tamanho = TAMANHOLISTA;
	    dados = new T[tamanho];
	    ult = -1;
	}
	/*!
	 * @brief construtor que incializa a lista com tamanho variavel.
	 * @param inteiro que indica o tamanho que se quer fazer a lista. 
	 */
	explicit Lista(int tam) {
	    tamanho = tam;
	    dados = new T[tamanho];
	    ult = -1;
	}
	/*!
	 * @brief método para adicionar elementos(dados), ao final da lista.
	 * @param genérico que é o dado que se quer adicionar na lista.
	 * @see adicionaNoInicio()
	 * @see adicionaNaPosicao();
	 * @see listaCheia().
	 */
	void adiciona(T dado) {
	    if (listaCheia()) {
	        throw("ERRO, a lista está cheia");
	    } else {
	        adicionaNaPosicao(dado, ult + 1);
	    }
	}
	/*!
	 * @brief método para adicionar dados ao inicio da lista.
	 * @param generico que é o dado a ser adicionado na lista.
	 * @see adicionaNaPosicao()
	 * @see adiciona()
	 * @see listaCheia()
	 */
	void adicionaNoInicio(T dado) {
	    if (listaCheia()) {
	        throw("ERRO, a lista está cheia");
	    } else {
	        adicionaNaPosicao(dado, 0);
	    }
	}
	/*!
	 * @brief método de adicionar dados na lista em uma posição qualquer.
	 * @param genérico que é o dado a ser adicionado
	 * @param inteiro que indica a posicao para adicionar o dado.
	 * @see listaCheia()
	 * @see adiciona()
	 * @see adicionaNoInicio()
	 */
	void adicionaNaPosicao(T dado, int posicao) {
	    if (listaCheia()) {
	        throw("ERRO, a lista está cheia");
	    } else if (posicao > ult + 1 || posicao < 0) {
	        throw("ERRO, essa posição é invalida");
	    } else {
	        ult = ult + 1;
	        for (int i = ult; i > posicao; i--) {
	            dados[i] = dados[(i-1)];
	        }
	        dados[posicao] = dado;
	    }
	}
	/*!
	 * @brief método para adicionar dados em ordem na lista.
	 * @param genérico que é o dado que vai ser adicionado na lista.
	 * @see adicionaNaPosicao()
	 * @see listaCheia()
	 * @see maior()
	 */
	void adicionaEmOrdem(T dado) {
	    int pos;
	    if (listaCheia()) {
	        throw("ERRO, a lista está cheia");
	    } else {
	        pos = 0;
	        while ((pos < ult) && (maior(dado, dados[pos]))) {
	            pos = pos + 1;
	        }
	        adicionaNaPosicao(dado, pos);
	    }
	}
	/*!
	 * @brief método que retira o ultimo elemento da lista.
	 * @return genérico que é o dado que saiu da lista.
	 * @see listaVazia()
	 * @see retiraDaPosicao()
	 */
	T retira() {
	    if (listaVazia()) {
	        throw("ERRO, a listá está vazia");
	    } else {
	        return(retiraDaPosicao(ult));
	    }
	}
	/*!
	 * @brief método para retirar um dado do inicio da lista.
	 * @return genérico que é o dado que saiu da lista.
	 * @see retiraDaPosicao()
	 */
	T retiraDoInicio() {
	    if (listaVazia()) {
	        throw("ERRO, a lista está vazia");
	    } else {
	        return(retiraDaPosicao(0));
	    }
	}
	/*!
	 * @brief método que retira um dado de uma determinada posicao.
	 * @param inteiro que vai indicar a posicao que esta o dado que se deseja tirar.
	 * @return genérico que é o dado que saiu da lista.
	 * @see listaVazia()
	 * @see retiraDoInicio()
	 * @see retira()
	 */
	T retiraDaPosicao(int posicao) {
	    T segura;
	    if (listaVazia()) {
	        throw("ERRO, a lista está vazia");
	    } else if (posicao > ult || posicao < 0) {
	        throw("ERRO, posição invalida");
	    } else {
	        segura = dados[posicao];
	        ult = ult - 1;
	        for (int i = posicao; i < ult; i++) {
	            dados[i] = dados[(i+1)];
	        }
	        return segura;
	    }
	}
	/*!
	 * @brief método para retirar um dado especifico da lista.
	 * @param generico que é o dado que se deseja retirar da lista.
	 * @return generico que é o dado que saiu da lista.
	 * @see retiraDaPosicao()
	 * @see posicao()
	 * @see listaVazia()
	 */
	T retiraEspecifico(T dado) {
	    int pos;
	    if (listaVazia()) {
	        throw("ERRO, a lista está vazia");
	    } else {
	        pos = posicao(dado);
	        ult = ult - 1;
	        if (pos < 0) {
	            throw("ERRO, posição invalida");
	        } else {
	           return retiraDaPosicao(pos);
	        }
	    }
	}
	/*!
	 * @brief método para saber a posicao de um determinado dado.
	 * @param genérico que é o dado que se quer saber a posicao.
	 * @return inteiro que indica a posicao que se encontra o dado.
	 * @see listaVazia()
	 * @see igual()
	 */
	int posicao(T dado) {
	    int pos;
	    if (listaVazia()) {
	        throw("ERRO, a lista está vazia");
	    } else {
	         pos = 0;
	         while ((pos <= ult) && (!(igual(dado, dados[pos])))) {
	            pos = pos + 1;
	         }
	         if (pos > ult) {
	            throw("ERRO, posição invalida");
	         } else {
	            return pos;
	         }
	    }
	}
	/*!
	 * @brief retorna o dado que está em uma determinada posição da lista.
	 * @param inteiro que indica a posição do dado que se quer mostrar.
	 * @return genérico que é o dado que se quer ver. 
	 */
	T mostra(int posicao) {
		T dado = dados[posicao];
		return dado;
	}
	/*!
	 * @brief método para saber se um determinado dado existe na lista.
	 * @param genérico que é o dado que se quer saber se está presente na lista.
	 * @return boolean verdadeiro se o dado existir na lista falso caso não.
	 */
	bool contem(T dado) {
	    if (listaVazia()) {
	        return false;
	    } else {
	        int i = 0;
	        bool contem;
	        while ((i <= ult) && (contem == false)) {
	            if (igual(dado, dados[i])) {
	                contem = true;
	            }
	            i = i+1;
	        }
	        return contem;
        }
	}
	/*!
	 * @brief método para saber se um dado é igual a outro
	 * @param que genérico que é um dado a ser comparado
	 * @param generico que é outro dado a ser comparado.
	 * @return booleano verdadeiro se um dado for igual ao outro falso caso não.
	 */
	bool igual(T dado1, T dado2) {
	    return(dado1 == dado2);
	}
	/*!
	 * @brief método para saber se um dado é maior que outro,
	 * @param generico que é um dado a ser comparado.
	 * @param generico que é outro dado a ser comparado.
	 * @return boolean verdadeiro se dado1 for maior que dado2.
	 */
	bool maior(T dado1, T dado2) {
	    return(dado1 > dado2);
	}
	/*!
	 * @brief método para saber se um dado é menor que o outro.
	 * @param generico que é um dado para comparar.
	 * @param generico que é outro dado a ser comparado.
	 * @return booleano verdadeiro se dado1 for menor que dado2, falso caso não.
	 */
	bool menor(T dado1, T dado2) {
	    return(dado1 < dado2);
	}
	/*!
	 * @brief método para saber se a lista está cheia.
	 * @return booleano verdadeiro se a lista estiver cheia, falso se não.
	 */
	bool listaCheia() {
	    return(ult == tamanho - 1);
	}
	/*!
	 * @brief método para saber se a lista está vazia.
	 * @return booleano verdadeiro se a lista estiver vazia, falso caso não.
	 */
	bool listaVazia() {
	    return(ult == -1);
	}
	/*!
	 * @brief método para apagar/reiniciar a lista.
	 */
	void destroiLista() {
	    ult = -1;
	}
};
