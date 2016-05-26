/*Copyright Gustavo Borges && Nathan Werlich 2016*/
#include "Semaforo.hpp"
#include "ListaEnc.hpp"

/*!
 * @brief Classe relogio que serve para "controlar" os eventos
 */
class Relogio: public ListaEnc<Eventos*> {

private:
public:
	/*!
	 * @brief método que diz se um evento tem o tempo maior que o do outro, Sobre escreve o da listaEnc.
	 * @param ev1 ponteiro de eventos para indicar um evento.
	 * @param ev2 ponteiro de evnetos para indicar outro evento.
	 * @return boolean verdadeiro se o tempo de ev1 for maior que o de 2 falso caso não.
	 */
	bool maior(Eventos* ev1, Eventos* ev2) {
		return ev1->getTimer() > ev2->getTimer();
	}
	/*!
	 * @brief método para saber a quantidade de eventos
	 * @return que indica a quantidade de eventos na lista.
	 */
	int quantidadeEventos() {
		return this->size;
	}
};