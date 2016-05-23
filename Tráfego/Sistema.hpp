#include "ListaCirc.hpp"
#include "Relogio.hpp"
#include <iostream>

class Sistema {
private:
	Relogio* relogio;
	ListaEnc<Pista*>* pistas;
	ListaCirc<Semaforo*>* semaforos;
	int tempoParaAbertura;
	int tempoExecucao;
	int tempoAtual;
public:
	Sistema(int _tempoParaAbertura, int _tempoExecucao) {
		tempoAtual = 0;
		tempoExecucao = _tempoExecucao;
		tempoParaAbertura = _tempoParaAbertura;
		semaforos = new ListaCirc<Semaforo*>();
		pistas = new ListaEnc<Pista*>();
		relogio = new Relogio();
		simulacao();
	}

	void simulacao() {
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
		Semaforo* s1n = new Semaforo(Pn1s,tempoParaAbertura,prob1,proxPistas1);

		Pista* proxPistas2[3] = {Pc1l, Pn1n, Ps1s};
		int prob2[3] = {80,10,10};
		Semaforo* s1o = new Semaforo(Po1l,tempoParaAbertura,prob2,proxPistas2);

		Pista* proxPistas3[3] = {Pc1l, Po1o, Pn1n};
		int prob3[3] = {80,10,10};
		Semaforo* s1s = new Semaforo(Ps1n,tempoParaAbertura,prob3,proxPistas3);
		
		Pista* proxPistas4[3] = {Po1o, Pn1n, Ps1s};
		int prob4[3] = {40,30,30};
		Semaforo* s1l = new Semaforo(Pc1o,tempoParaAbertura,prob4,proxPistas4);

		Pista* proxPistas5[3] = {Pl1l, Pn2n, Ps2s};
		int prob5[3] = {40,30,30};
		Semaforo* s2o = new Semaforo(Pc1l,tempoParaAbertura,prob5,proxPistas5);

		Pista* proxPistas6[3] = {Pl1l, Pc1o, Ps2s};
		int prob6[3] = {40,30,30};
		Semaforo* s2n = new Semaforo(Pn2s,tempoParaAbertura,prob6,proxPistas6);

		Pista* proxPistas7[3] = {Pl1l, Pn2n, Pc1o};
		int prob7[3] = {40,30,30};
		Semaforo* s2s = new Semaforo(Ps2n,tempoParaAbertura,prob7,proxPistas7);

		Pista* proxPistas8[3] = {Pl1l, Pn2n, Ps2s};
		int prob8[3] = {40,30,30};
		Semaforo* s2l = new Semaforo(Pc1o,tempoParaAbertura,prob8,proxPistas8);
		
		semaforos->adiciona(s1n);
		semaforos->adiciona(s2n);
		semaforos->adiciona(s1l);
		semaforos->adiciona(s2l);
		semaforos->adiciona(s1s);
		semaforos->adiciona(s2s);
		semaforos->adiciona(s1o);
		semaforos->adiciona(s2o);
	}

	void GerarEventos() {
		int temporizacao = tempoAtual;
		while (temporizacao < tempoExecucao) {
			for (int i = 0; i < 14; i++) {
				Pista* pista = pistas->mostra(i);
				if (pista->pistaCheia()) {
					std::cout<<"Pista "<< (i+1) << " engarrafada" << std::endl; 
				} else if (pista->isFont() == true) {
					Eventos* ev = pista->gerarCarros(temporizacao);
					// um tempo para chegar ao fim da pista aqui também;
					relogio->adicionaEvento(ev);	
					temporizacao = ev->getTimer() + temporizacao;
				} else if (pista->isSumidouro() == true) {
					Eventos* ev = pista->tempoParaChegarAoFimSumidouro(pista->primeiro(), temporizacao, pista);
					relogio->adicionaEvento(ev);
					temporizacao = ev->getTimer() + temporizacao;
				}
			}
			for (int j = 0; j < 8; j++) {
				Semaforo* semaforo = semaforos->mostra(j);
				if (semaforo->isOpen() == true) {
					Eventos* ev = semaforo->passaSemaforo(temporizacao);
					relogio->adicionaEvento(ev);
					//tem que colocar um evento de chegar ao fim da pista aqui
					temporizacao = ev->getTimer() + temporizacao;
				}
			}
		}
	}
	void abreFechaSemaforo() {
		
	}
	void RodarTudo() {
		//aqui vai ser feita a execução de todos os eventos de acordo com seu tipo..
		// tenho que ver um jeito correto de fazer isso -- o problema é que não descobri ainda um jeito massa sem um zilhão de iterações
	}
};