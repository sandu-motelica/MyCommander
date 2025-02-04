#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
class Button {
public:
	Button() {   }

	Button(std::string t, Vector2f size, int charSize, Color bgColor, Color textColor )
	{
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
	void setPosition(Vector2f pos) {
		button.setPosition(pos);
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
