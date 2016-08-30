#include "Thread.h"

Player p1('1', 'a', 'w', 'd', 's', 15, 10);
Player p2('2', 'g', 'y', 'j', 'h', 10, 5);
Game g;

void testMove1()
{
	g.Move(p1);
}

void testMove2()
{
	g.Move(p2);
}

void testDraw()
{
	g.DrawChar(p1,p2);
}

int main()
{

	thread t0(g.Input);
	thread t1(testMove1);
	thread t2(testMove2);
	thread t3(testDraw);

	t0.join();
	t1.join();
	t2.join();
	t3.join();

#if 0
	/*thread th1(Game::Move, p1);
	thread th2(Game::Move, p2);
	thread th3(Game::DrawChar, p1);*/

	/*th0.join();
	th1.join();
	th2.join();
	th3.join();*/

	//Game g;
	//g.StartGame();
#endif
	system("PAUSE");

	return 0;
}