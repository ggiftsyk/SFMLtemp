#include "Heart.h"

void Heart::initHeart()
{
	this->Heartbit.loadFromFile("heart.png");
	int p = 12;
	for (int i = 0; i < 8; i++)
	{
		heart[i].setTexture(Heartbit);
		heart[i].setPosition(12.f, 35.f);
		heart[i].setScale(1.5f, 1.5f);
		heart[i].setPosition(p, 35.f);
		p +=  22;
	}
}

Heart::Heart()
{
	this->initHeart();
}

Heart::~Heart()
{
}

void Heart::render(sf::RenderWindow& window)
{
	for (int i = 0; i < 8; i++)
	{
		window.draw(heart[i]);
	}
}
