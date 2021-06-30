#pragma once
#include <fstream>
#include <regex>
#include <exception>
#include <string>
#include <random>
#ifndef GUARD
#define GUARD
#include <SFML/Graphics.hpp>
using namespace sf;
#endif

class PieceInfo
{
public:
    PieceInfo(std::initializer_list<Vector2f>, const Vector2f&, const Color&, const std::string&, const int);
    PieceInfo(const int, const Vector2f*, const Vector2f&, const Color&, const std::string&, const int);
    PieceInfo(const PieceInfo&);
    ~PieceInfo();

    int getCount() const;
    int getCode() const;
    Vector2f* getBlockPos() const;
    Vector2f getPivot() const;
    Color getColor() const;
    std::string getName()const;
private:
    int count;
    int code;
    Vector2f *blockPos;
    Vector2f pivot;
    Color color;
    std::string name;
}; 

class PieceInitter
{
public:
    PieceInitter();
    ~PieceInitter();

    PieceInfo getNext();
    PieceInfo getPiece(const std::string&) const;
    //int getPieceCount() const;
private:
    const int defaultCount = 7;
    int pieceCount = 0;
    std::string fileName = "C:\\Users\\Lord\\source\\repos\\Elementary Games\\Tetris\\Data\\pieces.json";
    std::mt19937 gen;
    std::uniform_int_distribution<int> uidP;
    PieceInfo convertFromJSON(std::string, int);
    PieceInfo* ReadPiece();
    PieceInfo* defaultPiece;
    PieceInfo* pieces;
};

 