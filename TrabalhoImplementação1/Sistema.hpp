#include "Semaforo.hpp"
#include "Relogio.hpp"
#include "ListaCirc.hpp"

class Sistema {

private:
	ListaEnc<Semaforo*>* semaforos;
	ListaCirc<Pista*>* pistas;
	Relogio* relogio;
	int tempoEx;
	int tempoA;
	int semaTemp;

public:
	Sistema(int _tempoEx, int _semaTemp) {
		semaforos = new ListaEnc<Semaforo*>();
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
		semaforos->adiciona(s1n);

		Pista* proxPistas2[3] = {Pc1l, Pn1n, Ps1s};
		int prob2[3] = {80,10,10};
		Semaforo* s1o = new Semaforo(false,Po1l,prob2,semaTemp,proxPistas2);
		semaforos->adiciona(s1o);

		Pista* proxPistas3[3] = {Pc1l, Po1o, Pn1n};
		int prob3[3] = {80,10,10};
		Semaforo* s1s = new Semaforo(false,Ps1n,prob3,semaTemp,proxPistas3);
		semaforos->adiciona(s1s);

		Pista* proxPistas4[3] = {Po1o, Pn1n, Ps1s};
		int prob4[3] = {40,30,30};
		Semaforo* s1l = new Semaforo(false,Pc1o,prob4,semaTemp,proxPistas4);
		semaforos->adiciona(s1l);

		Pista* proxPistas5[3] = {Pl1l, Pn2n, Ps2s};
		int prob5[3] = {40,30,30};
		Semaforo* s2o = new Semaforo(false,Pc1l,prob5,semaTemp,proxPistas5);
		semaforos->adiciona(s2o);

		Pista* proxPistas6[3] = {Pl1l, Pc1o, Ps2s};
		int prob6[3] = {40,30,30};
		Semaforo* s2n = new Semaforo(false,Pn2s,prob6,semaTemp,proxPistas6);
		semaforos->adiciona(s2n);

		Pista* proxPistas7[3] = {Pl1l, Pn2n, Pc1o};
		int prob7[3] = {40,30,30};
		Semaforo* s2s = new Semaforo(false,Ps2n,prob7,semaTemp,proxPistas7);
		semaforos->adiciona(s2s);

		Pista* proxPistas8[3] = {Pl1l, Pn2n, Ps2s};
		int prob8[3] = {40,30,30};
		Semaforo* s2l = new Semaforo(false,Pc1o,prob8,semaTemp,proxPistas8);
		semaforos->adiciona(s2l);
	}
};