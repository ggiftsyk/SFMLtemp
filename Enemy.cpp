#include "Enemy.h"
int RandDir[8] = {};
void Enemy::initTexture()
{
	this->textureSheet.loadFromFile("Enemy2.png");
}

void Enemy::initSprite()
{
	int pathSize = path.size();
	bool checkTiled[80][40];
	for (int i = 0; i < 8; i++)
	{
		enemies[i].setScale(Vector2f(1.f, 1.f));
		enemies[i].setTexture(textureSheet);
		enemies[i].setOrigin(enemies->getGlobalBounds().width/2, enemies->getGlobalBounds().height / 3);
		RandDir[i] = (rand() % 2)? -1:1 ;
	}
		enemies[0].setPosition((rand() % 8 + 16 )* 18, 28 * 18);
		enemies[1].setPosition((rand() % 8 + 42 )* 18, 25 * 18);
		enemies[2].setPosition((rand() % 9 + 69 )* 18, 26 * 18);
		enemies[3].setPosition((rand() % 9 + 15 )* 18, 14 * 18);
		enemies[4].setPosition((rand() % 6 + 53 )* 18, 17 * 18);
		enemies[5].setPosition((rand() % 10 + 23)* 18, 5 * 18);
		enemies[6].setPosition((rand() % 9 + 25) * 18, 22 * 18);
		enemies[7].setPosition((rand() % 5 + 46) * 18, 9 * 18);
	
}


Enemy::Enemy()
{
	this->initTexture();
	this->initSprite();
}

Enemy::~Enemy()
{
}

const Vector2f Enemy::getPosition(int i) const
{
	return this->enemies[i].getPosition();
}

const FloatRect Enemy::getGlobalBounds(int i) const
{
	return this->enemies[i].getGlobalBounds();
}

const int& Enemy::getDamage() const
{
	return this->Damage;
}

void Enemy::update()
{
	for (int i = 0; i < 8; i++)
	{
		velocity.x = RandDir[i]*1;
		int posX = enemies[i].getPosition().x + velocity.x;
		int posY = enemies[i].getPosition().y;
		int x = posX / 18;
		int y = posY / 18;
		//cout << i<<" "<<x << " " << y << endl;
		if (!solid[x][y] and solid[x][y+1]) 
		{
			this->enemies[i].move(this->velocity);
		}
		else {
			if (RandDir[i] == -1) RandDir[i] = 1;
			else RandDir[i] = -1;
		}
	}
}

void Enemy::render(RenderTarget& target)
{
	for (int i = 0; i < 8; i++) {
		target.draw(this->enemies[i]);
	}
}
