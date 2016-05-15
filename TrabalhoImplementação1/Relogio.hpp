#include "Eventos.hpp"
#include "ListaEnc.hpp"

class Relogio: ListaEnc<Eventos> {

private:
public:
	bool maior(Evento ev1, Evento ev2) {
		return ev1->getTimer() > ev2->getTimer();
	}
}