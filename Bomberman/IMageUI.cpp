#include "IMageUI.h"

IMageUI::IMageUI()
{

}
IMageUI::~IMageUI()
{

}

void IMageUI::SetTexture(string url)
{
	texture.loadFromFile(url);
	sprite.setTexture(texture);
	texture.setSmooth(true);
}

void IMageUI::Draw()
{
	StaticWindow::window->draw(sprite);
}

void IMageUI::SetOrigin(float x, float y)
{
	sprite.setOrigin(x, y);
}

void IMageUI::SetPosition(float x, float y)
{
	sprite.setPosition(x, y);
}
void IMageUI::SetScale(float x, float y)
{
	sprite.setScale(x, y);
}
void IMageUI::SetOrigin(Vector2f v)
{
	sprite.setOrigin(v);
}

void IMageUI::SetPosition(Vector2f v)
{
	sprite.setPosition(v);
}
void IMageUI::SetScale(Vector2f v)
{
	sprite.setScale(v);
}
void IMageUI::SetRotation(float angle)
{
	sprite.setRotation(angle);
}

void IMageUI::SetColor(Color& color)
{
	sprite.setColor(color);
}

void IMageUI::SetTextureRect(IntRect& rect)
{
	sprite.setTextureRect(rect);
}