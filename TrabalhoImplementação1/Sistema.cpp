#include "Semaforo.hpp"
#include "Eventos.hpp"
#include "Pista.hpp"
#include "ListaCirc.hpp"
#include "ListaEnc.hpp"

class Sistema {

private:
	ListaEnc<Semaforo>* semaforos;
	ListaCirc<Pista>* pistas;
	Relogio* relogio;
	int tempoEx;
	int tempoA;
	int semaTemp;

public:
	Sistema(int _tempoEx, int _semaTemp) {
		semaforos = new ListaEnc<Semaforo>();
		pistas = new ListaCirc<Pista>();
		relogio = new Relogio();
		tempoEx = _tempoEx;
		semaTemp = _semaTemp;
	}
	void TrafficSim () {
		Pista* n1s = new Pista(500,60,15);
		Pista* n1n = new Pista(500,60,0);
		Pista* n2s = new Pista(500,40,20);
		Pista* n2n = new Pista(500,40,0);
		Pista* l1o = new Pista(400,30,12);
		Pista* l1l = new Pista(400,30,0);
		Pista* s2n = new Pista(500,40,50);
		Pista* s2s = new Pista(500,40,0);
		Pista* s1n = new Pista(500,60,35);
		Pista* s1s = new Pista(500,60,0);
		Pista* o1l = new Pista(2000,80,10);
		Pista* o1o = new Pista(2000,80,0);
		Pista* c1l = new Pista(300,60,1);
		Pista* c1o = new Pista(300,60,1);

		Pista* filas[] = {n1s,n1n,n2s,n2n,l1o,l1l,s2n,s2s,s1n,s1s,o1l,o1o,c1l,c1o};

		for (int i = 0, i < 14; i++) {
			pistas->adiciona(filas[i]);
		}

		Pista* proxPistas1[3] = {c1l, o1o, s1s};
		int prob1[3] = {80,10,10};
		Semaforo* s1n = new Semaforo(false,n1s,prob1,semaTemp,proxPistas1);
		semaforos->adiciona(s1n);

		Pista* proxPistas2[3] = {c1l, n1n, s1s};
		int prob2[3] = {80,10,10};
		Semaforo* s1o = new Semaforo(false,o1l,prob2,semaTemp,proxPistas2);
		semaforos->adiciona(s1o);

		Pista* proxPistas3[3] = {c1l, o1o, n1n};
		int prob3[3] = {80,10,10};
		Semaforo* s1s = new Semaforo(false,s1n,prob3,semaTemp,proxPistas3);
		semaforos->adiciona(s1s);

		Pista* proxPistas4[3] = {o1o, n1n, s1s};
		int prob4[3] = {40,30,30};
		Semaforo* s1l = new Semaforo(false,c1o,prob4,semaTemp,proxPistas4);
		semaforos->adiciona(s1l);

		Pista* proxPistas5[3] = {l1l, n2n, s2s};
		int prob5[3] = {40,30,30};
		Semaforo* s2o = new Semaforo(false,c1l,prob5,semaTemp,proxPistas5);
		semaforos->adiciona(s2o);

		Pista* proxPistas6[3] = {l1l, c1o, s2s};
		int prob6[3] = {40,30,30};
		Semaforo* s2n = new Semaforo(false,n2s,prob6,semaTemp,proxPistas6);
		semaforos->adiciona(s2n);

		Pista* proxPistas7[3] = {l1l, n2n, c1o};
		int prob7[3] = {40,30,30};
		Semaforo* s2s = new Semaforo(false,s2n,prob7,semaTemp,proxPistas7);
		semaforos->adiciona(s2s);

		Pista* proxPistas8[3] = {l1l, n2n, s2s};
		int prob8[3] = {40,30,30};
		Semaforo* s2l = new Semaforo(false,c1o,prob8,semaTemp,proxPistas8);
		semaforos->adiciona(s2l);
	}
};