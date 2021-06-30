#pragma once
#include <iostream>
#include "CoreClasses.h"
#include <list>
#include <UI UX/GUI.h>
#include <Windows.h>
#include <UI UX/FramedPiece.h>
#include <UI UX/Button.h>
using namespace std;

Vector2f resolution(1024, 576);//current window size
int blockSize = 22;//size of one block+outline
float startX = resolution.x / 2.5;//field startX
float startY = 0;//field startY

list<Keyboard::Key> KeyCheck(RenderWindow& window)
{
    Event e;
    list<Keyboard::Key> keys;
    while (window.pollEvent(e))
    {
        if (e.type == Event::KeyPressed)
            keys.push_back(e.key.code);
        if (e.type == Event::Closed)
            window.close();
    }
    return keys;
}

bool EndHandle(Field* game, GUI& gui, RenderWindow& window) 
{
    gui.getElement("gameOver").draw = true;
    gui.getElement("yesB").draw = true;
    gui.getElement("noB").draw = true;
    if (dynamic_cast<Button&>(gui.getElement("yesB").element).pressed(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left))
    {
        game->Refresh();
        gui.getElement("gameOver").draw = false;
        gui.getElement("yesB").draw = false;
        gui.getElement("noB").draw = false;
        return true;
    }
    else if(dynamic_cast<Button&>(gui.getElement("noB").element).pressed(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left))
        return false;
}

int main()//game itself 
{
    //var init
    Font font;
    font.loadFromFile("font.ttf");
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Tetris by DLWHI");
    Field *game = new Tetris(Vector2f(startX, startY));

    Button qwe(Vector2f(startX + Block::size * 10 + 75, 40 - startY), Vector2f(Block::size * 5.5, 350), "score:\n100000\n\n\n\n\n\n\level:\n1\n", font, 24);
    GUI hud("Tetris", Vector2f(startX, startY));
    //ShowWindow(GetConsoleWindow(), SW_HIDE);//console hider
    while (window.isOpen())
    {
        list<Keyboard::Key> keyL = KeyCheck(window);
        if (game->GameOver())
            EndHandle(game, hud, window);
        else
            game->Update(keyL);
        window.clear(Color::Black);
        /*Vector2i mpos = Mouse::getPosition(window);
        string pos = to_string(mpos.x) + " " + to_string(mpos.y);
        window.setTitle(pos);*/
        window.draw(hud);
        window.draw(*game);
        window.display();//display shiet
    }
    delete game;
    return 0;
};