#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "State.h"
#include "GameState.h"
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"
#include "Heart.h"
#include "Menu.h"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

#define GAME_MENU 0
#define GAME_PLAY 1
#define GAME_OVER 2


using namespace sf;
using namespace std;

class Game
{
private:
	//Variables
	RenderWindow window;
	Event ev;
	Menu *menu;
	View view;

	Clock dtClock;
	float dt;

	stack<State*> states;

	//State
	int game_state;

	//Player
	Player *player;

	//PlayerGUI
	RectangleShape playerHpBar;
	RectangleShape playerHpBarBack;

	Coin *coin;

	Enemy *enemy;

	Heart* heart;
	
	Level map;


	//Private Functions
	void initWindow();

	void initPlayer();
	void initVariables();
	void initFont();
	void initTex();

	void renderHeart();

	//Score
	int points;

	int Hp;

	// bool isGameOver;
	Font font;
	Text guiTex;
	
	//Gameover
	Sprite Gameover;
	Texture gameOverTex;
	

public:
	Game();
	virtual ~Game();

	//Functions
	void updateEvent();
	void updateDt();

	//Gameover
	void initGameover();

	void updatePlayer();
	void updateCollision();
	void update();
	void run();

	void renderPlayer();

	//Score text
	void renderGui(RenderTarget& target);
	void updateGui();

	void render();
	const RenderWindow& getWindow() const;

};

