/*Copyright Gustavo Borges && Nathan Werlich 2016*/

/*!
 * @brief Classe que descreve os eventos da lista.
 */
class Eventos{

private:
	int timer; /*<! o tempo do evento, que ele vai ser executado>*/
	int type;/*<! O tipo do evento>*/
	void* objeto;  //! < ponteiro void que indica um objeto relacionado ao evento.
	void* objeto2; //! < ponteiro void que indica um objeto relacionado ao evento.
	void* objeto3; //! < ponteiro void que indica um objeto relacionado ao evento.
	void* objeto4; //! < ponteiro void que indica um objeto relacionado ao evento.
public:
	/*!
	 * @brief Construtor
	 * @param int _timer o tempo que o evento vai ser executado.
	 * @param int _type o tipo do evento que vai ser executado.
	 */
	Eventos(int _timer, int _type, void* _objeto) {
		timer = _timer;
		type = _type;
		objeto = _objeto;
	}
	/*!
	 * @brief construtor mais completo (usado somente na abertura dos semaforos)
	 * @param inteiro que indica o tempo de execução do evento.
	 * @param inteiro que indica o tipo do evento.
	 * @param ponteiro void do primeiro objeto relacionado ao evento.
	 * @param ponteiro void de outro objeto relacionado ao evento
	 * @param ponteiro void de mais um objeto relacionado ao evento.
	 * @param ponteiro void do ultimo objeto relacionado ao evento.
	 */
	Eventos(int _timer, int _type, void* _objeto, void* _objeto2, void* _objeto3, void* _objeto4) {
		timer = _timer;
		type = _type;
		objeto = _objeto;
		objeto2 = _objeto2;
		objeto3 = _objeto3;
		objeto4 = _objeto4;
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
	/*!
	 * @brief método para retornar o segundo objeto relacionado ao evento
	 * @return ponteiro void.
	 */
	void* getObject2() {
		return objeto2;
	}
	/*!
	 * @brief método para retornar o terceiro objeto relacionado ao evento.
	 * @return ponteiro void.
	 */
	void* getObject3() {
		return objeto3;
	}
	/*!
	 * @brief método para retornar o quarto objeto relacionado ao evento.
	 * @return ponteiro void.
	 */
	void* getObject4() {
		return objeto4;
	}
};