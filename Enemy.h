#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>
#include "Level.h"

using namespace sf;
using namespace std;
class Enemy
{
private:
	
	Texture textureSheet;

	//Physics
	Vector2f velocity;
	float velocityMax;
	float velocityMin;

	//float accleration;
	float drag;
	float gravity;
	float velocityMaxY;
	float velocityX;

	//Hp
	int Damage;

	//Core

	//void initVariables();
	void initTexture();
	void initSprite();

public:
	Enemy();
	virtual ~Enemy();

	Sprite enemies[8]; //8 enemy

	//Accessors
	const Vector2f getPosition(int i) const;
	const FloatRect getGlobalBounds(int i) const;
	const int& getDamage() const;

	//Functions
	void update();
	void render(RenderTarget& target);
};

