#pragma once
#ifndef GUARD
#define GUARD
#include <SFML/Graphics.hpp>
using namespace sf;
#endif
class Button : public Drawable
{
public:
	Button() = default;
	Button(Vector2f, Vector2f);
	Button(Vector2f, Vector2f, std::string, const Font&, unsigned int = 30);
	Button(Button&);
	~Button() = default;

	void setPosition(Vector2f);
	void setSize(Vector2f);
	void setText(std::string);
	void setCharacterSize(unsigned int);
	void setOutlineThickness(unsigned int);
	void setTextColor(Color&);
	void setFillColor(Color&);
	void setOutlineColor(Color&);

	bool pressed(Vector2i);

	Vector2f getPosition();
	Vector2f getSize();
	std::string& getText();
	unsigned int getCharacterSize();
	unsigned int getOutlineThickness();
	Color getTextColor();
	Color getFillColor();
	Color getOutlineColor();
private:
	unsigned int maxCharSize;
	RectangleShape front;
	IntRect hitbox;
	Text txt;
	Vector2f center;

	void Reset();
	virtual void draw(RenderTarget&, RenderStates) const;
};