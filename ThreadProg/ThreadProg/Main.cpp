#include "Thread.h"


int main()
{

	//Player p1('1', 'a', 'w', 'd', 's', 15, 10);
	//Player p2('2', 'g', 'y', 'j', 'h', 15, 20);

	//thread th0(g.Input);
	//thread th1(&Game::Move, &p1);
	//thread th2(&Game::Move, &p2);
	//thread th3(&Game::DrawChar, p1, p2);

	//th0.join();
	//th1.join();
	//th2.join();
	//th3.join();

	Game g;
	g.StartGame();

	system("PAUSE");
	return 0;
}