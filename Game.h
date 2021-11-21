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
#include "ScoreList.h"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

#define GAME_MENU 0
#define INPUT_NAME 1
#define GAME_PLAY 2
#define GAME_OVER 3
#define GAME_WIN 4
#define HIGH_SCORE 5


using namespace sf;
using namespace std;

class Game
{
private:
	string name = "";

	//Variables
	RenderWindow window;
	//Event ev;
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
	/*RectangleShape playerHpBar;
	RectangleShape playerHpBarBack;*/

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

	//bool isGameOver;
	Font font;
	Text guiTex;
	
	//Gameover
	Sprite Gameover;
	Texture gameOverTex;

	Text gameOvertex;

	int TextEntered;

	//Gamewin
	Sprite Gamewin;
	Texture gameWinTex;

	//High score
	Sprite Highscore;
	Texture HighscoreTex;

	//Scorelist
	ScoreList* score_list;
	
	void updateDt();

	//Gameover
	void initGameover();

	//Gamewin
	void initGamewin();

	//HIGHSOCRE
	void initHighscore();

	//Enter name
	void initInputname();

	Sprite InputName;
	Texture inputnameTex;

public:
	Game(ScoreList* score_list);
	virtual ~Game();

	//Functions
	void updateEvent();

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

