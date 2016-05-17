#include "Semaforo.hpp"
#include "Relogio.hpp"
#include <iostream>

class Sistema {

private:
	ListaCirc<Semaforo*>* semaforos;
	ListaCirc<Pista*>* pistas;
	Relogio* relogio;
	int tempoEx;
	int tempoA;
	int semaTemp;
	int contador1;
	int contador2;
public:
	Sistema(int _tempoEx, int _semaTemp) {
		semaforos = new ListaCirc<Semaforo*>();
		pistas = new ListaCirc<Pista*>();
		relogio = new Relogio();
		tempoEx = _tempoEx;
		semaTemp = _semaTemp;
		TrafficSim();
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


	void GeraCarros() {
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
					Eventos* novo = new Eventos(proxE, 0);
					relogio->adicionaEvento(novo);
					tempDiscreto = proxE;
				} else {
					break;
				}
			}
		}
	}
	void AbreSemaforo(){
		Semaforo* semaforo1;
    	Semaforo* semaforo2;
    	Eventos* evento;
    	Eventos* evento2;
    	int proxE, tempDiscreto;

    	semaforo1 = semaforos->mostra(contador1);
    	semaforo2 = semaforos->mostra(contador1 + 1);

    	proxE = semaforo1->NextEvent(semaTemp);

    	if (proxE <= tempoEx) {
    		evento = new Eventos(proxE, 1);
    		evento2 = new Eventos(proxE, 1);
    		relogio->adicionaEvento(evento);
    		relogio->adicionaEvento(evento2);
    		contador1 += 2;
 		}
    	tempDiscreto = proxE;
	}
	void FechaSemaforo(){
		Semaforo* semaforo1;
    	Semaforo* semaforo2;
    	Eventos* evento;
    	Eventos* evento2;
    	int proxE, tempDiscreto;

    	semaforo1 = semaforos->mostra(contador2);
    	semaforo2 = semaforos->mostra(contador2+1);

    	proxE = semaforo1->NextEvent(semaforo1->getOpenTimer());

    	if (proxE <= tempoEx) {
    		evento = new Eventos(proxE, 2);
    		evento2 = new Eventos(proxE, 2);
    		relogio->adicionaEvento(evento);
    		relogio->adicionaEvento(evento2);
    		contador2 += 2;
   		}
    	tempDiscreto = proxE;
	}
	void CarroSome() {
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
					Eventos* evento = new Eventos(proxE,3);
					tempDiscreto = proxE;
					relogio->adicionaEvento(evento);
				}
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
					Eventos* evento = new Eventos(proxE, 4);
					tempDiscreto = proxE;
					relogio->adicionaEvento(evento);
				}
			}
		}
	}
	void ExecutarEventos() {
		for (int i = 0; i < relogio->quantidadeEventos(); i++) {
			Eventos* event = relogio->mostrar(i);
			if (tempoA <= tempoEx) {
				if (event->getType() == 0) {
					Pista* pista;
					for (int j = 0; j < 14; j++) {
						pista = pistas->mostra(j);
						if (pista->getFonte() == true and pista->pistaCheia() == false) {
							pista->AddCar(new Carro());
							tempoA = event->getTimer();
						}
					}	
				} else if (event->getType() == 1) {
					Semaforo* semaforo1;
					Semaforo* semaforo2;

					semaforo1 = semaforos->mostra(contador1);
					semaforo2 = semaforos->mostra(contador1+1);

					semaforo1->AbreFecha();
					semaforo2->AbreFecha();
				} else if (event->getType() == 2) {
					Semaforo* semaforo1;
					Semaforo* semaforo2;

					semaforo1 = semaforos->mostra(contador2);
					semaforo2 = semaforos->mostra(contador2 + 1);

					semaforo1->AbreFecha();
					semaforo2->AbreFecha();
				} else if (event->getType() == 3) {
					Pista* pista;
					for (int k = 0; k < 14; k++) {
						pista = pistas->mostra(i);
						if (pista->getSumi() == true) {
							pista->RemoveCar();
						}
					}
				} else if (event->getType() == 4) {
					Semaforo* semaforo;
					Pista* pista;
					for (int l = 0 ; l < 8; l++) {
						semaforo = semaforos->mostra(i);
						if (semaforo->isOpen() == true) {
							semaforo->ProxPista();
						}
					}
				}
			}
			relogio->retiraEvento(event);
		}
		Saida();
	}
	void GeraEventos() {
		GeraCarros();
		AbreSemaforo();
		CarroPassa();
		FechaSemaforo();
		CarroSome();
		AbreSemaforo();
		CarroPassa();
		FechaSemaforo();
		CarroSome();
		AbreSemaforo();
		CarroPassa();
		FechaSemaforo();
		CarroSome();
		AbreSemaforo();
		CarroPassa();
		FechaSemaforo();
		CarroSome();

		ExecutarEventos();
	}

	void Saida() {
		int carrosQueEntraram = 0;
        int carrosQueSairam = 0;
		for (int i = 0; i < 14; i++) {
        Pista* pista = pistas->mostra(i);
       		if (pista->getFonte()) {
            	carrosQueEntraram = carrosQueEntraram + pista->getCarrosPass();
        	} else {
            	if (pista->getSumi()) {
                	carrosQueSairam = carrosQueSairam + pista->getCarrosSai();
            	}
        	}
    	}
    	std::cout << "Carros que entraram no sistema: " << carrosQueEntraram << std::endl;
    	std::cout << "Carros que sairam do sistema: " << carrosQueSairam << std::endl;
	}
};

