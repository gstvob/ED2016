/*!
 * @brief Classe que descreve os eventos da lista.
 */
class Eventos{

private:
	int timer; /*<! o tempo do evento, que ele vai ser executado>*/
	int type;/*<! O tipo do evento>*/
	void* objeto;
public:
	/*!
	 * @brief Construtor
	 * @param int _timer o tempo que o evento vai ser executado.
	 * @param char _type o tipo do evento que vai ser executado.
	 */
	Eventos(int _timer, int _type, void* _objeto) {
		timer = _timer;
		type = _type;
		objeto = _objeto;
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
	int getType() {
		return type;
	}
	/*!
	 * @brief método para retornar o objeto que está relacionado ao evento.
	 * @return ponteiro void.
	 */
	void* getObject() {
		return objeto;
	}
};