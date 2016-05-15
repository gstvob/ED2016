#include <stdlib.h>
#include <time.h>
/*!
 * @brief Classe que implementa os carros das pistas
 */

 class Carro {
  protected:
  	int _size;
    int _proxPista;
  public:
  	/*!
  	 * @brief Construtor que cria um valor aleatório para o tamanho do veículo.
  	 */
  	Carro(){
  		srand((unsigned) time (NULL));
  		_size = (2 + rand() % 5) + 3;
  	}
  	int getSize () {
  		return _size;
  	}
    int getProxPista() {
      return _proxPista;
    }
 };