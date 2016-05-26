/*Copyright Gustavo Borges && Nathan Werlich 2016*/
#include "Sistema.hpp"
#include <iostream>
/*!
 * @brief classe com método main que starta o programa.
 * @return retorna 0 quando o programa rodou com sucesso.
 */
int main() {
	
	Sistema* trafego;

	int tempoSemaforo;
	int tempoExecucao;

	std::cout << "Indique o tempo de abertura dos semaforos : ";
	std::cin >> tempoSemaforo;

	std:: cout << "Indique o tempo total de execução do programa : ";
	std::cin >> tempoExecucao;
	trafego = new Sistema(tempoSemaforo, tempoExecucao);
	trafego->trafego();

	delete trafego;
	return 0;
}