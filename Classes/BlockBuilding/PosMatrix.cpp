#include "PosMatrix.h"
#include <iostream>

//matrix inits
#pragma region PieceInfo
PieceInfo::PieceInfo(std::initializer_list<Vector2f> blocks, const Vector2f& pivot, const Color& color, const std::string& name, const int code)
{
    this->count = blocks.size();
    this->pivot = pivot;
    this->color = color;
    this->name = name;
    this->code = code;
    blockPos = new Vector2f[count];
    for (int i = 0; i < count; i++)
        blockPos[i] = *(blocks.begin() + i);
}
PieceInfo::PieceInfo(const int count, const Vector2f* blocks, const Vector2f& pivot, const Color& color, const std::string& name, const int code)
{
    this->count = count;
    this->pivot = pivot;
    this->color = color;
    this->name = name;
    this->code = code;
    blockPos = new Vector2f[count];
    for (int i = 0; i < count; i++)
        blockPos[i] = blocks[i];
}
PieceInfo::PieceInfo(const PieceInfo& other)
{
    blockPos = new Vector2f[other.count];
    for (int i = 0; i < 4; i++)
        blockPos[i] = other.blockPos[i];
    count = other.count;
    pivot = other.pivot;
    color = other.color;
    name = other.name;
    code = other.code;
}
PieceInfo::~PieceInfo()
{
    delete[] blockPos;
}

int PieceInfo::getCount() const
{
    return count;
}
int PieceInfo::getCode() const
{
    return code;
}
Vector2f* PieceInfo::getBlockPos() const
{
    return blockPos;
}
Vector2f PieceInfo::getPivot() const
{
    return pivot;
}
Color PieceInfo::getColor() const
{
    return color;
}
std::string PieceInfo::getName() const
{
    return name;
}
#pragma endregion

#pragma region PieceInitter
PieceInitter::PieceInitter()
{
    pieces = ReadPiece();
    defaultPiece = static_cast<PieceInfo*>(operator new[](7 * sizeof(PieceInfo)));
    gen.seed(clock());
    uidP = std::uniform_int_distribution<int>(0, pieceCount + defaultCount - 1);
    new (defaultPiece) PieceInfo({
        Vector2f(0, 0),
        Vector2f(0, 1),
        Vector2f(1, 1),
        Vector2f(-1, 0)
        }, Vector2f(0, 0), Color(255, 0, 0), "zPiece", 0);
    new (defaultPiece + 1) PieceInfo({
        Vector2f(0, 0),
        Vector2f(0, 1),
        Vector2f(-1, 1),
        Vector2f(1, 0)
        }, Vector2f(0, 0), Color(0, 255, 0), "sPiece", 1);
    new (defaultPiece + 2) PieceInfo({
        Vector2f(0, 0),
        Vector2f(-1, 1),
        Vector2f(1, 0),
        Vector2f(-1, 0)
        }, Vector2f(0, 0), Color(255, 165, 0), "lPiece", 2);
    new (defaultPiece + 3) PieceInfo({
        Vector2f(0, 0),
        Vector2f(1, 1),
        Vector2f(1, 0),
        Vector2f(-1, 0)
        }, Vector2f(0, 0), Color(0, 0, 255), "jPiece", 3);
    new (defaultPiece + 4) PieceInfo({
        Vector2f(0, 0),
        Vector2f(0, -1),
        Vector2f(1, 0),
        Vector2f(-1, 0)
        }, Vector2f(0, 0), Color(80, 0, 255), "tPiece", 4);
    new (defaultPiece + 5) PieceInfo({
        Vector2f(0, 0),
        Vector2f(0, -1),
        Vector2f(-1, -1),
        Vector2f(-1, 0)
        }, Vector2f(0.5, 0.5), Color(255, 255, 0), "oPiece", 5);
    new (defaultPiece + 6) PieceInfo({
        Vector2f(0, 0),
        Vector2f(0, 1),
        Vector2f(0, -1),
        Vector2f(0, 2)
        }, Vector2f(0.5, -0.5), Color(0, 255, 255), "iPiece", 6);
}
PieceInitter::~PieceInitter()
{
    for (int i = 0; i < defaultCount; i++)
        defaultPiece[i].~PieceInfo();
    operator delete[](pieces);
    operator delete[](defaultPiece);
}

PieceInfo PieceInitter::convertFromJSON(std::string json, int iterNo) 
{
    using namespace std;
    regex keyVal("\".*\": ?(.|(\n *\\[[^\\]]*\\]))*");
    int count;
    Vector2f* blockPos = nullptr;
    Vector2f pivot;
    Color color;
    string name;
    for (auto i = sregex_iterator(json.begin(), json.end(), keyVal); i != sregex_iterator(); i++) 
    {
        string key = (*i).str();
        string value = (*i).str().substr((*i).str().find(":"), (*i).str().length());
        if (key.find("name") != string::npos)
        {
            regex r("[a-zA-Z_\\.1-9]+");
            smatch m;
            if (regex_search(value, m, r))
                name = m.str();
            else
                throw exception("Wrong piece data");
        }
        else if (key.find("pivot") != string::npos)
        {
            regex r("-?\\d+\\.?\\d*");
            sregex_iterator iStr(value.begin(), value.end(), r);
            for (int i = 0; iStr != sregex_iterator(); i++, iStr++)
                if (i == 0)
                    pivot.x = stof((*iStr).str());
                else if(i == 1)
                    pivot.y = stof((*iStr).str());
            else
                throw exception("Wrong piece data");
        }
        else if (key.find("color") != string::npos)
        {
            regex r("\\d{1,3}");
            sregex_iterator iStr(value.begin(), value.end(), r);
            for (int i = 0; iStr != sregex_iterator(); i++, iStr++)
                if (i == 0)
                    color.r = stof((*iStr).str());
                else if (i == 1)
                    color.g = stof((*iStr).str());
                else if (i == 2)
                    color.b = stof((*iStr).str());
                else
                    throw exception("Wrong piece data");
        }
        else if (key.find("blockPos") != string::npos)
        {
            regex r("-?\\d+\\.?\d*, ?-?\\d+\.?\\d*");
            count = distance(sregex_iterator(value.begin(), value.end(), r), sregex_iterator());
            sregex_iterator iStr(value.begin(), value.end(), r);
            blockPos = new Vector2f[count];
            for (int i = 0; iStr != sregex_iterator(); i++, iStr++)
            {
                string vecS = (*iStr).str();
                regex vecR("-?\\d+\\.?\\d*");
                sregex_iterator iVec(vecS.begin(), vecS.end(), vecR);
                for (int j = 0; iVec != sregex_iterator(); j++, iVec++)
                    if (j == 0)
                        blockPos[i].x = stof((*iVec).str());
                    else if (j == 1)
                        blockPos[i].y = stof((*iVec).str());
                    else
                        throw exception("Wrong piece data");
            }
        }
    }
    if(blockPos == nullptr)
        throw exception("Wrong piece data");
    return PieceInfo(count, blockPos, pivot, color, name, 7 + iterNo);
}
PieceInfo* PieceInitter::ReadPiece()
{
    return nullptr;
    using namespace std;
    ifstream pieceFile(fileName);
    if (!pieceFile.is_open())
        return nullptr;
    string content;
    content.assign(istreambuf_iterator<char>(pieceFile), istreambuf_iterator<char>());
    
    regex pieceReg("\\{[^\\}]*\\}");
    int count = distance(sregex_iterator(content.begin(), content.end(), pieceReg), sregex_iterator());
    PieceInfo* res = static_cast<PieceInfo*>(operator new[](count * sizeof(PieceInfo)));
    sregex_iterator iStr(content.begin(), content.end(), pieceReg);
    for (int i = 0; iStr != sregex_iterator(); i++, iStr++)
        new (res + i) PieceInfo(convertFromJSON((*iStr).str(), i));
    pieceCount = count;
    pieceFile.close();
    return res;
}
PieceInfo PieceInitter::getPiece(const std::string& name) const
{
    for (int i = 0; i < defaultCount; i++)
        if (defaultPiece[i].getName() == name)
            return defaultPiece[i];
    for (int i = 0; i < pieceCount; i++)
        if (pieces[i].getName() == name)
            return pieces[i];
    throw new std::exception("No such piece");
}
PieceInfo PieceInitter::getNext()
{
    int code = uidP(gen);
    for (int i = 0; i < defaultCount; i++)
        if (defaultPiece[i].getCode() == code)
            return defaultPiece[i];
    for (int i = 0; i < pieceCount; i++)
        if (pieces[i].getCode() == code)
            return pieces[i];
    throw new std::exception("No such piece");
}
/*int PieceInitter::getPieceCount() const
{
    return pieceCount;
}*/
#pragma endregion