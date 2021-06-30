#include "GUI.h"
GUI::GUI() 
{
	font.loadFromFile(fontFile);
}
GUI::GUI(std::string gameName, Vector2f offset) : GUI()
{
	this->offset = offset;
	if (gameName == "Tetris") 
	{
		setupGame("C:\\Users\\Lord\\source\\repos\\Elementary Games\\Tetris\\Data\\TetrisGUI.xml");
		getElement("gameOver").draw = false;
		getElement("yesB").draw = false;
		getElement("noB").draw = false;
	}
}
GUI::~GUI() 
{

}

void GUI::setupGame(std::string path) 
{
	TiXmlDocument xmlData(path);
	if (xmlData.LoadFile()) 
	{
		TiXmlElement* tCheck = xmlData.FirstChildElement();
		if (tCheck)
		{
			for (auto el = tCheck->FirstChildElement(); el != nullptr; el = el->NextSiblingElement()) 
			{
				if (strcmp(el->Value(), "FramedPiece") == 0) 
				{
					Vector2f elPos;
					std::string elName;

					if (el->Attribute("startOffset.x"))
						elPos.x = std::stof(el->Attribute("startOffset.x"));
					if(el->Attribute("startOffset.y"))
						elPos.y = std::stof(el->Attribute("startOffset.y"));
					if(el->Attribute("name"))
						elName = el->Attribute("name");

					FramedPiece *guiEl = new FramedPiece(offset + elPos);
					Push(Element(elName, *guiEl));
				}
				else if (strcmp(el->Value(), "Text") == 0) 
				{
					Vector2f elPos;
					std::string elName = "";
					std::string elTxt;
					int elCSize = 30;
					
					if (el->Attribute("startOffset.x"))
						elPos.x = std::stof(el->Attribute("startOffset.x"));
					if (el->Attribute("startOffset.y"))
						elPos.y = std::stof(el->Attribute("startOffset.y"));
					if (el->Attribute("name"))
						elName = el->Attribute("name");
					if (el->Attribute("charSize"))
						el->Attribute("charSize", &elCSize);
					if (el->GetText())
						elTxt = el->GetText();

					for (int start = elTxt.find("\\n", 0); start != std::string::npos; start = elTxt.find("\\n", start))
						elTxt.replace(start++, std::string("\\n").length(), "\n");

					Text* guiEl = new Text(elTxt, font, elCSize);
					guiEl->setPosition(elPos + offset);
					Push(Element(elName, *guiEl));
				}
				else if (strcmp(el->Value(), "Button") == 0)
				{
					Vector2f elPos;
					Vector2f elSize;
					std::string elName;
					std::string elTxt = "";
					int elCSize = 30;

					if (el->Attribute("startOffset.x"))
						elPos.x = std::stof(el->Attribute("startOffset.x"));
					if (el->Attribute("startOffset.y"))
						elPos.y = std::stof(el->Attribute("startOffset.y"));
					if (el->Attribute("size.x"))
						elSize.x = std::stof(el->Attribute("size.x"));
					if (el->Attribute("size.y"))
						elSize.y = std::stof(el->Attribute("size.y"));
					if (el->Attribute("name"))
						elName = el->Attribute("name");
					if (el->Attribute("charSize"))
						el->Attribute("charSize", &elCSize);
					if (el->GetText())
						elTxt = el->GetText();

					for (int start = elTxt.find("\\n", 0); start != std::string::npos; start = elTxt.find("\\n", start))
						elTxt.replace(start++, std::string("\\n").length(), "\n");

					Button* guiEl = new Button(offset + elPos, elSize, elTxt, font, elCSize);
					Push(Element(elName, *guiEl));
				}
			}
		}
	}
}
void GUI::Push(const Element& el) 
{
	elements.push_back(Element(el));
}
void GUI::Remove(std::string& name) 
{
	for (auto i = elements.begin(); i != elements.end(); i++)
		if (i->name == name)
			elements.remove(*i);
}
GUI::Element& GUI::getElement(const std::string& name)
{
	for (auto i = elements.begin(); i != elements.end(); i++)
		if (i->name == name)
			return (*i);
}

void GUI::draw(RenderTarget& target, RenderStates states) const 
{
	for (auto i = elements.begin(); i != elements.end(); i++)
		if((*i).draw)
			target.draw((*i).element);
}