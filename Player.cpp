#include "Player.h"


using namespace sf;
using namespace std;


int Player::getCollideCooldown()
{
	return this->collide_cooldown;
}

void Player::setCollideCooldown(int cooldown)
{
	//this->collide_cooldown = 0;
	this->collide_cooldown = cooldown;
}

void Player::initVariables()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;

	/*this->hpMax = 100;
	this->hp = this->hpMax;*/
}

void Player::initTexture()
{
	this->textureSheet.loadFromFile("unjiman5.png");
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = IntRect(0, 0, 68, 68); //sq of player 136

	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(0.55f, 0.55f); //size player
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height+22);

}
void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 5.f;
	this->velocityMin = 0.f;
	//this->accleration = 4.f;
	this->drag = 0.87f;
	this->gravity = 1.f;
	this->velocityMaxY = 8.f;
	this->velocityX = 0.f;
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
}

Player::~Player()
{

}

const bool& Player::getAnimationSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}

const Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityX()
{
	this->velocity.x = 0.f;
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
	//Acceleration
	velocity.x += dir_x ;

	//Limit velocity
	if (abs(this->velocity.x) > velocityMax)
	{
		this->velocity.x = velocityMax * ((this->velocity.x<0.f) ? - 1.f:1.f);
	}

}

void Player::updatePhysics()
{
	//Jumping
	resetVelocityY();
	if (abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	int posX = sprite.getPosition().x + velocity.x;
	int posY = sprite.getPosition().y ;
	int x = posX / 18;
	int xLeft = (posX-14) / 18;
	int xRight = (posX+13) / 18; 
	int y;
	if (this->jumpingUp == true )
	{
		y = posY ;
		y /= 18;
		
		if (!solid[x][y] )
		{
			this->velocity.y = -2.f+countJumpUp/30.0; //high jump

			countJumpUp++;
		}
		else
		{
			gravityBool = true;
			countJumpUp = 0;
			jumpingUp = false;
		}
		
	}
	if (this->gravityBool == true)
	{
		this->velocity.y = 2; //high jump //Fall
		int Y = posY + velocity.y;
		if (solid[x][Y/ 18] )
		{
			velocity.y = 0;
		}
		else
		{
			//countJumpUp++;
		}
	}

	posY += velocity.y;
	y = posY / 18;
	if ((solid[x][y]  or countJumpUp > 60) and jumpingUp)
	{
		countJumpUp = 0;
		gravityBool = true;
		jumpingUp = false;
	}
	else if (velocity.y==0 and gravityBool)
	{
		gravityBool = true;
		jumping = false;
	}
		
		if (!solid[xLeft][y] and velocity.x < 0) 
		{
			this->sprite.move(this->velocity);
		}
		else if (!solid[x][y] and velocity.x == 0)
		{
			this->sprite.move(this->velocity);
		}
		else if (!solid[xRight][y] and velocity.x > 0)
		{
			this->sprite.move(this->velocity);
		}
}

void Player::updateMovement()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	if (Keyboard::isKeyPressed(Keyboard::Key::A)) //Left
	{
		this->move(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::D)) //Right
	{
		this->move(1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::W) && this->jumping == false) //Top
	{
			this->jumping = true;
			this->jumpingUp = true;
			this->gravityBool = false;
			countJumpUp = 0;
			//std::cout << "new" << std::endl;
			//this->velocity.y = -60.f;  //high
	}
	
	
	//cout << this->sprite.getPosition().x/80 <<" "<< this->sprite.getPosition().y/40<<endl;
}

void Player::updateAnimations()
{
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.6f || this->getAnimationSwitch()) //speed of player
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 68.f;
			if (this->currentFrame.left > 136.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f) //speed of player
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 68.f;
			if (this->currentFrame.left >= 136.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			
		}
		this->sprite.setScale(0.55f, 0.55f); //Size
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height + 22);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f) //speed of player
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 68.f;
			if (this->currentFrame.left >= 136.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		
		}
		
		this->sprite.setScale(-0.55f, 0.55f); //size player
		//this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 0.5f, sprite.getGlobalBounds().width); //width / Size hello
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height + 22);
	}
	else
		this->animationTimer.restart();
}

void Player::update()
{
	if (this->collide_cooldown > 0)
	{
		this->collide_cooldown--;
	}
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
}

void Player::render(RenderTarget& target)
{
	target.draw(this->sprite);

}
