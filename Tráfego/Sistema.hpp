/*Copyright Gustavo Borges && Nathan Werlich*/
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
	int tempoExecucao;  //! Tempo que o sistema rodará, passado pelo usuario
	int tempoAtual;  //! Tempo atual que o sistema se encontra.
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
	 */
	void GerarEventos() {
		int temporizacao = tempoAtual;
		while (temporizacao < tempoExecucao) {
			for (int i = 0; i < 14; i++) {
				Pista* pista = pistas->mostra(i);
				if (pista->pistaCheia()) {
					std::cout<<"Pista "<< (i+1) << " engarrafada" << std::endl; 
				} else if (pista->isFont() == true) {
					Eventos* ev = pista->gerarCarros(temporizacao);
					Eventos* ev2 = pista->tempoParaChegarAoFim(temporizacao);
					relogio->adicionaEvento(ev);
					relogio->adicionaEvento(ev2);
					temporizacao = ev->getTimer() + temporizacao;
				} else if (pista->isSumidouro() == true) {
					Eventos* ev = pista->tempoParaChegarAoFimSumidouro(temporizacao);
					relogio->adicionaEvento(ev);
					temporizacao = ev->getTimer() + temporizacao;
				}
			}
			for (int j = 0; j < 8; j++) {
				Semaforo* semaforo = semaforos->mostra(j);
				if (semaforo->isOpen() == true) {
					Eventos* ev = semaforo->passaSemaforo(temporizacao);
					Eventos* ev2 = semaforo->getLocal()->tempoParaChegarAoFim(temporizacao);
					relogio->adicionaEvento(ev);
					relogio->adicionaEvento(ev2);
					temporizacao = ev->getTimer() + temporizacao;
				}
			}
			abreFechaSemaforo(temporizacao);
		}
	}
	/*!
	 * @brief método para gerar os eventos de abrir e fechar semaforos.
	 * @param tempo, o tempo que o sistema se encontra.
	 */
	void abreFechaSemaforo(int tempo) {
		Eventos* ev1;
		Eventos* ev2;
		Eventos* ev3;
		Eventos* ev4;
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
			ev1 = new Eventos(tempoParaAbertura+tempo,5,semaforo1);
			ev2 = new Eventos(tempoParaAbertura+tempo,5,semaforo2);
			if (tempo == tempoParaAbertura) {
				ev3 = new Eventos(tempoParaAbertura+tempo,6,semaforo3);
				ev4 = new Eventos(tempoParaAbertura+tempo,6,semaforo4);
			}
			relogio->adicionaEvento(ev1);
			relogio->adicionaEvento(ev2);
			relogio->adicionaEvento(ev3);
			relogio->adicionaEvento(ev4);
		}
		tempo = tempoParaAbertura + tempo;
	}
	/*!
	 * @brief método que processa e executa todos os eventos do sistema.
	 */
	void RodarTudo() {
		tempoAtual = 0;
		int contador = 0;
		while (tempoAtual <= tempoExecucao) {
			Eventos* ev = relogio->mostrar(contador);
			switch (ev->getType()) {
				case 1: {
					Pista* track = (Pista*) ev->getObject();
					track->adicionaCarro(new Carro());
					tempoAtual = tempoAtual + ev->getTimer();
					relogio->retiraEvento(ev);
					break;
				}
				case 2: {
					Semaforo* semaf = (Semaforo*) ev->getObject();
					Pista* local = semaf->getLocal();
					Carro* carro = local->retiraCarro();
					Pista* prox = semaf->nextPista();
					prox->adicionaCarro(carro);
					tempoAtual = tempoAtual + ev->getTimer();
					relogio->retiraEvento(ev);
					break;
				}
				case 3:	{
					Pista* pista = (Pista*) ev->getObject();
					pista->retiraCarro();
					tempoAtual = tempoAtual + ev->getTimer();
					relogio->retiraEvento(ev);
					break;
				}
				case 4: {
					tempoAtual = tempoAtual + ev->getTimer();
					relogio->retiraEvento(ev);
					break;
				}
				case 5: {
					Semaforo* semaforo = (Semaforo*) ev->getObject();
					semaforo->AbreFecha();
					break;
				} 
				case 6: {
					Semaforo* semaforo = (Semaforo*) ev->getObject();
					semaforo->AbreFecha();
					int cont = 0;
					cont++;
					if (cont == 2) {
						cont = 0;
						tempoAtual = tempoAtual + ev->getTimer();
					}
					break;
				}
				default: {
					throw "ALGO ERRADO NÃO ESTA CERTO";
				}
			}
		}
		dadosFinais();
	}
	// TO DO -- probabilidades do carro entrar em uma pista, gerar tamanho aleatorio do carro, e cpp do programa.
	void dadosFinais() {
		for (int i = 0; i < 14; i++) {
			Pista* pista = pistas->mostra(i);
			std::cout << "Carros que entraram na pista " << (i+1) << pista->getCarrosEntraram() << std::endl;
			std::cout << "Carros que sairam da pista " << (i+1) << pista->getCarrosQueSairam() << std::endl;
		}
	}
};