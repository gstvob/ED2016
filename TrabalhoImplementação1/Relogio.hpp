#include "Eventos.hpp"
#include "ListaEnc.hpp"

/*!
 * @brief Classe relogio que serve para "controlar" os eventos
 */
class Relogio: ListaEnc<Eventos*> {

private:
public:
	/*!
	 * @brief método que diz se um evento tem o tempo maior que o do outro.
	 * @param ev1 ponteiro de eventos para indicar um evento.
	 * @param ev2 ponteiro de evnetos para indicar outro evento.
	 * @return boolean verdadeiro se o tempo de ev1 for maior que o de 2 falso caso não.
	 */
	bool maior(Eventos* ev1, Eventos* ev2) {
		return ev1->getTimer() > ev2->getTimer();
	}
	/*!
	 * @brief métood para adicionar eventos ao relogio (que é uma lista encadeada de eventos).
	 * @param ev, o ponteiro do evento que vai ser adicionado.
	 * chama método adicionaEmOrdem de ListaEnc.hpp passando ev como parâmetro.
	 */
	void adicionaEvento(Eventos* ev) {
		this->adicionaEmOrdem(ev);
	}

	int quantidadeEventos() {
		return this->size;
	}
	Eventos* mostrar(int pos) {
		return this->mostra(pos);
	}
};