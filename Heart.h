#pragma once
#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

using namespace sf;
using namespace std;

class Heart
{
private:
	//RenderWindow window;
	void initHeart();

	//Coin
	Texture Heartbit;

	Player player;


public:
	Heart();
	virtual ~Heart();

	Sprite heart[8];

	void render(sf::RenderWindow& window);
};
