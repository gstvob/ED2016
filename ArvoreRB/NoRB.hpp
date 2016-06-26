#ifndef NO_RB_HPP
#define NO_RB_HPP

#include <vector>
#define RB_RUBRO true
#define RB_NEGRO false

template <typename T>
class NoRB {
 private:
    T* dado;  //!< Atributo onde é guardado o valor representado pelo nó
    NoRB<T>* esquerda;  //!< Atributo que aponta para menor nó descendente
    NoRB<T>* direita;  //!< Atributo que aponta para maior nó descendente
    NoRB<T>* pai;  //!< Atributo que aponta para nó ascendente
    bool cor;  //!< Atributo que indica a cor do nó
    std::vector<NoRB<T>*> elementos;

 public:
    explicit NoRB(const T& dado) {
	    this->dado = new T(dado);
	    esquerda = 0;
	    direita = 0;
	    cor = RB_NEGRO;
    	pai = 0;
    }
    virtual ~NoRB() {
        delete esquerda;
        delete direita;
	    delete pai;
	    delete dado;
    }
    NoRB<T>* getPai() {
    	return pai;
    }
    bool getCor(NoRB<T>*) {
    	return this->cor;
    }
    std::vector<NoRB<T>* > getElementos() {
	    return elementos;
    }
    NoRB<T>* getEsquerda() {
        return esquerda;
    }
    NoRB<T>* getDireita() {
        return direita;
    }
    NoRB<T>* inserir(const T& dado, NoRB<T>* arv) {
        return insereRB(arv,dado,nullptr);
    }
    NoRB<T>* remover(NoRB<T>* arv, const T& dado) {
        return removerB(arv, dado);
    }
    NoRB<T>* minimo(NoRB<T>* nodo) {
        NoRB<T>* min;
        if (nodo->getEsquerda() != nullptr) {
            min = minimo(nodo->getEsquerda());
        } else {
            min = nodo;
        }
        return min;
    }
    T* getDado() {
        return dado;
    }
    T* busca(const T& dado, NoRB<T>* arv) {
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
    void preOrdem(NoRB<T>* nodo) {
        if (nodo != nullptr) {
            elementos.push_back(nodo);
            preOrdem(nodo->getEsquerda());
            preOrdem(nodo->getDireita());
        }
    }
    void emOrdem(NoRB<T>* nodo) {
        if (nodo != nullptr) {
            emOrdem(nodo->getEsquerda());
            elementos.push_back(nodo);
            emOrdem(nodo->getDireita());
        }
    }
    void posOrdem(NoRB<T>* nodo) {
        if (nodo != nullptr) {
            posOrdem(nodo->getEsquerda());
            posOrdem(nodo->getDireita());
            elementos.push_back(nodo);
        }
    }
    NoRB<T>* simpRodaPE(NoRB<T>* x) {
        NoRB<T> *p, *y;
        bool lado;  // True == esquerda false == direita;
        p = x->getPai();
        if (p->getEsquerda() == x) {
            lado = true;
        } else {
            lado = false;
        }
        y = x->getDireita();
        y->pai = p;
        x->direita = y->getEsquerda();
        x->direita->pai = x;
        y->esquerda = x;
        y->esquerda->pai = y;
        if (lado == true) {
            p->esquerda = y;
        } else {
            p->direita = y;
        }
        return y;
    }
    NoRB<T>* simpRodaPD(NoRB<T>* x) {
        NoRB<T> *p, *y;
        bool lado;  // True == esquerda false == direita;
        p = x->getPai();
        if (pai->getEsquerda() == x) {
            lado = true;
        } else {
            lado = false;
        }
        y = x->getEsquerda();
        y->pai= p;
        x->esquerda = y->getDireita();
        x->esquerda->pai = x;
        y->direita = x;
        y->direita->pai = y;
        if (lado == true) {
            p->esquerda = y;
        } else {
            p->direita = y;
        }
        return y;
    }
    NoRB<T>* insereRB(NoRB<T>* raiz, const T& dado, NoRB<T>* nodo) {
        NoRB<T> *atual, *p, *avo;
        nodo = inserirB(dado, raiz);
        nodo->cor = RB_RUBRO;
        atual = nodo;
        while (atual != raiz && atual->pai->cor == RB_RUBRO) {
            p = atual->pai;
            avo = p->pai;
            if (avo->getEsquerda() == p) {
                passoCE_esq(atual, p, avo);
            } else {
                passoCE_dir(atual, p, avo);
            }
        }
        raiz->cor = false;
        return atual;
    }
    NoRB<T>* passoCE_esq(NoRB<T>* atual, NoRB<T>* p, NoRB<T>* avo) {
        NoRB<T>* tio = avo->getDireita();
        if (tio->cor == RB_RUBRO) {
            p->cor = RB_NEGRO;
            p->cor = RB_RUBRO;
            tio->cor = RB_NEGRO;
            atual = avo;
        } else {
            if (p->getDireita() == atual) {
                simpRodaPE(p);
                atual = atual->getEsquerda();
            }
            p->cor = RB_NEGRO;
            avo->cor = RB_RUBRO;
            simpRodaPD(avo);
        }
        return atual;
    }
    NoRB<T>* passoCE_dir(NoRB<T>* atual, NoRB<T>* p, NoRB<T>* avo) {
        NoRB<T>* tio = avo->getEsquerda();
        if (tio->cor == RB_RUBRO) {
            p->cor = RB_NEGRO;
            p->cor = RB_RUBRO;
            tio->cor = RB_NEGRO;
            atual = avo;
        } else {
            if (p->getEsquerda() == atual) {
                simpRodaPD(p);
                atual = atual->getDireita();
            }
            p->cor = RB_NEGRO;
            avo->cor = RB_RUBRO;
            simpRodaPE(avo);
        }
        return atual;
    }
    NoRB<T>* inserirB(const T& dado, NoRB<T>* arv) {
        NoRB<T>* novo;
        if (dado < *arv->getDado()) {
            if (arv->getEsquerda() == nullptr) {
                novo = new NoRB<T>(dado);
                arv->esquerda = novo;
            } else {
                inserirB(dado, arv->getEsquerda());
            }
        } else {
            if (arv->getDireita() == nullptr) {
                novo = new NoRB<T>(dado);
                arv->direita = novo;
            } else {
                inserirB(dado, arv->getDireita());
            }
        }
        return arv;
    }
    NoRB<T>* removerB(NoRB<T>* arv, const T& dado) {
        NoRB<T>* temp, *filho;
        if (arv == nullptr) {
            return arv;
        } else {
            if (dado < *arv->getDado()) {
                arv->esquerda = removerB(arv->getEsquerda(), dado);
                return arv;
            } else if (dado > *arv->getDado()) {
                arv->direita = removerB(arv->getDireita(), dado);
                return arv;
            } else {
                if (arv->getDireita() != nullptr &&
                                    arv->getEsquerda() != nullptr) {
                    temp = minimo(arv->getDireita());
                    arv->dado = temp->getDado();
                    arv->direita = removerB(arv->getDireita(), *arv->getDado());
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
    NoRB<T>* passoCED(NoRB<T>* w, NoRB<T>* raiz) {
        while (w != raiz) {
            if (w = w->pai->esq) {
                w = passoCED_esq(w, raiz);
            } else {
                w = passoCED_dir(w, raiz);
            }
        }
        return w;
    }

    NoRB<T>* passoCED_esq(NoRB<T>* w, NoRB<T>* raiz) {
        NoRB<T>* y;
        y = w->pai->getDireita();
        if (y->cor == RB_RUBRO) {
            y->cor = RB_NEGRO;
            w->pai->cor = RB_RUBRO;
            simpRodaPE(w->pai);
            y = w->pai->getDireita();
        }
        if (y->esquerda->cor == RB_NEGRO && y->direita->cor == RB_NEGRO) {
            y->cor = RB_RUBRO;
            w = w->pai;
        } else {
            if (y->direita->cor == RB_NEGRO) {
                y->esquerda->cor = RB_NEGRO;
                y->cor = RB_RUBRO;
                simpRodaPD(y);
                y = w->pai->direita;
            }
            y->cor = w->pai->cor;
            w->pai->cor = RB_NEGRO;
            y->dir->cor = RB_NEGRO;
            simpRodaPE(w->pai);
            w = raiz;
        }
        return w;
    }
    NoRB<T>* passoCED_dir(NoRB<T>* w, NoRB<T>* raiz) {
        NoRB<T>* y;
        y = w->pai->getEsquerda();
        if (y->cor == RB_RUBRO) {
            y->cor = RB_NEGRO;
            w->pai->cor = RB_RUBRO;
            simpRodaPD(w->pai);
            y = w->pai->getEsquerda();
        }
        if (y->esquerda->cor == RB_NEGRO && y->direita->cor == RB_NEGRO) {
            y->cor = RB_RUBRO;
            w = w->pai;
        } else {
            if (y->esquerda->cor == RB_NEGRO) {
                y->direita->cor = RB_NEGRO;
                y->cor = RB_RUBRO;
                simpRodaPE(y);
                y = w->pai->direita;
            }
            y->cor = w->pai->cor;
            w->pai->cor = RB_NEGRO;
            y->esq->cor = RB_NEGRO;
            simpRodaPD(w->pai);
            w = raiz;
        }
        return w;
    }
};

#endif /* NO_RB_HPP */
