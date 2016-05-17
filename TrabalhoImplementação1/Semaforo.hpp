#include "Pista.hpp"
#include "ListaCirc.hpp"
#include "Lista.hpp"
#include <stdlib.h>
#include <time.h>
/*!
 * @brief Implementação do semaforo, que contem uma lista de suas pistas eferentes e a pista que é "dele"
 */
class Semaforo {

private:
	Lista<Pista*>* pistas; /*<! Pistas eferentes do semaforo>*/
	Pista* pistaDele; /*<! A pista relacionada ao semaforo>*/
	bool aberto; /*<! Indicador para saber se o semaforo está aberto ou fechado>*/
	int *probs; /*<! A problabilidade de um carro virar para as pistas eferentes desse semaforo>*/
	int timer; /*<! Tempo para abrir um semaforo>*/
	int opentimer; /*<! Tempo que o semaforo vai ficar aberto>*/
public:
/* !
 * @brief construtor.
 * @param boolean open vai passar se o semaforo ta aberto ou fechado.
 * @param Pista* pistaL passa a pista que está relacionada a esse semaforo.
 * @param int *probs ponteiro que indica a probabilidade de um carro virar para uma pista eferente.
 * @param Pista* eferentes[] array que contem as pistas efentes do semaforo.
 */
	Semaforo(bool open,Pista* pistaL, int *_probs ,int tempo, Pista* eferentes[]) {
		aberto = open;
		timer = tempo;
		opentimer = 10;
		probs = probs;
		pistas = new Lista<Pista*>(3);
		pistaDele = pistaL;
		for (int i = 0; i < 3; i++) {
			pistas->adiciona(eferentes[i]);
		}
	}
/*!
 * @brief método que retorna um numero para saber a proxima pista que o carro vai.
 * @return inteiro que vai indicar pra qual pista o carro vai
 */
	int escolheProxPista() {
		srand((unsigned) time (NULL));
  		int aleatorio = (rand() % 10);

  		int escolhe[10];
  		int *probab = probs;
  		for (int i = 0; i < probab[0]/10 - 1; i++) {
  			escolhe[i] = probab[0];
  		}

  		for (int j = probs[0]/10; j < probab[1]/10 - 1; j++) {
  			escolhe[j] = probab[1];
  		}

  		for (int k = probs[1]/10; k < probab[2]/10 - 1; k++) {
  			escolhe[k] = probab[1];
  		}

  		return escolhe[aleatorio];
	}
/*!
 * @brief método que calcula o tempo do proximo evento do sistema.
 */
	int NextEvent(int actTimer) {
		return timer + actTimer;
	}
/*!
 * @brief método que abre o semaforo se estiver fechado e fecha se estiver aberto.
 * @param inteiro que indica o tempo que o semaforo vai abrir ou fechar.
 */

	void AbreFecha() {
		if (aberto == true) {
			aberto = false;
		} else {
			aberto = true;
		}
	}
/*!
 * @brief método para calcular a proxima pista que o primeiro carro da fila vai.
 * @return Pista*, ponteiro de pista que indica pra qual pista o carro foi.
 */
	Pista* ProxPista() {
		Carro* carro = pistaDele->prim();
		if(aberto == false) {
			throw "Semaforo fechado";
		} else {
			int proxPista = escolheProxPista(); 
			Pista* next = pistas->mostra(proxPista);
			if (next->pistaCheia() == true) {
				ProxPista();
			} else {
				pistaDele->RemoveCar();
				next->AddCar(carro);
				return next;
			}
		}
	}
	Pista* getPistaLocal() {
		return pistaDele;
	}
	bool isOpen() {
		return aberto;
	}
	int getOpenTimer() {
		return opentimer;
	}
};