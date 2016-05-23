#include "Pista.hpp"
#include "Lista.hpp"

class Semaforo {
	
private:
	Lista<Pista*>* eferentes;
	Pista* local;
	bool aberto,fechado;
	int tempoQueMantem;
	int* probs;

public:
	Semaforo(Pista* _local, int _tempoQueMantem, int* _probs, Pista* _eferentes[]) {
		eferentes = new Lista<Pista*>(3);
		aberto = false;
		local = _local;
		probs = _probs;
		tempoQueMantem = _tempoQueMantem;
		for (int i = 0; i < 3; i++) {
			eferentes->adiciona(_eferentes[i]);
		}
	}

	Eventos* tempoParaChegarAoFim(Carro* carro, int currentTime) {
		Eventos* ev;
		if (local->pistaCheia() == true) {
			return ev = new Eventos(0,0);
		} else {
			int tempo = local->chegarAoFim(carro);
			ev = new Eventos(tempo+currentTime, 6);
			return ev;
		}
	}

	Eventos* passaSemaforo(int currentTime) {
		Eventos* ev;
		Carro* carro = local->primeiro();
		Pista* proxPista = eferentes->mostra(carro->getNextPista());
		if (proxPista->pistaCheia() == false) {
			ev = new Eventos(currentTime+1, 2);
			return ev;
		} else {
			ev = new Eventos(0,0);
			return ev;
		}
	}
	Eventos* tempoParaChegarAoFimSumidouro(Carro* carro, int currentTime,Pista* pista) {
		Eventos* ev;
		if (pista->pistaCheia() == true || pista->isSumidouro() == false) {
			return ev = new Eventos(0,0);
		} else {
			int tempo = pista->chegarAoFim(carro);
			ev = new Eventos(tempo+currentTime, 4);
			return ev;
		}
	}

	void AbreFecha() {
		if (aberto == true) {
			aberto = false;
		} else {
			aberto = true;
		}
	}
//o método aqui para escolher a pista aleatoriamente do carro e talz
	void escolhePista() {
		Carro* carro = local->primeiro();
	}

	bool isOpen() {
		return aberto;
	}
};