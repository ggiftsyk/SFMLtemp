#include "Coin.h"

void Coin::initCoin()
{
	this->Cointex.loadFromFile("Coin.png");
	this->Cointex2.loadFromFile("Diamond.png");
	this->healtex.loadFromFile("heal.png");
	this->winTex.loadFromFile("Win.png");

	//Game Win
	this->win.setTexture(winTex);
	this->win.setPosition(1300.f, 145.f);

	bool checkTiled[80][40];
	this->resetCoin();
}

void Coin::resetCoin() {

	diamond.clear();
	Sprite diamond_sprite;
	//Diamond
	diamond_sprite.setTexture(Cointex2);
	diamond_sprite.setPosition(940.f, 100.f);
	diamond.push_back(diamond_sprite);

	diamond_sprite.setTexture(Cointex2);
	diamond_sprite.setPosition(1100.f, 250.f);
	diamond.push_back(diamond_sprite);

	diamond_sprite.setTexture(Cointex2);
	diamond_sprite.setPosition(420.f, 325.f);
	diamond.push_back(diamond_sprite);

	diamond_sprite.setTexture(Cointex2);
	diamond_sprite.setPosition(350.f, 40.f);
	diamond.push_back(diamond_sprite);

	heal.clear();
	Sprite heal_sprite;
	//Heal
	heal_sprite.setTexture(healtex);
	heal_sprite.setPosition(200.f, 315.f);
	heal.push_back(heal_sprite);

	heal_sprite.setTexture(healtex);
	heal_sprite.setPosition(770.f, 120.f);
	heal.push_back(heal_sprite);

	heal_sprite.setTexture(healtex);
	heal_sprite.setPosition(830.f, 370.f);
	heal.push_back(heal_sprite);

	coins.clear();
	int pathSize = path.size();
	for (int i = 0; i < pathSize; i++)
	{
		Sprite sprite;
		int Rand = rand() % pathSize; //Random coin
		sprite.setPosition(path[Rand].first*18, path[Rand].second*18);
		sprite.setTexture(Cointex);

		coins.push_back(sprite);
	}
}

Coin::Coin()
{
	this->initCoin();
}

Coin::~Coin()
{
}

void Coin::render(sf::RenderWindow& window)
{
	for (auto i : coins)
	{
		window.draw(i);
	}
	
	for (auto i : diamond)
	{
		window.draw(i);
	}

	for (auto i : heal)
	{
		window.draw(i);
	}

	window.draw(win);
}
