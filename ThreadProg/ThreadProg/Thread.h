#pragma once

#include <thread>
#include <iostream>
#include <chrono>
#include <conio.h>
#include <deque> 
#include <thread>
#include <mutex>
#include "Console.h"

using namespace std;
using namespace std::chrono;
using namespace Course;

// Mutex
mutex mtx;

// Global variables
char c;
//int gX1 = 0, gY1 = 0;


class Player
{
private:
	char name;
	int posX;
	int posY;

public:
	//int posX;
	//int posY;
	deque<char> charPlayer;
	Player(){}
	~Player(){}

	Player(char name, char left, char up, char right, char down, int iniPosX, int iniPosY)
	{
		// A player has a name and initial position on X and Y.
		this->name = name;
		charPlayer.push_front(left);
		charPlayer.push_front(up);
		charPlayer.push_front(right);
		charPlayer.push_front(down);
		posX = iniPosX;
		posY = iniPosY;
	}

	const void setPosX(int x)
	{
		this->posX = x;
	}

	int getPosX() const
	{
		return this->posX;
	}

	const void setPosY(int y)
	{
		this->posY = y;
	}

	int getPosY() const
	{
		return this->posY;
	}

	char getName() const
	{
		return this->name;
	}

};



class Game
{

private:

public:
	Game(){}
	~Game(){}

	static void DrawChar(const Player& player) // Thought const would help.
	{

		while (true)
		{
			Console::clrscr();

			Console::gotoxy(50, 0);
			for (auto column = 0; column < 27; ++column)
			{
				cout << "|\n";
				Console::gotoxy(50, column);
			}
			Console::gotoxy(0, 26);
			for (auto row = 0; row < 50; ++row)
			{
				cout << "-";
			}

			mtx.lock();
			/*Console::gotoxy(gX1, gY1);
			cout << player.getPosY();*/
			Console::gotoxy(player.getPosX(), player.getPosY());
			cout << player.getPosY();
			mtx.unlock();

			// To make the plane more stable.
			this_thread::sleep_for(chrono::milliseconds(300));
		}

	}

	// Check later!
	static bool CollisionCheck(Player player1, Player player2)
	{
		if ((player1.getPosX() == player2.getPosX()) &&
			(player1.getPosY() == player2.getPosY()))
		{
			cout << "\nThe game has come to an end!\nGood luck next time!\n";
			return false;
		}
		return true;
	}

	static void Input()
	{
		while(true)
		{
			if(_kbhit())
			{
				mtx.lock();
				c = _getch();
				mtx.unlock();
			}
		}
	}

	static void Move(Player& player)
	{	
		//gX1 = player.getPosX(), gY1 = player.getPosY();
		int x = player.getPosX(), y = player.getPosY();

		while (true)
		{
			mtx.lock();
			if (c == player.charPlayer[0])
			{
				c = 'x'; // Erase input character.
				player.setPosY(++y);
				if (player.getPosY() > 25)
					player.setPosY(25);
			}
			
			if (c == player.charPlayer[1])
			{
				c = 'x';
				player.setPosX(++x);
				if (player.getPosX() > 49)
					player.setPosX(49);
			}

			if (c == player.charPlayer[2])
			{
				c = 'x'; 
				player.setPosY(--y);
				if (player.getPosY() < 0)
					player.setPosY(0);
			}

			if (c == player.charPlayer[3])
			{
				c = 'x';
				player.setPosX(--x);
				if (player.getPosX() < 0)
					player.setPosX(0);
			}

			//if (_kbhit())
			//{
			//	Console::gotoxy(player.getPosX(), player.getPosY());
			//	cout << player.getPosY();
			//}
			mtx.unlock();
		}
	}


	void StartGame()
	{
		// Create player 1 and player 2.
		Player p1('1', 'a', 'w', 'd', 's', 15, 5);
		Player p2('2', 'g', 'y', 'j', 'h', 15, 20);

		thread th0(Input);
		thread th1(Move, p1);
		thread th2(Move, p2);
		thread th3(DrawChar, p1);

		th0.join();
		th1.join();
		th2.join();
		th3.join();


	}

};

