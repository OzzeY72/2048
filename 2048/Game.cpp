#pragma once 
#pragma warning(disable : 4996)
#include "Game.h"

Game::Game() 
{
	this->font.loadFromFile("arial.ttf");
	this->text.setFont(font);
	this->text.setCharacterSize(20);
	this->text.setStyle(sf::Text::Bold);
	this->text.setColor(sf::Color::Black);
}

void Game::DrawBox() 
{
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++)
		{
			this->box.setPosition((j * 101)+13, (i * 101)+13);

			if (field[i][j]  == 0) this->box.setFillColor(sf::Color::White);
			if (field[i][j]  == 2) this->box.setFillColor(sf::Color(238,228,218,255));
			if (field[i][j]  == 4) this->box.setFillColor(sf::Color(238,225,201,255));
			if (field[i][j]  == 8) this->box.setFillColor(sf::Color(243,178,122,255));
			if (field[i][j]  == 16) this->box.setFillColor(sf::Color(246,150,100,255));
			if (field[i][j]  == 32) this->box.setFillColor(sf::Color(247,124,95,255));
			if (field[i][j]  == 64) this->box.setFillColor(sf::Color(247,95,59,255));
			if (field[i][j]  == 128) this->box.setFillColor(sf::Color(237,208,115,255));
			if (field[i][j]  == 256) this->box.setFillColor(sf::Color(237,204,98,255));
			if (field[i][j]  == 512) this->box.setFillColor(sf::Color(237,200,80,255));
			if (field[i][j]  == 1024) this->box.setFillColor(sf::Color(237,197,63,255));
			if (field[i][j]  == 2048) this->box.setFillColor(sf::Color(236,194,48,255));
			if (field[i][j]  > 2048) this->box.setFillColor(sf::Color(255,10,20,255));

			this->text.setPosition((j * 101) + 13 + 40, (i * 101) + 13 + 40);

			if(field[i][j] > 100) this->text.setPosition((j * 101)  +40, (i * 101) + 13 + 40);
			if(field[i][j] != 0)this->text.setString(std::to_string(this->field[i][j]));
			else this->text.setString("");
			this->window.draw(box);
			this->window.draw(text);
		}
	}
}

void Game::Compare()
{
	int arr[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			arr[i][j] = field[i][j];
		}

	}

	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++)
		{	
			if (dir == 0 && i != 0) { if (field[4 - i][j] == arr[4 - i - 1][j]) { field[4 - i - 1][j] = field[4 - i - 1][j] * 2; field[4 - i][j] = 0; };
				if (field[4 - i - 1][j] == 0) 
				{ 
					field[4 - i - 1][j] = field[4 - i][j]; field[4 - i][j] = 0;
				};
			};
			if (dir == 1) { if (field[i][j] == arr[i + 1][j]) { field[i + 1][j] = field[i + 1][j] * 2; field[i][j] = 0; }
				if (field[i + 1][j] == 0)
				{
						field[i + 1][j] = field[i][j]; field[i][j] = 0;
				};
			};
			if (dir == 2 && j != 0) { if (field[i][4 - j] == arr[i][4 - j - 1]) { field[i][4 - j - 1] = field[i][4 - j - 1] * 2; field[i][4 - j] = 0; };
				if (field[i][4-j-1] == 0)
				{
					field[i][4-j-1] = field[i][4-j]; field[i][4-j] = 0;
				};
			};
			if (dir == 3 && j < 4) { if (field[i][j] == arr[i][j + 1]) { field[i][j + 1] = field[i][j + 1] * 2; field[i][j] = 0; };
				if (field[i][j+1] == 0)
				{
					field[i][j+1] = field[i][j]; field[i][j] = 0;
				};
			};

		}
	}
}

int Game::GetRandom() 
{
	return rand() % 4;
}

void Game::SpawnTile() 
{
	if (!IsLose()) {
		int x = GetRandom();
		int y = GetRandom();
		while (field[x][y] != 0) {
			x = GetRandom();
			y = GetRandom();
		}
		if ((rand() % 10 + 1) < 10) field[x][y] = 2;
		else field[x][y] = 4;
		IsWin();
	}
	IsLose();
}

bool Game::IsLose() 
{
	int count = 0;
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++)
		{
			if (field[i][j] == 0) count++;
		}
	}
	if (count > 0) return false;
	if (count == 0) { return true; Lose(); }
}

bool Game::IsWin()
{
	if (isWin) return false;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (field[i][j] == 2048) { return true; isWin = true; }
		}
	}
	return false;
}

void Game::InitField()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			field[i][j] = 0;
		}
	}
}

void Game::RestartGame()
{
	InitField();
	SpawnTile();
	SpawnTile();
}

void Game::Lose()
{
	RestartGame();
	std::cout << "LOSE !" << std::endl;
}

void Game::Rotate()
{
	int arr[4][4];
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			//if(i != 0 && j != 0) 
			/*
			N = field[4 - i][j];
			std::cout << std::to_string(field[i][j]) << std::endl;
			field[4 - i][j] = field[j][i];
			field[i][4 - j] = N;*/
			arr[i][j] = field[i][j];
		}
		
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			field[j][i] = arr[3 - i][j];
		}

	}

}

void Game::StartGame() 
{
	srand(time(NULL));
	RestartGame();

	while (this->window.isOpen())
	{
		sf::Event event;
		while (this->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->window.close();

			if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Up) {
				dir = 0;
				Compare();
				Compare();
				//Rotate();
				if (IsLose())window.close();
				SpawnTile();
				std::cout << "Key UP pressed" << std::endl;
			}
			if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Down) {
				dir = 1;
				Compare();
				Compare();
				//Rotate();
				//Rotate();
				//Rotate();
				if (IsLose())window.close();
				SpawnTile();
				std::cout << "Key DOWN pressed" << std::endl;
			}
			if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Left) {
				dir = 2;
				//Rotate();
				Compare();
				if (IsLose())window.close();
				SpawnTile();
				std::cout << "Key LEFT pressed" << std::endl;
			}
			if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Right) {
				dir = 3;
				//Rotate();
				Compare();
				if (IsLose())window.close();
				SpawnTile();
				std::cout << "Key RIGHT pressed" << std::endl;
			}


		}

		DrawBox();
		this->window.display();
	}
}


