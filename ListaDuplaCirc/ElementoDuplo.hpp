//! Copyright 2016 Gustavo Borges França
#ifndef ELEMENTODUPLO_HPP
#define ELEMENTODUPLO_HPP

template<typename T>
//! Implementação template de uma classe que será os elementos de uma listaDupla
/*!
 * A classe elemento duplo será a classe dos elementos da lista duplamente
 * encadeados.
 */
class ElementoDuplo {
 private:
/*<!Ponteiros que indicam o anterior e o proximo elemento da lista.>*/
    ElementoDuplo<T> *anterior, *sucessor;
/*<!Ponteiro genérico que será a informação que o elemento carrega>*/
    T* info;

 public:
//! Construtor da classe elemento duplo.
/*!
 * Construtor que inicializa o anterior, o proximo e a info do elemento duplo.
 */
    ElementoDuplo(const T& inf, ElementoDuplo<T>* ant, ElementoDuplo<T>* suc) {
        info = new T(inf);
        anterior = ant;
        sucessor = suc;
    }
//! Desconstrutor do elemento Duplo
/*!
 * O desconstrutor apenas deleta a informação do elemento.
 */
    ~ElementoDuplo() {
        delete info;
    }
//! Getter do elemento anterior.
/*!
 * @return o elemento anterior da lista.
 */
    ElementoDuplo<T>* getAnterior() const {
        return anterior;
    }
//! Getter do proximo elemento.
/*!
 * @ return o proximo elemento da lista.
 */
    ElementoDuplo<T>* getSucessor() const {
        return sucessor;
    }
//! Getter da informação do elemento.
/*!
 * @return um generico que é a info do elemento.
 */
    T getInfo() const {
        return *info;
    }
//! setter de elemento anterior.
/*!
 * @param o elemento que sera setado para ser o anterior de um elemento.
 */
    void setAnterior(ElementoDuplo<T>* antes) {
        anterior = antes;
    }
//! setter do proximo elemento.
/*!
 * @param o elemento que sera setado para ser o proximo elemento da lista.
 */
    void setSucessor(ElementoDuplo<T>* depois) {
        sucessor = depois;
    }
};

#endif
