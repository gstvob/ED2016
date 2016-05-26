/*Copyright Gustavo Borges && Nathan Werlich 2016*/

#include "ListaCirc.hpp"
#include "Relogio.hpp"
#include <iostream>

/*!
 * @brief classe que implementa o sistema como um todo, conectando as partes e fazendo o programa rodar;
 */
class Sistema {
private:
	Relogio* relogio;  //! < ponteiro do tipo relogio que é a lista de eventos.
	ListaEnc<Pista*>* pistas;  //! < Lista encadeada de todas as pistas do sistema.
	ListaCirc<Semaforo*>* semaforos; //! < Lista circular de todos os semaforos
	int tempoParaAbertura;  //! inteiro que indica o tempo de abertura, e por consequencia
							// o de fechamento dos semáforos.
	int tempoExecucao;  //! < Tempo que o sistema rodará, passado pelo usuario
	int tempoAtual = 0;  //! < Tempo atual que o sistema se encontra.
	int carrosQueEntraram = 0;  //! < inteiro que indica o total de carros que entraram no sistema.
	int carrosQueSairam = 0;  //! < inteiro que indica o total de carros que sairam do sistema.
public:
	/*!
	 * @brief Construtor do sistema
	 * @param inteiro que indica o tempo para abertura dos semaforos
	 * @param inteiro que indica o tempo de execucao do programa.
	 */
	Sistema(int _tempoParaAbertura, int _tempoExecucao) {
		tempoAtual = 0;
		tempoExecucao = _tempoExecucao;
		tempoParaAbertura = _tempoParaAbertura;
		semaforos = new ListaCirc<Semaforo*>();
		pistas = new ListaEnc<Pista*>();
		relogio = new Relogio();
		simulacao();
	}
	/*!
	 * @brief método que inicializa as pistas, semaforos, probabilidades e etc.
	 * @see RodarTudo()
	 * @see GerarEventos()
	 */
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
	/*!
	 * @brief método para gerar todos os eventos do sistema.
	 * @see RodarTudo()
	 * @see simulacao()
	 */
	void GerarEventos() {
		int temporizacao1 = 0;
		Pista* pista;
		Semaforo* semaforo;
		for(int i = 0; i < 14; i++) {
			pista = pistas->mostra(i);
			if(pista->isFont() == true) {
				while(temporizacao1 < tempoExecucao) {
					Eventos* ev = pista->gerarCarros(temporizacao1);
					relogio->adicionaEmOrdem(ev);
					temporizacao1 = ev->getTimer();
				}
			} else {
				break;
			}
		}
		for (int i = 0; i < 8; i++) {
			semaforo = semaforos->mostra(i);
			if (semaforo->isOpen() == true) {
				Eventos* ev = semaforo->passaSemaforo(temporizacao1);
				relogio->adicionaEmOrdem(ev);
				temporizacao1 = ev->getTimer();
			}
		}
		temporizacao1 = 0;
		while (temporizacao1 < tempoExecucao) {
			Eventos* ev1;
			Semaforo* semaforo1;
			Semaforo* semaforo2;
			Semaforo* semaforo3;
			Semaforo* semaforo4;
			for (int i = 0; i < 8; i+=2) {
				semaforo1 = semaforos->mostra(i);
				semaforo2 = semaforos->mostra(i+1);
				if (i >= 2) {
					semaforo3 = semaforos->mostra(i-2);
					semaforo4 = semaforos->mostra(i-1);
				} else {
					semaforo3 = semaforos->mostra(7);
					semaforo4 = semaforos->mostra(6);
				}
				if (temporizacao1 == 0) {
					ev1 = new Eventos(temporizacao1+tempoParaAbertura, 5, semaforo1, semaforo2, nullptr,nullptr);
					relogio->adicionaEmOrdem(ev1);
				} else {
					ev1 = new Eventos(temporizacao1+tempoParaAbertura,6,semaforo1,semaforo2,semaforo3,semaforo4);
					relogio->adicionaEmOrdem(ev1);
				}
			}
			temporizacao1 = ev1->getTimer();
		}
	}
	/*!
	 * @brief método que processa e executa todos os eventos do sistema.
	 */
	void RodarTudo() {
		int contador = 0;
		for (int i = 0; i < relogio->quantidadeEventos(); i++) {
			Eventos* ev = relogio->mostra(i);
			if (tempoAtual >= tempoExecucao) {
				break;
			}
			switch (ev->getType()) {
				case 0: {
					break;
					tempoAtual = tempoAtual + ev->getTimer();
				}
				case 1: {
					Pista* track = (Pista*) ev->getObject();
					Carro* carro = new Carro();
					track->adicionaCarro(carro);
					carrosQueEntraram++;
					Eventos* eve = track->tempoParaChegarAoFim(tempoAtual, carro);
					relogio->retiraEspecifico(ev);
					tempoAtual = tempoAtual + ev->getTimer();
					break;
				}
				case 2: {
					Semaforo* semaf = (Semaforo*) ev->getObject();
					Pista* local = semaf->getLocal();
					Pista* prox = semaf->nextPista();
					if (prox->pistaCheia() == false && semaf->isOpen() == true) {
						Carro* carro = local->retiraCarro();
						prox->adicionaCarro(carro);
						Eventos* eve = prox->tempoParaChegarAoFim(tempoAtual, carro);
						relogio->retiraEspecifico(ev);
						tempoAtual = tempoAtual + ev->getTimer();
					} else {
						break;
					}
					break;
				}
				case 3:	{
					Pista* pista = (Pista*) ev->getObject();
					pista->retiraCarro();
					carrosQueSairam++;
					relogio->retiraEspecifico(ev);
					tempoAtual = tempoAtual + ev->getTimer();
					break;
				}
				case 4: {
					relogio->retiraEspecifico(ev);
					tempoAtual = tempoAtual + ev->getTimer();
					break;
				}
				case 5: {
					Semaforo* semaforo1 = (Semaforo*) ev->getObject();
					Semaforo* semaforo2 = (Semaforo*) ev->getObject2();
					semaforo2->AbreFecha();
					semaforo1->AbreFecha();
					tempoAtual = tempoAtual + ev->getTimer();
					break;
				} 
				case 6: {
					Semaforo* semaforo1 = (Semaforo*) ev->getObject();
					Semaforo* semaforo2 = (Semaforo*) ev->getObject2();
					Semaforo* semaforo3 = (Semaforo*) ev->getObject3();
					Semaforo* semaforo4 = (Semaforo*) ev->getObject4();
					semaforo1->AbreFecha();
					semaforo2->AbreFecha();
					semaforo3->AbreFecha();
					semaforo4->AbreFecha();
					tempoAtual = tempoAtual + ev->getTimer();
					break;
				}
				default: {
					std::cout << "ALGO ERRADO NÃO ESTA CERTO" << std::endl;
				}
			}
			contador++;
		}
	}
	/*!
	 * @brief método que inicializa tudo chamando os dois principais métodos
	 * @see GerarEventos()
	 * @see RodarTudo()
	 */
	void trafego() {
		GerarEventos();
		RodarTudo();
		dadosFinais();
	}
	/*!
	 * @brief método para finalizar o programa que apenas joga os dados para a saida.
	 */
	void dadosFinais() {
		int contador = 1;
		std::cout << "Carros totais que entraram no sistema: " << carrosQueEntraram << std::endl;
		std::cout << "Carros que sairam do sistema: " << carrosQueSairam << std::endl;
	}
};