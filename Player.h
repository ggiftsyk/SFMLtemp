#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>
#include "Level.h"

enum PLAYER_ANIMATION_STATES { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING };

using namespace sf;
using namespace std;
class Player
{
private:
	Sprite sprite;
	Texture textureSheet;
	Clock animationTimer;

	//Animation
	short animState;
	IntRect currentFrame;
	bool animationSwitch;

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
	/*int hp;
	int hpMax;*/

	//Core
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	void initPhysics();

public:
	Player();
	virtual ~Player();

	//Accessors
	const bool& getAnimationSwitch();
	const Vector2f getPosition() const;
	const FloatRect getGlobalBounds() const;
	/*const int& getHp() const;
	const int& getHpMax() const;*/

	//Modifiers
	void setPosition(const float x, const float y);
	
	void resetVelocityX();
	void resetVelocityY();

	/*void setHp(const int hp);
	void loseHp(const int value);*/

	//Jumping
	bool jumping = true;
	bool jumpingUp = false;
	bool gravityBool = true;
	int countJumpUp = 0;

	//Heart
	int collide_cooldown = 0;
	int getCollideCooldown();
	void setCollideCooldown(int cooldown);

	//Functions
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y); //direction
	void updatePhysics();
	void updateMovement();
	void updateAnimations();
	void update();
	void render(RenderTarget& target);

};

