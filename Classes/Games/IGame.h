#pragma once
#include <list>
class IGame 
{
public:
	virtual void Update(std::list<Keyboard::Key>&) = 0;
	virtual void Refresh() = 0;
	virtual bool GameOver() = 0;

protected:
	virtual int Check() = 0;
};