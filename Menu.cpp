#include "Menu.h"


Menu::Menu(View& view)
{	
	//view.setCenter(view.getSize().x / 2, view.getSize().y / 2);

	if(!backgroundTex.loadFromFile("Bgmenu2.png")){}
	background.setTexture(backgroundTex);
	background.setPosition(view.getSize().x / 2, view.getSize().y / 2);

	if (!font.loadFromFile("SHOWG.ttf")){}
	float offset_x = 1440 / 2;
	float offset_y = 720 / 2;
	menu[0].setFont(font);
	menu[0].setCharacterSize(60);
	menu[0].setFillColor(Color::Magenta);
	menu[0].setString("Play");
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 4);
	menu[0].setPosition(Vector2f((view.getSize().x * 3 / 2) - offset_x, (view.getSize().y * 3 / 7) + offset_y)); 

	menu[1].setFont(font);
	menu[1].setCharacterSize(40);
	menu[1].setFillColor(Color::Color(44, 52, 107));
	menu[1].setString("High Score");
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 4);
	menu[1].setPosition(Vector2f((view.getSize().x * 3 / 2) - offset_x, (view.getSize().y * 4 / 7) + offset_y));

	menu[2].setFont(font);
	menu[2].setCharacterSize(40);
	menu[2].setFillColor(Color::Color(44, 52, 107));
	menu[2].setString("Exist");
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 4);
	menu[2].setPosition(Vector2f((view.getSize().x * 3 / 2) - offset_x, (view.getSize().y * 5 / 7) + offset_y));
}

Menu::~Menu()
{
}

void Menu::draw(RenderWindow& window, sf::View& view)
{	
	view.setCenter(view.getSize().x, view.getSize().y);
	view.setSize(1440, 720);
	window.setView(view);
	window.draw(background);

	for (int i = 0; i < MAX_ITEM; i++)
	{
		//menu[i].setOrigin(menu[i].getLocalBounds().width / 2, menu[i].getLocalBounds().height * (i + 3) / 7.5);
		menu[i].setOrigin(menu[i].getLocalBounds().width / 2, menu[i].getLocalBounds().height * (i + 3) / 7);
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItem - 1 >= 0)
	{
		menu[selectedItem].setFillColor(Color::Color(44, 52, 107));
		//menu[selectedItem].setCharacterSize(36);
		selectedItem--;
		menu[selectedItem].setFillColor(Color::Magenta);
		//menu[selectedItem].setCharacterSize(60);
	}
}

void Menu::MoveDown()
{
	if (selectedItem +1 < MAX_ITEM)
	{
		menu[selectedItem].setFillColor(Color::Color(44, 52, 107));
		//menu[selectedItem].setCharacterSize(36);
		selectedItem++;
		menu[selectedItem].setFillColor(Color::Magenta);
		//menu[selectedItem].setCharacterSize(60);
	}
}

void Menu::Event(RenderWindow& window, sf::Event ev)
{
	switch (ev.type)
	{
	case Event::KeyReleased:
		switch (ev.key.code)
		{
		case Keyboard::Up:
			MoveUp();
			break;
		case Keyboard::Down:
			MoveDown();
			break;
		}
		break;
	}
}

int Menu::getSelectedItem()
{
	return this->selectedItem;
}
