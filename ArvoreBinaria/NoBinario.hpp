
/*! Copyright Gustavo Borges França 2016 */
#ifndef NO_BINARIO_HPP
#define NO_BINARIO_HPP

#include <cstdlib>
#include <vector>

template<typename T>
/*!
 * @brief classe de implementação de uma arvore binaria
 */
class NoBinario {
 protected:
    T* dado; /*<! o dado de um nó>*/
    NoBinario<T>* esquerda; /*<! o filho a esquerda de um nó>*/
    NoBinario<T>* direita; /*<! o filho a direita de um nó>*/
    std::vector<NoBinario<T>* > elementos;  //!< Elementos acessados durante
                                            // o percurso realizado

 public:
 	/*!
 	 * @brief construtor que inicializa o dado, o filho da esquerda e o da direita de um nodo.
 	 */
    NoBinario<T>(const T& dado) {
        this->dado = new T(dado);
        esquerda = nullptr;
        direita = nullptr;
    }
    /*!
     * @brief destrutor que deleta o dado, o filho da direita e o da esquerda de um nodo.
     */
    virtual ~NoBinario() {
        delete(dado);
        delete(esquerda);
        delete(direita);
    }
    /*!
     * @brief método que retorna o dado do nodo.
     * @return ponteiro de um genérico que é o dado do nodo.
     */
    T* getDado() {
        return dado;
    }
    /*!
     * @brief método para retornar o vetor dos elementos.
     * @return o vector de nodos da arvore.
     */
    std::vector< NoBinario<T>* > getElementos() {
        return elementos;
    }
    /*!
     * @brief getter que retorna o filho da esquerda de um nodo.
     * @return o ponteiro que é um nodo que é filho da esquerda de outro nodo.
     */
    NoBinario<T>* getEsquerda() {
        return esquerda;
    }
    /*!
     * @brief getter que retorna o filho da direita de um nodo.
     * @return o ponteiro que é um nodo que é filho da direita de outro nodo.
     */
    NoBinario<T>* getDireita() {
        return direita;
    }
    /*!
     * @brief método que busca se existir um dado em um nodo de uma arvore.
     * @param o endereço do dado que se quer encontrar
     * @param o ponteiro da arvore onde se vai procurar.
     * @return ponteiro de um genérico que vai ser o dado buscado(se encontrado)
     */
    T* busca(const T& dado, NoBinario<T>* arv) {
        while (arv != nullptr) {
        	if (*arv->getDado() != dado) {
            	if (*arv->getDado() < dado) {
                	arv = arv->getDireita();
            	} else {
                	arv = arv->getEsquerda();
            	}
        	} else {
        		return arv->getDado();
        	}
        }
        throw "ERRO";
    }
    /*!
     * @brief método para inserir dados na arvore.
     * @param o endereço do dado que vai ser o dado inserido na arvore.
     * @param ponteiro da arvore/subarvore que vai ter um dado adicionado.
     * @return ponteiro da arvore.
     */
    NoBinario<T>* inserir(const T& dado, NoBinario<T>* arv) {
        if (dado < *arv->getDado()) {
            if (arv->getEsquerda() == nullptr) {
                NoBinario<T>* novo = new NoBinario<T>(dado);
                arv->esquerda = novo;
            } else {
                return arv->inserir(dado, arv->getEsquerda());
            }
        } else {
                if (arv->getDireita() == nullptr) {
                NoBinario<T>* novo = new NoBinario<T>(dado);
                arv->direita = novo;
            } else {
                return arv->inserir(dado, arv->getDireita());
            }
        }
        return arv;
    }
    /*!
     * @brief método para retirar um dado da arvore.
     * @param ponteiro que indica a subarvore/arvore para procurar o dado.
     * @param endereço do dado que se quer adicionar.
     * @return ponteiro de um nodo generico.
     */
    NoBinario<T>* remover(NoBinario<T>* arv, const T& dado) {
        NoBinario<T>* temp, *filho;
        if (arv == nullptr) {
            return arv;
        } else {
            if (dado < *arv->getDado()) {
                arv->esquerda = remover(arv->getEsquerda(), dado);
                return arv;
            } else if (dado > *arv->getDado()) {
                arv->direita = remover(arv->getDireita(), dado);
                return arv;
            } else {
                if (arv->getDireita() != nullptr &&
                                    arv->getEsquerda() != nullptr) {
                    temp = minimo(arv->getDireita());
                    arv->dado = temp->getDado();
                    arv->direita = remover(arv->getDireita(), *arv->getDado());
                    return arv;
                } else {
                    temp = arv;
                    if (arv->getDireita() != nullptr) {
                        filho = arv->getDireita();
                        return filho;
                    } else if (arv->getEsquerda() != nullptr) {
                        filho = arv->getEsquerda();
                        return filho;
                    } else {
                        delete arv;
                        return nullptr;
                    }
                }
            }
        }
    }
    /*!
     * @brief método que retorna o nodo com menor valor da arvore.
     * @param nodo onde se vai começar a busca.
     * @return o nodo mais a esquerda e com maior nivel.
     */
    NoBinario<T>* minimo(NoBinario<T>* nodo) {
        NoBinario<T>* walker = nodo;
        if (walker == nullptr) {
        	return nullptr;
        } else {
       		while (walker->getEsquerda() != nullptr) {
            	walker = walker->getEsquerda();
        	}
        	return walker;
    	}
    }
    /*!
     * @brief método para percorrer a arvore em preOrdem(raiz,esquerda,direita)
     * @param ponteiro do nodo da arvore que será percorrida.
     */
    void preOrdem(NoBinario<T>* nodo) {
        if (nodo != nullptr) {
            elementos.push_back(nodo);
            preOrdem(nodo->getEsquerda());
            preOrdem(nodo->getDireita());
        }
    }
    /*!
     * @brief método para percorrer a arvore em emOrdem(esquerda,raiz,direita)
     * @param ponteiro do nodo da arvore que será percorrida.
     */
    void emOrdem(NoBinario<T>* nodo) {
        if (nodo != nullptr) {
            emOrdem(nodo->getEsquerda());
            elementos.push_back(nodo);
            emOrdem(nodo->getDireita());
        }
    }
    /*!
     * @brief método para perocorre a arvore em posOrdem(esquerda,direita,raiz)
     * @param ponteiro do nodo da arvore que será percorrida.
     */
    void posOrdem(NoBinario<T>* nodo) {
        if (nodo != nullptr) {
            posOrdem(nodo->getEsquerda());
            posOrdem(nodo->getDireita());
            elementos.push_back(nodo);
        }
    }
};

#endif /* NO_BINARIO_HPP */
