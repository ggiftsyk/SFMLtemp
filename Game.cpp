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
}

void Game::renderHeart()
{
	for (int i = 0; i < Hp; i++)
	{
		window.draw(this->heart->heart[i]);
	}
}

Game::Game(ScoreList* score_list)
{	
	game_state = 0;
	this->view.setSize(1440, 720);
	this->menu = new Menu(view);
	//Hp
	this->initVariables();

	this->initGameover();
	this->initGamewin();
	this->initHighscore();
	this->initInputname();

	this->initWindow();

	//Scorelist
	this->score_list = score_list;

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
	Event event;
	while (this->window.pollEvent(event))
	{
		this->menu->Event(window, event);

		if (event.type == Event::Closed)
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
	this->gameOverTex.loadFromFile("over.png");
	this->Gameover.setTexture(gameOverTex);
	this->Gameover.setPosition(0, 0);
}

void Game::initGamewin()
{
	this->gameWinTex.loadFromFile("Win.png");
	this->Gamewin.setTexture(gameWinTex);
	this->Gamewin.setPosition(0, 0);
}
void Game::initHighscore()
{
	this->HighscoreTex.loadFromFile("score.png");
	this->Highscore.setTexture(HighscoreTex);
	this->Highscore.setPosition(1440.f/2.f, 720.f/2.f);
	//this->Highscore.setPosition();
}

void Game::initInputname()
{
	this->inputnameTex.loadFromFile("inputname.png");
	this->InputName.setTexture(inputnameTex);
	this->InputName.setPosition(1440.f / 2.f, 720.f / 2.f);
	//this->Highscore.setPosition();
}

void Game::update()
{
	sf::sleep(sf::seconds(0.01f));
	
	//this->updateEvent();
	//Polling window events
	if(this->game_state == GAME_MENU) 
	{
		Event event;
		while (this->window.pollEvent(event))
		{
			this->menu->Event(window, event);
			if (event.type == Event::Closed) this->window.close();
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				this->window.close();
			}
			if (event.type == Event::TextEntered) {
				
				if(event.text.unicode == 13) //13=Enter
				{
					int selected_item = this->menu->getSelectedItem();
					if (selected_item == 0)
					{
						this->game_state = INPUT_NAME;
						cout << "Enter" << endl;
					}
					if (selected_item == 1)
					{
						this->game_state = HIGH_SCORE;
						cout << "Enter" << endl;
					}
					if (selected_item == 2)
					{
						this->window.close();
						cout << "Enter" << endl;
					}
				}	
			}
		}	
	}
	if (this->game_state == INPUT_NAME)
	{
		Event event;
		while (this->window.pollEvent(event))
		{
			if (event.type == Event::Closed) this->window.close();
			if (event.type == Event::TextEntered)
			{
				cout << event.text.unicode << endl;
				if (event.text.unicode == 8)
				{
					if (name.size() > 0)
						name.erase(name.end() - 1);
				}
				if (event.text.unicode == 13) //Enter
				{
					this->game_state = GAME_PLAY;
				}
				if ((event.text.unicode >= 'A' and event.text.unicode <= 'Z') or (event.text.unicode >= 'a' and event.text.unicode <= 'z'))
				{
					if (name.size() < 10)
						name+=char(event.text.unicode);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			{
				this->game_state = GAME_MENU;
			}
		
		}
	}
	if(this->game_state == GAME_PLAY) 
	{
		Event event;
		while (this->window.pollEvent(event))
		{
			if(event.type == Event::Closed) this->window.close();
		}

		if (Hp <= 0)
		{
			sleep(seconds(0.4f));
			this->game_state = GAME_OVER;

			// Reset
			Hp = 4;
		}
		// Win
		else if (player->getGlobalBounds().intersects(this->coin->finish.getGlobalBounds()))
		{
			sleep(seconds(0.6f));
			this->game_state = GAME_WIN;
			// Reset
			Hp = 4;
		}

		this->updatePlayer();
		this->updateCollision();
		this->enemy->update();
		this->updateGui();

		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
		{
			this->game_state = GAME_MENU;
		}

	}

	if (this->game_state == HIGH_SCORE)
	{
		Event event;
		while (this->window.pollEvent(event))
		{
			if (event.type == Event::Closed) this->window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
		{
			this->game_state = GAME_MENU;
		}
	}
	if (this->game_state == GAME_OVER)
	{	
		Event event;
		while (this->window.pollEvent(event))
		{
			if(event.type == Event::Closed) this->window.close();
			if (event.text.unicode == 13)
			{
				//Reset
				coin->resetCoin();
				this->player->setPosition(18.f, 18.f);
				score_list->addEntry(name, points);
				cout << "GAME_OVER" << endl;
				name = "";
				points = 0;
				this->game_state = GAME_MENU;
				break;
			}
		}

		
	}
	if (this->game_state == GAME_WIN)
	{
		Event event;
		while (this->window.pollEvent(event))
		{
			if (event.type == Event::Closed) this->window.close();
			if (event.text.unicode == 13)
			{
				score_list->addEntry(name, points);
				name = "";
				cout << "GAME_WIN" << endl;
				//Reset
				coin->resetCoin();
				this->player->setPosition(18.f, 18.f);
				points = 0;
				Hp = 4;
				this->game_state = GAME_MENU;
				break;
			}
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
		//cout << " " << game_state << endl;
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
	if (this->game_state == INPUT_NAME)
	{
		this->window.draw(InputName);

		Text text;
		text.setFont(font);
		text.setString(name + "_");
		text.setFillColor(Color::White);
		text.setOrigin(Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height) / 2.f);
		text.setPosition(1400.f,700.f);
		text.setCharacterSize(70);
		cout<<name<<endl;
		window.draw(text);
	}
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
	if (this->game_state == HIGH_SCORE)
	{
		this->window.draw(Highscore);
		Text text;
		text.setFont(font);
		text.setFillColor(Color::Blue);
		text.setCharacterSize(33);
		//Show name
		int show_max_entry = 5;
		for (int i = 0; i < this->score_list->get().size(); i++)
		{
			if (i >= show_max_entry) break;
			text.setPosition(910, 600 + (i * 60));
			text.setString(score_list->get().at(i).getName());
			window.draw(text);
		}
		//Show score
		for (int i = 0; i < this->score_list->get().size(); i++)
		{
			if (i >= show_max_entry) break;
			text.setPosition(1100, 600 + (i * 60));
			text.setString(to_string(score_list->get().at(i).getScore()));
			window.draw(text);
		}
	}
	if (this->game_state == GAME_OVER)
	{
		this->window.draw(Gameover);
	}

	if (this->game_state == GAME_WIN)
	{
		cout << "hahaha" << endl;
		this->window.draw(Gamewin);
	}
	
	this->window.display();
}

const RenderWindow& Game::getWindow() const
{
	// TODO: insert return statement here
	return this->window;
}
