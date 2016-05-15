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
		Semaforo* semaforo = new Semaforo(false,);
	}
}