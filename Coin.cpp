#include "Coin.h"

void Coin::initCoin()
{
	this->Cointex.loadFromFile("Coin.png");
	this->Cointex2.loadFromFile("Diamond.png");
	this->healtex.loadFromFile("heal.png");

	diamond.resize(4);
	//Diamond
	diamond[0].setTexture(Cointex2);
	diamond[0].setPosition(940.f, 100.f);

	diamond[1].setTexture(Cointex2);
	diamond[1].setPosition(1100.f, 250.f);

	diamond[2].setTexture(Cointex2);
	diamond[2].setPosition(420.f, 325.f);

	diamond[3].setTexture(Cointex2);
	diamond[3].setPosition(350.f, 40.f);


	heal.resize(3);
	//Heal
	heal[0].setTexture(healtex);
	heal[0].setPosition(200.f, 315.f);

	heal[1].setTexture(healtex);
	heal[1].setPosition(770.f, 120.f);

	heal[2].setTexture(healtex);
	heal[2].setPosition(830.f, 370.f);


	int pathSize = path.size();
	bool checkTiled[80][40];
	for (int i = 0; i < pathSize; i++)
	{
		int Rand = rand() % pathSize; //Random coin
		coins[i].setPosition(path[Rand].first*18, path[Rand].second*18);
		coins[i].setTexture(Cointex);
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
}
