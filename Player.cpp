#include "Player.h"

Player::Player(const sf::Vector2f& pos)
	:
	pos(pos)
{
	//Set sprite at specific position
	sprite.setTextureRect({ 0,0,24,24 });
	animation[int(AnimationIndex::StandingLeft)] = Animation(24 * 4, 0, -24, 24);
	animation[int(AnimationIndex::StandingRight)] = Animation(0, 0, 24, 24);
	animation[int(AnimationIndex::WalkingUp)] = Animation(24 * 3, 0, 24, 24);
	animation[int(AnimationIndex::WalkingDown)] = Animation(24 * 3, 0, 24, 24);
	animation[int(AnimationIndex::WalkingLeft)] = Animation(24 * 7, 0, -24, 24);
	animation[int(AnimationIndex::WalkingRight)] = Animation(24 * 3, 0, 24, 24);
	animation[int(AnimationIndex::SprintRight)] = Animation(24 * 18, 0, 24, 24);
	animation[int(AnimationIndex::SprintLeft)] = Animation(24 * 22, 0, -24, 24);
	animation[int(AnimationIndex::SprintUp)] = Animation(24 * 18, 0, 24, 24);
	animation[int(AnimationIndex::SprintDown)] = Animation(24 * 22, 0, -24, 24);
	//Scale sprite
	sprite.setScale(sf::Vector2f(1.f, 1.f)); // absolute scale factor
	sprite.scale(sf::Vector2f(4.f, 4.f)); // factor relative to the current scale
}
void Player::Draw(sf::RenderTarget& rt) const
{
	rt.draw(sprite);
}
void Player::SetDirection(const sf::Vector2f& dir)
{
	vel = dir * speed;
	//Swiching between animations
	if (dir.x > 0.0f && dir.x < 3.0f)
	{
		state = AnimationIndex::breakRight;
		curAnimation = AnimationIndex::WalkingRight;
	}
	else if (dir.x < 0.0f && dir.x > -3.0f)
	{
		state = AnimationIndex::breakLeft;
		curAnimation = AnimationIndex::WalkingLeft;

	}
	else if (dir.y < 0.0f)
	{
		curAnimation = AnimationIndex::WalkingUp;

	}
	else if (dir.y > 0.0f)
	{
		curAnimation = AnimationIndex::WalkingDown;
	}
	else if (dir.x > 3.0f)
	{
		curAnimation = AnimationIndex::SprintRight;
	}
	else if (dir.x < -3.0f)
	{
		curAnimation = AnimationIndex::SprintLeft;
	}
	else if (dir.y > 3.0f)
	{
		curAnimation = AnimationIndex::SprintUp;
	}
	else if (dir.y < -3.0f)
	{
		curAnimation = AnimationIndex::SprintDown;
	}
	else if (dir.x == 0 && dir.y == 0)
	{
		if (state == AnimationIndex::breakRight)
			curAnimation = AnimationIndex::StandingRight;
		else curAnimation = AnimationIndex::StandingLeft;
	}
}
void Player::SetPosition(sf::Vector2f newPos) {
	sprite.setPosition(newPos);
}
void Player::Update(float dt) {
	pos += vel * dt;
	animation[int(curAnimation)].Update(dt);
	animation[int(curAnimation)].ApplyToSprite(sprite);
	sprite.setPosition(pos);
}
float Player::getY() {
	return sprite.getPosition().y;
}
float Player::getX() {
	return sprite.getPosition().x;
}