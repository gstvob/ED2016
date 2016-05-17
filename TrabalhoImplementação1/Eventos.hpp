/*!
 * @brief Classe que descreve os eventos da lista.
 */
class Eventos{

private:
	int timer; /*<! o tempo do evento, que ele vai ser executado>*/
	char type;/*<! O tipo do evento>*/
public:
	/*!
	 * @brief Construtor
	 * @param int _timer o tempo que o evento vai ser executado.
	 * @param char _type o tipo do evento que vai ser executado.
	 */
	Eventos(int _timer, char _type) {
		timer = _timer;
		type = _type;
	}
	/*! 
	 * @brief getter do tempo que o evento vai ser executado.
	 * @return inteiro que indica o tempo que o evento vai ser executado.
	 */
	int getTimer (){
		return timer;
	}
	/*!
     * @brief getter do tipo de evento a ser executado.
     * @return char que indica o tipo do evento que vai ser executado.
	 */
	char getType() {
		return type;
	}
};