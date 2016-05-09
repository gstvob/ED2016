//! Copyright 2016 Gustavo Borges França
#include "ListaEnc.hpp"
template<typename T>
//! Classe de pilha encadeada
/*!
 * A classe pilha encadeada herda as operações da classe ListaEnc. a classe
 * da pilha encadeada não tem nenhum atributo.
 */
class PilhaEnc : public ListaEnc<T> {
 public:
//! Construtor Vazio
    PilhaEnc() {
    }
//! Destrutor
/*!
 * o destrutor apenas chama o método limpar pilha que deleta a pilha inteira.
 * @see limparPilha();
 */
    ~PilhaEnc() {
        limparPilha();
    }
//! Método para adicionar um elemento ao topo da pilha
/*!
 * @param endereço da memória do dado que vai ser adicionado na pilha, como a
 * a pilha herda os métodos da lista encadeada, é feito o uso do método adiciona
 * no inicio da lista encadeada
 * @see ListaEnc adicionaNoInicio()
 */
    void empilha(const T& dado) {
        this->adicionaNoInicio(dado);
    }
//! Método que retira o ultimo elemento que foi posto na pilha.
/*!
 * @retorno um genérico que é a informação do elemento retirado.
 * O método desempilha utiliza o método retira do inicio da classe ListaEnc.
 * @see ListaEnc retiraDoInicio()
 */
    T desempilha() {
        return this->retiraDoInicio();
    }
//! Método para retornar a informação do primeiro elemento no topo da lista.
/*!
 * @return um generico que vai ser a info do elemento head da classe ListaEnc
 */
	T topo() {
	    if (PilhaVazia()) {
	        throw "erro pilha vazia";
	    } else {
	        return this->head->getInfo();
	    }
	}
//! Método para apagar a lista.
/*!
 * Método sem retorno e sem parâmetros apenas chama o método destroiLista da
 * classe ListaEnc
 * @see ListaEnc destroiLista();
 */
	void limparPilha() {
        this->destroiLista();
	}
//! Método para saber se a pihla esta vazia.
/*!
 * @return um booleano que retorna verdade quando lista vazia e falso quando não
 * O método pilha vazia chama o método listaVazia de sua classe pai, e retorna
 * verdadeiro se a pilha estiver vazia, e falso caso não
 * @see ListaEnc listaVazia()
 */
	bool PilhaVazia() {
	    return this->listaVazia();
	}
};
