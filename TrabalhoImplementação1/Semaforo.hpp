#include "Pista.hpp"
#include "Lista.hpp"
#include <stdlib.h>
#include <time.h>
class Semaforo {

private:
	Lista<Pista*>* pistas;
	Pista* pistaDele;
	bool aberto;
	int *probs;
	int timer;
	int opentimer;
public:
	Semaforo(bool open,Pista* pistaL, int *_probs ,int tempo, Pista* eferentes[]) {
		aberto = open;
		timer = tempo;
		opentimer = 0;
		probs = probs;
		pistas = new Lista<Pista*>(3);
		pistaDele = pistaL;
		for (int i = 0; i < 3; i++) {
			pistas->adiciona(eferentes[i]);
		}
	}
	
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
	int Events(int actTimer) {
		return timer + actTimer;
	}

	void AbreFecha(int tempo) {
		if (aberto) {
			Events(tempo);
		}
		aberto = !aberto;
	}

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
	int ProxEvento(int tempo) {
		return tempo+timer;
	}
};