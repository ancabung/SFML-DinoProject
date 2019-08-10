#include "Obstacles.h"

Obstacles::Obstacles(const sf::Vector2f& pos)
	:
	pos(pos)
{
	texture.loadFromFile("shuriken2.png");
	shuriken.setTexture(texture);

	//Scale sprite
	shuriken.setOrigin(sf::Vector2f(12, 12));
	shuriken.setScale(sf::Vector2f(1.f, 1.f)); // absolute scale factor
	shuriken.scale(sf::Vector2f(2.f, 2.f)); // factor relative to the current scale
}
void Obstacles::Draw(sf::RenderTarget& rt) const
{
	rt.draw(shuriken);
}
void Obstacles::SetDirection(sf::Vector2f& dir) {
	vel = dir * speed;
}
void Obstacles::SetPosition(sf::Vector2f newPos) {
	shuriken.setPosition(newPos);
}
void Obstacles::Update(float dt) {
	pos += vel * dt;
	shuriken.rotate(1.5f);
	shuriken.setPosition(pos);
}
float Obstacles::getY() {
	return shuriken.getPosition().y;
}
float Obstacles::getX() {
	return shuriken.getPosition().x;
}