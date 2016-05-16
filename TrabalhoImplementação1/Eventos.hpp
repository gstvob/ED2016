class Eventos{

private:
	int timer;
	char type;
public:
	Eventos(int _timer, int _type) {
		timer = _timer;
		type = _type;
	}
	int getTimer (){
		return timer;
	}
	int getType() {
		return type;
	}
};