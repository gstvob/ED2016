#include "Pista.hpp"
#include "Lista.hpp"
#include <stdlib.h>
#include <time.h>
class Semaforo {

private:
	Lista<Pista>* pistas;
	Pista* pistaDele;
	bool aberto;
	int timer;
	int probs[3];
	int opentimer;
public:
	Semaforo(bool open,Pista* pistaL, int _probs[] ,int tempo, Pista* eferentes[]) {
		aberto = open;
		timer = tempo;
		openTimer = 0;
		probs = probs;
		pistas = new Lista<Pista*>(3);
		pistaDele = pistaL;
		for (int i = 0; i < 3; i++) {
			pistas->adiciona(eferentes[i]);
		}
	}
	
	int escolheProxPista() {
		srand((unsigned) time (NULL));
  		random = (rand() % 100);

  		int pist1 = probs[0] + random;
  		int pist2 = probs[1] + random;
  		int pist3 = probs[2] + random;

  		if (pist1 > pist2 and pist1 > pist3) {
  			return 0;
  		} else if (pist2 > pist1 and pist2 > pist3) {
  			return 1;
  		} else if (pist3 > pist1 and pist3 > pist2) {
  			return 2;
  		}
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

	Pista ProxPista() {
		Carro* carro = pistaDele->primeiro();
		if(aberto == false) {
			throw "Semaforo fechado";
		} else {
			int proxPista = escolheProxPista(); 
			Pista* next = pistas->mostra(proxPista);
			if (prox->pistaCheia() == true) {
				ProxPista();
			} else {
				pistaDele->RemoveCar();
				prox->AddCar(carro);
				return prox;
			}
		}
	}
	int ProxEvento(int tempo) {
		return tempo+timer;
	}
};