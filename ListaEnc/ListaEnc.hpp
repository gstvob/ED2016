//! Copyright 2016 Gustavo Borges França
#include "Elemento.hpp"

template<typename T>
/*!
 * Implementação de uma classe de lista encadeada, com operações de add elemento
 * no inicio, no final ou em qualquer posição, retirar um elemento de qualquer
 * posição, destruir a lista, verificar se contem um elemento na lista, qual a
 * posição de um determinado elemento da lista, etc.
 */
class ListaEnc {
 protected:
    Elemento<T>* head; /*< ponteiro tElemento da cabeça da lista*/
    int size; /*< Inteiro para indicar o tamanho atua da lista*/

 public:
 /*!
  * Construtor inicializa a lista atribuindo um null pointer para o head e
  * zerando o size;
  */
	ListaEnc() {
	    head = nullptr;
	    size = 0;
	}
/*!
 * Desconstrutor da lista que chama o método destroi lista, e atribui 0 ao
 * tamanho size, dessa forma "resetando" a lista
 * @see destroiLista()
 */
	~ListaEnc() {
	    destroiLista();
	    size = 0;
	}
//! Método para adicionar um elemento no inicio da lista.
/*!
 * @param dado, o endereço do T dado que vai ser adicionado no inicio da lista.
 * Metodo para adicionar um elemento no inicio da lista, cria um ponteiro novo
 * do tipo tElemento que recebe como argumentos, dado, que é a info do elemento
 * e um ponteiro que vai ser o proximo elemento. Se esse novo elemento não for
 * nulo, ou seja, a lista não está cheia, o Elemento head vai apontar para o
 * novo elemento e o atributo de tamanho da lista é incrementado.
 */
	void adicionaNoInicio(const T& dado) {
	    Elemento<T>* novo = new Elemento<T>(dado, head);
	    if (novo != nullptr) {
	        head = novo;
	        size++;
	    } else {
	        throw "ERROLISTACHEIA";
	    }
	}
//! Método que retira o elemento do inicio da lista.
/*!
 * método sem parâmetros apenas com duas variaveis internas uma tElemento e uma
 * variavel generica T, é feita uma verificação para ver se a lista está vazia,
 * caso esteja é jogado um erro, caso não o processo de remoção do primeiro
 * elemento é iniciado, a variavel interna "deletoso" recebe o Elemento head.
 * a variavel interna "volta" recebe a informação da variavel "deletoso"
 */
	T retiraDoInicio() {
	    Elemento<T>* deletoso;
	    T volta;
	    if (listaVazia()) {
	       throw "ERROLISTAVAZIA";
	    } else {
	        deletoso = head;
            volta = deletoso->getInfo();
	        head = deletoso->getProximo();
	        size--;
	        delete(deletoso);
	        return volta;
	    }
	}
//! Método que deleta o elemento do inicio da lista.
/*!
 * Método similar ao retiraDoInicio porém ele não tem retorno, o método tem uma
 * variavel interna do tipo Elemento<T> chamada deletoso, um teste é feito, para
 * verificar se a lista está vazia, se sim um erro é jogado, se não, o processo
 * de remoção do elemento é iniciado, a variavel deletoso recebe o elemento head
 * o elemento head recebe o proximo deletoso, o tamanho é decrementado, e a info
 * do deletoso e o deletoso em si são ambos deletados.
 * @see retiraDoInicio()
 */
	void eliminaDoInicio() {
	    Elemento<T>* deletoso;
	    if (listaVazia()) {
	        throw "ERROLISTAVAZIA";
	    } else {
	        deletoso = head;
	        head = deletoso->getProximo();
	        size--;
	        deletoso->~Elemento();
	        delete(deletoso);
	    }
	}
//! Método para adicionar em uma posição qualquer, desde que ela seja valida.
/*!
 * @param dado, o endereço do T dado que vai ser adicionado na lista.
 * @param pos, um inteiro que indica a posição que esse dado vai ser adicionado.
 * O método de adicionar na posição começa testando se a posição é valida, se
 * ela não for valida um erro é jogado, caso seja valida, é verificado se a pos
 * é zero, caso seja o elemento é adicionado no inicio da lista, caso a posição
 * seja valida e != de zero, começa o "calculo" para saber onde será adicionado
 * o elemento novo. São criados dois ponteiros Elementos<T> anterior e atual,
 * o anterior é um auxiliar que vai servir para andar na lista, ele começa rece-
 * bendo o elemento head, e um laço for é iniciado para fazer esse elemento "ir
 * para frente" o atual recebe o proximo do anterior e o proximo do anterior é
 * setado para um novo elemento onde a info é o dado (parâmetro) e o proximo o
 * Elemento atual (variavel interna).
 * @see adicionaNoInicio().
 */
	void adicionaNaPosicao(const T& dado, int pos) {
	    if (pos < 0 || pos > size) {
	        throw "ERROPOSICAO";
	    } else if (pos == 0) {
	        adicionaNoInicio(dado);
	    } else {
	        Elemento<T> *anterior, *atual;
	        anterior = head;
	        for (int i = 0; i < pos-1; i++) {
	            anterior = anterior->getProximo();
	        }
	        atual = anterior->getProximo();
	        anterior->setProximo(new Elemento<T>(dado, atual));
	        size++;
	    }
	}
//! Método para retornar a posicao na lista de um dado.
/*!
 * @param dado, o endereço na memoria do dado que quer se saber a posicao.
 * @return int, o retorno vai ser a posição do dado, ou um erro vai ser jogado.
 * O método posição começa criando uma variavel interna do tipo Elemento<T>, um
 * ponteiro, essa variavel chamada atual recebe o elemento head, e é feita uma
 * verificação para saber se a lista esta vazia, caso esteja um erro é jogado,
 * caso não, o processo de procura da posição começa em um laço for que vai de 0
 * até o ultimo elemento, verificando a cada interação se o dado é igual a info
 * do elemento, se for é retornado o valor de i (variavel de interação do laço),
 * assim terminando a execução do método, se não for encontrada essa posição uma
 * exceção é jogada avisando que o elemento não existe na lista.
 * @see listaVazia();
 */
	int posicao(const T& dado) const {
	    Elemento<T>* atual;
	    atual = head;
	    if (listaVazia()) {
	        throw "errolistavazia";
	    } else {
            for (int i = 0; i <= size; i++) {
                if (atual->getInfo() == dado) {
                    return i;
                }
                atual = atual->getProximo();
            }
            throw "ELEMENTO NAO EXISTE";
	    }
	}
//! Método para retornar o endereço da memoria de um dado.
/*!
 * @param dado, o endereço na memoria do dado que quer se saber o endereço.
 * @return T*, o retorno vai ser a posição da memória em que o dado se encontra.
 * O método posiçãoMem começa criando 3 variaveis internas, um ponteiro do tipo
 * Elemento<T> chamada de atual, uma generica T data, e um inteiro anda. Começa
 * fazendo a verificação para saber se a lista está vazia, caso não esteja, o
 * ponteiro atual recebe o elemento head, e o inteiro anda recebe 1, um laço é
 * criado, e só ira parar quando anda for maior ou igual que size, dentro do
 * laço é verificado se a informação de atual é igual ao dado, se for, data
 * (a variavel interna do tipo T) recebe a info de atual e é retornad o endereço
 * da memoria onde se encontra data, caso não seja igual, atual recebe o proximo
 * elemento. se não for achado o elemento, uma exceção é jogada dizendo que o
 * elemento não existe.
 * @see posicao()
 * @see listaVazia();
 */
	T* posicaoMem(const T& dado) const {
	    Elemento<T> *atual;
	    T data;
	    int anda;
	    if (listaVazia()) {
	        throw "ERROLISTAVAZIA";
	    } else {
	        atual = head;
	        anda = 1;
	        while (anda < size) {
	            if (atual->getInfo() == dado) {
	                data = atual->getInfo();
	                return &data;
	            }
	            atual = atual->getProximo();
	        }
	        throw "ERROELEMENTOINEXISTENTE";
	    }
	}
//! Método de retorno booleano para saber se um dado existe na lista.
/*!
 * @param dado, o endereço da memoria de um generico.
 * @return boolean, verdadeiro se existe esse dado na lista, falso se não.
 * Esse método tem 2 variaveis internas, um ponteiro Elemento<T> atual, e um int
 * pos, ambos para andar pela lista. é verificado se a lista está vazia, se sim
 * return false, se não pos é inicializado com 1 e atual com o elemento head e
 * um laço para andar pela lista é criado, o laço é igual ao do posicaoMem(), só
 * que ele retorna true na verificação dentro do laço.
 */
	bool contem(const T& dado) {
        Elemento<T>* atual;
	    int pos;
	    if (listaVazia()) {
	        return false;
	    } else {
	       pos = 0;
	       atual = head;
	       for (pos; pos < size; pos++) {
	           if (atual->getInfo() == dado) {
	                return true;
	           }
	           atual = atual->getProximo();
	      }
	       return false;
	    }
	}
//! Método de retirar um elemento de uma posição passada como parâmetro.
/*!
 * @param pos, um inteiro que vai indicar que elemento vai ser deletado.
 * @return um generico, que vai ser a informação do elemento deletado.
 * O método retira da posicao tem 3 variaveis internas, dois ponteiros tElemento
 * anterior e deletoso, a anterior vai servir para andar dentro da lista, e o
 * deletoso será o elemento que vai sumir, o método verifica se a posição é
 * valida, e verifica se a posição é a primeira, caso a pos for valida, e não
 * for a primeira, a variavel anterior recebe o elemento head, e um laço for é
 * criado para andar na lista, quando ele chegar no elemento anterior ao que vai
 * ser deletado ele para, e o deletoso recebe esse elemento que vai ser deletado
 * volta recebe a informação de deletoso, e como deletoso vai ser deletado,
 * o proximo de anterior passa a ser o proximo de deletoso, size é decrementado,
 * e deletoso é efetivamente deletado.
 * @see retiraDoInicio()
 */
	T retiraDaPosicao(int pos) {
	    Elemento<T> *anterior, *deletoso;
	    T volta;
        if (pos < 0 || pos > size - 1) {
	        throw "ERROPOSICAO";
	    } else {
	       if (pos == 0) {
	        return(retiraDoInicio());
	       } else {
	            anterior = head;
	            for (int i = 1; i < pos; i++) {
	                anterior = anterior->getProximo();
	            }
                deletoso = anterior->getProximo();
	            volta = deletoso->getInfo();
	            anterior->setProximo(deletoso->getProximo());
	            size--;
	            delete(deletoso);
	       }
	       return volta;
	    }
	    throw "ERROPOSICAO";
	}
//! Método para adicionar um dado na ultima posicao.
/*!
 * @param dado, o endereço da memoria do elemento que vai ser adicionado.
 * Sem valor de retorno, o método adiciona verifica se a lista está vazia, caso
 * esteja ele adiciona um elemento no inicio, já que o ultimo elemento de uma
 * lista vazia de certa forma sera o inicio, caso não esteja vazia, é chamado o
 * método adicionaNaPosicao passando dado e size como parâmetros.
 * @see listaVazia(), adicionaNoInicio(), adicioNaPosicao()
 */
	void adiciona(const T& dado) {
	    if (listaVazia()) {
	        adicionaNoInicio(dado);
	    } else {
            adicionaNaPosicao(dado, size);
	    }
	}
//! método para retirar o ultimo elemento não nulo da lista.
/*!
 * @return um generico que vai ser no caso a info do elemento retirado.
 * é verificado se a lista está vazia, caso esteja uma exceção é jogada, caso
 * não esteja é retornado um retiraDaPosicao() com size-1 como parâmetro, assim
 * deletando o ultimo elemento não nulo da lista.
 * @see retiraDaPosicao(), listaVazia()
 */
	T retira() {
	    if (listaVazia()) {
	        throw "ERROLISTAVAZIA";
	    } else {
            return retiraDaPosicao(size - 1);
	    }
	}
//! método para retirar um dado especifico da lista
/*!
 * @param dado, o endereço da memoria do dado que será removido.
 * @return um generico que será na verdade a info do elemento removido.
 * o método começa verificando se a lista está vazia, se estiver uma exceção é
 * jogada, se não é verificado se o dado existe efetivamente na lista, se sim
 * é chamado o metodo retiraDaPosicao() como posicao a posicao do dado que é
 * "descoberta" por meio do método posicao() com o dado como parâmetro, se o 
 * dado não existe na lista, é jogada uma exceção.
 * @see listaVazia(), retiraDaPosicao(), posicao()
 */
	T retiraEspecifico(const T& dado) {
	    if (listaVazia()) {
	        throw("ERROLISTAVAZIA");
	    } else {
	        if (contem(dado) == true) {
	            return(retiraDaPosicao(posicao(dado)));
	        } else {
	            throw "DADO INEXISTENTE";
	        }
	    }
	}
//! Método para adicionar os dados em ordem
/*!
 * @param data, o espaço na memoria do dado, que vai ser adicionado na lista.
 * Sem valor de retorno, o método adiciona em ordem tem duas variaveis internas,
 * um ponteiro do tipo Elemento<T> chamado atual, que vai servir para andar na
 * lista, e um inteiro posição, que vai servir para saber onde colocar o dado.
 * é feita uma verificação para saber se a lista está vazia, se estiver o dado
 * é inserido no inicio, se não, atual recebe o elemento head, e pos é iniciado
 * com 1, um laço while é criado e só irá parar quando o proximo de atual for
 * nulo, significando que chegou no fim da lista, ou o data for menor que a info
 * de atual, dentro do while o atual recebe o seu proximo e o pos é incrementado
 * após o final do laço, é feita uma verificação para saber se o laço acabou
 * por conta do fim da lista ou por ter achado um info de atual que é maior que
 * data, se o laço acabou por causa do fim da lista, é chamado o método adiciona
 * naPosicao(data, pos+1), se não adicionaNaPosicao(data,pos-1)
 * @see adicionaNaPosicao(), adicionaNoInicio(), maior().
 */
	void adicionaEmOrdem(const T& data) {
	    Elemento<T> *atual;
	    int pos;
	    if (listaVazia()) {
	        adicionaNoInicio(data);
	    } else {
	        atual = head;
	        pos = 1;
	        while ((atual->getProximo() != nullptr)
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
//! método para saber se a lista está vazia
/*!
 * @return boolean, true se size for zero, e falso caso contrario
 */
	bool listaVazia() const {
	    return size == 0;
	}
//! método para saber se dado1 é igual ao dado2
/*!
 * @param dado1, um generico qualquer para fins de comparação.
 * @param dado2 outro generico qualquer para fins de comparação.
 * @return boolean, verdadeiro se dado1 for igual a dado2, falso caso contrario.
 */
	bool igual(T dado1, T dado2) {
	    return dado1 == dado2;
	}
//! método para saber se dado1 é maior que dado22
/*!
 * @param dado1, um generico qualquer para fins de comparação.
 * @param dado2 outro generico qualquer para fins de comparação.
 * @return boolean, verdadeiro se dado1 for maior que dado2, falso se não.
 */
	bool maior(T dado1, T dado2) {
	    return dado1 > dado2;
	}
//! método para saber se dado1 é menor que dado22
/*!
 * @param dado1, um generico qualquer para fins de comparação.
 * @param dado2 outro generico qualquer para fins de comparação.
 * @return boolean, verdadeiro se dado1 for menor que dado2, falso se não.
 */
	bool menor(T dado1, T dado2) {
	    return dado1 < dado2;
	}
//! método para deletar a lista.
/*!
 * O método destroi lista não tem parametro, nem retorno, tem duas variaveis
 * internas , dois ponteiros do tipo Elemento<T> chamadas atual e deletoso,
 * a atual começa recebendo o elemento head e um laço while é criado com 
 * condição de parada o atual ser igual a nullptr, enquanto não for, o deletoso
 * recebe atual, atual recebe o proximo elemento, e o deletoso é deletado, após
 * o fim do laço head recebe nullptr e o size recebe zero, assim terminando o
 * processo de destruição da lista.
 * @see ~ListaEnc()
 */
	void destroiLista() {
	   Elemento<T> *deletoso, *atual;
	   atual = head;
	   while (atual != nullptr) {
	        deletoso = atual;
	        atual = atual->getProximo();
	        delete(deletoso);
	   }
	   head = nullptr;
	   size = 0;
	}
};
