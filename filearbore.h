#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "folders.h"
using namespace sf;
using namespace std;
class fileButtonArbore {
public:
    string textBtn;
    int xPos = 0;
    int yPos = 0;
    string extensionName;

	fileButtonArbore(string t, Vector2f size, int charSize, Color bgColor, Color textColor,int x, int y, string extensionP)
	{
	    //cout << t << " " << x << " " << y << endl;
	    extensionName = extensionP;
	    xPos = x;
	    yPos = y;
	    textBtn= t ;
		text.setString(t);
		text.setFillColor(textColor);
		text.setCharacterSize(charSize);

		button.setSize(size);
		button.setFillColor(bgColor);

	}
	void setFont(Font& font) {
		text.setFont(font);
	}
	void setBackColor(Color color) {
		button.setFillColor(color);
	}
	void setTextColor(Color color) {
		text.setFillColor(color);
	}
	void setPosition(Vector2f pos, int &x, int &y, int i) {
		x = pos.x; y = pos.y+i*20;
		button.setPosition(x,y);
			float xPos = button.getSize().x / 2.0;
			float yPos = button.getSize().y / 2.0;
			text.setOrigin({ xPos,yPos });
			xPos += pos.x;
			yPos += pos.y;
		if(extensionName == "folder")
		text.setPosition(xPos+35,yPos+i*20);
		else
            text.setPosition(xPos+20,yPos+i*20);

	}
	void drawTo(RenderWindow &window, float x, float y) {
		Texture texturefile;
		Texture texturearbore;
		texturearbore.loadFromFile("images/arbore.png");
		if(extensionName == "folder") texturefile.loadFromFile("images/folder1.png");
		else if(extensionName == "rar" || extensionName == "zip") texturefile.loadFromFile("images/rar.png");
		else if(extensionName == "dll") texturefile.loadFromFile("images/dll.png");
		else if(extensionName == "jpg" || extensionName == "jpeg" || extensionName == "png" || extensionName == "gif") texturefile.loadFromFile("images/image.png");
		else if(extensionName == "mp4" || extensionName == "mkv" || extensionName == "avi" || extensionName == "mov") texturefile.loadFromFile("images/video.png");
		else if(extensionName == "m4a" || extensionName == "mp3" || extensionName == "ape") texturefile.loadFromFile("images/audio.png");
        else if(extensionName == "txt" || extensionName == "tag" ) texturefile.loadFromFile("images/txt.png");
		else texturefile.loadFromFile("images/all.png");
		Sprite file(texturefile);
		Sprite arbore(texturearbore);
		if(extensionName == "folder"){
		file.setPosition(x+12,y);
		arbore.setPosition(x,y);
		window.draw(button);
		window.draw(arbore);
		}
		else{
        file.setPosition(x,y);
		window.draw(button);}
		window.draw(text);
		window.draw(file);
	}
	bool isMouseOver(RenderWindow &window) {
		float mouseX = Mouse::getPosition(window).x;
		float mouseY = Mouse::getPosition(window).y;

		/*float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;

		float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
		float btnxPosHeight = button.getPosition().y + button.getLocalBounds().height;
*/
        float btnPosX = xPos;
		float btnPosY = yPos;

		float btnxPosWidth = xPos + button.getLocalBounds().width;
		float btnxPosHeight = yPos + button.getLocalBounds().height;
		if (mouseX<btnxPosWidth && mouseX>btnPosX && mouseY<btnxPosHeight && mouseY>btnPosY) {
			return true;
		}
		return false;
	}


private:
	RectangleShape button;
	Text text;
};
