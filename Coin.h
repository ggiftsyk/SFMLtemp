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

	Texture winTex;
	
	Player player;

public:
	Coin();
	virtual ~Coin();

	vector<sf::Sprite> diamond;

	vector<sf::Sprite> heal;

	void resetCoin();

	Sprite win;

	//void update();
	vector<sf::Sprite>  coins;//MAX_COIN
	void render(sf::RenderWindow& window);
	//const RenderWindow& getWindow() const;
};

