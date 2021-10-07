#pragma once
#include <SFML/Graphics.hpp>

class StaticWindow
{
public:

	static sf::RenderWindow* window;
	StaticWindow();
	~StaticWindow();
};

