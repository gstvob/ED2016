/* Copyright 2016 - Nathan Sargon Werlich, Gustavo Borges */
#ifndef NO_AVL_HPP
#define NO_AVL_HPP
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>

template <typename T>
/*!
 * @brief Construtor da Classe NoAVL
 * @details
*/
class NoAVL {
 private:
    int altur;  //!< Representa a altura do nó AVL
    T* dado;
    NoAVL<T>* esquerda;
    NoAVL<T>* direita;
    std::vector<NoAVL<T>* > elementos;

 public:
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    explicit NoAVL(const T& dado) {
        altur = 0;
        this->dado = new T(dado);
        esquerda = NULL;
        direita = NULL;
        elementos.clear();
    }
    virtual ~NoAVL() {
        delete dado;
        if (esquerda != NULL) {
            delete esquerda;
        }
        if (direita != NULL) {
            delete direita;
        }
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    int getAltura() {
        return altur;
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    int altura(NoAVL<T>* node) {
        if (node == NULL)
            return -1;
        else
            return node->getAltura();
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    int alturaEsq(NoAVL<T>* node) {
        if (node == NULL)
            return -1;
        else
            return altura(node->getEsquerda());
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    int alturaDir(NoAVL<T>* node) {
        if (node == NULL)
            return -1;
        else
            return altura(node->getDireita());
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    std::vector<NoAVL<T>* > getElementos() {
        return elementos;
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    NoAVL<T>* getEsquerda() {
        return esquerda;
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    NoAVL<T>* getDireita() {
        return direita;
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    NoAVL<T>* inserir(const T& dado, NoAVL<T>* arv) {
        return insercaoAVL(dado, arv, NULL);
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    NoAVL<T>* remover(NoAVL<T>* arv, const T& dado) {
        NoAVL<T> *tmp, *filho;
        if (arv == NULL) {
            return arv;
        } else {
            if (dado < *arv->getDado()) {
                arv->esquerda = remover(arv->getEsquerda(), dado);
                if (altura(arv->getEsquerda()) > altura(arv->getDireita())+1) {
                    if (alturaEsq(arv->getEsquerda()) >=
                                                alturaDir(arv->getEsquerda())) {
                        arv = simp_roda_esq(arv);
                    } else {
                        arv = dup_roda_esq(arv);
                    }
                } else if (altura(arv->getEsquerda())+1 <
                                                    altura(arv->getDireita())) {
                    if (alturaDir(arv->getDireita()) >=
                                                 alturaEsq(arv->getDireita())) {
                        arv = simp_roda_dir(arv);
                    } else {
                        arv = dup_roda_dir(arv);
                    }
                }
                arv->altur = std::max(altura(arv->getEsquerda()),
                            altura(arv->getDireita())) + 1;
                return arv;
            } else {
                if (dado > *arv->getDado()) {
                    arv->direita = remover(arv->getDireita(), dado);
                    if (altura(arv->getEsquerda()) >
                                                altura(arv->getDireita())+1) {
                        if (alturaEsq(arv->getEsquerda()) >=
                                                alturaDir(arv->getEsquerda())) {
                            arv = simp_roda_esq(arv);
                        } else {
                            arv = dup_roda_esq(arv);
                        }
                    } else if (altura(arv->getEsquerda())+1 <
                                                    altura(arv->getDireita())) {
                        if (alturaDir(arv->getDireita()) >=
                            alturaEsq(arv->getDireita())) {
                            arv = simp_roda_dir(arv);
                        } else {
                            arv = dup_roda_dir(arv);
                        }
                    }
                    arv->altur = std::max(altura(arv->getEsquerda()),
                                                 altura(arv->getDireita())) + 1;
                    return arv;
                } else {
                    if (arv->getDireita() != NULL &&
                                                arv->getEsquerda() != NULL) {
                        tmp = minimo(arv->getDireita());
                        *arv->dado = *tmp->getDado();
                        arv->direita = remover(arv->getDireita(),
                        *arv->getDado());
                        if (altura(arv->getEsquerda()) >
                                                altura(arv->getDireita())+1) {
                            if (alturaEsq(arv->getEsquerda()) >=
                                                alturaDir(arv->getEsquerda())) {
                                arv = simp_roda_esq(arv);
                            } else {
                                arv = dup_roda_esq(arv);
                            }
                        } else if (altura(arv->getEsquerda())+1 <
                                                 altura(arv->getDireita())) {
                            if (alturaDir(arv->getDireita()) >=
                                alturaEsq(arv->getDireita())) {
                                arv = simp_roda_dir(arv);
                            } else {
                                arv = dup_roda_dir(arv);
                            }
                        }
                        arv->altur = std::max(altura(arv->getEsquerda()),
                           altura(arv->getDireita())) + 1;
                        return arv;
                    } else {
                        tmp = arv;
                        if (arv->getDireita() != NULL) {
                            filho = arv->getDireita();
                            return filho;
                        } else {
                            if (arv->getEsquerda() != NULL) {
                                filho = arv->getEsquerda();
                                return filho;
                            } else {
                                delete arv;
                                return NULL;
                            }
                        }
                    }
                }
            }
        }
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    NoAVL<T>* minimo(NoAVL<T>* nodo) {
        if (nodo == NULL) {
            return NULL;
        } else {
            while (nodo->getEsquerda() != NULL) {
                nodo = nodo->getEsquerda();
            }
        }
        return nodo;
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    T* getDado() {
        return dado;
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    T* busca(const T& dado, NoAVL<T>* arv) {
        while (arv != NULL) {
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
    throw("!!!!!!!");
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    void preOrdem(NoAVL<T>* nodo) {
        if (nodo != NULL) {
            elementos.push_back(nodo);
            preOrdem(nodo->getEsquerda());
            preOrdem(nodo->getDireita());
        }
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    void emOrdem(NoAVL<T>* nodo) {
        if (nodo != NULL) {
            emOrdem(nodo->getEsquerda());
            elementos.push_back(nodo);
            emOrdem(nodo->getDireita());
        }
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    void posOrdem(NoAVL<T>* nodo) {
        if (nodo != NULL) {
            posOrdem(nodo->getEsquerda());
            posOrdem(nodo->getDireita());
            elementos.push_back(nodo);
        }
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    NoAVL<T> *simp_roda_esq(NoAVL<T>* k2) {
        NoAVL<T>* k1;
        k1 = k2->getEsquerda();
        k2->esquerda = k1->getDireita();
        k1->direita = k2;
        k2->altur = std::max(altura(k2->getEsquerda()),
                                                altura(k2->getDireita()))+1;
        k1->altur = std::max(altura(k1->getEsquerda()),
                                                altura(k1->getDireita()))+1;
        return k1;
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    NoAVL<T> *simp_roda_dir(NoAVL<T>* k2) {
        NoAVL<T>* k1;
        k1 = k2->getDireita();
        k2->direita = k1->getEsquerda();
        k1->esquerda = k2;
        k2->altur = std::max(altura(k2->getDireita()),
                                                altura(k2->getEsquerda()))+1;
        k1->altur = std::max(altura(k1->direita),
                                                altura(k1->getEsquerda()))+1;
        return k1;
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    NoAVL<T> *dup_roda_esq(NoAVL<T>* k3) {
            k3->esquerda = simp_roda_dir(k3->esquerda);
            return (simp_roda_esq(k3));
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    NoAVL<T> *dup_roda_dir(NoAVL<T>* k3) {
            k3->direita = simp_roda_esq(k3->direita);
            return (simp_roda_dir(k3));
    }
    /*!
     * @brief Construtor da Classe NoAVL
     * @details
    */
    NoAVL<T> *insercaoAVL(const T& dado, NoAVL<T>* arv, NoAVL<T>* pai) {
        NoAVL<T>* arv_rodada;
        if (arv == NULL) {
                arv = new NoAVL<T>(dado);
                if (arv == NULL) {
                    throw("1");
                }
                arv->dado = new T(dado);
                arv->altur = 0;
                arv->esquerda = NULL;
                arv->direita = NULL;
        } else {
                if (dado < *arv->getDado()) {
                    arv->esquerda = insercaoAVL
                                                (dado, arv->getEsquerda(), arv);
                    if ((altura(arv->getEsquerda()) -
                                            (altura(arv->getDireita()))) > 1) {
                        if (dado < *arv->esquerda->getDado()) {
                            arv_rodada = simp_roda_esq(arv);
                        } else {
                            arv_rodada = dup_roda_esq(arv);
                        }
                        return arv_rodada;
                    } else {
                        arv->altur = std::max(altura(arv->getEsquerda()),
                                                altura(arv->getDireita())) + 1;
                    }
                } else {
                    if (dado > *arv->getDado()) {
                        arv->direita = insercaoAVL
                                                (dado, arv->getDireita(), arv);
                        if ((altura(arv->getDireita()) -
                                              altura(arv->getEsquerda())) > 1) {
                            if (dado > *arv->direita->getDado()) {
                                arv_rodada = simp_roda_dir(arv);
                            } else {
                                arv_rodada = dup_roda_dir(arv);
                            }
                            return arv_rodada;
                        } else {
                            arv->altur = std::max(altura(arv->getDireita()),
                                                altura(arv->getEsquerda())) + 1;
                        }
                    } else {
                        throw("1");
                    }
                }
        }
        return arv;
    }
};

#endif /* NO_AVL_HPP */