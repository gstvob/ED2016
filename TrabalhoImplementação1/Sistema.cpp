#include "Semaforo.hpp"
#include "Relogio.hpp"

class Sistema {

private:
	ListaCirc<Semaforo*>* semaforos;
	ListaCirc<Pista*>* pistas;
	Relogio* relogio;
	int tempoEx;
	int tempoA;
	int semaTemp;

public:
	Sistema(int _tempoEx, int _semaTemp) {
		semaforos = new ListaCirc<Semaforo*>();
		pistas = new ListaCirc<Pista*>();
		relogio = new Relogio();
		tempoEx = _tempoEx;
		semaTemp = _semaTemp;
	}
	void TrafficSim () {
		Pista* Pn1s = new Pista(500,60,15);
		Pista* Pn1n = new Pista(500,60,0);
		Pista* Pn2s = new Pista(500,40,20);
		Pista* Pn2n = new Pista(500,40,0);
		Pista* Pl1o = new Pista(400,30,12);
		Pista* Pl1l = new Pista(400,30,0);
		Pista* Ps2n = new Pista(500,40,50);
		Pista* Ps2s = new Pista(500,40,0);
		Pista* Ps1n = new Pista(500,60,35);
		Pista* Ps1s = new Pista(500,60,0);
		Pista* Po1l = new Pista(2000,80,10);
		Pista* Po1o = new Pista(2000,80,0);
		Pista* Pc1l = new Pista(300,60,1);
		Pista* Pc1o = new Pista(300,60,1);

		Pista* filas[] = {Pn1s,Pn1n,Pn2s,Pn2n,Pl1o,Pl1l,Ps2n,Ps2s,Ps1n,Ps1s,Po1l,Po1o,Pc1l,Pc1o};

		for (int i = 0; i < 14; i++) {
			pistas->adiciona(filas[i]);
		}

		Pista* proxPistas1[3] = {Pc1l, Po1o, Ps1s};
		int prob1[3] = {80,10,10};
		Semaforo* s1n = new Semaforo(false,Pn1s,prob1,semaTemp,proxPistas1);

		Pista* proxPistas2[3] = {Pc1l, Pn1n, Ps1s};
		int prob2[3] = {80,10,10};
		Semaforo* s1o = new Semaforo(false,Po1l,prob2,semaTemp,proxPistas2);

		Pista* proxPistas3[3] = {Pc1l, Po1o, Pn1n};
		int prob3[3] = {80,10,10};
		Semaforo* s1s = new Semaforo(false,Ps1n,prob3,semaTemp,proxPistas3);
		
		Pista* proxPistas4[3] = {Po1o, Pn1n, Ps1s};
		int prob4[3] = {40,30,30};
		Semaforo* s1l = new Semaforo(false,Pc1o,prob4,semaTemp,proxPistas4);

		Pista* proxPistas5[3] = {Pl1l, Pn2n, Ps2s};
		int prob5[3] = {40,30,30};
		Semaforo* s2o = new Semaforo(false,Pc1l,prob5,semaTemp,proxPistas5);

		Pista* proxPistas6[3] = {Pl1l, Pc1o, Ps2s};
		int prob6[3] = {40,30,30};
		Semaforo* s2n = new Semaforo(false,Pn2s,prob6,semaTemp,proxPistas6);

		Pista* proxPistas7[3] = {Pl1l, Pn2n, Pc1o};
		int prob7[3] = {40,30,30};
		Semaforo* s2s = new Semaforo(false,Ps2n,prob7,semaTemp,proxPistas7);

		Pista* proxPistas8[3] = {Pl1l, Pn2n, Ps2s};
		int prob8[3] = {40,30,30};
		Semaforo* s2l = new Semaforo(false,Pc1o,prob8,semaTemp,proxPistas8);
		semaforos->adiciona(s1n);
		semaforos->adiciona(s2n);
		semaforos->adiciona(s1l);
		semaforos->adiciona(s2l);
		semaforos->adiciona(s1s);
		semaforos->adiciona(s2s);
		semaforos->adiciona(s1o);
		semaforos->adiciona(s2o);

	}


	Carro* GeraCarros() {
		Pista* pist[14];
		Carro* novoCarro = new Carro();
		int proxE;
		int tempDiscreto;
		for (int i = 0; i < 14; i++) {
			pist[i] = pistas->mostra(i);
		}
		for (int j = 0; j < 14; j++) {
			if (pist[j]->getFonte() == true) {
				tempDiscreto = tempoA;
			}
			for (int k = tempDiscreto; k < tempoEx; k++) {
				proxE = pist[j]->tempoChegada(novoCarro) + tempoA;

				if (proxE <= tempoEx) {
					Eventos* novo = new Eventos(proxE,'c');
					relogio->adicionaEvento(novo);
					tempDiscreto = proxE;
					return novoCarro;
				} else {
					break;
				}
				throw "ERROR";
			}
		}
	}
	void AbreSemaforo(int cont){
		Semaforo* semaforo1;
    	Semaforo* semaforo2;
    	Eventos* evento;
    	Eventos* evento2;
    	int proxE, tempDiscreto;
    	cont = 0;

    	semaforo1 = semaforos->mostra(cont);
    	semaforo2 = semaforos->mostra(cont+1);

    	proxE = semaforo1->NextEvent(semaTemp);

    	if (proxE <= tempoEx) {
    		evento = new Eventos(proxE, 'a');
    		evento2 = new Eventos(proxE, 'a');
    		relogio->adicionaEvento(evento);
    		relogio->adicionaEvento(evento2);
    	}
    	tempDiscreto = proxE;
	}
	Carro* CarroSome() {
		Pista* pista[6];
		for (int i = 0; i < 14; i++) {
			pista[i] = pistas->mostra(i);
			if (pista[i]->getSumi() == true) {
				Carro* carroDelete = pista[i]->prim();
				int proxE;
				int tempDiscreto;
				tempDiscreto = tempoA;
				proxE = pista[i]->tempoChegada(carroDelete);
				if (proxE <= tempoEx) {
					Eventos* evento = new Eventos(proxE,'s');
					tempDiscreto = proxE;
					relogio->adicionaEvento(evento);
					return carroDelete;
				}
				throw "ERRO";
			}
		}
	}
	void CarroPassa() {
		Semaforo* semaforo[8];
		for (int i = 0; i < 8; i++) {
			semaforo[i] = semaforos->mostra(i);
			if (semaforo[i]->isOpen() == true) {
				Carro* carro = semaforo[i]->getPistaLocal()->prim();
				int proxE;
				int tempDiscreto;
				tempDiscreto = tempoA;
				proxE = semaforo[i]->ProxPista()->tempoChegada(carro);
				if (proxE <= tempoEx) {
					Eventos* evento = new Eventos(proxE, 'p');
					tempDiscreto = proxE;
					relogio->adicionaEvento(evento);
				}
			}
		}
	}
	void ExecutarEventos() {

	}
};


