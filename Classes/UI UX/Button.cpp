#include "Button.h"
Button::Button(Vector2f pos, Vector2f size) 
{
	front.setPosition(pos);
	front.setSize(size);
	front.setFillColor(Color::Black);
	front.setOutlineColor(Color::White);
	front.setOutlineThickness(4);

	hitbox.left = round(pos.x);
	hitbox.top = round(pos.y);
	hitbox.width = round(size.x);
	hitbox.height = round(size.y);

	center = size / 2.0f;
	maxCharSize = UINT_MAX;
}
Button::Button(Vector2f pos, Vector2f size, std::string text, const Font& font, unsigned int charSize) : Button(pos, size)
{
	txt.setString(text);
	txt.setFont(font);
	txt.setCharacterSize(charSize);

	if (size == Vector2f(0, 0))
		return;
	FloatRect bounds = txt.getLocalBounds();
	while (bounds.width > 2*center.x || bounds.height > 2*center.y) 
	{
		txt.setCharacterSize(--charSize);
		bounds = txt.getLocalBounds();
	}
	txt.setPosition(front.getPosition() + center);
	txt.move(-Vector2f(bounds.width, bounds.height)/2.0f);
	txt.move(-Vector2f(bounds.left, bounds.top));
	maxCharSize = charSize;

}
Button::Button(Button& other) 
{
	txt = other.txt;
	front = other.front;
	hitbox = other.hitbox;
}

void Button::setPosition(Vector2f pos) 
{
	front.setPosition(pos);
	Reset();
}
void Button::setSize(Vector2f size)
{
	front.setSize(size);
	Reset();
}
void Button::setText(std::string text)
{
	txt.setString(text);
	FloatRect bounds = txt.getLocalBounds();
	unsigned int charSize = txt.getCharacterSize();
	while (bounds.width > 2 * center.x || bounds.height > 2 * center.y)
	{
		txt.setCharacterSize(--charSize);
		bounds = txt.getLocalBounds();
	}
	txt.setPosition(front.getPosition() + center);
	txt.move(-Vector2f(bounds.width / 2, bounds.height / 2));
	txt.move(-Vector2f(bounds.left, bounds.top));
	maxCharSize = charSize;
}

bool Button::pressed(Vector2i pressPos) 
{
	if (hitbox.contains(pressPos))
		return true;
	return false;
}

void Button::Reset() 
{
	Vector2f pos = front.getPosition();
	Vector2f size = front.getSize();
	hitbox.left = round(pos.x);
	hitbox.top = round(pos.y);
	hitbox.width = round(size.x);
	hitbox.height = round(size.y);

	FloatRect bounds = txt.getLocalBounds();
	txt.setPosition(front.getPosition() + center);
	txt.move(-Vector2f(bounds.width / 2, bounds.height / 2));
	txt.move(-Vector2f(bounds.left, bounds.top));
}
void Button::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(front);
	if (front.getSize() != Vector2f(0, 0))
		target.draw(txt);
}