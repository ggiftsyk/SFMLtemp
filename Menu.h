#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>

#include"State.h"
#define MAX_ITEM 3 //start leaderboard exit

using namespace sf;
using namespace std;

class Menu
{
private:
	Texture backgroundTex;
	Sprite background;
	int selectedItem = 0;
	Font font;
	Text menu[MAX_ITEM]; 

public:
	Menu(View& view);
	virtual ~Menu();

	void draw(RenderWindow& window, View& view);
	void MoveUp();
	void MoveDown();
	void Event(RenderWindow& window, Event ev);
	int getSelectedItem();
	int GetPressedItem() { return selectedItem; }
};

