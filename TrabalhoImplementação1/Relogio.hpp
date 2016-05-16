#include "Eventos.hpp"
#include "ListaEnc.hpp"

class Relogio: ListaEnc<Eventos> {

private:
public:
	bool maior(Eventos* ev1, Eventos* ev2) {
		return ev1->getTimer() > ev2->getTimer();
	}
};