#ifndef  GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class GameState 
	//public State
{
private:
	

public:
	GameState(RenderWindow* window);
	virtual ~GameState();

	//Functions
	void endState();

	void updateKeybind(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target = nullptr);
};
#endif // ! GAMESTATE_H