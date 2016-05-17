#include "Sistema.hpp"
#include <iostream>
using namespace std;
int main() {

	int tempoEx;
	int semaTemp;
		cout << "Quanto tempo você gostaria de fazer a simulação? : " << endl;
		cin >> tempoEx;
		cout << "Quanto tempo você gostaria de abrir os semaforos? : " << endl;
		cin >> semaTemp;
		Sistema* sistema = new Sistema(tempoEx, semaTemp);
		sistema->GeraEventos();
		return 0;
	}