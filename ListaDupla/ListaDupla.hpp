//! Copyright 2016 Gustavo Borges França
#include "ElementoDuplo.hpp"
template<typename T>
//! Classe que implementa uma lista duplamente encadeada.
class ListaDupla {
 private:
    ElementoDuplo<T>* head; /*<!um ponteiro da lista que apontará pro 1o elem>*/
    int size; /*<!inteiro para indicar o tamanho da lista>*/

 public:
//! Construtor da lista dupla.
/*!
 * construtor que inicializa o elemento head como um ponteiro nulo, e o tamanho
 * recebe 0;
 */
	ListaDupla() {
	    head = nullptr;
	    size = 0;
	}
//! Destrutor da lista dupla.
/*!
 * Método que destroi a lista chamando o método destroiListaDuplo()
 * @see destroiListaDuplo();
 */
	~ListaDupla() {
	    destroiListaDuplo();
	}
//! Método para adicionar um dado ao inicio da lista.
/*!
 * @param o espaço da memória em que está o genérico que vai ser adicionado.
 * o método adiciona no inicio começa criando uma variavel interna do tipo 
 * Elemento<T> e essa variavel é inicializada passando como parâmetros o proprio
 * parâmetro dado do método, um nullpointer que sera o anterior desse e
 * o head, que será o sucessor. Se o novo não for um nullpointer, o elemento 
 * head aponta para ele e se o sucessor do novo não for um nullpointer, o 
 * anterior do sucessor do novo recebe o proprio novo, e o size é incrementado.
 */
	void adicionaNoInicioDuplo(const T& dado) {
	    ElementoDuplo<T> *novo;
	    novo = new ElementoDuplo<T>(dado, nullptr, head);
	    if (novo == nullptr) {
	        throw "errolistacheia";
	    } else {
            head = novo;
            if (novo->getSucessor() != nullptr) {
                novo->getSucessor()->setAnterior(novo);
            }
        size++;
        }
	}
//! Método para retirar um elemento do inicio da lista dupla.
/*!
 * @return um genérico que vai ser a info do elemento retirado da lista.
 * O método começa testando se a lista esta vazia, se sim joga uma exceção, se
 * não, duas variaveis são criadas, um ponteiro ElementoDuplo<T> e um generico,
 * o ponteiro recebe o proximo do elemento head, e o generico recebe a info
 * desse ponteiro. Se o elemento cabeça não for nulo o seu anterior é setado
 * para um nullpointer. é deletado o ponteiro criado no método, o size é decre-
 * mentado, e é retonado o genérico.
 * @see listaVazia()
 */
	T retiraDoInicioDuplo() {
	    if (listaVazia()) {
	        throw "Erro lista vazia";
	    } else {
	        ElementoDuplo<T>* sai;
	        sai = head;
	        T volta = sai->getInfo();
	        head = sai->getSucessor();
	        if (head != nullptr) {
	            head->setAnterior(nullptr);
	        }
	        delete sai;
	        size--;
	        return volta;
	    }
	}
//! Método para eliminar o elemento do inicio e sua informação.
/*!
 * Método similar ao retiraDoInicioDuplo() porém ele não tem retorno e deleta
 * não só o elemento que sai mas também a sua informação
 * @see listaVazia(), retiraDoInicio()
 */
	void eliminaDoInicioDuplo() {
	    if (listaVazia()) {
	        throw "Erro lista vazia";
	    } else {
	        ElementoDuplo<T>* sai;
	        sai = head;
	        head = sai->getSucessor();
	        if (head != nullptr) {
	            head->setAnterior(nullptr);
	        }
	        delete sai->getInfo();
	        delete sai;
	        size--;
	    }
	}
//! Método para adicionar um elemento a lista em uma determinada posição.
/*!
 * @param dado, o endereço da memória de um genérico que vai ser adicionado.
 * @param pos um inteiro que indica a posição em que o dado será adicionado.
 * Inicialmente, é feita a verificação para saber se a posição é valida, se ela
 * não for, uma exceção é jogada, senão é verificado se a lista está vazia, ou
 * se a posição equivale a posição inicial, se sim o método de adicionar no
 * inicio é chamado, senão é criado dois ponteiro ElementoDuplo<T> e um deles,
 * o que será usado para caminhar chamado de ant recebe o elemento head.
 * Após isso um laço for é criado, para andar na lista. Após o termino do laço
 * o outro ponteiro que foi criado chamado novo é alocado, recebendo como
 * parâmetros, o dado que foi passado como parâmetro do método para ser a info,
 * o ponteiro ant que foi criado no método para ser o anterior. e o proximo
 * do elemento ant para ser o sucessor do novo, se o sucessor do novo não for 
 * um ponteiro nullo, esse sucessor recebe como anterior o proprio novo, e
 * para terminar o sucessor do elemento ant é setado para o novo, e o size é
 * incrementado.
 * @see listaVazia(), adicionaNoInicioDuplo().
 */
	void adicionaNaPosicaoDuplo(const T& dado, int pos) {
	    if (pos > size || pos < 0) {
	        throw "ERROPOSICAO";
	    } else {
	        if (pos == 0 || listaVazia()) {
	            adicionaNoInicioDuplo(dado);
	        } else {
	            ElementoDuplo<T> *novo, *ant;
	            ant = head;
	            for (int i = 0; i < pos - 1; i++) {
	                ant = ant->getSucessor();
	            }
	            novo = new ElementoDuplo<T>(dado, ant, ant->getSucessor());
	            if (novo->getSucessor() != nullptr) {
	                novo->getSucessor()->setAnterior(novo);
	            }
	            ant->setSucessor(novo);
	            size++;
	        }
	    }
	}
//! Método para retornar a posição de um determinado dado.
/*!
 * @return um inteiro que vai ser a posição em que está o elemento com o dado.
 * @param o endereço da memória do dado genérico do qual se quer saber a posição
 * é criado um ponteiro ElementoDuplo<T> para andar na lista e um inteiro para
 * ser o controlador de um laço. Uma verificação é feita para saber se a lista
 * está vazia, se estiver joga uma exceção senão continua para descobrir a pos
 * do dado. a variavel int pos recebe 0 e o ponteiro de ElementoDuplo<T> recebe
 * head. enquando a variavel inteira pos for menor que o tamanho da lista, uma
 * verificação é feita, se a info do Elemento da lista for igual ao dado passado
 * como parâmetro ele retorna a pos, caso não for, o corre recebe o seu proximo
 * e a pos é incrementada. Se após tudo isso não for achado o elemento, uma
 * exceção é jogada dizendo que o elemento não existe na lista.
 * @see listaVazia();
 */
	int posicaoDuplo(const T& dado) const {
	    ElementoDuplo<T> *corre;
	    int pos;
	    if (listaVazia()) {
	        throw "ERROLISTAVAZIA";
	    } else {
	        pos = 0;
	        corre = head;
	        while (pos < size) {
	            if (corre->getInfo() == dado) {
	                return pos;
	            }
	            corre = corre->getSucessor();
	            pos++;
	        }
	        throw "ELEMENTO INEXISTENTE";
	    }
	}
//! Método para retornar a posição na memória de um determinado dado.
/*!
 * @return um ponteiro generico que é a pos da mem do elemento que contem o dado
 * @param o endereço da memória do dado genérico do qual se quer saber a posição
 * Uma verificação é feita para saber se a lista está vazia, se estiver joga uma
 * exceção senão continua para descobrir a posição da mem. É criado um ponteiro 
 * ElementoDuplo<T> para andar na lista e um inteiro para ser o controlador de 
 * um laço. A variavel int pos recebe 0 e o ponteiro de ElementoDuplo<T> recebe
 * head. enquando a variavel inteira pos for menor que o tamanho da lista, uma
 * verificação é feita, se a info do Elemento da lista for igual ao dado passado
 * como parâmetro é criado um generico que recebe essa info, e é retornado sua
 * posição na memória, caso não for, o corre recebe o seu proximo e a pos é 
 * incrementada. Se após tudo isso não for achado o elemento, uma exceção é 
 * jogada dizendo que o elemento não existe na lista.
 * @see listaVazia();
 */
	T* posicaoMemDuplo(const T& dado) const {
	    if (listaVazia()) {
	        throw "ERROLISTAVAZIA";
	    } else {
	        ElementoDuplo<T> *corre;
	        int pos = 0;
	        corre = head;
	        while (pos <= size) {
	            if (corre->getInfo() == dado) {
	                T volta = corre->getInfo();
	                return &volta;
	            }
	            corre = corre->getSucessor();
	            pos++;
	        }
	        throw "ELEMENTOINEXISTENTE";
	    }
	}
//! Método de retorno booleano para saber se um dado existe na lista.
/*!
 * @param dado, o endereço da memoria de um generico.
 * @return boolean, verdadeiro se existe esse dado na lista, falso se não.
 * é verificado se a lista está vazia, se sim return false, se não, são criadas 
 * 2 variaveis internas, um ponteiro ElementoDuplo<T> corre, e um int pos, pos é
 * inicializado com 1 e corre com o elemento head e um laço para andar pela 
 * lista é criado, o laço é igual ao do posicaoMemDuplo(), só que ele retorna 
 * true na verificação dentro do laço.
 * @see posicaoMemDuplo(), listaVazia().
 */
	bool contemDuplo(const T& dado) {
	    if (listaVazia()) {
	        return false;
	    } else {
    	    ElementoDuplo<T> *corre;
    	    int pos = 1;
    	    corre = head;
    	    while (pos <= size) {
    	       if (corre->getInfo() == dado) {
    	             return true;
    	       }
    	       corre = corre->getSucessor();
    	       pos++;
    	    }
    	    return false;
    	}
	}
//! Método para retira um elemento de uma determinada posição.
/*!
 * @param um inteiro que será a posição em que vai ser retirado o elemento.
 * @return um genérico que vai ser a info do elemento retirado.
 * é verificado se a posicao passada como parâmetro é valida se não é, então uma
 * exceção é jogada, se é valida então prossegue para proxima verificação, que
 * se a posição passada como parâmetro é zero, se sim é retirado um elemento
 * do inicio, se não são criadas duas variaveis internas, dois ponteiros de
 * ElementoDuplo<T> chamados atual e eliminar, o atual recebe o elemento cabeça
 * e um laço for é criado para caminhar na lista até a posição que foi passada
 * como parâmetro, dentro do laço o elemento atual recebe o proximo.
 * Quando é terminado o laço, o Elemento duplo eliminar recebe o sucessor de
 * atual um generico é criado que recebe a info de eliminar, o sucessor de atual
 * é setado para ser o sucessor de eliminar, e se esse sucessor não for nulo
 * ele recebe o atual como anterior. após tudo isso o eliminar é deletado, o
 * tamanho da lista e decrementada e o generico com a info do delete é retornado
 * @see retiraDoInicioDuplo()
 */
	T retiraDaPosicaoDuplo(int pos) {
	    if (pos > size || pos < 0) {
	        throw "errposicao";
	    } else {
	        if (pos == 0) {
	            return retiraDoInicioDuplo();
	        } else {
	            ElementoDuplo<T> *atual, *eliminar;
	            atual = head;
	            for (int i = 1; i < pos; i++) {
	                atual = atual->getSucessor();
	            }
	            eliminar = atual->getSucessor();
	            T volta = eliminar->getInfo();
	            atual->setSucessor(eliminar->getSucessor());
	            if (atual->getSucessor() != nullptr) {
	                eliminar->getSucessor()->setAnterior(atual);
	            }
	            delete eliminar;
	            size--;
	            return volta;
	        }
	    }
	}
//! Método para adicionar no fim da lista
/*!
 * @param o endereço da memória do dado genérico que será adicionado na lista.
 * se a lista estiver vazia, é chamado o método adicionaNoInicio, já que será
 * o fim da lista. senão é chamado o método adicionaNaPosicao com o dado e
 * o tamanho da lista como parâmetro.
 * @see listaVazia(), adicionaNoInicioDuplo(), adicionaNaPosicaoDuplo().
 */
	void adicionaDuplo(const T& dado) {
	    if (listaVazia()) {
	        adicionaNoInicioDuplo(dado);
	    } else {
	        adicionaNaPosicaoDuplo(dado, size);
	    }
	}
//! método para retirar o ultimo elemento não nulo da lista.
/*!
 * @return um generico que vai ser a info do elemento retirado.
 * é verificado se a lista está vazia, caso esteja uma exceção é jogada, caso
 * não esteja é retornado um retiraDaPosicao() com size-1 como parâmetro, assim
 * deletando o ultimo elemento não nulo da lista.
 * @see retiraDaPosicao(), listaVazia()
 */
	T retiraDuplo() {
		if (listaVazia()) {
	        throw "ERROLISTAVAZIA";
	    } else {
	        return retiraDaPosicaoDuplo(size-1);
	    }
	}
//! método para retirar um dado especifico da lista
/*!
 * @param dado, o endereço da memoria do dado que será removido.
 * @return um generico que será a info do elemento removido.
 * o método começa verificando se a lista está vazia, se estiver uma exceção é
 * jogada, se não é verificado se o dado existe efetivamente na lista, se sim
 * é chamado o metodo retiraDaPosicao() como posicao a posicao do dado que é
 * "descoberta" por meio do método posicao() com o dado como parâmetro, se o 
 * dado não existe na lista, é jogada uma exceção.
 * @see listaVazia(), retiraDaPosicao(), posicao()
 */
	T retiraEspecificoDuplo(const T& dado) {
	    if (listaVazia()) {
	        throw "ERROLISTAVAZIA";
	    } else {
	        if (contemDuplo(dado) == true) {
	            return retiraDaPosicaoDuplo(posicaoDuplo(dado));
	        } else {
	            throw "DADOINEXISTENTE";
	        }
	    }
	}
//! Método para retornar a info de um elemento em uma certa posição.
/*!
 * @param a posição em que está o elemento que vai mostar a info.
 * @return um genérico que vai ser a info do elemento.
 * é feita a verificação para saber se a lista está vazia, se estiver, uma
 * exceção é lançada, senão um ponteiro ElementoDuplo<T> que já recebe head.
 * Um laço é criado e esse ponteiro vai recebendo o proximo elemento, no fim
 * é retornado a info do elemento.
 * @see listaVazia()
 */
	T mostra(int pos) {
	    if (listaVazia()) {
	        throw "ERROLISTAVAZIA";
	    } else {
	        ElementoDuplo<T> *corre;
	        corre = head;
	        for (int i = 0; i < pos; i++) {
	            corre = corre->getSucessor();
	        }
	        return corre->getInfo();
	    }
	}
//! Método para adicionar os dados em ordem
/*!
 * @param data, o espaço na memoria do dado, que vai ser adicionado na lista.
 * Sem valor de retorno, o método adiciona em ordem tem duas variaveis internas,
 * um ponteiro do tipo ElementoDuplo<T> chamado atual, que vai servir para andar
 * na lista, e um inteiro posi, que vai servir para saber onde colocar o dado,
 * é feita uma verificação para saber se a lista está vazia, se estiver o dado
 * é inserido no inicio, se não, atual recebe o elemento head, e posi é iniciado
 * com 1, um laço while é criado e só irá parar quando o proximo de atual for
 * nulo, significando que chegou no fim da lista, ou o data for menor que a info
 * de atual, dentro do while o atual recebe o seu proximo e posi é incrementado
 * após o final do laço, é feita uma verificação para saber se o laço acabou
 * por conta do fim da lista ou por ter achado um info de atual que é maior que
 * data, se o laço acabou por causa do fim da lista, é chamado o método adiciona
 * naPosicaoDuplo(data, posi+1), se não adicionaNaPosicaoDuplo(data,posi-1)
 * @see adicionaNaPosicaoDuplo(), adicionaNoInicioDuplo(), maior().
 */
	void adicionaEmOrdem(const T& data) {
	    ElementoDuplo<T> *atual;
	    int posi;
	    if (listaVazia()) {
	        adicionaNoInicioDuplo(data);
	    } else {
	        atual = head;
	        posi = 1;
	        while (atual->getSucessor() != nullptr &&
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
//! Método para retornar a posição do ultimo elemento.
/*!
 * @return size - 1 que é a posição do ultimo elemento.
 */
	int verUltimo() {
	    return size-1;
	}
//! método para saber se a lista está vazia
/*!
 * @return boolean, true se size for zero, e falso caso contrario
 */
	bool listaVazia() const {
	    return size == 0;
	}
//! método para saber se um dado1 é igual a um dado2.
/*!
 * @return boolean, true se dado1 for igual a dado2, falso se não.
 */
	bool igual(T dado1, T dado2) {
	    return dado1 == dado2;
	}
//! método para saber se um dado1 é maior que um dado2.
/*!
 * @return boolean, true se dado1 for maior que dado2, falso se não.
 */
	bool maior(T dado1, T dado2) {
	    return dado1 > dado2;
	}
//! método para saber se um dado1 é menor que um dado2.
/*!
 * @return boolean, true se dado1 for menor que dado2, falso se não.
 */
	bool menor(T dado1, T dado2) {
	    return dado1 < dado2;
	}
//! método para deletar a lista.
/*!
 * O método destroiListaDuplo não tem parametro, nem retorno, tem duas variaveis
 * internas , dois ponteiros do tipo ElementoDuplo<T> chamadas atual e deleta,
 * a atual começa recebendo o elemento head e um laço for é criado com condição 
 * de parada i >= size - 1  enquanto não for, o deleta recebe atual, atual 
 * recebe o proximo elemento, e o deleta é deletado, após o fim do laço head 
 * recebe nullptr e o size recebe zero, assim terminando o processo de 
 * destruição da lista.
 * @see ~ListaEnc()
 */
	void destroiListaDuplo() {
	   ElementoDuplo<T> *atual;
	   atual = head;
	   for (int i = 0; i < size-1; i++) {
	       ElementoDuplo<T>* deleta = atual;
	       atual = atual->getSucessor();
	       delete deleta;
	   }
	   head = nullptr;
	   size = 0;
	}
};

