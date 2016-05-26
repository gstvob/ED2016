/*
     Copyright 2016 Gustavo Borges && Nathan Werlich
*/
#include <iostream>
template <typename T>
#define FILA 100
     
/*!
 * @brief Classe de implementação de uma fila com vetores.
 */
class Fila {
protected:
    T* m_dados; /*! <Ponteiro que vai receber os elementos da fila*/
    int ult; /*! <Inteiro que vai indicar a posição do ultimo elemento*/
    int TAMANHOFILA; /*! <Inteiro para indicar o tamanho da fila*/
   
public:
   	/*!
     * @brief Construtor da fila que inicializa ela com o tamanho definido.
     */
    Fila() {
        TAMANHOFILA = FILA;
   	    m_dados = new T[TAMANHOFILA];
   	    ult = -1;
   	}
    /*!
     * @brief Construtor da fila que inicializa ela com tamanho variavel.
     * @param inteiro que vai ser passado para ser o tamanho da fila.
     */
    Fila<T>(int tam) {
    	 TAMANHOFILA = tam;
    	 m_dados = new T[TAMANHOFILA];
    	 ult = -1;
    }
    /*!
   	 * @brief método para incluir dados no fim da fila
     * @param genérico que é o dado a ser incluido na fila.
     */
   	void inclui(T dado) {
   	   if (filaCheia()) {
          throw("Fila cheia, não é possivel adicionar mais elementos");
    	 } else {
    	    ult = ult + 1;
    	    m_dados[ult] = dado;
    	}
    }
   	/*!
     * @brief método que retira o dado do inicio da fila.
     * @return genérico que é o dado retirado da fila.
     */
    T retira() {
      T aux = m_dados[0];
      if (filaVazia()) {
	       throw("Fila vazia, não é possivel retirar nenhum elemento");
   	  } else {
   	     aux = m_dados[0];
         for (int i = 0; i < ult; i++) {
              m_dados[i] = m_dados[(i+1)];
         }
      }
		  m_dados[ult] = 0;
		  ult--;
		  return aux;
	  }
    /*!
     * @brief método para retornar o primeiro elemento da fila.
     * @return genérico que será o primeiro dado da fila.
     */
    T prim() {
      return m_dados[0];
    }
	/*!
	 * @brief método para retornar o ultimo dado da fila
     * @return genérico que será o ultimo elemento da fila.
     */
   	T ultimo() {
   	    if (filaVazia()) {
   	        throw("essa fila ta vazia como eu vo retorna o ultimo?");
        } else {
   	       	return m_dados[ult];
   	    }
   	}
    /*!
     * @brief método para retornar a posição do ultimo elemento da fila.
     * @return inteiro que é a posição do ultimo elemento.
     */
   	int getUltimo() {
   	   return ult;
   	}
   	/*!
   	 * @brief método para verificar se a fila está cheia
   	 * @return boolean verdadeiro se a fila estiver cheia, falso caso não.
   	 */
   	bool filaCheia() {
   	   	return(ult == TAMANHOFILA - 1);
   	}
   	/*!
   	 * @brief método para verificar se a fila está vazia
   	 * @return boolean verdadeiro se estiver vazia, falso caso não.
   	 */
   	bool filaVazia() {
       	return(ult == -1);
   	}
    /*!
     * @brief método para reinciar/apagar a fila.
     */
   	void inicializaFila() {
   	    ult = -1;
   	}
}; 
