#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class SelectedFont
{
private:

	Font font;

public:
	static SelectedFont* instance;

	SelectedFont();
	~SelectedFont();

	Font& GetFont();
};

