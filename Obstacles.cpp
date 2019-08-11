#include "Obstacles.h"

Obstacles::Obstacles(const sf::Vector2f& pos, int& a)
	:
	pos(pos)
{
	switch (a){
	case 1:
	{	texture.loadFromFile("shuriken2.png");
	shuriken.setTexture(texture);
	break;
	}
	case 2:
	{
		texture.loadFromFile("ufo.png");
		shuriken.setTexture(texture);
		break;
	}
}
	//Scale sprite
	shuriken.setOrigin(sf::Vector2f(12, 12));
	shuriken.setScale(sf::Vector2f(1.f, 1.f)); // absolute scale factor
	shuriken.scale(sf::Vector2f(3.f, 3.f)); // factor relative to the current scale
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
void Obstacles::Update(float dt, int& a) {
	
	switch (a) {
	case 1: {
		pos += vel * dt;
		shuriken.rotate(1.5f);
		shuriken.setPosition(pos);
		break;
	}
	case 2: {
		pos +=  vel * dt * 1.65f ;
		shuriken.setPosition(pos);
		break;
	}
	}
}
float Obstacles::getY() {
	return shuriken.getPosition().y;
}
float Obstacles::getX() {
	return shuriken.getPosition().x;
}

sf::FloatRect Obstacles::getGlobalBounds() {
	return shuriken.getGlobalBounds();
}