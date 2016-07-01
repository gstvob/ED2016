// "Copyright 2016 Gustavo Borges França"
#ifndef NO_RB_HPP
#define NO_RB_HPP

#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>

#define RB_RUBRO true
#define RB_NEGRO false

template <typename T>
/*!
 * @brief Construtor da Classe NoRB
 * @details
*/
class NoRB {
 private:
    T* dado;  //!< Atributo onde Ã© guardado o valor representado pelo nÃ³
    NoRB<T>* esquerda;  //!< Atributo que aponta para menor nÃ³ descendente
    NoRB<T>* direita;  //!< Atributo que aponta para maior nÃ³ descendente
    NoRB<T>* pai;  //!< Atributo que aponta para nÃ³ ascendente
    std::vector<NoRB<T>* > elementos;
    bool cor;  //!< Atributo que indica a cor do nÃ³

 public:
    /*!
     * @brief Construtor da Classe NoRB
     * @details
    */
    explicit NoRB(const T& dado) {
        this->dado = new T(dado);
        esquerda = nullptr;
        direita = nullptr;
        pai = nullptr;
        elementos.clear();
        cor = RB_NEGRO;
    }
    virtual ~NoRB() {}
    /*!
     * @brief Construtor da Classe NoRB
     * @details
    */
    NoRB<T>* getPai() {
        return pai;
    }
    /*!
     * @brief Construtor da Classe NoRB
     * @details
    */
    bool getCor(NoRB<T>* nodo) {
        if (nodo != nullptr) {
            return nodo->cor;
        } else {
            return false;
        }
    }
    /*!
     * @brief Construtor da Classe NoRB
     * @details
    */
    std::vector<NoRB<T>* > getElementos() {
        return elementos;
    }
    /*!
     * @brief Construtor da Classe NoRB
     * @details
    */
    NoRB<T>* getEsquerda() {
        return esquerda;
    }
    /*!
     * @brief Construtor da Classe NoRB
     * @details
    */
    NoRB<T>* getDireita() {
        return direita;
    }

    /*!
     * @brief Construtor da Classe NoRB
     * @details
    */
    NoRB<T>* minimo(NoRB<T>* nodo) {
       while (nodo->getEsquerda() != NULL) {
            nodo = nodo->getEsquerda();
        }
        return nodo;
    }
    /*!
     * @brief Construtor da Classe NoRB
     * @details
    */
    T* getDado() {
        return dado;
    }
    /*!
     * @brief Construtor da Classe NoRB
     * @details
    */
    T* busca(const T& dado, NoRB<T>* arv) {
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
     * @brief Construtor da Classe NoRB
     * @details
    */
    void preOrdem(NoRB<T>* nodo) {
        if (nodo != NULL) {
            emOrdem(nodo->getEsquerda());
            elementos.push_back(nodo);
            emOrdem(nodo->getDireita());
        }
    }
    /*!
     * @brief Construtor da Classe NoRB
     * @details
    */
    void emOrdem(NoRB<T>* nodo) {
        if (nodo != NULL) {
            emOrdem(nodo->getEsquerda());
            elementos.push_back(nodo);
            emOrdem(nodo->getDireita());
        }
    }
    /*!
     * @brief Construtor da Classe NoRB
     * @details
    */
    void posOrdem(NoRB<T>* nodo) {
        if (nodo != NULL) {
            posOrdem(nodo->getEsquerda());
            posOrdem(nodo->getDireita());
            elementos.push_back(nodo);
        }
    }
    /*!
     * @brief Construtor da Classe NoRB
     * @details
    */
    NoRB<T>* roda_esq(NoRB<T>* x) {
        NoRB<T> *y, *pai;
        bool lado;  // false = esquerda || true = direita
        pai = x->getPai();  // guardo o pai da subÃ¡rvore que vou rodar
        if (pai->getEsquerda() == x) {  // x estÃ¡ pendurado de qual lado do pai?
            lado = false;
        } else {
            lado = true;
        }
        y = x->getDireita();
        y->pai = pai;
        if (y->esquerda != nullptr) {
            x->direita = y->esquerda;
            x->direita->pai = x;
        }
        y->esquerda = x;
        y->esquerda->pai = y;
        if (pai != nullptr) {
            if (lado == false) {
                pai->esquerda = y;
            } else {
                pai->direita = y;
            }
        }
        return y;
    }
    /*!
     * @brief Construtor da Classe NoRB
     * @details
     */
    NoRB<T>* roda_dir(NoRB<T>* x) {
        NoRB<T> *y, *pai;
        bool lado;  // false = esquerda || true = direita
        pai = x->getPai();    // guardo o pai da subÃ¡rvore que vou rodar
        if (pai->getEsquerda() == x) {  // x estÃ¡ pendurado de qual lado do pai?
            lado = false;
        } else {
            lado = true;
        }
        y = x->esquerda;
        y->pai = pai;       //  roda & ajusta pais
        if (y->direita != nullptr) {
            x->esquerda = y->direita;
            x->esquerda->pai = x;
        }
        y->direita = x;
        y->direita->pai = y;
        if (pai != nullptr) {
            if (lado == false) {
                pai->esquerda = y;
            } else {
                pai->direita = y;
            }
        }
        return y;
    }
    NoRB<T>* PassoCE_dir(NoRB<T> *atual, NoRB<T> *pai, NoRB<T> *avo) {
        NoRB<T>* tio;
        tio = avo->getEsquerda();
        if (getCor(tio) == RB_RUBRO) {          //  caso 1
            pai->cor = RB_NEGRO;
            avo->cor = RB_RUBRO;
            tio->cor = RB_NEGRO;
            atual = avo;                //  sobe 2 nÃ­veis
        } else {
            if (pai->getEsquerda() == atual) {      //  caso 2
                avo->direita = roda_dir(pai);
                pai = atual;
                atual = atual->getDireita();            //  reseta atual
            }
            pai->cor = RB_NEGRO;            //  caso3
            avo->cor = RB_RUBRO;
            return roda_esq(avo);
       }
       return nullptr;
    }
    /*!
     * @brief Construtor da Classe NoRB
     * @details
     */
    NoRB<T>* PassoCE_esq(NoRB<T> *atual, NoRB<T> *pai, NoRB<T> *avo) {
        NoRB<T>* tio;
        tio = avo->getDireita();
        if (getCor(tio) == true) {          //  caso 1
            pai->cor = RB_NEGRO;
            avo->cor = RB_RUBRO;
            tio->cor = RB_NEGRO;
            atual = avo;            //  sobe 2 nÃ­veis
        } else {
            if (pai->getDireita() == atual) {       //  caso 2
                roda_esq(pai);
                pai = atual;
                atual = atual->getEsquerda();           //  reseta atual
            }
            pai->cor = RB_NEGRO;            //  caso3
            avo->cor = RB_RUBRO;
            return roda_dir(avo);
        }
        return nullptr;
    }
    /*!
     * @brief Construtor da Classe NoRB
     * @details
     */
    NoRB<T>* InsereRB(const T& dado, NoRB<T>* arv, NoRB<T>* nodo) {
        NoRB<T> *atual, *pai, *avo;
        InsereAB(dado, arv);
        nodo->cor = RB_RUBRO;
        atual = nodo;
        while ((atual != arv) && (getCor(atual->pai) == RB_RUBRO)) {
            pai = atual->getPai();
            avo = pai->getPai();
            if (avo->getEsquerda() == pai) {
                atual = PassoCE_esq(atual, pai, avo);
            } else {
                atual = PassoCE_dir(atual, pai, avo);
            }
        }
        // arv->cor = false;
        return arv;
    }
    /*!
     * @brief Construtor da Classe NoRB
     * @details
     */
    NoRB<T>* passoCED(NoRB<T>* w, NoRB<T>* raiz) {
        while (w != raiz) {     //  Cond. de tÃ©rmino
            if (w == w->getPai()->getEsquerda()) {
                w = passoCED_esq(w, raiz);      //  Esquerda
            } else {
                w = passoCED_dir(w, raiz);  //  Direita
            }
        }
    return w;
    }
    /*!
     * @brief Construtor da Classe NoRB
     * @details
     */
    NoRB<T>* passoCED_esq(NoRB<T>* w, NoRB<T>* arv) {
        NoRB<T>* y;
        y = w->getPai()->getDireita();              //  IrmÃ£o da direita
        if (getCor(y) == RB_RUBRO) {
            y->cor = RB_NEGRO;                              //  Caso 1
            w->pai->cor = RB_RUBRO;                             //  Caso 1
            roda_esq(w->pai);               //  Caso 1
            y = w->getPai()->getDireita();                  //  Reseta Caso 1
        }
        if ((getCor(y->getEsquerda()) == false) &&
                                         (getCor(y->getDireita()) == false)) {
            y->cor = RB_RUBRO;                                  //  Caso 2
            w = w->getPai();                                        //  Sobe Caso 2
        } else {
            if (getCor(y->getDireita()) == RB_NEGRO) {
                y->esquerda->cor = RB_NEGRO;                //  Caso 3
                y->cor = RB_RUBRO;                      //  Caso 3
                roda_dir(y);                        //  Caso 3
                y = w->getPai()->getDireita();              //  Caso 3
            }
            y->cor = getCor(w->getPai());                       //  Caso 4
            w->pai->cor = RB_NEGRO;                         //  Caso 4
            y->direita->cor = RB_NEGRO;                     //  Caso 4
            roda_esq(w->pai);                           //  Caso 4
            w = arv;                                    //  Caso 4
        }
        return w;
    }
    /*!
     * @brief Construtor da Classe NoRB
     * @details
     */
    NoRB<T>* passoCED_dir(NoRB<T>* w, NoRB<T>* arv) {
        NoRB<T>* y;
        y = w->getPai()->getEsquerda();             //  IrmÃ£o da direita
        if (getCor(y) == RB_RUBRO) {
            y->cor = RB_NEGRO;                              //  Caso 1
            w->pai->cor = RB_RUBRO;                             //  Caso 1
            roda_dir(w->pai);               //  Caso 1
            y = w->getPai()->getEsquerda();                 //  Reseta Caso 1
        }
        if ((getCor(y->direita) == RB_NEGRO) &&
                    (getCor(y->esquerda) == RB_NEGRO)) {
            y->cor = RB_RUBRO;                                  //  Caso 2
            w = w->getPai();                                        //  Sobe Caso 2
        } else {
            if (getCor(y->getEsquerda()) == RB_NEGRO) {
                y->direita->cor = RB_NEGRO;                 //  Caso 3
                y->cor = RB_RUBRO;                      //  Caso 3
                roda_esq(y);                        //  Caso 3
                y = w->getPai()->getEsquerda();             //  Caso 3
            }
            y->cor = getCor(w->getPai());                       //  Caso 4
            w->pai->cor = RB_NEGRO;                         //  Caso 4
            y->esquerda->cor = RB_NEGRO;                    //  Caso 4
            roda_dir(w->pai);                           //  Caso 4
            w = arv;                                    //  Caso 4
        }
        return w;
    }
        /*!
     * @brief Construtor da Classe NoRB
     * @details
    */
    NoRB<T>* inserir(const T& dado, NoRB<T>* arv) {
        return InsereRB(dado, arv, arv);
    }
    /*!
     * @brief Construtor da Classe NoRB
     * @details
    */
    NoRB<T>* remover(NoRB<T>* arv, const T& dado) {
        arv = removerAB(arv, dado);
        return passoCED(arv, arv);
    }
    NoRB<T>* removerAB(NoRB<T>* arv, const T& dado) {
        if (arv == NULL) {
            return arv;
        } else {
            if (dado < *(arv->getDado())) {
                arv->esquerda = remover(arv->getEsquerda(), dado);
                return arv;
            } else if (dado > *(arv->getDado())) {
                arv->direita = remover(arv->getDireita(), dado);
                return arv;
            } else {
                if (arv->getDireita() != NULL && arv->getEsquerda() != NULL) {
                    NoRB<T>* tmp = minimo(arv->getDireita());
                    arv->dado = tmp->getDado();
                    arv->direita = remover(arv->getDireita(), *(arv->dado));
                    return arv;
                } else {
                    if (arv->getDireita() != NULL) {
                        NoRB<T>* filho = (arv->getDireita());
                        return filho;
                    } else if (arv->getEsquerda() != NULL) {
                        NoRB<T>* filho = (arv->getEsquerda());
                        return filho;
                    } else {
                        delete arv;
                        return nullptr;
                    }
                }
            }
        }
    }
    NoRB<T>* InsereAB(const T& dado, NoRB<T>* arv) {
        NoRB<T>* novo;
        if (dado < *(arv->getDado())) {
            if (arv->getEsquerda() == nullptr) {
                novo = new NoRB<T>(dado);
                arv->esquerda = novo;
            } else {
                arv->esquerda = InsereAB(dado, arv->getEsquerda());
            }
        } else if (dado > *(arv->getDado())) {
            if (arv->getDireita() == nullptr) {
                novo = new NoRB<T>(dado);
                arv->direita = novo;
            } else {
                arv->direita = InsereAB(dado, arv->getDireita());
            }
        }
        return arv;
    }
};

#endif /* NO_RB_HPP */
