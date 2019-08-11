#pragma once
#include <SFML/Graphics.hpp>
class Obstacles
{
public:
	Obstacles(const sf::Vector2f& pos, int& a);
	void Draw(sf::RenderTarget& rt) const;
	void SetDirection(sf::Vector2f& dir);
	void SetPosition(sf::Vector2f newPos);
	void Update(float dt, int& a);
	float getY();
	float getX();
	sf::FloatRect getGlobalBounds();
private:
	static constexpr float speed = 505.0f;
	sf::Vector2f pos;
	sf::Vector2f vel = { 0.0f,0.0f };
	sf::Texture texture;
	sf::Sprite shuriken;
};

