#include <windows.h>
#include <iostream>
#include <String>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <time.h>

class Game{
public:
	sf::RenderWindow window{ sf::VideoMode(430,430),"2048" };
	sf::RectangleShape box{ sf::Vector2f(100,100)};
	sf::Font font;
	sf::Text text;
	int dir = 0;
	int isWin = false;

	int field[4][4] = 
	{
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}
	};

	inline Game();
	inline void DrawBox();
	inline void StartGame();
	inline void RestartGame();
	inline void Rotate();
	inline void Compare();
	inline int	GetRandom();
	inline void SpawnTile();
	inline bool IsLose();
	inline bool IsWin();
	inline void Lose();
	inline void InitField();

};