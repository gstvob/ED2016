//! Copyright Gustavo Borges França , Nathan Werlich 2016
#ifndef NO_AVL_HPP
#define NO_AVL_HPP
#include <vector>
#include <algorithm>

template <typename T>
class NoAVL  {
 private:
    int altura;  //!< Representa a altura do nó AVL
    T* dado;  //!< Ponteiro generico que representa o dado do nó AVL
    NoAVL<T>* esquerda;  //!< "Filho" da esquerda de um nó "Pai"
    NoAVL<T>* direita;  //!< "Filho" da direita de um nó "pai"
    std::vector<NoAVL<T>* > elementos; //

 public:
    explicit NoAVL(const T& dado) {
        esquerda = nullptr;
        direita = nullptr;
        altura = 0;
        this->dado = new T(dado);
    }
    virtual ~NoAVL() {
        delete esquerda;
        delete direita;
        delete dado;
        altura = 0;
        elementos.clear();
    }
    int getAltura() {
        return altura;
    }
    std::vector<NoAVL<T>* > getElementos() {
        return elementos;
    }
    NoAVL<T>* getEsquerda() {
        return esquerda;
    }
    NoAVL<T>* getDireita() {
        return direita;
    }
    NoAVL<T>* inserir(const T& dado, NoAVL<T>* arv) {
        return insereAVL(dado, arv, nullptr);     
    }
    NoAVL<T>* remover(NoAVL<T>* arv, const T& dado) {
        NoAVL<T>* temp, *filho;
        if (arv == nullptr) {
            return arv;
        } else {
            if (dado < *arv->getDado()) {
                arv->esquerda = remover(arv->getEsquerda(), dado);
                arv = Ziguezague(arv);
                arv->altura = std::max(alt(arv->getEsquerda()),
                            alt(arv->getDireita())) + 1; 
                return arv;
            } else if (dado > *arv->getDado()) {
                arv->direita = remover(arv->getDireita(), dado);
                arv = Ziguezague(arv);
                arv->altura = std::max(alt(arv->getEsquerda()),
                            alt(arv->getDireita())) + 1; 
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
    NoAVL<T>* minimo(NoAVL<T>* nodo) {
        NoAVL<T>* walker = nodo;
        if (walker == nullptr) {
            return nullptr;
        } else {
            while (walker->getEsquerda() != nullptr) {
                walker = walker->getEsquerda();
            }
            return walker;
        }

    }
    T* getDado() {
        return dado;
    }
    T* busca(const T& dado, NoAVL<T>* arv) {
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
    void preOrdem(NoAVL<T>* nodo) {
        if (nodo != nullptr) {
            elementos.push_back(nodo);
            preOrdem(nodo->getEsquerda());
            preOrdem(nodo->getDireita());
        }
    }
    void emOrdem(NoAVL<T>* nodo) {
        if (nodo != nullptr) {
            emOrdem(nodo->getEsquerda());
            elementos.push_back(nodo);
            emOrdem(nodo->getDireita());
        }
    }
    void posOrdem(NoAVL<T>* nodo) {
        if (nodo != nullptr) {
            posOrdem(nodo->getEsquerda());
            posOrdem(nodo->getDireita());
            elementos.push_back(nodo);
        }
        return elementos;
    }

//algoritmos novos
    int alt(NoAVL<T>* k1) {
        if (k1 == nullptr) {
            return -1;
        } else {
            return k1->getAltura();
        }
    }
    NoAVL<T>* simpRodaEsq(NoAVL<T>* k2) {
        NoAVL<T>* k1;
        k1 = k2->getEsquerda();
        k2->esquerda = k1->getDireita();
        k1->direita = k2;
        k2->altura = std::max(alt(k2->getEsquerda()), alt(k2->getDireita())) + 1;
        k1->altura = std::max(alt(k1->getEsquerda()), k2->getAltura()) + 1;
        return k1;
    }
    NoAVL<T>* simpRodaDir(NoAVL<T>* k2) {
        NoAVL<T>* k1;
        k1 = k2->getDireita();
        k2->direita = k1->getEsquerda();
        k1->esquerda = k2;
        k2->altura = std::max(alt(k2->getDireita()), alt(k2->getEsquerda())) + 1;
        k1->altura = std::max(alt(k1->getDireita()), k2->getAltura()) + 1;
        return k1;
    }
    NoAVL<T>* duplRodaEsq(NoAVL<T>* k3) {
        k3->esquerda = simpRodaDir(k3->getEsquerda());
        return (simpRodaEsq(k3));
    }
    NoAVL<T>* duplRodaDir(NoAVL<T>* k3) {
        k3->direita = simpRodaEsq(k3->getDireita());
        return (simpRodaDir(k3));
    }

    //! algoritmo de inserção do avl agora 
    NoAVL<T>* insereAVL(const T& dado, NoAVL<T>* arv, NoAVL<T>* pai) {
        NoAVL<T>* arv_rodada;
        if (arv == nullptr) {
            arv = new NoAVL<T>(dado);
            if (arv == nullptr) {
                throw "ERRO";
            }
        } else if (dado < *arv->getDado()) {
            arv->esquerda = insereAVL(dado, arv->getEsquerda(), arv);
            if (alt(arv->getEsquerda()) - alt(arv->getDireita()) > 1) {
                if (dado < *arv->getEsquerda()->getDado()) {
                    arv_rodada = simpRodaEsq(arv);
                } else {
                    arv_rodada = duplRodaEsq(arv);
                } 
                return arv_rodada;
            } else {
                arv->altura = std::max(alt(arv->getEsquerda()), alt(arv->getDireita())) + 1;
            }
        } else if (dado > *arv->getDado()) {
            arv->direita = insereAVL(dado, arv->getDireita(), arv);
            if (alt(arv->getDireita()) - alt(arv->getEsquerda()) > 1) {
                if (dado > *arv->getDireita()->getDado()) {
                    arv_rodada = simpRodaDir(arv);
                } else {
                    arv_rodada = duplRodaDir(arv);
                }
                return arv_rodada;
            } else { 
                arv->altura = std::max(alt(arv->getDireita()), alt(arv->getEsquerda())) + 1;
            }
        } else {
            throw "ERRO";
        }
        return arv;
    }
    NoAVL<T>* Ziguezague(NoAVL<T>* k3) {
        if (alt(k3->getEsquerda()) > alt(k3->getDireita())) {
            NoAVL<T>* esq = k3->getEsquerda();
            if (alt(esq->getEsquerda()) >= alt(esq->getDireita())) {
                k3 = simpRodaEsq(k3);
            } else {
                k3 = duplRodaEsq(k3);
            }
        } else if (alt(k3->getDireita()) > alt(k3->getEsquerda())){
            NoAVL<T>* dir = k3->getDireita();
            if (alt(dir->getDireita()) >= alt(dir->getEsquerda())) {
                k3 = simpRodaDir(k3);
            } else {
                k3 = duplRodaDir(k3);
            }
        }
        return k3;
    }
};

#endif /* NO_AVL_HPP */