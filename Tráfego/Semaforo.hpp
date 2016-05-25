/*Copyright Gustavo Borges && Nathan Werlich*/
#include "Pista.hpp"
#include "Lista.hpp"

/*!
 * @brief classe de implementação dos semaforos da pista.
 */
class Semaforo {
	
private:
	Lista<Pista*>* eferentes;  //! < Ponteiro de uma Lista de vetores de pista, pistas eferentes do semaforo.
	Pista* local;  //! < Ponteiro de uma pista que é uma pista local
	bool aberto;  //! < Boolean que indica se o semaforo esta aberto ou não. 
	int tempoQueMantem;  //! < inteiro que indica o tempo que o semaforo vai ficar aberto.
	int* probs;  //! ponteiro de inteiros que vai passar as probabilidades de um carro virar pra uma pista.

public:
	/*!
	 * @brief Construtor do semaforo que inicializa a pista local, as eferentes, etcetc..
	 * @param ponteiro de pista que indica a pista local.
	 * @param inteiro que indica o tempo que o semaforo vai ficar aberto.
	 * @param ponteiro de inteiros que são as probabilidades de um carro virar pra uma pista.
	 * @param ponteiro de um array de pistas que são as pistas eferentes do semaforo.
	 */
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
	/*!
	 * @brief Método que marca os eventos dos carros passarem do semaforo.
	 * @param Inteiro que indica o tempo atua da execução do programa.
	 * @return Ponteiro do tipo eventos que é o evento.
	 */
	Eventos* passaSemaforo(int currentTime) {
		Eventos* ev;
		Carro* carro = local->primeiro();
		Pista* proxPista = eferentes->mostra(carro->getNextPista());
		if (proxPista->pistaCheia() == false) {
			ev = new Eventos(currentTime+1, 2, this);
			return ev;
		} else {
			ev = new Eventos(0,0,nullptr);
			return ev;
		}
	}
	/*!
	 * @brief método para abrir e fechar o semaforo.
	 */
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
	/*!
	 * @brief método para saber se o semaforo está aberto ou fechado.
	 * @return boolean verdadeiro se o semaforo estiver aberto falso caso não.
	 */
	bool isOpen() {
		return aberto;
	}
	/*!
	 * @brief método para retornar a pista local do semaforo
	 * @return ponteiro de pista que é a pista local do semaforo.
	 */
	Pista* getLocal() {
		return local;
	}
	/*!
	 * @brief método para retornar a proxima pista que o primeiro carro da local quer ir.
	 * @return ponteiro de pista que é a proxima pista que o carro em primeiro lugar da local vai.
	 */
	Pista* nextPista() {
		Carro* carro = local->primeiro();
		Pista* proxPista = eferentes->mostra(carro->getNextPista());
		return proxPista;
	}
};