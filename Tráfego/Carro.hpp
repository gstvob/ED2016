#include <cstdlib>

/*!
 * @brief Classe de implementação dos carros que vão entrar nas pistas da simulação.
 */
class Carro{

private:	
	int tamanho; /*<! Inteiro que indica o tamanho do carro.>*/
	int nextPista; /*<! Inteiro que vai indicar para qual pista o carro vai querer ir.>*/
public:
	/*!
	 * @brief Construtor que incializa o tamanho do carro e para qual pista ele vai depois.
	 */
	Carro(int _tamanho, int _nextPista) {
		tamanho = _tamanho;
		nextPista = _nextPista;
	}
	/*!
	 * @brief Getter da proxima pista que o carro irá.
	 * @return inteiro que irá indicar a pista que o carro vai.
	 */
	int getNextPista() {
		return nextPista;
	}
	/*!
	 * @brief getter do tamanho do carro.
	 * @return inteiro que indica o tamanho do carro.
	 */
	int getTamanho() {
		return tamanho;
	}
};