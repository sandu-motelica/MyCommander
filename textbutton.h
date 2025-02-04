#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
class textButton {
public:


	textButton(std::string t, Vector2f pos_text, int charSize, Color bgColor, Color textColor, Vector2f size)
	{
		text.setString(t);
		text.setFillColor(textColor);
		text.setCharacterSize(charSize);
		text.setPosition(pos_text);

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
	void setOutlineThickness(int i) {
		button.setOutlineThickness(1);
	}
	void setOutlineColor(Color color) {
		button.setOutlineColor(color);
	}
	void setPosition(Vector2f pos) {
		button.setPosition(pos);
		/*float xPos = button.getSize().x/2.0 ;
		float yPos = button.getSize().y/2.0 ;
		text.setOrigin({ xPos,yPos });
		xPos = xPos + pos.x;
		yPos = yPos + pos.y;
		text.setPosition(xPos,yPos );*/
	}
	void drawTo(RenderWindow& window) {
		window.draw(button);
		window.draw(text);
	}
	bool isMouseOver(RenderWindow& window) {
		float mouseX = Mouse::getPosition(window).x;
		float mouseY = Mouse::getPosition(window).y;

		float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;

		float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
		float btnxPosHeight = button.getPosition().y + button.getLocalBounds().height;

		if (mouseX<btnxPosWidth && mouseX>btnPosX && mouseY<btnxPosHeight && mouseY>btnPosY) {
			return true;
		}
		return false;
	}


private:
	RectangleShape button;
	Text text;
};
