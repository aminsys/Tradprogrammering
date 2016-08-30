#pragma once

#include <thread>
#include <iostream>
#include <chrono>
#include <conio.h>
#include <deque> 
#include <mutex>
#include "Console.h"

using namespace std;
using namespace std::chrono;
using namespace Course;

// Mutex
mutex mtx;

// Global variables
char c;
bool gCHECKDRAW = true;

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

	static void DrawChar(Player& player1, Player& player2) // Thought const would help.
	{

		while (CollisionCheck(player1, player2))
		{
			Console::clrscr();

			Console::gotoxy(25, 0);
			for (auto column = 0; column < 14; ++column)
			{
				cout << "|\n";
				Console::gotoxy(25, column);
			}
			Console::gotoxy(0, 13);
			for (auto row = 0; row < 25; ++row)
			{
				cout << "-";
			}

			mtx.lock();
			Console::gotoxy(player1.getPosX(), player1.getPosY());
			cout << player1.getName();
			Console::gotoxy(player2.getPosX(), player2.getPosY());
			cout << player2.getName();
			mtx.unlock();

			// To make the plane more stable.
			this_thread::sleep_for(chrono::milliseconds(300));
		}

		gCHECKDRAW = false; // Stops all other while loops in Move and Input.
	}

	// Check for collision!
	static bool CollisionCheck(Player player1, Player player2)
	{
		if ((player1.getPosX() == player2.getPosX()) &&
			(player1.getPosY() == player2.getPosY()))
		{
			Console::gotoxy(2, 15);
			cout << "\nThe game has come to an end!\nGood luck next time!\n";
			return false;
		}
		return true;
	}

	static void Input()
	{
		while(gCHECKDRAW)
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
		int x = player.getPosX(), y = player.getPosY();

		while (gCHECKDRAW)
		{
			mtx.lock();
			if (c == player.charPlayer[0])
			{
				c = 'x'; // Erase input character.
				player.setPosY(++y);
				if (player.getPosY() > 12)
				{
					y = 12;
					player.setPosY(y);
				}
			}
			
			if (c == player.charPlayer[1])
			{
				c = 'x';
				player.setPosX(++x);
				if (player.getPosX() > 24)
				{
					x = 24;
					player.setPosX(x);					
				}
			}

			if (c == player.charPlayer[2])
			{
				c = 'x'; 
				player.setPosY(--y);
				if (player.getPosY() < 0)
				{
					y = 0;
					player.setPosY(y);
				}
			}

			if (c == player.charPlayer[3])
			{
				c = 'x';
				player.setPosX(--x);
				if (player.getPosX() < 0)
				{
					x = 0;
					player.setPosX(x);
				}
			}
			mtx.unlock();
		}
	}

#if 0
	void StartGame()
	{
		// Create player 1 and player 2.
		//Player p1('1', 'a', 'w', 'd', 's', 15, 5);
		//Player p2('2', 'g', 'y', 'j', 'h', 15, 20);

		//thread th0(Input);
		//thread th1(Move, &p1);
		//thread th2(Move, p2);
		//thread th3(DrawChar, &p1);

		//th0.join();
		//th1.join();
		//th2.join();
		//th3.join();


	}
#endif
};

