#pragma once
#ifndef  GUARD
#define GUARD
#include <SFML/Graphics.hpp>
using namespace sf;
#endif
class FramedText : public Drawable
{
public:
	FramedText() = default;
	FramedText(Text, Vector2f);
	FramedText(Text, Vector2f, bool);
	FramedText(FramedText&);
	~FramedText();

	void setPos(Vector2f);
	void setSpacing(Vector2f);
	void setString(std::string);
	void setCharacterSize(unsigned int);
	void setOutlineThickness(unsigned int);
	void setTextColor(Color);
	void setFillColor(Color);
	void setOutlineColor(Color);
	void setState(bool);

	Vector2f getPos();
	Vector2f getSpacing();
	std::string getString();
	unsigned int getCharacterSize();
	unsigned int getOutlineThickness();
	Color getTextColor();
	Color getFillColor();
	Color getOutlineColor();
	bool getState();
private:
	bool isFixed = false;
	Text txt;
	RectangleShape frame;
	Vector2f spacing = Vector2f(7, 7);
	const std::string* bindedStr = nullptr;

	void Reset();
	virtual void draw(RenderTarget & taget, RenderStates states) const;
};

