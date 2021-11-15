#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "GameState.h"

#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

extern int CurrentState;

using namespace sf;
using namespace std;

class State
{
private:
	int state;
	/*RenderWindow* window;
	vector<Texture> textures;
	bool quit;*/

public:
	int currentState();
	void NextState(int s);

	/*State(RenderWindow* window);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();
	virtual void endState() = 0;

	virtual void updateKeybinds(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(RenderTarget* target = nullptr) = 0;*/
};
#endif // !STATE_H
