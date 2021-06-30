#pragma once
#include <list>
#include <algorithm>
#include <tinyxml.h>
#include "FramedPiece.h"
#include "Button.h"
#ifndef  GUARD
#define GUARD
#include <SFML/Graphics.hpp>
using namespace sf;
#endif

class GUI : public Drawable
{
public:
	struct Element 
	{
		bool draw = true;
		std::string name;
		Drawable& element;

		Element(const std::string& neim, Drawable& el) : name(neim), element(el) { };
		Element(const Element& other) : name(other.name), element(other.element) { };

		friend bool operator==(const Element& ths, const Element& other) { return ths.name == other.name; }
	};
	GUI();
	GUI(std::string, Vector2f);
	GUI(const GUI&);
	~GUI();

	void KeyCheck();
	void Push(const Element&);
	void Remove(std::string&);
	Element& getElement(const std::string&);
private:
	Font font;
	Vector2f offset;
	std::string fontFile = "font.ttf";
	std::list<Element> elements;

	void setupGame(std::string);
	virtual void draw(RenderTarget&, RenderStates) const;
};