/*
    Copyright 2016 Gustavo Borges.
*/
template<typename T>
#define TAMANHOLISTA 100

//! Classe de uma lista de vetor.
/*!
 * Classe que implementa uma lista de vetor com as operações de adicionar e ret-
 * irar elementos, adicionar no inicio, em uma posição determinada, ou retirar
 * do inicio ou da posição determinada, verificar se a lista está cheia ou vazia
 * e mais outras.
 */
class Lista {
 private:
    T* dados; /*!<ponteiro de tipo T para guardar os elementos da lista*/
    int ult; /*!<inteiro para indicar a posição do ultimo elemento*/
    int tamanho; /*!<inteiro para "controlar" o tamanho da lista*/

 public:
//! Construtor de tamanho constante
/*!
  * Nesse construtor é incializada a lista com tamanho constante (#define) e o
  * \param ult que indica a posição do ultimo elemento recebe -1
  */
	Lista() {
	    tamanho = TAMANHOLISTA;
	    dados = new T[tamanho];
	    ult = -1;
	}
//! Construtor de tamanho variável
/*!
 * Nesse construtor o tamanho da lista é passado como parâmetro, e ult que
 * indica a posição do último elemento recebe -1.
 */
	explicit Lista(int tam) {
	    tamanho = tam;
	    dados = new T[tamanho];
	    ult = -1;
	}
//! Operação de adicionar elemento na posição ult + 1
/*!
 * Esse método recebe um \param T dado (o elemento que vai ser adicionado) 
 * verifica se a lista está cheia, caso esteja, um erro é retornado,caso não é 
 * chamado o metodo adicionaNaPosicao que adiciona o \param dado na posição ult+1
 * \sa listaCheia()
 * \sa adicionaNaPosicao()
 */
	void adiciona(T dado) {
	    if (listaCheia()) {
	        throw("ERRO, a lista está cheia");
	    } else {
	        adicionaNaPosicao(dado, ult + 1);
	    }
	}
//! Operação de adicionar elemento no inicio da lista
/*!
 * Esse método recebe um \param dado, similarmente ao metodo adiciona verifica 
 * se a lista está cheia, caso esteja, um erro é retornado, caso não é chamado o
 * metodo adicionaNaPosicao que adiciona o dado na posiçã 0, que no caso é o 
 * primeiro elemento.
 * \sa listaCheia()
 * \sa adicionaNaPosicao()
 * \sa adiciona()
 */
	void adicionaNoInicio(T dado) {
	    if (listaCheia()) {
	        throw("ERRO, a lista está cheia");
	    } else {
	        adicionaNaPosicao(dado, 0);
	    }
	}
//! Operação de adicionar elemento em uma determinada posição.
/*!
 * O método de adicionar na posição recebe como parâmetros \param T dado e int
 * posicao. verifica se a lista está cheia, e se a posição é valida, caso ela 
 * não esteja cheia e a posição seja válida, ult é incrementado e um laço é 
 * criado, esse laço vai da posição do ultimo elemento, jogando todos os 
 * elementos nos qual ele passa "para cima" até chegar na posição que é para 
 * adicionar o elemento.
 * \sa listaCheia()
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
//! Método para adicionar elementos em ordem
/*!
 * O método de adicionar em ordem recebe \param T dado verifica se a lista está 
 * cheia, caso não, a variavel \param pos recebe 0 e um laço é criado, esse laço
 * parando apenas quando a posição for maior ou igual ao \param ult ou o dado 
 * que vai ser adicionado for menor que o array dados[] na posição \param pos, 
 * e dentro desse laço o \param pos é incrementado de um em um, após esse laço 
 * terminar o méto do adicionaNaPosicao é chamado com os parâmetros \param dado 
 * e pos.
 * \sa adicionaNaPosicao()
 * \sa maior()
 * \sa listaCheia()
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
//! Método que retira elemento da ultima posicao da lista.
/*!
 * O método retira, tem retorno do tipo T, ele verifica se a lista está vazia,
 * caso não esteja, \return o método retiraDaPosicao, com \param ult como
 * parâmetro, retirando o ultimo elemento da lista
 * \sa listavazia().
 * \sa retiraDaPosicao().
 */
	T retira() {
	    if (listaVazia()) {
	        throw("ERRO, a listá está vazia");
	    } else {
	        return(retiraDaPosicao(ult));
	    }
	}
//! Método que retira elemento da posição 0
/*!
 * O método retiraDoInicio, tem retorno do tipo T, ele verifica se a lista está 
 * vazia, caso não esteja, \return o método retiraDaPosicao, com 0 como parâme-
 * tro, dessa forma retirando o primeiro elemento da lista.
 * \sa listaVazia()
 * \sa retiraDaPosicao()
 */
	T retiraDoInicio() {
	    if (listaVazia()) {
	        throw("ERRO, a lista está vazia");
	    } else {
	        return(retiraDaPosicao(0));
	    }
	}
//! Método para retirar um elemento de uma posição específica.
/*!
 * O retiraDaPosicao tem \param int posicao como parâmetro do método, e uma var
 * interna \param segura, do tipo T, o método verifica se a lista está vazia por
 * meio do chamado do método listaVazia(), e verifica se a posicao passada como
 * parâmetro é valida, caso a lista não esteja vazia e a posição seja valida,
 * a variavel interna \param segura recebe o elemento que está na posição que
 * foi passada como parâmetro, a variavel \param ult é decrementada em 1, e um
 * laço "for" que começa da posição que foi passada como variavel e vai até 
 * \param ult é iniciado e dentro desse lado, todos os elementos da lista são
 * "jogados para baixo" e \return segura.
 * \sa listaVazia()
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
//! Método que retira um elemento específico da lista.
/*!
 * O método retira específico recebe como \param dado, do tipo T, sendo esse
 * dado um elemento da lista, e tem uma variavel interna \param int pos, ele
 * começa verificando se a lista está vazia, caso não esteja vazia, ele começa
 * colocando na variavel interna \param pos a posição em que o elemento que vai
 * ser retirado está, isso por meio de um método que retorna, se existir, a
 * posição que o elemento está, e decrementa \param ult, se o valor da variavel
 * \param pos for menor que zero, um erro é retornado, significando que o dado
 * provavelmente não existe na lista, caso o valor de \param pos for válido,
 * \return retiraDaPosicao com \param pos como parâmetro do método
 * \sa posicao()
 * \sa listaVazia()
 * \sa retiraDaPosicao()
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
//! Método para saber a posição de um elemento.
/*!
 * O método posicao recebe como parâmetro \param T dado, e tem uma variavel
 * interna \param int pos. O método começa verificando se a lista está vazia,
 * caso não esteja, \param pos recebe 0 e um laço é iniciado, esse laço só ira
 * parar se \param pos for igual ou maior que \param ult ou, o \param dado for
 * igual a \param dados[] na posicao \param pos, enquanto o laço ocorre \param
 * pos é incrementado em 1, após o laço terminar, um teste é feito para ver se
 * a posição é valida, se ela for, \return pos.
 * \sa listaVazia()
 * \sa igual()
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


	T mostra(int posicao) {
	    if (listaVazia()) {
	        throw("ERRO, a lista está vazia");
	    } else {
			T dado = dados[posicao];
			return dado;
	    }
	}
//! Método para verificar se contém um elemento na lista.
/*!
 * O método booleano contém tem um parâmetro \param T dado, e começa já vendo se
 * a lista está vazia, caso esteja \return false, se não estiver, são criadas 2
 * variaveis internas \param int i que começa recebendo zero, e \param contem,do
 * tipo bool, após criadas essas variaveis um laço é iniciado, esse laço só tem
 * fim quando \param i for maior que \param ult, ou \param contem tiver um valor
 * verdadeiro, dentro do laço é feito um teste para ver se o elemento passado
 * como parâmetro é igual a \param dados[] na posição \param i, se forem iguais
 * \param contem recebe true, após essa verificação \param i é incrementada em
 * 1, após o fim do laço \return contem, que pode ser verdadeiro ou falso.
 * \sa listaVazia()
 * \sa igual()
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
//! Método para verificar se um elemento é igual a outro.
/*!
 * O método igual é um metodo com retorno booleano, e recebe como parâmetro 2
 * elementos, \param T dado1 e \param T dado2, e \return true se os dois dados
 * forem iguais e \return false caso não.
 */
	bool igual(T dado1, T dado2) {
	    return(dado1 == dado2);
	}
//! Método para verificar se um elemento é maior que o outro.
/*!
 * O método maior é um metodo com retorno booleano, e recebe como parâmetro 2
 * elementos, \param T dado1 e \param T dado2, e \return true se \param dado1
 * for maior que \param dado2, \return false caso contrário.
 */
	bool maior(T dado1, T dado2) {
	    return(dado1 > dado2);
	}
//! Método para verificar se um elemento é menor que o outro.
/*!
 * O método menor é um metodo com retorno booleano, e recebe como parâmetro 2
 * elementos, \param T dado1 e \param T dado2, e \return true se \param dado1
 * for menor que \param dado2, \return false caso contrário.
 */
	bool menor(T dado1, T dado2) {
	    return(dado1 < dado2);
	}
//! Método para saber se a lista está cheia.
/*
 * O método listaCheia tem retorno do tipo booleano, não tem parâmetros e apenas
 * \return true caso \param ult é igual a \param tamanho - 1, caso isso não seja
 * verdade, \return false.
 */
	bool listaCheia() {
	    return(ult == tamanho - 1);
	}
//! Método para saber se a lista está vazia.
/*
 * O método listaVazia tem retorno do tipo booleano, não tem parâmetros e apenas
 * \return true caso \param ult é igual a - 1, caso isso não seja verdade é
 * \return false.
 */
	bool listaVazia() {
	    return(ult == -1);
	}
//! Método para reiniciar/apagar a lista.
/*!
 * O método destroiLista não tem retorno, e não recebe parâmetros, ele apenas
 * seta \param ult para -1 quando chamado, dessa forma "deletando" a lista já
 * que quando for adicionado um novo elemento ele vai ser adicionado na posição
 * 0, assim recomeçando a lista.
 */
	void destroiLista() {
	    ult = -1;
	}
};
