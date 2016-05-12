#include "Carro.hpp"
#include "Fila.hpp"

/*!
 * @brief Implementação das pistas que herdam de uma fila de vetores de carros.
 */
class Pista : Fila<Carro*> {
	protected:
		int tam; /*<! Inteiro que indica o tamanho da pista>*/
		int espaço; /*<! Inteiro que indica quanto espaço a pista "perdeu">*/
		int vel; /*<! Inteiro que indica a velocidade da pista.>*/
		int freq /*<! Inteiro que indica a frequencia que add um veículo*/
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
			espaço = 0;
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
				if(espaço+car->getSize() <= tam) {
					this->inclui(carro);
					espaço = espaço + carro->getSize();
				} else {
					throw "erro: carro não cabe na pista";
				}
			}
		}
		/*
		 * @brief método para retirar um carro da pista, usado em sumidouros.
		 * sem valor de retorno e sem parâmetros, apenas chama o método retira.
		 */
		void RemoveCar(){
			this->retira();
		}
		/*!
		 * @brief método para saber se a pista está cheia.
		 * @return boolean que é verdadeiro se a pista esta cheia falso caso nao
		 */
		bool pistaCheia () {
			return espaço == tam
		}
};