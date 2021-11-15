#pragma once
#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

#define MAX_COIN 400
using namespace sf;
using namespace std;

class Coin
{
private:
	//RenderWindow window;
	void initCoin();

	//Coin
	Texture Cointex;
	//Sprite coin2;

	Texture Cointex2;

	Texture healtex;
	
	Player player;

public:
	Coin();
	virtual ~Coin();

	vector<sf::Sprite>  diamond{ 4 };

	vector<sf::Sprite>  heal{ 3 };

	//void update();
	vector<sf::Sprite>  coins{ 400 };//MAX_COIN
	void render(sf::RenderWindow& window);
	//const RenderWindow& getWindow() const;
};

