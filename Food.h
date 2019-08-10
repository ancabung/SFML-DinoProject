#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
class Food {
public:
	Food(sf::Vector2f size) {
		texture.loadFromFile("food.png");
		food.setTexture(texture);
		//Scale sprite
		food.setOrigin(sf::Vector2f(12, 12));
		food.setScale(sf::Vector2f(1.f, 1.f)); // absolute scale factor
		food.scale(sf::Vector2f(3.f, 3.f)); // factor relative to the current scale
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(food);
	}

	sf::FloatRect getGlobalBounds() {
		return food.getGlobalBounds();
	}

	void setPos(sf::Vector2f newPos) {
		food.setPosition(newPos);
	}
private:
	sf::Texture texture;
	sf::Sprite food;
};

