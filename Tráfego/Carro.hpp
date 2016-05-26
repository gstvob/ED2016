/*Copyright Gustavo Borges && Nathan Werlich 2016*/
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

/*!
 * @brief Classe de implementação dos carros que vão entrar nas pistas da simulação.
 */
class Carro{

private:	
	int tamanho; /*<! Inteiro que indica o tamanho do carro.>*/
	int nextPista; /*<! Inteiro que vai indicar para qual pista o carro vai querer ir.>*/
public:
	/*!
	 * @brief Construtor que incializa o tamanho do carro e para qual pista ele vai depois.
	 */
	Carro() {
		srand(time (NULL));
  		tamanho = (2 + rand() % 5) + 3;
	}
	/*!
	 * @brief Getter da proxima pista que o carro irá.
	 * @return inteiro que irá indicar a pista que o carro vai.
	 */
	int getNextPista() {
		return nextPista;
	}
	/*!
	 * @brief getter do tamanho do carro.
	 * @return inteiro que indica o tamanho do carro.
	 */
	int getTamanho() {
		return this->tamanho;
	}
	/*!
	 * @brief método para setar a proxima pista do carro.
	 * @param inteiro que vai indicar a proxima da pista do carro.
	 */
	void setProxPista(int _nextPista) {
		nextPista = _nextPista;
	}

	/*!
	 * @brief método para calcular a proxima pista que o carro vai.
	 * @param ponteiro de inteiro que são as probabilidades.
	 * @return inteiro que é a proxima pista do carro.
	 */
	int calculaProxPista(int* probs) {
		srand(time(NULL));
		int numero = 0;
		int aleatorio = (rand() % 10)+ 1;
		int range1 = probs[0]/10;
		int range2 = range1 + probs[1]/10;
		int range3 = range2 + probs[2]/10;
		if (aleatorio >= 1 && aleatorio <= range1) numero = 0;
		else if(aleatorio > range1 && aleatorio <= range2)numero = 1;
		else if(aleatorio > range2 && aleatorio <= range3)numero = 2;
		return numero;	
	}
};