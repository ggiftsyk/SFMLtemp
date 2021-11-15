#include "GameState.h"
#include "State.h"

//GameState::GameState(RenderWindow* window)
//	: State(window)
//{
//}

GameState::~GameState()
{
}

void GameState::endState()
{
	cout << "Ending Game" << endl;
}

//void GameState::updateKeybind(const float& dt)
//{
//	this->checkForQuit();
//}

void GameState::update(const float& dt)
{
	this->updateKeybind(dt);
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		cout << "A" << endl;
	}
}

void GameState::render(RenderTarget* target)
{
}
