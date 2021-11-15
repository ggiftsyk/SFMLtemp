#include "Game.h"
#include "Player.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
unsigned long score;

void Game::initWindow()
{
	this->window.create(VideoMode(1440,720),"Unjiman Game");

	this->window.setFramerateLimit(60);
	map.LoadFromFile("Mapgame3.tmx");
}

void Game::initPlayer()
{
	this->player = new Player();
	this->player->setPosition(18.f, 18.f);
}

void Game::initVariables()
{
	this->points = 0;
	Hp = 4;
}

void Game::initFont()
{
	if (this->font.loadFromFile("SHOWG.ttf"))
	{
		//cout << "ERROR::GAME::INITFONTS::COULD NOT LOAD" << endl;
	}
}

void Game::initTex()
{
	//Gui text init 
	this->guiTex.setFont(this->font);
	this->guiTex.setFillColor(Color::Black);
	this->guiTex.setPosition(18.f, 18.f);
	this->guiTex.setCharacterSize(15);

	//Gameover text init 
	/*this->gameOverTex.setFont(this->font);
	this->gameOverTex.setFillColor(Color::Red);
	this->gameOverTex.setPosition(this->window.getSize().x/2, this->window.getSize().y / 2);
	this->gameOverTex.setCharacterSize(60);
	this->gameOverTex.setString("Gamr Over!");*/
}

void Game::renderHeart()
{
	for (int i = 0; i < Hp; i++)
	{
		window.draw(this->heart->heart[i]);
	}
}

Game::Game()
{	
	this->view.setSize(1440, 720);
	this->menu = new Menu(view);
	//Hp
	this->initVariables();
	this->initGameover();
	this->initWindow();

	this->initFont();
	this->initTex();

	this->initPlayer();

	this->coin=new Coin;

	this->enemy = new Enemy;

	this->heart = new Heart;

}

Game::~Game()
{
	//delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}

	delete this->player;
}

void Game::updateEvent()
{
	while (this->window.pollEvent(this->ev))
	{
		this->menu->Event(window, this->ev);

		if (this->ev.type == Event::Closed)
			this->window.close();
	}
}

void Game::updateDt()
{
	//Upadte the dt variable with the time it takes to update and render one frame
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateCollision()
{
	//Collision bottom of screen
	if (this->player->getPosition().y > this->window.getSize().y - this->player->getGlobalBounds().height)
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			this->window.getSize().y - this->player->getGlobalBounds().height);
	}
	if (player->getPosition().x > 0)
	{
		this->player->resetVelocityX();
		this->player->setPosition(
			this->player->getPosition().x, this->player->getPosition().y
			);
	}
	//Coin
	for (int i = 0; i < this->coin->coins.size(); i++)
	{
		if (player->getGlobalBounds().intersects(this->coin->coins[i].getGlobalBounds()))
		{
			this->coin->coins.erase(this->coin->coins.begin() + i);
			this->points = points +2;
			break;
		}
	}
	//Diamond
	for (int i = 0; i < this->coin->diamond.size(); i++)
	{
		if (player->getGlobalBounds().intersects(this->coin->diamond[i].getGlobalBounds()))
		{
			this->coin->diamond.erase(this->coin->diamond.begin() + i);
			this->points = points + 10;
			//or Hp++
			break;
		}
	}
	//Heal
	for (int i = 0; i < this->coin->heal.size(); i++)
	{
		if (player->getGlobalBounds().intersects(this->coin->heal[i].getGlobalBounds()))
		{
			this->coin->heal.erase(this->coin->heal.begin() + i);
			Hp++;
			break;
		}
	}
	//Enemy
	for (int i = 0; i < 8; i++)
	{
		if (player->getGlobalBounds().intersects(this->enemy->enemies[i].getGlobalBounds())&&this->player->getCollideCooldown()<=0)
		{
			if (Hp > 0)
			{
				Hp = Hp - 1;
			}
			else {} //End Game
			this->player->setCollideCooldown(60);
			break;
		}
	}
}

void Game::initGameover()
{
	this->gameOverTex.loadFromFile("Gameover.png");
	this->Gameover.setTexture(gameOverTex);
	this->Gameover.setPosition(0, 0);
}

void Game::update()
{
	this->updateEvent();

	//Polling window events
	if(this->game_state == GAME_MENU) 
	{
		
		if(Keyboard::isKeyPressed(Keyboard::Key::Enter)) 
		{
			int selected_item = this->menu->getSelectedItem();
			if (selected_item == 0)
			{
				this->game_state = GAME_PLAY;
				cout << "Enter" << endl;
			}
			if (selected_item == 2)
			{
				this->window.close();
				cout << "Enter" << endl;
			}
		}		

		/*
		while (this->window.pollEvent(this->ev))
		{
			if (this->ev.type == Event::Closed)
				this->window.close();
			else if (this->ev.type == Event::KeyPressed && this->ev.key.code == Keyboard::Escape)
				this->window.close();

			if (this->ev.type == Event::KeyReleased &&
				(
					this->ev.key.code == Keyboard::A ||
					this->ev.key.code == Keyboard::D ||
					this->ev.key.code == Keyboard::W ||
					this->ev.key.code == Keyboard::S
					)
				)
			{
				this->player->resetAnimationTimer();
			}
			if (this->ev.type == Event::KeyPressed && this->ev.key.code == Keyboard::Enter)
			{
				int selected_item = this->menu->getSelectedItem();
				if (selected_item == 0)
				{
					this->game_state = GAME_PLAY;
					cout << "Enter" << endl;
				}
			}
		}
		*/
	}
	if(this->game_state == GAME_PLAY) 
	{
		if (Hp <= 0)
		{
			this->game_state = GAME_OVER;
		}
		this->updatePlayer();
		this->updateCollision();
		this->enemy->update();
		this->updateGui();

	}
	if (this->game_state == GAME_OVER)
	{

		if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
		{
			this->game_state = GAME_MENU;
		}
	}

}

void Game::run()
{
	while (this->window.isOpen())
	{
		//this->updateDt();
		this->update();
		this->render();
	}
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::updateGui()
{
	stringstream ss;

	ss << "Points : " << this->points;

	this->guiTex.setString(ss.str());

}

void Game::renderGui(RenderTarget& target)
{
	target.draw(this->guiTex);
}


void Game::render()
{
	this->window.clear();

	if(this->game_state == GAME_MENU) this->menu->draw(window, view);
	if (this->game_state == GAME_PLAY)
	{

		this->view.setCenter(1440/2, 720/2);
		this->view.setSize(1440, 720);
		this->window.setView(view);

		map.Draw(window);

		//Render game
		this->coin->render(window);

		this->renderGui(window);
		this->enemy->render(window);

		renderHeart();

		this->renderPlayer();

	}
	if (this->game_state == GAME_OVER)
	{
		this->window.draw(Gameover);
	}
	
	this->window.display();
}

const RenderWindow& Game::getWindow() const
{
	// TODO: insert return statement here
	return this->window;
}
