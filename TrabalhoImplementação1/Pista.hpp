#include "Carro.hpp"
#include "Fila.hpp"

/*!
 * @brief Implementação das pistas que herdam de uma fila de vetores de carros.
 */
class Pista : Fila<Carro*> {
	protected:
		int tam; /*<! Inteiro que indica o tamanho da pista>*/
		int espaco; /*<! Inteiro que indica quanto espaço a pista "perdeu">*/
		int vel; /*<! Inteiro que indica a velocidade da pista.>*/
		int freq; /*<! Inteiro que indica a frequencia que add um veículo*/
		int tempoParaFim;
		int carrosPassados,carrosSaidos;
		bool font, sum; /*<! Booleans para indicar se é fonte ou sumidouro.*/

	public:
		/*!
		 * @brief Construtor basico da pista
		 * @param _tam, o tamanho que será passado para a pista.
		 * @param _vel, a velocidade da pista.
		 */
		Pista(int _tam, int _vel, int _freq) {
			tam = _tam;
			vel = _vel;
			espaco = 0;
			freq = _freq;
			if (freq == 0) {
				sum = true;
				font = false;
			} else if (freq == 1) {
				sum = false;
				font = false;
			} else {
				font = true;
				sum = false;
			}
		}
		/*!
		 * @brief método que adiciona um carro na pista se for possivel.
		 * @param um ponteiro do tipo carro que vai ser colocado na pista.
		 */
		void AddCar(Carro* veiculo) {
			if (pistaCheia()) {
				throw "Erro: a pista está cheia";
			} else {
				if(espaco+veiculo->getSize() <= tam) {
					this->inclui(veiculo);
					espaco = espaco + veiculo->getSize();
					carrosPassados++;
				} else {
					throw "erro: veiculo não cabe na pista";
				}
			}
		}
		/*
		 * @brief método para retirar um carro da pista, usado em sumidouros.
		 * sem valor de retorno e sem parâmetros, apenas chama o método retira.
		 */
		void RemoveCar(){
			this->retira();
			carrosSaidos++;
		}
		/*!
		 * @brief método para saber se a pista está cheia.
		 * @return boolean que é verdadeiro se a pista esta cheia falso caso nao
		 */
		bool pistaCheia () {
			return espaco == tam;
		}
		/*!
		 * @brief retorna o primeiro carro da fila.
		 * @return Carro*, ponteiro que indica o carro que está em primeiro lugar na fila.
		 */
		Carro* prim() {
			return this->primeiro();
		}
		/*!
		 * @brief Retorna o tempo que um carro demora para chegar em um semaforo.
		 * @param carro, o carro que se quer saber o tempo de chegada.
		 * @return inteiro que indica o tempo que o carro demorou para chegar no fim da fila.
		 */
		int tempoChegada(Carro* carro) {	
			int localCheg = carro->getSize() - tam - espaco;
			int vels = vel/3.6;
			int tempo = 0;
			if (localCheg > 0) {
				while (vels != localCheg) {
					vels +=vels;
					tempo++;
				}
				return tempo;
			} else {
				throw "Impossivel chegar nesse local.";
			}
		}
		/*!
		 * @brief método para retornar se o pista é uma fonte ou não.
		 * @return booleano verdadeiro se a pista for fonte, falso caso não.
		 */
		bool getFonte() {
			return font;
		}

		bool getSumi() {
			return sum;
		}
		int getCarrosPass() {
			return carrosPassados;
		}
		int getCarrosSai(){
			return carrosSaidos;
		}
};